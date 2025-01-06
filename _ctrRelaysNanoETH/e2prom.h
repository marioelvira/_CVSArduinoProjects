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

#define EEPROM_ADD_LOGIC_INS          0xA0
#define EEPROM_ADD_LOGIC_OUTS         0xA1

#define EEPROM_ADD_ADC0_TYPE          0xA2
#define EEPROM_ADD_ADC0_EMON_R_LO     0xA3
#define EEPROM_ADD_ADC0_EMON_R_HI     0xA4
#define EEPROM_ADD_ADC0_EMON_L_LO     0xA9
#define EEPROM_ADD_ADC0_EMON_L_HI     0xAA
#define EEPROM_ADD_ADC0_EMON_SEC_LO   0xAB
#define EEPROM_ADD_ADC0_EMON_SEC_HI   0xAC

#define EEPROM_ADD_ADC1_TYPE          0xAD
#define EEPROM_ADD_ADC1_EMON_R_LO     0xAE
#define EEPROM_ADD_ADC1_EMON_R_HI     0xAF
#define EEPROM_ADD_ADC1_EMON_L_LO     0xB4
#define EEPROM_ADD_ADC1_EMON_L_HI     0xB5
#define EEPROM_ADD_ADC1_EMON_SEC_LO   0xB6
#define EEPROM_ADD_ADC1_EMON_SEC_HI   0xB7

#define EEPROM_ADD_ADC2_VDC_M_LO      0xB8
#define EEPROM_ADD_ADC2_VDC_M_HI      0xB9
#define EEPROM_ADD_ADC2_VDC_B_LO      0xBA
#define EEPROM_ADD_ADC2_VDC_B_HI      0xBB

#define EEPROM_ADD_ADC3_VDC_M_LO      0xBC
#define EEPROM_ADD_ADC3_VDC_M_HI      0xBD
#define EEPROM_ADD_ADC3_VDC_B_LO      0xBE
#define EEPROM_ADD_ADC3_VDC_B_HI      0xBF

#define EEPROM_ADD_ADC4_VDC_M_LO      0xC0
#define EEPROM_ADD_ADC4_VDC_M_HI      0xC1
#define EEPROM_ADD_ADC4_VDC_B_LO      0xC2
#define EEPROM_ADD_ADC4_VDC_B_HI      0xC3

#define EEPROM_ADD_ADC5_VDC_M_LO      0xC4
#define EEPROM_ADD_ADC5_VDC_M_HI      0xC5
#define EEPROM_ADD_ADC5_VDC_B_LO      0xC6
#define EEPROM_ADD_ADC5_VDC_B_HI      0xC7

#define EEPROM_ADD_ADC6_VDC_M_LO      0xC8
#define EEPROM_ADD_ADC6_VDC_M_HI      0xC9
#define EEPROM_ADD_ADC6_VDC_B_LO      0xCA
#define EEPROM_ADD_ADC6_VDC_B_HI      0xCB

#define EEPROM_ADD_ADC7_VDC_M_LO      0xCC
#define EEPROM_ADD_ADC7_VDC_M_HI      0xCD
#define EEPROM_ADD_ADC7_VDC_B_LO      0xCE
#define EEPROM_ADD_ADC7_VDC_B_HI      0xCF

#define EEPROM_ADD_STATE0_0_1_SEC     0xD0
#define EEPROM_ADD_STATE0_1_2_SEC     0xD1
#define EEPROM_ADD_STATE1_0_1_SEC     0xD2
#define EEPROM_ADD_STATE1_1_2_SEC     0xD3
#define EEPROM_ADD_STATE2_0_1_SEC     0xD4
#define EEPROM_ADD_STATE2_1_2_SEC     0xD5
#define EEPROM_ADD_IRMS_STATE2_SEC    0xD6

//#define EEPROM_ADD_MAX              0xFA // 250

// Values
#define EEPROM_VAL_OK                 0xAA

#define EEPROM_VAL_IP_MODE        DHCP_MODE // FIXIP_MODE // 
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

#define EEPROM_VAL_LOGIC_INS            0     // Logica leer 1
#define EEPROM_VAL_LOGIC_OUTS           0     // Logica activar out

#define EEPROM_VAL_ADC0_TYPE           1      // 0-> NOT USED, 1->AC
#define EEPROM_VAL_ADC0_EMON_R         5      // 5A -> 1V
#define EEPROM_VAL_ADC0_EMON_L         6510   // 6510 mA -> 1500W
#define EEPROM_VAL_ADC0_EMON_SEC       3      // 3s

#define EEPROM_VAL_ADC1_TYPE           1      // 0-> NOT USED, 1->AC
#define EEPROM_VAL_ADC1_EMON_R         5      // 5A -> 1V
#define EEPROM_VAL_ADC1_EMON_L         6510   // 6510 mA -> 1500W
#define EEPROM_VAL_ADC1_EMON_SEC       3      // 3s
#define EEPROM_VAL_ADC2_VDC_M          20000  // 5V -> 100A
#define EEPROM_VAL_ADC2_VDC_B          0
#define EEPROM_VAL_ADC3_VDC_M          20000  // 5V -> 100A
#define EEPROM_VAL_ADC3_VDC_B          0
#define EEPROM_VAL_ADC4_VDC_M          2500
#define EEPROM_VAL_ADC4_VDC_B          0
#define EEPROM_VAL_ADC5_VDC_M          540
#define EEPROM_VAL_ADC5_VDC_B          0
#define EEPROM_VAL_ADC6_VDC_M          2200
#define EEPROM_VAL_ADC6_VDC_B          0
#define EEPROM_VAL_ADC7_VDC_M          2200
#define EEPROM_VAL_ADC7_VDC_B          0

#define EEPROM_VAL_STATE0_0_1_SEC      2    // 2s
#define EEPROM_VAL_STATE0_1_2_SEC      180  // 3m
#define EEPROM_VAL_STATE1_0_1_SEC      2    // 2s
#define EEPROM_VAL_STATE1_1_2_SEC      2    // 2s
#define EEPROM_VAL_STATE2_0_1_SEC      2    // 2s
#define EEPROM_VAL_STATE2_1_2_SEC      2    // 2s
#define EEPROM_VAL_IRMS_STATE2_SEC     180  // 3m

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
