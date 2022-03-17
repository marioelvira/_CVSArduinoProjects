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

#define EEPROM_ADD_WIFI_MODE      0x0E
#define EEPROM_ADD_WIFI_SSID      0x0F
#define WIFI_SSID_MAX             32 // SSID max 32 char -> Next 0x2F
#define EEPROM_ADD_WIFI_PSWD      0x2F
#define WIFI_PSWD_MAX             32 // Password max 32 char -> Next 0x4F

#define EEPROM_ADD_BROKER         0x4F
#define BROKER_MAX                32 // Broker max 32 char -> Next 0x6F
#define EEPROM_ADD_BROKER_PORT    0x6F
#define BROKER_PORT_MAX           2

#define EEPROM_ADD_SCALE_XM       0x71
#define EEPROM_ADD_FAN_XM         0x72
#define EEPROM_ADD_PUMP_XM        0x73
#define EEPROM_ADD_IRRI_XM        0x74
#define EEPROM_ADD_AUX1_XM        0x75
#define EEPROM_ADD_AUX2_XM        0x76

#define EEPROM_ADD_LOGIC_INS      0x77
#define EEPROM_ADD_LOGIC_OUTS     0x78

#define EEPROM_ADD_ADC_F          0x79

#define EEPROM_ADD_TEMP_HI        0x80
#define EEPROM_ADD_TEMP_LO        0x81
#define EEPROM_ADD_OPEN_MIN       0x82
#define EEPROM_ADD_CLOSE_MIN      0x83
#define EEPROM_ADD_CICLO_MIN      0x84

//#define EEPROM_ADD_MAX          0xFA // 250

// Values
#define EEPROM_VAL_OK             0xA4

#define EEPROM_VAL_IP_MODE        DHCP_MODE
#define EEPROM_VAL_IP1            192
#define EEPROM_VAL_IP2            168
#define EEPROM_VAL_IP3            43
#define EEPROM_VAL_IP4            10
#define EEPROM_VAL_MASK1          255
#define EEPROM_VAL_MASK2          255
#define EEPROM_VAL_MASK3          255
#define EEPROM_VAL_MASK4          0
#define EEPROM_VAL_GATE1          192
#define EEPROM_VAL_GATE2          168
#define EEPROM_VAL_GATE3          43
#define EEPROM_VAL_GATE4          1

#define ACCESSPOINT_MODE          0
#define STATION_MODE              1
#define EEPROM_VAL_WIFI_MODE      ACCESSPOINT_MODE // STATION_MODE

//#define EEPROM_VAL_BROKER       
#define EEPROM_VAL_BROKER_PORT    7000

#define EEPROM_VAL_SCALE_XM       5   // 5min
#define EEPROM_VAL_FAN_XM         1
#define EEPROM_VAL_PUMP_XM        1
#define EEPROM_VAL_IRRI_XM        1
#define EEPROM_VAL_AUX1_XM        1
#define EEPROM_VAL_AUX2_XM        1

#define EEPROM_VAL_LOGIC_INS      0
#define EEPROM_VAL_LOGIC_OUTS     1

#define EEPROM_VAL_ADC_F          0   // si/no 1/0

#define EEPROM_VAL_TEMP_HI        30
#define EEPROM_VAL_TEMP_LO        20
#define EEPROM_VAL_OPEN_MIN       1
#define EEPROM_VAL_CLOSE_MIN      1
#define EEPROM_VAL_CICLO_MIN      8

//#define EEPROM_VAL_DEBUG        0

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
