#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MAIN_H_
#define _MAIN_H_

// Libs
// C:\Users\mario.elvira\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4
// D:\Datos\Documents\Arduino\libraries

// Board: Arduino AVR Boards -> Arduino Nano
// Porcessor: ATMega328P (old Bootloader)

///////////
// Debug //
///////////

#define _USE_BOARDLED_             1
#define _USE_WDE_                  0
#define _USE_FREERAM_              0
#define _USE_RS485_                1
#define _USE_MB_                   1
#define _USE_LED_                  1

#if (_USE_RS485_ == 1)
#define _SERIAL_DEBUG_             0
#define _USE_RS485_RXTX_           1
#else
#define _SERIAL_DEBUG_             1
#define _USE_RS485_RXTX_           0
#endif

#if (_SERIAL_DEBUG_ == 1)
#define _PULS_SERIAL_DEBUG_        1
#define _EEPROM_SERIAL_DEBUG_      1
#define _STATUS_SERIAL_DEBUG_      0
#else 
#define _PULS_SERIAL_DEBUG_        0
#define _EEPROM_SERIAL_DEBUG_      0
#define _STATUS_SERIAL_DEBUG_      0
#endif

#endif // _MAIN_H_

#ifdef __cplusplus
} // extern "C"
#endif
