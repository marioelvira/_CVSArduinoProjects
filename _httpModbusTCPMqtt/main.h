#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MAIN_H_
#define _MAIN_H_

//////////
// Libs //
//////////
// C:\Users\mario.elvira\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4
// D:\Datos\Documents\Arduino\libraries

///////////
// Board //
///////////
// Board: ESP8266 Boards -> Generic ESP8266 Module
#define ROOM_PINOUT     0	  // ESP01 - Hostal Room Board
#define ELIGHT_PINOUT   1	  // ESP01 - Only OUT Board
// Board: ESP8266 Boards -> NodeMCU 1.0 (ESP-12E Module)
#define LOLIN_PINOUT    0   // ESP8266 - LolinV3

#define PROJECT     "MBTCPMQTT+"

///////////
// Debug //
///////////
#define _SERIAL_DEBUG_             1
#define _MQTT_DEBUG_               0

#define _USE_LED_INDICATOR_        1
#define _USE_WDE_                  1

#define _EEPROM_SERIAL_DEBUG_      1
#define _HTTP_SERIAL_DEBUG_        1
#define _WIFI_SERIAL_DEBUG_        1
#define _STATUS_SERIAL_DEBUG_      1
#define _MQTT_SERIAL_DEBUG_        1
#define _NTP_SERIAL_DEBUG_         1
#define _FREERAM_SERIAL_DEBUG_     1

#endif // _MAIN_H_

#ifdef __cplusplus
} // extern "C"
#endif
