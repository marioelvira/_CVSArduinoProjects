#ifdef __cplusplus
extern "C" {
#endif

#ifndef _E2PROM_H_
#define _E2PROM_H_

#include "main.h"

#define _ERASE_EEPROM_        0
#define _READ_EEPROM_         0
#define _WRITE_SSID_EEPROM_   0

// Address
#define EEPROM_ADD_OK             0x00

#define EEPROM_ADD_1P_TIMER_GEN   0x01
#define EEPROM_ADD_2P_TIMER_GEN   0x02
#define EEPROM_ADD_3P_TIMER_GEN   0x03
#define EEPROM_ADD_4P_TIMER_GEN   0x04
#define EEPROM_ADD_5P_TIMER_GEN   0x05
#define EEPROM_ADD_6P_TIMER_GEN   0x06
#define EEPROM_ADD_7P_TIMER_GEN   0x07
#define EEPROM_ADD_8P_TIMER_GEN   0x08
#define EEPROM_ADD_9P_TIMER_GEN   0x09

#define EEPROM_ADD_BUZZER_ON      0x0A
#define EEPROM_ADD_TSTART         0x0B
#define EEPROM_ADD_TSTOP          0x0C
#define EEPROM_ADD_DEBUG          0x0D

//#define EEPROM_ADD_MAX          0xFA // 250

// Values
#define EEPROM_VAL_OK             0xA3

//#define EEPROM_VAL_RESERVA      

#define EEPROM_VAL_1P_TIMER_GEN   15  // Min
#define EEPROM_VAL_2P_TIMER_GEN   30  // Min
#define EEPROM_VAL_3P_TIMER_GEN   60  // Min
#define EEPROM_VAL_4P_TIMER_GEN   90  // Min
#define EEPROM_VAL_5P_TIMER_GEN   120 // Min
#define EEPROM_VAL_6P_TIMER_GEN   3   // Horas
#define EEPROM_VAL_7P_TIMER_GEN   4   // Horas
#define EEPROM_VAL_8P_TIMER_GEN   5   // Horas
#define EEPROM_VAL_9P_TIMER_GEN   7   // Horas

#define EEPROM_VAL_BUZZER_ON      10  // Secs
#define EEPROM_VAL_TSTART         10  // Secs
#define EEPROM_VAL_TSTOP          20  // Secs
#define EEPROM_VAL_DEBUG          0

/*
#define _DEBUG_TIME   1

#if (_DEBUG_TIME == 1)
  #define X_60    3
  #define X_3600  180
#else
  #define X_60    60
  #define X_3600  3600
#endif
*/

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
