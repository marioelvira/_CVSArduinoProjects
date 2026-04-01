#ifdef __cplusplus
extern "C" {
#endif

#ifndef _E2PROM_H_
#define _E2PROM_H_

extern bool cfgLogicIns;
extern bool cfgLogicOuts;
extern byte cfgMB1Add;

extern int cfgResPrimInyeTemp;
extern int cfgResPrimConsTemp;
extern int cfgResPrimHystTemp;
extern int cfgResInyeConsTemp;
extern int cfgResInyeHystTemp;
extern int cfgAguaConsTemp;
extern int cfgAguaHystTemp;

extern int cfgResPrimAlarMin;
extern int cfgResInyeAlarMin;
extern int cfgAguaAlarMin;

#if (_USE_TRIAC_ == 1)
extern int cfgTriacVout[];
extern int cfgTriacUse[];
#endif

#if (_USE_MBRTU_ == 1)
extern int cfgTempUse[];
#endif

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
#define EEPROM_ADD_MBADD1             0xA2

#define EEPROM_ADD_RES_PRIM_INYE_TEMP 0xB0
#define EEPROM_ADD_RES_PRIM_CONS_TEMP 0xB1
#define EEPROM_ADD_RES_PRIM_HYST_TEMP 0xB2
#define EEPROM_ADD_RES_INYE_CONS_TEMP 0xB3
#define EEPROM_ADD_RES_PRIM_HYST_TEMP 0xB4
#define EEPROM_ADD_AGUA_CONS_TEMP     0xB5
#define EEPROM_ADD_AGUA_HYST_TEMP     0xB6
#define EEPROM_ADD_RES_PRIM_ALAR_MIN  0xB7
#define EEPROM_ADD_RES_INYE_ALAR_MIN  0xB8
#define EEPROM_ADD_AGUA_ALAR_MIN      0xB9

#define EEPROM_ADD_TRIAC1_VOUT        0xBA
#define EEPROM_ADD_TRIAC2_VOUT        0xBB
#define EEPROM_ADD_TRIAC3_VOUT        0xBC

#define EEPROM_ADD_TRIAC1_USE         0xBD
#define EEPROM_ADD_TRIAC2_USE         0xBE
#define EEPROM_ADD_TRIAC3_USE         0xBF

#define EEPROM_ADD_TEMP1_USE          0xC0
#define EEPROM_ADD_TEMP2_USE          0xC1
#define EEPROM_ADD_TEMP3_USE          0xC2
#define EEPROM_ADD_TEMP4_USE          0xC3

//#define EEPROM_ADD_MAX              0xFA // 250

// Values
#define EEPROM_VAL_OK                 0xA1

#define EEPROM_VAL_IP_MODE        FIXIP_MODE // DHCP_MODE
#define EEPROM_VAL_IP1            192
#define EEPROM_VAL_IP2            168
#define EEPROM_VAL_IP3            5
#define EEPROM_VAL_IP4            50
#define EEPROM_VAL_MASK1          255
#define EEPROM_VAL_MASK2          255
#define EEPROM_VAL_MASK3          255
#define EEPROM_VAL_MASK4          0
#define EEPROM_VAL_GATE1          192
#define EEPROM_VAL_GATE2          168
#define EEPROM_VAL_GATE3          5
#define EEPROM_VAL_GATE4          1

//#define EEPROM_VAL_BROKER  
//#define EEPROM_VAL_MQTT_USER
//#define EEPROM_VAL_MQTT_PSWD
//#define EEPROM_VAL_BROKER_PORT

#define EEPROM_VAL_LOGIC_INS            1     // Logica Reposo
#define EEPROM_VAL_LOGIC_OUTS           0     // Logica Reposo
#define EEPROM_VAL_MBADD1               1

#define EEPROM_VAL_RES_PRIM_INYE_TEMP   70    //º
#define EEPROM_VAL_RES_PRIM_CONS_TEMP   115   //º
#define EEPROM_VAL_RES_PRIM_HYST_TEMP   1     //º
#define EEPROM_VAL_RES_INYE_CONS_TEMP   115   //º
#define EEPROM_VAL_RES_PRIM_HYST_TEMP   1     //º
#define EEPROM_VAL_AGUA_CONS_TEMP       60    //º
#define EEPROM_VAL_AGUA_HYST_TEMP       5     //º

#define EEPROM_VAL_RES_PRIM_ALAR_MIN    30
#define EEPROM_VAL_RES_INYE_ALAR_MIN    30
#define EEPROM_VAL_AGUA_ALAR_MIN        30

#define EEPROM_VAL_TRIAC1_VOUT          110 // Vac
#define EEPROM_VAL_TRIAC2_VOUT          110 // Vac
#define EEPROM_VAL_TRIAC3_VOUT          230 // Vac

#define EEPROM_VAL_TRIAC1_USE           1   // 1-> RES_PRIN_TRC
#define EEPROM_VAL_TRIAC2_USE           2   // 2-> RES_INYE_TRC
#define EEPROM_VAL_TRIAC3_USE           0   // 0-> Not used

#define EEPROM_VAL_TEMP1_USE            1   // 1-> RES_PRIN_TEMP 
#define EEPROM_VAL_TEMP2_USE            2   // 2-> RES_INYE_TEMP
#define EEPROM_VAL_TEMP3_USE            3   // 3-> BOM_AGUA_TEMP
#define EEPROM_VAL_TEMP4_USE            0   // 0-> Not used

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
