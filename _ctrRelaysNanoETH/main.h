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

#define _USE_LED_                  0  // Used as SPI
#define _USE_WDE_                  0  // TODO
#define _USE_FREERAM_              0
#define _USE_ETHERNET_             1

#if (_USE_ETHERNET_ == 1)
#define _USE_MBTCP_                1
#endif

#define _SERIAL_DEBUG_             1

#if (_SERIAL_DEBUG_ == 1)
#define _EEPROM_SERIAL_DEBUG_      1
#define _STATUS_SERIAL_DEBUG_      0
#define _ETH_SERIAL_DEBUG_         1
#define _MBTCP_SERIAL_DEBUG_       1
#endif

#endif // _MAIN_H_

#ifdef __cplusplus
} // extern "C"
#endif
