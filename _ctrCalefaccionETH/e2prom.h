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

#define EEPROM_ADD_BROKER         0x4F
#define MQTT_URL_MAX              22 // max 24 char -> Next 0x67
#define EEPROM_ADD_BROKER_PORT    0x65
#define BROKER_PORT_MAX           2
#define EEPROM_ADD_MQTT_USER      0x67
#define MQTT_USER_MAX             22 // max 22 char -> Next 0x7D
#define EEPROM_ADD_MQTT_PSWD      0x7D
#define MQTT_PSWD_MAX             22 // max 24 char -> Next 0x95

#define EEPROM_ADD_LOGIC_INS          0xA0
#define EEPROM_ADD_LOGIC_OUTS         0xA1

#define EEPROM_ADD_RES_PRIM_VOUT      0xA2
#define EEPROM_ADD_RES_INYE_VOUT      0xA3
#define EEPROM_ADD_RES_PRIM_INYE_TEMP 0xA4
#define EEPROM_ADD_RES_PRIM_CONS_TEMP 0xA5
#define EEPROM_ADD_RES_PRIM_HYST_TEMP 0xA6
#define EEPROM_ADD_RES_INYE_CONS_TEMP 0xA7
#define EEPROM_ADD_RES_PRIM_HYST_TEMP 0xA8
#define EEPROM_ADD_AGUA_CONS_TEMP     0xA9
#define EEPROM_ADD_AGUA_HYST_TEMP     0xAA
#define EEPROM_ADD_RES_PRIM_ALAR_MIN  0xAB
#define EEPROM_ADD_RES_INYE_ALAR_MIN  0xAC
#define EEPROM_ADD_AGUA_ALAR_MIN      0xAD

//#define EEPROM_ADD_MAX              0xFA // 250

// Values
#define EEPROM_VAL_OK                 0xAA

#define EEPROM_VAL_IP_MODE        FIXIP_MODE // DHCP_MODE
#define EEPROM_VAL_IP1            192
#define EEPROM_VAL_IP2            168
#define EEPROM_VAL_IP3            1
#define EEPROM_VAL_IP4            50
#define EEPROM_VAL_MASK1          255
#define EEPROM_VAL_MASK2          255
#define EEPROM_VAL_MASK3          255
#define EEPROM_VAL_MASK4          0
#define EEPROM_VAL_GATE1          192
#define EEPROM_VAL_GATE2          168
#define EEPROM_VAL_GATE3          1
#define EEPROM_VAL_GATE4          1

//#define EEPROM_VAL_BROKER  
//#define EEPROM_VAL_MQTT_USER
//#define EEPROM_ADD_MQTT_PSWD    
//#define EEPROM_VAL_BROKER_PORT    7000

#define EEPROM_VAL_LOGIC_INS            0     // Logica leer 1
#define EEPROM_VAL_LOGIC_OUTS           0     // Logica activar out

#define EEPROM_VAL_RES_PRIM_VOUT        110   // V
#define EEPROM_VAL_RES_INYE_VOUT        110   // V
#define EEPROM_VAL_RES_PRIM_INYE_TEMP   70    //º
#define EEPROM_VAL_RES_PRIM_CONS_TEMP   115   //º
#define EEPROM_VAL_RES_PRIM_HYST_TEMP   1     //º
#define EEPROM_VAL_RES_INYE_CONS_TEMP   115
#define EEPROM_VAL_RES_PRIM_HYST_TEMP   1
#define EEPROM_VAL_AGUA_CONS_TEMP       60
#define EEPROM_VAL_AGUA_HYST_TEMP       5
#define EEPROM_VAL_RES_PRIM_ALAR_MIN    30
#define EEPROM_VAL_RES_INYE_ALAR_MIN    30
#define EEPROM_VAL_AGUA_ALAR_MIN        30

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
