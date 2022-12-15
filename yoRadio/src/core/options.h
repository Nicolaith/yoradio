#ifndef options_h
#define options_h

#define YOVERSION "0.8.800"

/*******************************************************
DO NOT EDIT THIS FILE. 
ALL YOUR SETTINGS WILL BE OVERWRITTEN DURING THE UPDATE.
STORE YOUR SETTINGS IN THE *** myoptions.h *** FILE.
********************************************************/

#if __has_include("../../myoptions.h")
  #include "../../myoptions.h"        /* <- write your variable values here */
#endif
#if __has_include("../../mytheme.h")
  #include "../../mytheme.h"            /* <- Theme file */
#endif

/*******************************************************

The connection tables are located here https://github.com/e2002/yoradio#connection-tables
   
********************************************************/

#define DSP_DUMMY       0     // without display
#define DSP_ST7735      1     // 160x128  1.8'  or 128x128  1.44'  or 160x80   0.96'  https://aliexpress.com/item/1005002822797745.html
#define DSP_SSD1306     2     // 128x64   0.96' https://aliexpress.com/item/1005001621806398.html
#define DSP_NOKIA5110   3     // 84x48    1.6'  https://aliexpress.com/item/1005001621837569.html
#define DSP_ST7789      4     // 320x240  2.4'  https://aliexpress.com/item/32960241206.html 
#define DSP_SH1106      5     // 128x64   1.3'  https://aliexpress.com/item/32683094040.html
#define DSP_1602I2C     6     // 16x2           https://aliexpress.com/item/32305776560.html
#define DSP_SSD1306x32  7     // 128x32   0.91' https://aliexpress.com/item/32798439084.html
#define DSP_SSD1327     8     // 128x128  1.5'  https://aliexpress.com/item/1005001414175498.html
#define DSP_ILI9341     9     // 320x240  3.2'  https://aliexpress.com/item/33048191074.html
#define DSP_SSD1305     10    // 128x64   2.4'  SSD1305 and SSD1309 SPI https://aliexpress.com/item/32950307344.html
#define DSP_SH1107      11    // 128x64   1.3'  https://aliexpress.com/item/4000551696674.html
#define DSP_1602        12    // 16x2           https://aliexpress.com/item/32685016568.html
#define DSP_GC9106      13    // 160x80   0.96' (looks like ST7735S, but it's not him) https://aliexpress.com/item/32947890530.html
#define DSP_2004I2C     14    // 20x4           https://aliexpress.com/item/32783128355.html
#define DSP_2004        15    // 20x4           https://aliexpress.com/item/32783128355.html
#define DSP_SSD1305I2C  16    // 128x64   2.4'  SSD1305 and SSD1309 I2C https://aliexpress.com/item/32950307344.html
#define DSP_ILI9225     17    // 220x176  2.0'  https://aliexpress.com/item/32952021835.html
#define DSP_ST7789_240  18    // 240x240  1.3'  https://aliexpress.com/item/32996979276.html
/* !!! DSP_ST7789_240 requires further development when used in conjunction with the VS1053 module !!! See the link https://www.instructables.com/Adding-CS-Pin-to-13-LCD/ */
#define DSP_ST7796      19    // 480x320  3.5'  https://aliexpress.com/item/1005004632953455.html?sku_id=12000029911293172
#define DSP_GC9A01A     20    // 240x240  1.28' https://aliexpress.com/item/1005004069703494.html?sku_id=12000029869654615
#define DSP_CUSTOM      101   // your display

#ifndef DSP_MODEL
  #define DSP_MODEL  DSP_DUMMY
#endif
#ifndef DSP_HSPI
  #define DSP_HSPI   false      // use HSPI for displays (miso=12, mosi=13, clk=14) instead of VSPI (by default)
#endif
#ifndef LED_INVERT
  #define LED_INVERT   false      // invert onboard LED?
#endif

/*        TFT DISPLAY             */
#ifndef TFT_CS
  #define TFT_CS        255
#endif
#ifndef TFT_RST
  #define TFT_RST       15   // Or set to -1 and connect to Esp EN pin
#endif
#ifndef TFT_DC
  #define TFT_DC        4
#endif

/*        NEXTION                 */
#ifndef NEXTION_RX
  #define NEXTION_RX    255
#endif
#ifndef NEXTION_TX
  #define NEXTION_TX    255
#endif

/*        OLED I2C DISPLAY        */
#ifndef I2C_SDA
  #define I2C_SDA 21
#endif
#ifndef I2C_SCL
  #define I2C_SCL 22
#endif
#ifndef I2C_RST
  #define I2C_RST -1
#endif

/*        VS1053                  */
#ifndef VS1053_CS
  #define VS1053_CS     255 // 27
#endif
#ifndef VS1053_DCS
  #define VS1053_DCS    25
#endif
#ifndef VS1053_DREQ
  #define VS1053_DREQ   26
#endif
#ifndef VS1053_RST
  #define VS1053_RST    -1    // set to -1 if connected to Esp EN pin
#endif
#ifndef VS_HSPI
  #define VS_HSPI   false      // use HSPI for VS1053 (miso=12, mosi=13, clk=14) instead of VSPI (by default)
#endif

/*        I2S DAC                 */
#ifndef I2S_DOUT
  #define I2S_DOUT      27  // DIN connection
#endif
#ifndef I2S_BCLK
  #define I2S_BCLK      26  // BCLK Bit clock
#endif
#ifndef I2S_LRC
  #define I2S_LRC       25  // WSEL Left Right Clock
#endif

/*        SDCARD                  */
#ifndef SDC_SPI
  #define SDC_SPI       18, 19, 23  // SDCARD SPI pins (SCK, MISO, MOSI)
#endif
#ifndef SDC_CS
  #define SDC_CS        255  // SDCARD CS pin
#endif

/*        ENCODER                 */
#ifndef ENC_BTNL
  #define ENC_BTNL              255
#endif
#ifndef ENC_BTNB
  #define ENC_BTNB              255
#endif
#ifndef ENC_BTNR
  #define ENC_BTNR              255
#endif
#ifndef ENC_INTERNALPULLUP                // Thanks for Buska1968. See this topic: https://4pda.to/forum/index.php?s=&showtopic=1010378&view=findpost&p=113385448
  #define ENC_INTERNALPULLUP    true
#endif
#ifndef ENC_HALFQUARD
  #define ENC_HALFQUARD         false
#endif

#ifndef ENC2_BTNL
  #define ENC2_BTNL              255
#endif
#ifndef ENC2_BTNB
  #define ENC2_BTNB              255
#endif
#ifndef ENC2_BTNR
  #define ENC2_BTNR              255
#endif
#ifndef ENC2_INTERNALPULLUP
  #define ENC2_INTERNALPULLUP    true
#endif
#ifndef ENC2_HALFQUARD
  #define ENC2_HALFQUARD         false
#endif

/*        BUTTONS                 */
#ifndef BTN_LEFT
  #define BTN_LEFT              255
#endif
#ifndef BTN_CENTER
  #define BTN_CENTER            255
#endif
#ifndef BTN_RIGHT
  #define BTN_RIGHT             255
#endif
#ifndef BTN_UP
  #define BTN_UP            255
#endif
#ifndef BTN_DOWN
  #define BTN_DOWN             255
#endif
#ifndef BTN_MODE
  #define BTN_MODE             255
#endif
#ifndef BTN_INTERNALPULLUP
  #define BTN_INTERNALPULLUP    true
#endif
#ifndef BTN_LONGPRESS_LOOP_DELAY
  #define BTN_LONGPRESS_LOOP_DELAY    200   // delay between calling DuringLongPress event
#endif
#ifndef BTN_CLICK_TICKS
  #define BTN_CLICK_TICKS    300
#endif
#ifndef BTN_PRESS_TICKS
  #define BTN_PRESS_TICKS    500
#endif

/*        TOUCH SCREEN            */
#define TS_MODEL_UNDEFINED      0
#define TS_MODEL_XPT2046        1
#define TS_MODEL_GT911          2

#ifndef TS_MODEL
  #define TS_MODEL              TS_MODEL_UNDEFINED
#endif

#ifndef TS_CS
  #define TS_CS                 13
#endif
#ifndef TS_SDA
  #define TS_SDA                33
#endif
#ifndef TS_SCL
  #define TS_SCL                32
#endif
#ifndef TS_INT
  #define TS_INT                21
#endif
#ifndef TS_RST
  #define TS_RST                25
#endif

#ifndef TS_HSPI
  #define TS_HSPI   false      // use HSPI for touchscreen (miso=12, mosi=13, clk=14) instead of VSPI (by default)
#endif

/*        LCD DISPLAY            */
#ifndef LCD_RS
  #define LCD_RS                255
#endif
#ifndef LCD_E
  #define LCD_E                 255
#endif
#ifndef LCD_D4
  #define LCD_D4                255
#endif
#ifndef LCD_D5
  #define LCD_D5                255
#endif
#ifndef LCD_D6
  #define LCD_D6                255
#endif
#ifndef LCD_D7
  #define LCD_D7                255
#endif

/*        ESP DEVBOARD            */
#ifndef LED_BUILTIN
  #define LED_BUILTIN   255
#endif

/*        Other settings. You can overwrite them in the myoptions.h file        */
#ifndef MUTE_PIN
  #define MUTE_PIN      255   // MUTE Pin
#endif
#ifndef MUTE_VAL
  #define MUTE_VAL      HIGH  // Write this to MUTE_PIN when player is stopped
#endif
#ifndef BRIGHTNESS_PIN
  #define BRIGHTNESS_PIN 255   // BRIGHTNESS Pin
#endif
#ifndef PLAYER_FORCE_MONO
  #define PLAYER_FORCE_MONO      false  // mono option - false stereo, true mono
#endif
#ifndef I2S_INTERNAL
  #define I2S_INTERNAL      false  // If true - use esp32 internal DAC
#endif
#ifndef ROTATE_90
  #define ROTATE_90         false  // Optional 90 degree rotation for square displays
#endif
#ifndef WAKE_PIN
  #define WAKE_PIN      255   // Wake Pin (for manual wakeup from sleep mode. can match with BTN_XXXX, ENC_BTNB, ENC2_BTNB.  must be one of: 0,2,4,12,13,14,15,25,26,27,32,33,34,35,36,39)
#endif
#ifndef LIGHT_SENSOR
  #define LIGHT_SENSOR  255   // Light sensor
#endif
#ifndef AUTOBACKLIGHT
  #ifndef AUTOBACKLIGHT_MAX
    #define AUTOBACKLIGHT_MAX          2500
  #endif
  #ifndef AUTOBACKLIGHT_MIN
    #define AUTOBACKLIGHT_MIN          12
  #endif
  #define AUTOBACKLIGHT(x) ({uint16_t _lh=(x>AUTOBACKLIGHT_MAX?AUTOBACKLIGHT_MAX:x); map(_lh, AUTOBACKLIGHT_MAX, 0, AUTOBACKLIGHT_MIN, 100);})  // autobacklight function
#endif
#ifndef DSP_INVERT_TITLE
  #define DSP_INVERT_TITLE  true   // Invert title colors for OLED displays ?
#endif
/*
*** ST7735 display submodel ***
  INITR_BLACKTAB        // 1.8' https://aliexpress.ru/item/1005002822797745.html
      See this note If INITR_BLACKTAB have a noisy line on one side of the screen https://github.com/e2002/yoradio#note-if-initr_blacktab-dsp-have-a-noisy-line-on-one-side-of-the-screen-then-in-adafruit_st7735cpp
  INITR_144GREENTAB     // 1.44' https://aliexpress.ru/item/1005002822797745.html
  INITR_MINI160x80      // 0.96' 160x80 ST7735S   https://????
  INITR_GREENTAB
  INITR_REDTAB
 */
#ifndef DTYPE
  #define DTYPE INITR_BLACKTAB
#endif

/*        IR                      */
#ifndef IR_PIN
  #define IR_PIN                255
#endif
#ifndef IR_TIMEOUT
  #define IR_TIMEOUT            80        // kTimeout, see IRremoteESP8266 documentation
#endif

/*        THEMES                                 */
/*        color name               R    G    B   */
#ifndef COLOR_BACKGROUND
  #define COLOR_BACKGROUND          0,   0,   0
#endif
#ifndef COLOR_STATION_NAME
  #define COLOR_STATION_NAME        0,   0,   0
#endif
#ifndef COLOR_STATION_BG
  #define COLOR_STATION_BG        231, 211,  90
#endif
#ifndef COLOR_STATION_FILL
  #define COLOR_STATION_FILL      231, 211,  90
#endif
#ifndef COLOR_SNG_TITLE_1
  #define COLOR_SNG_TITLE_1       255, 255, 255
#endif
#ifndef COLOR_SNG_TITLE_2
  #define COLOR_SNG_TITLE_2       165, 162, 132
#endif
#ifndef COLOR_WEATHER
  #define COLOR_WEATHER           255, 150,   0
#endif
#ifndef COLOR_VU_MAX
  #define COLOR_VU_MAX            231, 211,  90
#endif
#ifndef COLOR_VU_MIN
  #define COLOR_VU_MIN            123, 125, 123
#endif
#ifndef COLOR_CLOCK
  #define COLOR_CLOCK             231, 211,  90
#endif
#ifndef COLOR_SECONDS
  #define COLOR_SECONDS           231, 211,  90
#endif
#ifndef COLOR_DAY_OF_W
  #define COLOR_DAY_OF_W          255, 255, 255
#endif
#ifndef COLOR_DATE
  #define COLOR_DATE              255, 255, 255
#endif
#ifndef COLOR_HEAP
  #define COLOR_HEAP               41,  40,  41
#endif
#ifndef COLOR_BUFFER
  #define COLOR_BUFFER            165, 162, 132
#endif
#ifndef COLOR_IP
  #define COLOR_IP                165, 162, 132
#endif
#ifndef COLOR_VOLUME_VALUE
  #define COLOR_VOLUME_VALUE      165, 162, 132
#endif
#ifndef COLOR_RSSI
  #define COLOR_RSSI              165, 162, 132
#endif
#ifndef COLOR_VOLBAR_OUT
  #define COLOR_VOLBAR_OUT        231, 211,  90
#endif
#ifndef COLOR_VOLBAR_IN
  #define COLOR_VOLBAR_IN         231, 211,  90
#endif
#ifndef COLOR_DIGITS
  #define COLOR_DIGITS            255, 255, 255
#endif
#ifndef COLOR_DIVIDER
  #define COLOR_DIVIDER           165, 162, 132
#endif
#ifndef COLOR_PL_CURRENT
  #define COLOR_PL_CURRENT          0,   0,   0
#endif
#ifndef COLOR_PL_CURRENT_BG
  #define COLOR_PL_CURRENT_BG     231, 211,  90
#endif
#ifndef COLOR_PL_CURRENT_FILL
  #define COLOR_PL_CURRENT_FILL   231, 211,  90
#endif
#ifndef COLOR_PLAYLIST_0
  #define COLOR_PLAYLIST_0        115, 115, 115
#endif
#ifndef COLOR_PLAYLIST_1
  #define COLOR_PLAYLIST_1         89,  89,  89
#endif
#ifndef COLOR_PLAYLIST_2
  #define COLOR_PLAYLIST_2         56,  56,  56
#endif
#ifndef COLOR_PLAYLIST_3
  #define COLOR_PLAYLIST_3         35,  35,  35
#endif
#ifndef COLOR_PLAYLIST_4
  #define COLOR_PLAYLIST_4         25,  25,  25
#endif
#ifndef COLOR_BITRATE
  #define COLOR_BITRATE           231, 211,  90
#endif

#define EN  1
#define RU  2
#ifndef L10N_LANGUAGE
  #define L10N_LANGUAGE EN
#endif



#endif
