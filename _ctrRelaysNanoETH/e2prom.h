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
#define EEPROM_ADD_OK                  0x00

#define EEPROM_ADD_LOGIC_INS           0x01
#define EEPROM_ADD_LOGIC_OUTS          0x02
//#define EEPROM_ADD_RESERVED          0x03

#define EEPROM_ADD_C0ADC_TYPE          0x04
#define EEPROM_ADD_C0ADC_EMON_R_LO     0x05
#define EEPROM_ADD_C0ADC_EMON_R_HI     0x06
#define EEPROM_ADD_C0ADC_EMON_S_LO     0x07
#define EEPROM_ADD_C0ADC_EMON_S_HI     0x08
#define EEPROM_ADD_C0ADC_EMON_O_LO     0x09
#define EEPROM_ADD_C0ADC_EMON_O_HI     0x0A
#define EEPROM_ADD_C0ADC_IDC_M_LO      0x0B
#define EEPROM_ADD_C0ADC_IDC_M_HI      0x0C
#define EEPROM_ADD_C0ADC_IDC_B_LO      0x0D
#define EEPROM_ADD_C0ADC_IDC_B_HI      0x0E
#define EEPROM_ADD_C0ADC_EMON_L_LO     0x0F
#define EEPROM_ADD_C0ADC_EMON_L_HI     0x10
#define EEPROM_ADD_C0ADC_EMON_SEC_LO   0x11
#define EEPROM_ADD_C0ADC_EMON_SEC_HI   0x12

#define EEPROM_ADD_C1ADC_TYPE          0x13
#define EEPROM_ADD_C1ADC_EMON_R_LO     0x14
#define EEPROM_ADD_C1ADC_EMON_R_HI     0x15
#define EEPROM_ADD_C1ADC_EMON_S_LO     0x16
#define EEPROM_ADD_C1ADC_EMON_S_HI     0x17
#define EEPROM_ADD_C1ADC_EMON_O_LO     0x18
#define EEPROM_ADD_C1ADC_EMON_O_HI     0x19
#define EEPROM_ADD_C1ADC_IDC_M_LO      0x1A
#define EEPROM_ADD_C1ADC_IDC_M_HI      0x1B
#define EEPROM_ADD_C1ADC_IDC_B_LO      0x1C
#define EEPROM_ADD_C1ADC_IDC_B_HI      0x1D
#define EEPROM_ADD_C1ADC_EMON_L_LO     0x1E
#define EEPROM_ADD_C1ADC_EMON_L_HI     0x1F
#define EEPROM_ADD_C1ADC_EMON_SEC_LO   0x20
#define EEPROM_ADD_C1ADC_EMON_SEC_HI   0x21
#define EEPROM_ADD_V0ADC_VDC_M_LO      0x22
#define EEPROM_ADD_V0ADC_VDC_M_HI      0x23
#define EEPROM_ADD_V0ADC_VDC_B_LO      0x24
#define EEPROM_ADD_V0ADC_VDC_B_HI      0x25

#define EEPROM_ADD_V1ADC_VDC_M_LO      0x26
#define EEPROM_ADD_V1ADC_VDC_M_HI      0x27
#define EEPROM_ADD_V1ADC_VDC_B_LO      0x28
#define EEPROM_ADD_V1ADC_VDC_B_HI      0x29

//#define EEPROM_ADD_MAX               0xFA // 250

// Values
#define EEPROM_VAL_OK                   0xA0

#define EEPROM_VAL_LOGIC_INS            1
#define EEPROM_VAL_LOGIC_OUTS           1

#define EEPROM_VAL_C0ADC_TYPE           0      // 0->AC, 1->DC
#define EEPROM_VAL_C0ADC_EMON_R         5      // 5A -> 1V
#define EEPROM_VAL_C0ADC_EMON_S         1480   // Samples
#define EEPROM_VAL_C0ADC_EMON_O         -200   // Offset mA
#define EEPROM_VAL_C0ADC_IDC_M          5000   // 5A
#define EEPROM_VAL_C0ADC_IDC_B          0
#define EEPROM_VAL_C0ADC_EMON_L         6510   // 6510 mA -> 1500W
#define EEPROM_VAL_C0ADC_EMON_SEC       2      // 2s

#define EEPROM_VAL_C1ADC_TYPE           0      // 0->AC, 1->DC
#define EEPROM_VAL_C1ADC_EMON_R         5      // 5A -> 1V
#define EEPROM_VAL_C1ADC_EMON_S         1480   // Samples
#define EEPROM_VAL_C1ADC_EMON_O         -200   // Offset mA
#define EEPROM_VAL_C1ADC_IDC_M          5000   // 5A
#define EEPROM_VAL_C1ADC_IDC_B          0
#define EEPROM_VAL_C1ADC_EMON_L         6510   // 6510 mA -> 1500W
#define EEPROM_VAL_C1ADC_EMON_SEC       2      // 2s

#define EEPROM_VAL_V0ADC_VDC_M          2900   // 29V
#define EEPROM_VAL_V0ADC_VDC_B          0

#define EEPROM_VAL_V1ADC_VDC_M          2900   // 29V
#define EEPROM_VAL_V1ADC_VDC_B          0

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
