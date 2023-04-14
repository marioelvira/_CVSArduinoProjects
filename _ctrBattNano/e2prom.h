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
#define EEPROM_ADD_LOGIC_INS      0x02
#define EEPROM_ADD_LOGIC_OUTS     0x03

#define EEPROM_ADD_ADC            0x04
#define EEPROM_ADD_ADC_M_LO       EEPROM_ADD_ADC    
#define EEPROM_ADD_ADC_M_HI       EEPROM_ADD_ADC + 1
#define EEPROM_ADD_ADC_B_LO       EEPROM_ADD_ADC + 2
#define EEPROM_ADD_ADC_B_HI       EEPROM_ADD_ADC + 3
#define EEPROM_ADD_ADC_S          EEPROM_ADD_ADC + 4
#define EEPROM_ADD_ADC_TRIG       EEPROM_ADD_ADC + 5

//#define EEPROM_ADD_MAX          0xFA // 250

// Values
#define EEPROM_VAL_OK             0xAA

//#define EEPROM_VAL_RESERVA      
#define EEPROM_VAL_MODBUS_ID      0x01
#define EEPROM_VAL_LOGIC_INS      1
#define EEPROM_VAL_LOGIC_OUTS     1

#define EEPROM_VAL_ADC_M          250   // 25V
#define EEPROM_VAL_ADC_B          0
#define EEPROM_VAL_ADC_S          0     // +/-  1/0
#define EEPROM_VAL_ADC_T          120   // 12V

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
