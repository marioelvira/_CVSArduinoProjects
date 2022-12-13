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
#define EEPROM_ADD_ADCF0          0x02  // ADC_NUMBER
#define EEPROM_ADD_ADCF1          0x03
#define EEPROM_ADD_ADCF2          0x04
#define EEPROM_ADD_ADCF3          0x05

#define EEPROM_ADD_RPM            0x06
#define EEPROM_ADD_PRESS          0x07

//#define EEPROM_ADD_MAX          0xFA // 250

// Values
#define EEPROM_VAL_OK             0xA0

//#define EEPROM_VAL_RESERVA      
#define EEPROM_VAL_MODBUS_ID      0x01
#define EEPROM_VAL_ADCF0          0x00
#define EEPROM_VAL_ADCF1          0x00
#define EEPROM_VAL_ADCF2          0x00
#define EEPROM_VAL_ADCF3          0x00

#define EEPROM_VAL_RPM            100
#define EEPROM_VAL_PRESS          100

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
