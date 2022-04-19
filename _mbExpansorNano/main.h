#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MAIN_H_
#define _MAIN_H_

// Libs
// C:\Users\mario.elvira\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4

///////////
// Debug //
///////////

#define _USE_BOARDLED_             1
#define _USE_WDE_                  0
#define _USE_FREERAM_              0
#define _USE_MUART_                1

#if (_USE_MUART_ == 1)
#define _SERIAL_DEBUG_             0
#define _PULS_SERIAL_DEBUG_        0
#define _EEPROM_SERIAL_DEBUG_      0
#define _HTTP_SERIAL_DEBUG_        0
#define _WIFI_SERIAL_DEBUG_        0
#define _STATUS_SERIAL_DEBUG_      0
#else 
#define _SERIAL_DEBUG_             1
#define _PULS_SERIAL_DEBUG_        1
#define _EEPROM_SERIAL_DEBUG_      1
#define _HTTP_SERIAL_DEBUG_        1
#define _WIFI_SERIAL_DEBUG_        1
#define _STATUS_SERIAL_DEBUG_      1
#endif

#endif // _MAIN_H_

#ifdef __cplusplus
} // extern "C"
#endif
