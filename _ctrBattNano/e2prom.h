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
#define EEPROM_ADD_OK                 0x00

#define EEPROM_ADD_MODBUS_ID          0x01
#define EEPROM_ADD_LOGIC_INS          0x02
#define EEPROM_ADD_LOGIC_OUTS         0x03

#define EEPROM_ADD_ADC0_EMON_R_LO     0x04
#define EEPROM_ADD_ADC0_EMON_R_HI     0x05
#define EEPROM_ADD_ADC0_EMON_S_LO     0x06
#define EEPROM_ADD_ADC0_EMON_S_HI     0x07
#define EEPROM_ADD_ADC0_EMON_O_LO     0x08
#define EEPROM_ADD_ADC0_EMON_O_HI     0x09
#define EEPROM_ADD_ADC0_EMON_TS       0x0A
#define EEPROM_ADD_ADC0_EMON_T_LO     0x0B
#define EEPROM_ADD_ADC0_EMON_T_HI     0x0C

#define EEPROM_ADD_ADC1_M_LO          0x0D
#define EEPROM_ADD_ADC1_M_HI          0x0E
#define EEPROM_ADD_ADC1_B_LO          0x0F
#define EEPROM_ADD_ADC1_B_HI          0x20
#define EEPROM_ADD_ADC1_S             0x21
#define EEPROM_ADD_ADC1_TS            0x22
#define EEPROM_ADD_ADC1_T_LO          0x23
#define EEPROM_ADD_ADC1_T_HI          0x24

//#define EEPROM_ADD_MAX              0xFA // 250

// Values
#define EEPROM_VAL_OK                 0xAA

//#define EEPROM_VAL_RESERVA      
#define EEPROM_VAL_MODBUS_ID           0x01
#define EEPROM_VAL_LOGIC_INS           1
#define EEPROM_VAL_LOGIC_OUTS          1

#define EEPROM_VAL_ADC0_EMON_R         5      // 5A -> 1V
#define EEPROM_VAL_ADC0_EMON_S         1480   // Samples
#define EEPROM_VAL_ADC0_EMON_O         -200   // Offset mA
#define EEPROM_VAL_ADC0_EMON_TS        1      // 0->Down; 1->Up
#define EEPROM_VAL_ADC0_EMON_T         2000   // 2A

#define EEPROM_VAL_ADC1_M              290   // 29V
#define EEPROM_VAL_ADC1_B              0
#define EEPROM_VAL_ADC1_S              0     // +/-  1/0
#define EEPROM_VAL_ADC1_TS             1     // 0->Down; 1->Up
#define EEPROM_VAL_ADC1_T              120   // 12V

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
