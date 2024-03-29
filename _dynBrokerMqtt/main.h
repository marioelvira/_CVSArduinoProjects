#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MAIN_H_
#define _MAIN_H_

// Libs
// C:\Users\mario.elvira\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4

//////////
// DDNS //
//////////
#define _SDPELICANOS_DDNS_         1
#define _AHICLAVIJO_DDNS_          0

#define _ARCH_                     1
#define _ARCH_ESP8266_             1
#define _ARCH_ESP01_               2
#define _ARCH_ESP01S_              3

///////////
// Debug //
///////////
#define _SERIAL_DEBUG_             0

#define _USE_LED_INDICATOR_        1
#define _USE_WDE_                  1

#define SMQTT_LOGD                 1 // Log MQTT

#if (_SERIAL_DEBUG_ == 1)

#define _PULS_SERIAL_DEBUG_        1
#define _EEPROM_SERIAL_DEBUG_      1
#define _HTTP_SERIAL_DEBUG_        1
#define _WIFI_SERIAL_DEBUG_        1
#define _STATUS_SERIAL_DEBUG_      1
#define _BROKER_SERIAL_DEBUG_      1
#define _DYNDNS_SERIAL_DEBUG_      1
#define _FREERAM_SERIAL_DEBUG_     1

#else

#define _PULS_SERIAL_DEBUG_        0
#define _EEPROM_SERIAL_DEBUG_      0
#define _HTTP_SERIAL_DEBUG_        0
#define _WIFI_SERIAL_DEBUG_        0
#define _STATUS_SERIAL_DEBUG_      0
#define _MQTT_SERIAL_DEBUG_        0

#endif

#endif // _MAIN_H_

#ifdef __cplusplus
} // extern "C"
#endif
