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

#define EEPROM_ADD_ADC0_M_LO      0x04
#define EEPROM_ADD_ADC0_M_HI      0x05
#define EEPROM_ADD_ADC0_B_LO      0x06
#define EEPROM_ADD_ADC0_B_HI      0x07
#define EEPROM_ADD_ADC0_S         0x08
#define EEPROM_ADD_ADC0_T_LO      0x09
#define EEPROM_ADD_ADC0_T_HI      0x0A

#define EEPROM_ADD_ADC1_M_LO      0x0B
#define EEPROM_ADD_ADC1_M_HI      0x0C
#define EEPROM_ADD_ADC1_B_LO      0x0D
#define EEPROM_ADD_ADC1_B_HI      0x0E
#define EEPROM_ADD_ADC1_S         0x0F
#define EEPROM_ADD_ADC1_T_LO      0x10
#define EEPROM_ADD_ADC1_T_HI      0x11

//#define EEPROM_ADD_MAX          0xFA // 250

// Values
#define EEPROM_VAL_OK             0xA0

//#define EEPROM_VAL_RESERVA      
#define EEPROM_VAL_MODBUS_ID      0x01
#define EEPROM_VAL_LOGIC_INS      1
#define EEPROM_VAL_LOGIC_OUTS     1

#define EEPROM_VAL_ADC0_M         5555  // 5555W
#define EEPROM_VAL_ADC0_B         0
#define EEPROM_VAL_ADC0_S         0     // +/-  1/0
#define EEPROM_VAL_ADC0_T         2000  // 2000w

#define EEPROM_VAL_ADC1_M         290   // 29V
#define EEPROM_VAL_ADC1_B         0
#define EEPROM_VAL_ADC1_S         0     // +/-  1/0
#define EEPROM_VAL_ADC1_T         120   // 12V



#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
