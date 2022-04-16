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

#define EEPROM_ADD_MODBUS_ID      0x01
#define EEPROM_ADD_ADCF           0x02

//#define EEPROM_ADD_MAX          0xFA // 250

// Values
#define EEPROM_VAL_OK             0xA0

//#define EEPROM_VAL_RESERVA      
#define EEPROM_VAL_MODBUS_ID      0x01
#define EEPROM_VAL_ADCF           0x00

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
