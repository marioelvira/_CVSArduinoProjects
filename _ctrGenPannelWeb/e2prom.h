#ifdef __cplusplus
extern "C" {
#endif

#ifndef _E2PROM_H_
#define _E2PROM_H_

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

//#define EEPROM_ADD_RESERVA        0x4F

#define EEPROM_ADD_1P_TIMER_GEN   0x50
#define EEPROM_ADD_2P_TIMER_GEN   0x51
#define EEPROM_ADD_3P_TIMER_GEN   0x52
#define EEPROM_ADD_4P_TIMER_GEN   0x53
#define EEPROM_ADD_5P_TIMER_GEN   0x54
#define EEPROM_ADD_6P_TIMER_GEN   0x55
#define EEPROM_ADD_7P_TIMER_GEN   0x56
#define EEPROM_ADD_8P_TIMER_GEN   0x57
#define EEPROM_ADD_9P_TIMER_GEN   0x58

#define EEPROM_ADD_BUZZER_ON      0x59
#define EEPROM_ADD_TSTART         0x5A
#define EEPROM_ADD_TSTOP          0x5B
#define EEPROM_ADD_DEBUG          0x5C

//#define EEPROM_ADD_MAX              0xFA // 250

// Values
#define EEPROM_VAL_OK             0xAA

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

//#define EEPROM_VAL_RESERVA      

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
#define EEPROM_VAL_DEBUG          0

/*
#define _DEBUG_TIME   1

#if (_DEBUG_TIME == 1)
  #define X_60    3
  #define X_3600  180
#else
  #define X_60    60
  #define X_3600  3600
#endif
*/

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
