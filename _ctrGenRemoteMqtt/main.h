#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MAIN_H_
#define _MAIN_H_

///////////
// Debug //
///////////
#define _SERIAL_DEBUG_             1
#define _MQTT_DEBUG_               1

#define _USE_LED_INDICATOR_        1

#if (_SERIAL_DEBUG_ == 1)

#define _PULS_SERIAL_DEBUG_        1
#define _EEPROM_SERIAL_DEBUG_      1
#define _HTTP_SERIAL_DEBUG_        1
#define _WIFI_SERIAL_DEBUG_        1
#define _STATUS_SERIAL_DEBUG_      1
#define _MQTT_SERIAL_DEBUG_        1
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
