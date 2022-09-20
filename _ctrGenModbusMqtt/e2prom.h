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
#define WIFI_SSID_MAX             32 // max 32 char -> Next 0x2F
#define EEPROM_ADD_WIFI_PSWD      0x2F
#define WIFI_PSWD_MAX             32 // max 32 char -> Next 0x4F

#define EEPROM_ADD_BROKER         0x4F
#define MQTT_URL_MAX              24 // max 24 char -> Next 0x67
#define EEPROM_ADD_BROKER_PORT    0x67
#define BROKER_PORT_MAX           2
#define EEPROM_ADD_MQTT_USER      0x69
#define MQTT_USER_MAX             24 // max 24 char -> Next 0x81
#define EEPROM_ADD_MQTT_PSWD      0x81
#define MQTT_PSWD_MAX             24 // max 24 char -> Next 0x99

#define EEPROM_ADD_LOGIC_INS      0x99
#define EEPROM_ADD_LOGIC_OUTS     0x9A
#define EEPROM_ADD_MBADD1         0x9B
#define EEPROM_ADD_MBADD2         0x9C

#define EEPROM_ADD_ADC_M_LO       0x9D
#define EEPROM_ADD_ADC_M_HI       0x9E
#define EEPROM_ADD_ADC_B_LO       0x9F
#define EEPROM_ADD_ADC_B_HI       0xA0
#define EEPROM_ADD_ADC_P_LO       0xA1
#define EEPROM_ADD_ADC_P_HI       0xA2
#define EEPROM_ADD_ADC_S          0xA3
#define EEPROM_ADD_ADC_F          0xA4

// Control
#define EEPROM_ADD_1P_TIMER_GEN   0xA5
#define EEPROM_ADD_2P_TIMER_GEN   0xA6
#define EEPROM_ADD_3P_TIMER_GEN   0xA7
#define EEPROM_ADD_4P_TIMER_GEN   0xA8
#define EEPROM_ADD_5P_TIMER_GEN   0xA9
#define EEPROM_ADD_6P_TIMER_GEN   0xAA
#define EEPROM_ADD_7P_TIMER_GEN   0xAB
#define EEPROM_ADD_8P_TIMER_GEN   0xAC
#define EEPROM_ADD_9P_TIMER_GEN   0xAD

#define EEPROM_ADD_BUZZER_ON      0xAE
#define EEPROM_ADD_TSTART         0xAF
#define EEPROM_ADD_TSTOP          0xB0

#define EEPROM_ADD_O11_TIMER   	0xB1
#define EEPROM_ADD_O12_TIMER   	0xB2
#define EEPROM_ADD_O13_TIMER   	0xB3
#define EEPROM_ADD_O14_TIMER   	0xB4
#define EEPROM_ADD_O15_TIMER   	0xB5
#define EEPROM_ADD_O16_TIMER   	0xB6
#define EEPROM_ADD_O17_TIMER   	0xB7
#define EEPROM_ADD_O18_TIMER   	0xB8

//#define EEPROM_ADD_MAX          0xFA // 250

// Values
#define EEPROM_VAL_OK             0xA1

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
//#define EEPROM_VAL_MQTT_USER
//#define EEPROM_ADD_MQTT_PSWD    
//#define EEPROM_VAL_BROKER_PORT    7000

#define EEPROM_VAL_LOGIC_INS      1
#define EEPROM_VAL_LOGIC_OUTS     1
#define EEPROM_VAL_MBADD1         255
#define EEPROM_VAL_MBADD2         1

#define EEPROM_VAL_ADC_M          153
#define EEPROM_VAL_ADC_B          0
#define EEPROM_VAL_ADC_P          10000
#define EEPROM_VAL_ADC_S          0   // +/-  1/0
#define EEPROM_VAL_ADC_F          0   // si/no 1/0

// Control
#define EEPROM_VAL_1P_TIMER_GEN   15  // Min
#define EEPROM_VAL_2P_TIMER_GEN   30  // Min
#define EEPROM_VAL_3P_TIMER_GEN   60  // Min
#define EEPROM_VAL_4P_TIMER_GEN   90  // Min
#define EEPROM_VAL_5P_TIMER_GEN   120 // Min
#define EEPROM_VAL_6P_TIMER_GEN   3   // Horas
#define EEPROM_VAL_7P_TIMER_GEN   4   // Horas
#define EEPROM_VAL_8P_TIMER_GEN   5   // Horas
#define EEPROM_VAL_9P_TIMER_GEN   7   // Horas

#define EEPROM_VAL_BUZZER_ON      10  // Secs
#define EEPROM_VAL_TSTART         10  // Secs
#define EEPROM_VAL_TSTOP          20  // Secs

#define EEPROM_VAL_O11_TIMER   	10  // Min
#define EEPROM_VAL_O12_TIMER   	20  // Min
#define EEPROM_VAL_O13_TIMER   	30  // Min
#define EEPROM_VAL_O14_TIMER   	40  // Min
#define EEPROM_VAL_O15_TIMER   	1  	// Horas
#define EEPROM_VAL_O16_TIMER   	2  	// Horas
#define EEPROM_VAL_O17_TIMER   	3  	// Horas
#define EEPROM_VAL_O18_TIMER   	4  	// Horas

#define NUM_O1X_MAX		8

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
