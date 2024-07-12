#ifdef __cplusplus
extern "C" {
#endif

#ifndef _E2PROM_H_
#define _E2PROM_H_

#include "main.h"
#include "mEthernet.h"

#define _ERASE_EEPROM_        0
#define _READ_EEPROM_         0
#define _WRITE_SSID_EEPROM_   0

// Address
#define EEPROM_ADD_OK             0x00

#define EEPROM_ADD_IP_MODE        0x01
#define EEPROM_ADD_IP1            0x02
#define EEPROM_ADD_IP2            0x03
#define EEPROM_ADD_IP3            0x04
#define EEPROM_ADD_IP4            0x05
#define EEPROM_ADD_MASK1          0x06
#define EEPROM_ADD_MASK2          0x07
#define EEPROM_ADD_MASK3          0x08
#define EEPROM_ADD_MASK4          0x09
#define EEPROM_ADD_GATE1          0x0A
#define EEPROM_ADD_GATE2          0x0B
#define EEPROM_ADD_GATE3          0x0C
#define EEPROM_ADD_GATE4          0x0D

#define EEPROM_ADD_LOGIC_INS           0xA1
#define EEPROM_ADD_LOGIC_OUTS          0xA2

#define EEPROM_ADD_C0ADC_TYPE          0xA3
#define EEPROM_ADD_C0ADC_EMON_R_LO     0xA4
#define EEPROM_ADD_C0ADC_EMON_R_HI     0xA5
#define EEPROM_ADD_C0ADC_EMON_O_LO     0xA6
#define EEPROM_ADD_C0ADC_EMON_O_HI     0xA7
#define EEPROM_ADD_C0ADC_IDC_M_LO      0xA8
#define EEPROM_ADD_C0ADC_IDC_M_HI      0xA9
#define EEPROM_ADD_C0ADC_IDC_B_LO      0xAA
#define EEPROM_ADD_C0ADC_IDC_B_HI      0xAB
#define EEPROM_ADD_C0ADC_EMON_L_LO     0xAC
#define EEPROM_ADD_C0ADC_EMON_L_HI     0xAD
#define EEPROM_ADD_C0ADC_EMON_SEC_LO   0xAE
#define EEPROM_ADD_C0ADC_EMON_SEC_HI   0xAF

#define EEPROM_ADD_C1ADC_TYPE          0xB0
#define EEPROM_ADD_C1ADC_EMON_R_LO     0xB1
#define EEPROM_ADD_C1ADC_EMON_R_HI     0xB2
#define EEPROM_ADD_C1ADC_EMON_O_LO     0xB3
#define EEPROM_ADD_C1ADC_EMON_O_HI     0xB4
#define EEPROM_ADD_C1ADC_IDC_M_LO      0xB5
#define EEPROM_ADD_C1ADC_IDC_M_HI      0xB6
#define EEPROM_ADD_C1ADC_IDC_B_LO      0xB7
#define EEPROM_ADD_C1ADC_IDC_B_HI      0xB9
#define EEPROM_ADD_C1ADC_EMON_L_LO     0xBA
#define EEPROM_ADD_C1ADC_EMON_L_HI     0xBB
#define EEPROM_ADD_C1ADC_EMON_SEC_LO   0xBC
#define EEPROM_ADD_C1ADC_EMON_SEC_HI   0xBD
#define EEPROM_ADD_V0ADC_VDC_M_LO      0xBE
#define EEPROM_ADD_V0ADC_VDC_M_HI      0xBF
#define EEPROM_ADD_V0ADC_VDC_B_LO      0xC0
#define EEPROM_ADD_V0ADC_VDC_B_HI      0xC1

#define EEPROM_ADD_V1ADC_VDC_M_LO      0xC4
#define EEPROM_ADD_V1ADC_VDC_M_HI      0xC5
#define EEPROM_ADD_V1ADC_VDC_B_LO      0xC6
#define EEPROM_ADD_V1ADC_VDC_B_HI      0xC7

//#define EEPROM_ADD_MAX               0xFA // 250

// Values
#define EEPROM_VAL_OK                   0xAA

#define EEPROM_VAL_IP_MODE        FIXIP_MODE // DHCP_MODE
#define EEPROM_VAL_IP1            172
#define EEPROM_VAL_IP2            19
#define EEPROM_VAL_IP3            1
#define EEPROM_VAL_IP4            200
#define EEPROM_VAL_MASK1          255
#define EEPROM_VAL_MASK2          255
#define EEPROM_VAL_MASK3          255
#define EEPROM_VAL_MASK4          0
#define EEPROM_VAL_GATE1          172
#define EEPROM_VAL_GATE2          19
#define EEPROM_VAL_GATE3          1
#define EEPROM_VAL_GATE4          8

#define EEPROM_VAL_LOGIC_INS            1
#define EEPROM_VAL_LOGIC_OUTS           1

#define EEPROM_VAL_C0ADC_TYPE           0      // 0->AC, 1->DC
#define EEPROM_VAL_C0ADC_EMON_R         5      // 5A -> 1V
#define EEPROM_VAL_C0ADC_EMON_O         0      // Offset mA
#define EEPROM_VAL_C0ADC_IDC_M          5000   // 5A
#define EEPROM_VAL_C0ADC_IDC_B          0
#define EEPROM_VAL_C0ADC_EMON_L         6510   // 6510 mA -> 1500W
#define EEPROM_VAL_C0ADC_EMON_SEC       2      // 2s

#define EEPROM_VAL_C1ADC_TYPE           0      // 0->AC, 1->DC
#define EEPROM_VAL_C1ADC_EMON_R         15     // 15A -> 1V
#define EEPROM_VAL_C1ADC_EMON_O         0      // Offset mA
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
