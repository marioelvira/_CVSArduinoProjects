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
#define EEPROM_ADD_OK                0x00

#define EEPROM_ADD_MODBUS_ID         0x01
#define EEPROM_ADD_LOGIC_INS         0x02
#define EEPROM_ADD_LOGIC_OUTS        0x03
#define EEPROM_ADD_NTIME_SECS_LO     0x04
#define EEPROM_ADD_NTIME_SECS_HI     0x05

#define EEPROM_ADD_ADC_EMON_R_LO     0x06
#define EEPROM_ADD_ADC_EMON_R_HI     0x07
#define EEPROM_ADD_ADC_EMON_S_LO     0x80
#define EEPROM_ADD_ADC_EMON_S_HI     0x09
#define EEPROM_ADD_ADC_EMON_O_LO     0x0A
#define EEPROM_ADD_ADC_EMON_O_HI     0x0B
#define EEPROM_ADD_ADC_EMON_L_LO     0x0C
#define EEPROM_ADD_ADC_EMON_L_HI     0x0D
#define EEPROM_ADD_ADC_EMON_SEC_LO   0x0E
#define EEPROM_ADD_ADC_EMON_SEC_HI   0x0F

#define EEPROM_ADD_ADC_VDC_M_LO      0x10
#define EEPROM_ADD_ADC_VDC_M_HI      0x11
#define EEPROM_ADD_ADC_VDC_B_LO      0x12
#define EEPROM_ADD_ADC_VDC_B_HI      0x13

#define EEPROM_ADD_ADC_VDC_L1_LO     0x14
#define EEPROM_ADD_ADC_VDC_L1_HI     0x15
#define EEPROM_ADD_ADC_VDC_L2_LO     0x16
#define EEPROM_ADD_ADC_VDC_L2_HI     0x17
#define EEPROM_ADD_ADC_VDC_SEC_LO    0x18
#define EEPROM_ADD_ADC_VDC_SEC_HI    0x19

//#define EEPROM_ADD_MAX             0xFA // 250

// Values
#define EEPROM_VAL_OK                 0xAE
  
#define EEPROM_VAL_MODBUS_ID          0x01
#define EEPROM_VAL_LOGIC_INS          1
#define EEPROM_VAL_LOGIC_OUTS         1
#define EEPROM_VAL_NTIME_SECS         3600

#define EEPROM_VAL_ADC_EMON_R         5      // 5A -> 1V
#define EEPROM_VAL_ADC_EMON_S         1480   // Samples
#define EEPROM_VAL_ADC_EMON_O         -200   // Offset mA
#define EEPROM_VAL_ADC_EMON_L         2170   // 2170 mA -> 500W
#define EEPROM_VAL_ADC_EMON_SEC       600    // 10 min

#define EEPROM_VAL_ADC_VDC_M          2900   // 29V
#define EEPROM_VAL_ADC_VDC_B          0
#define EEPROM_VAL_ADC_VDC_L1         123   // 12,3V
#define EEPROM_VAL_ADC_VDC_L2         140   // 14V
#define EEPROM_VAL_ADC_VDC_SEC        10     // 10 sec

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
