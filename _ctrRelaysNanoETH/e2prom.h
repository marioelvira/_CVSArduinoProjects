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

#define EEPROM_ADD_BROKER         		0x0E
#define MQTT_URL_MAX              		24 // max 24 char -> Next 0x26
#define EEPROM_ADD_BROKER_PORT    		0x26
#define BROKER_PORT_MAX           		2
#define EEPROM_ADD_MQTT_USER      		0x28
#define MQTT_USER_MAX             		24 // max 24 char -> Next 0x28
#define EEPROM_ADD_MQTT_PSWD      		0x40
#define MQTT_PSWD_MAX             		24 // max 24 char -> Next 0x58

#define EEPROM_ADD_LOGIC_INS           0xA0
#define EEPROM_ADD_LOGIC_OUTS          0xA1

#define EEPROM_ADD_C0ADC_TYPE          0xA2
#define EEPROM_ADD_C0ADC_EMON_R_LO     0xA3
#define EEPROM_ADD_C0ADC_EMON_R_HI     0xA4
#define EEPROM_ADD_C0ADC_IDC_M_LO      0xA5
#define EEPROM_ADD_C0ADC_IDC_M_HI      0xA6
#define EEPROM_ADD_C0ADC_IDC_B_LO      0xA7
#define EEPROM_ADD_C0ADC_IDC_B_HI      0xA8
#define EEPROM_ADD_C0ADC_EMON_L_LO     0xA9
#define EEPROM_ADD_C0ADC_EMON_L_HI     0xAA
#define EEPROM_ADD_C0ADC_EMON_SEC_LO   0xAB
#define EEPROM_ADD_C0ADC_EMON_SEC_HI   0xAC

#define EEPROM_ADD_C1ADC_TYPE          0xAD
#define EEPROM_ADD_C1ADC_EMON_R_LO     0xAE
#define EEPROM_ADD_C1ADC_EMON_R_HI     0xAF
#define EEPROM_ADD_C1ADC_IDC_M_LO      0xB0
#define EEPROM_ADD_C1ADC_IDC_M_HI      0xB1

#define EEPROM_ADD_C1ADC_IDC_B_LO      0xB2
#define EEPROM_ADD_C1ADC_IDC_B_HI      0xB3
#define EEPROM_ADD_C1ADC_EMON_L_LO     0xB4
#define EEPROM_ADD_C1ADC_EMON_L_HI     0xB5
#define EEPROM_ADD_C1ADC_EMON_SEC_LO   0xB6
#define EEPROM_ADD_C1ADC_EMON_SEC_HI   0xB7

#define EEPROM_ADD_C2ADC_TYPE          0xB8
#define EEPROM_ADD_C2ADC_EMON_R_LO     0xB9
#define EEPROM_ADD_C2ADC_EMON_R_HI     0xBA
#define EEPROM_ADD_C2ADC_EMON_O_LO     0xBB
#define EEPROM_ADD_C2ADC_EMON_O_HI     0xBC
#define EEPROM_ADD_C2ADC_IDC_M_LO      0xBD
#define EEPROM_ADD_C2ADC_IDC_M_HI      0xBE
#define EEPROM_ADD_C2ADC_IDC_B_LO      0xBF
#define EEPROM_ADD_C2ADC_IDC_B_HI      0xC0
#define EEPROM_ADD_C2ADC_EMON_L_LO     0xC1
#define EEPROM_ADD_C2ADC_EMON_L_HI     0xC2
#define EEPROM_ADD_C2ADC_EMON_SEC_LO   0xC3
#define EEPROM_ADD_C2ADC_EMON_SEC_HI   0xC4

#define EEPROM_ADD_C3ADC_TYPE          0xC5
#define EEPROM_ADD_C3ADC_EMON_R_LO     0xC6
#define EEPROM_ADD_C3ADC_EMON_R_HI     0xC7
#define EEPROM_ADD_C3ADC_EMON_O_LO     0xC8
#define EEPROM_ADD_C3ADC_EMON_O_HI     0xC9
#define EEPROM_ADD_C3ADC_IDC_M_LO      0xCA
#define EEPROM_ADD_C3ADC_IDC_M_HI      0xCB
#define EEPROM_ADD_C3ADC_IDC_B_LO      0xCC
#define EEPROM_ADD_C3ADC_IDC_B_HI      0xCD
#define EEPROM_ADD_C3ADC_EMON_L_LO     0xCE
#define EEPROM_ADD_C3ADC_EMON_L_HI     0xCF
#define EEPROM_ADD_C3ADC_EMON_SEC_LO   0xD0
#define EEPROM_ADD_C3ADC_EMON_SEC_HI   0xD1

#define EEPROM_ADD_V0ADC_VDC_M_LO      0xD2
#define EEPROM_ADD_V0ADC_VDC_M_HI      0xD3
#define EEPROM_ADD_V0ADC_VDC_B_LO      0xD4
#define EEPROM_ADD_V0ADC_VDC_B_HI      0xD5

#define EEPROM_ADD_V1ADC_VDC_M_LO      0xD6
#define EEPROM_ADD_V1ADC_VDC_M_HI      0xD7
#define EEPROM_ADD_V1ADC_VDC_B_LO      0xD8
#define EEPROM_ADD_V1ADC_VDC_B_HI      0xD9

#define EEPROM_ADD_V2ADC_VDC_M_LO      0xDA
#define EEPROM_ADD_V2ADC_VDC_M_HI      0xDB
#define EEPROM_ADD_V2ADC_VDC_B_LO      0xDC
#define EEPROM_ADD_V2ADC_VDC_B_HI      0xDD

#define EEPROM_ADD_V3ADC_VDC_M_LO      0xDE
#define EEPROM_ADD_V3ADC_VDC_M_HI      0xDF
#define EEPROM_ADD_V3ADC_VDC_B_LO      0xE0
#define EEPROM_ADD_V3ADC_VDC_B_HI      0xE1

//#define EEPROM_ADD_MAX               0xFA // 250

// Values
#define EEPROM_VAL_OK                   0xA1

#define EEPROM_VAL_IP_MODE        DHCP_MODE // FIXIP_MODE
#define EEPROM_VAL_IP1            192
#define EEPROM_VAL_IP2            168
#define EEPROM_VAL_IP3            100
#define EEPROM_VAL_IP4            200
#define EEPROM_VAL_MASK1          255
#define EEPROM_VAL_MASK2          255
#define EEPROM_VAL_MASK3          255
#define EEPROM_VAL_MASK4          0
#define EEPROM_VAL_GATE1          192
#define EEPROM_VAL_GATE2          168
#define EEPROM_VAL_GATE3          100
#define EEPROM_VAL_GATE4          1

#define EEPROM_VAL_LOGIC_INS            1
#define EEPROM_VAL_LOGIC_OUTS           1

#define EEPROM_VAL_C0ADC_TYPE           1      // 0-> NOT USED, 1->AC, D->DC
#define EEPROM_VAL_C0ADC_EMON_R         5      // 5A -> 1V
#define EEPROM_VAL_C0ADC_IDC_M          5000   // 5A
#define EEPROM_VAL_C0ADC_IDC_B          0
#define EEPROM_VAL_C0ADC_EMON_L         6510   // 6510 mA -> 1500W
#define EEPROM_VAL_C0ADC_EMON_SEC       2      // 2s

#define EEPROM_VAL_C1ADC_TYPE           1      // 0-> NOT USED, 1->AC, D->DC
#define EEPROM_VAL_C1ADC_EMON_R         5      // 5A -> 1V
#define EEPROM_VAL_C1ADC_IDC_M          10000  // 10A
#define EEPROM_VAL_C1ADC_IDC_B          0
#define EEPROM_VAL_C1ADC_EMON_L         6510   // 6510 mA -> 1500W
#define EEPROM_VAL_C1ADC_EMON_SEC       2      // 2s

#define EEPROM_VAL_C2ADC_TYPE           0      // 0-> NOT USED, 1->AC, D->DC
#define EEPROM_VAL_C2ADC_EMON_R         5      // 5A -> 1V
#define EEPROM_VAL_C2ADC_IDC_M          5000   // 5A
#define EEPROM_VAL_C2ADC_IDC_B          0
#define EEPROM_VAL_C2ADC_EMON_L         3255   // 6510 mA -> 750W
#define EEPROM_VAL_C2ADC_EMON_SEC       3      // 3s

#define EEPROM_VAL_C3ADC_TYPE           0      // 0-> NOT USED, 1->AC, D->DC
#define EEPROM_VAL_C3ADC_EMON_R         5      // 5A -> 1V
#define EEPROM_VAL_C3ADC_IDC_M          5000   // 5A
#define EEPROM_VAL_C3ADC_IDC_B          0
#define EEPROM_VAL_C3ADC_EMON_L         3255   // 3255 mA -> 750W
#define EEPROM_VAL_C3ADC_EMON_SEC       4      // 4s

#define EEPROM_VAL_V0ADC_VDC_M          2500   // 25V
#define EEPROM_VAL_V0ADC_VDC_B          0

#define EEPROM_VAL_V1ADC_VDC_M          2500   // 25V
#define EEPROM_VAL_V1ADC_VDC_B          0

#define EEPROM_VAL_V2ADC_VDC_M          2500   // 25V
#define EEPROM_VAL_V2ADC_VDC_B          0

#define EEPROM_VAL_V3ADC_VDC_M          2500   // 25V
#define EEPROM_VAL_V3ADC_VDC_B          0

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
