import asyncio
import logging
import voluptuous as vol
import json
import urllib.request
from homeassistant.components import media_source
from homeassistant.helpers.aiohttp_client import async_get_clientsession
from homeassistant.helpers import config_validation as cv
from homeassistant.components.media_player.browse_media import async_process_play_media_url
from homeassistant.components.media_player import (
    MediaPlayerEntity,
    MediaPlayerEnqueue,
    BrowseMedia,
    PLATFORM_SCHEMA
)
from homeassistant.components.media_player.const import MediaPlayerEntityFeature
from homeassistant.const import (
    CONF_NAME,
    STATE_IDLE,
    STATE_PLAYING,
    STATE_OFF,
    STATE_ON
)
from homeassistant.components.mqtt import async_subscribe, async_publish

_LOGGER = logging.getLogger(__name__)

VERSION = '0.9.300'
DOMAIN = "yoradio"
DEFAULT_NAME = 'yoRadio'
CONF_MAX_VOLUME = 'max_volume'
CONF_ROOT_TOPIC = 'root_topic'

PLATFORM_SCHEMA = PLATFORM_SCHEMA.extend({
    vol.Required(CONF_ROOT_TOPIC, default="yoradio"): cv.string,
    vol.Optional(CONF_NAME, default=DEFAULT_NAME): cv.string,
    vol.Optional(CONF_MAX_VOLUME, default='254'): cv.string
})

async def async_setup_platform(hass, config, async_add_entities, discovery_info=None):
    if hass is None:
        _LOGGER.error("Home Assistant instance is not initialized")
        raise ValueError("Home Assistant instance is not initialized")
    root_topic = config[CONF_ROOT_TOPIC]
    name = config[CONF_NAME]
    max_volume = int(config[CONF_MAX_VOLUME])
    session = async_get_clientsession(hass)
    playlist = []
    api = YoRadioAPI(root_topic, session, hass, playlist)
    device = YoRadioDevice(name, max_volume, api)
    await device.initialize()
    async_add_entities([device])

def setup_platform(hass, config, add_devices, discovery_info=None):
    hass.async_create_task(async_setup_platform(hass, config, add_devices, discovery_info))

class YoRadioAPI:
    def __init__(self, root_topic, session, hass, playlist):
        self.session = session
        self.hass = hass
        self.root_topic = root_topic
        self.playlist = playlist
        self.playlist_url = ""

    async def initialize(self):
        if self.hass is None:
            _LOGGER.error("Home Assistant instance is not initialized")
            raise ValueError("Home Assistant instance is not initialized")

    async def set_command(self, command):
        try:
            await async_publish(self.hass, f'{self.root_topic}/command', command)
        except Exception as e:
            _LOGGER.error(f"Error publishing command: {e}")

    async def set_volume(self, volume):
        command = f"vol {volume}"
        await async_publish(self.hass, f'{self.root_topic}/command', command)

    def fetch_data(self):
        try:
            html = urllib.request.urlopen(self.playlist_url).read().decode("utf-8")
            return html
        except Exception as e:
            _LOGGER.error(f"Unable to fetch data: {e}")
            return ""

    async def set_source(self, source):
        number = source.split('.')[0]
        command = f"play {number}"
        await async_publish(self.hass, f'{self.root_topic}/command', command)

    async def set_browse_media(self, media_content_id):
        await async_publish(self.hass, f'{self.root_topic}/command', media_content_id)

    async def load_playlist(self, msg):
        try:
            self.playlist_url = msg.payload
            file_data = await self.hass.async_add_executor_job(self.fetch_data)
        except Exception as e:
            _LOGGER.error(f'Error downloading {msg.payload}: {e}')
        else:
            file_lines = file_data.split('\n')
            self.playlist.clear()
            for index, line in enumerate(file_lines, start=1):
                station_name = line.split('\t')[0]
                if station_name:
                    self.playlist.append(f'{index}. {station_name}')

class YoRadioDevice(MediaPlayerEntity):
    def __init__(self, name, max_volume, api):
        self._name = name
        self.api = api
        self._state = STATE_OFF
        self._current_source = None
        self._media_title = ''
        self._track_artist = ''
        self._track_album_name = ''
        self._volume = 0
        self._muted = False
        self._max_volume = max_volume
        self._subscriptions = []
        self._supported_features = (
            MediaPlayerEntityFeature.PAUSE
            | MediaPlayerEntityFeature.VOLUME_SET
            | MediaPlayerEntityFeature.PREVIOUS_TRACK
            | MediaPlayerEntityFeature.NEXT_TRACK
            | MediaPlayerEntityFeature.TURN_ON
            | MediaPlayerEntityFeature.TURN_OFF
            | MediaPlayerEntityFeature.PLAY_MEDIA
            | MediaPlayerEntityFeature.VOLUME_STEP
            | MediaPlayerEntityFeature.SELECT_SOURCE
            | MediaPlayerEntityFeature.STOP
            | MediaPlayerEntityFeature.PLAY
            | MediaPlayerEntityFeature.BROWSE_MEDIA
        )
        self._entity_picture = None

    async def initialize(self):
        if self.api.hass is None:
            _LOGGER.error("Home Assistant instance is not initialized in YoRadioAPI")
            raise ValueError("Home Assistant instance is not initialized in YoRadioAPI")
        self._subscriptions.extend([
            await async_subscribe(
                self.api.hass, f'{self.api.root_topic}/status',
                self.status_listener, 0, "utf-8"),
            await async_subscribe(
                self.api.hass, f'{self.api.root_topic}/playlist',
                self.playlist_listener, 0, "utf-8"),
            await async_subscribe(
                self.api.hass, f'{self.api.root_topic}/volume',
                self.volume_listener, 0, "utf-8")
        ])

    async def status_listener(self, msg):
        _LOGGER.debug(f"Received status message: {msg}")
        try:
            js = json.loads(msg.payload)
            self._media_title = js['title']
            self._track_artist = js['name']
            self._state = STATE_PLAYING if js['status'] == 1 else STATE_IDLE if js['on'] == 1 else STATE_OFF
            self._current_source = f"{js['station']}. {js['name']}"
            self.async_schedule_update_ha_state()
        except Exception as e:
            _LOGGER.error(f"Error handling status message: {e}")

    async def playlist_listener(self, msg):
        _LOGGER.debug(f"Received playlist message: {msg}")
        try:
            await self.api.load_playlist(msg)
            self.async_schedule_update_ha_state()
        except Exception as e:
            _LOGGER.error(f"Error handling playlist message: {e}")

    async def volume_listener(self, msg):
        _LOGGER.debug(f"Received volume message: {msg}")
        try:
            self._volume = int(msg.payload) / self._max_volume
            self.async_schedule_update_ha_state()
        except Exception as e:
            _LOGGER.error(f"Error handling volume message: {e}")

    @property
    def supported_features(self):
        return self._supported_features

    @property
    def name(self):
        return self._name

    @property
    def media_title(self):
        return self._media_title

    @property
    def media_artist(self):
        return self._track_artist

    @property
    def media_album_name(self):
        return self._track_album_name

    @property
    def state(self):
        return self._state

    @property
    def volume_level(self):
        return self._volume

    @property
    def source(self):
        return self._current_source

    @property
    def source_list(self):
        return self.api.playlist

    @property
    def entity_picture(self):
        return self._entity_picture

    async def async_update(self):
        self._entity_picture = "https://brands.home-assistant.io/yoradio/icon.png"

    async def async_set_volume_level(self, volume):
        await self.api.set_volume(round(volume * self._max_volume, 1))

    async def async_browse_media(self, media_content_type: str | None = None, media_content_id: str | None = None) -> BrowseMedia:
        return await media_source.async_browse_media(self.hass, media_content_id)

    async def async_play_media(self, media_type: str, media_id: str, enqueue: MediaPlayerEnqueue | None = None, announce: bool | None = None, **kwargs) -> None:
        if media_source.is_media_source_id(media_id):
            media_type = MEDIA_TYPE_URL
            play_item = await media_source.async_resolve_media(self.hass, media_id, self.entity_id)
            media_id = async_process_play_media_url(self.hass, play_item.url)
        await self.api.set_browse_media(media_id)

    async def async_select_source(self, source):
        await self.api.set_source(source)
        self._current_source = source

    async def async_volume_up(self):
        new_volume = self._volume + 0.05
        await self.async_set_volume_level(new_volume)
        self._volume = new_volume

    async def async_volume_down(self):
        new_volume = self._volume - 0.05
        await self.async_set_volume_level(new_volume)
        self._volume = new_volume

    async def async_media_next_track(self):
        await self.api.set_command("next")

    async def async_media_previous_track(self):
        await self.api.set_command("prev")

    async def async_media_stop(self):
        await self.api.set_command("stop")
        self._state = STATE_IDLE

    async def async_turn_on(self):
        await self.api.set_command("turnon")
        self._state = STATE_ON

    async def async_media_play(self):
        await self.api.set_command("start")
        self._state = STATE_PLAYING

    async def async_media_pause(self):
        await self.api.set_command("stop")
        self._state = STATE_IDLE

    async def async_turn_off(self):
        await self.api.set_command("turnoff")
        self._state = STATE_OFF
