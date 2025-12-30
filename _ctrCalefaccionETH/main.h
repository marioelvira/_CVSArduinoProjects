
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MAIN_H_
#define _MAIN_H_

// Libs
// C:\Users\mario.elvira\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4
// D:\Datos\Documents\Arduino\libraries

// Board: Arduino magaAVR Boards -> Arduino Nano Every

#define PROJECT     "CONTROL CALEF"
#define TECHNOLOGY  "Arduino Nano Every"

///////////
// Debug //
///////////

#define _USE_LED_                  0 // Used as SPI
#define _USE_WDE_                  0//1
#define _USE_ETHERNET_             1
#define _USE_RS485_                0
#define _USE_UID_                  1

#if (_USE_ETHERNET_ == 1)
#define _USE_HTTP_                 1
#define _USE_MQTT_                 0
#define _USE_NTP_                  0
#endif

#if (_USE_RS485_ == 1)
#define _SERIAL_DEBUG_             0
#define _USE_MBRTU_                1
#else
#define _SERIAL_DEBUG_             1
#endif

#if (_SERIAL_DEBUG_ == 1)
#define _EEPROM_SERIAL_DEBUG_      0
#define _STATUS_SERIAL_DEBUG_      0
#define _HTTP_SERIAL_DEBUG_        0
#define _ETH_SERIAL_DEBUG_         0
#define _MQTT_SERIAL_DEBUG_        1
#define _NTP_SERIAL_DEBUG_         0
#define _WD_SERIAL_DEBUG_          0
#endif

#endif // _MAIN_H_

#ifdef __cplusplus
} // extern "C"
#endif
