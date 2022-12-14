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
#define EEPROM_ADD_OK              0x00

#define EEPROM_ADD_MODBUS_ID       0x01

#define EEPROM_ADD_ADC0_M_LO       0x02
#define EEPROM_ADD_ADC0_M_HI       0x03
#define EEPROM_ADD_ADC0_B_LO       0x04
#define EEPROM_ADD_ADC0_B_HI       0x05
#define EEPROM_ADD_ADC0_P_LO       0x06
#define EEPROM_ADD_ADC0_P_HI       0x07
#define EEPROM_ADD_ADC0_S          0x08
#define EEPROM_ADD_ADC0_F          0x09

#define EEPROM_ADD_ADC1_M_LO       0x0A
#define EEPROM_ADD_ADC1_M_HI       0x0B
#define EEPROM_ADD_ADC1_B_LO       0x0C
#define EEPROM_ADD_ADC1_B_HI       0x0D
#define EEPROM_ADD_ADC1_P_LO       0x0E
#define EEPROM_ADD_ADC1_P_HI       0x0F
#define EEPROM_ADD_ADC1_S          0x10
#define EEPROM_ADD_ADC1_F          0x11

#define EEPROM_ADD_ADC2_M_LO       0x12
#define EEPROM_ADD_ADC2_M_HI       0x13
#define EEPROM_ADD_ADC2_B_LO       0x14
#define EEPROM_ADD_ADC2_B_HI       0x15
#define EEPROM_ADD_ADC2_P_LO       0x16
#define EEPROM_ADD_ADC2_P_HI       0x17
#define EEPROM_ADD_ADC2_S          0x18
#define EEPROM_ADD_ADC2_F          0x19

#define EEPROM_ADD_ADC3_M_LO       0x1A
#define EEPROM_ADD_ADC3_M_HI       0x1B
#define EEPROM_ADD_ADC3_B_LO       0x1C
#define EEPROM_ADD_ADC3_B_HI       0x1D
#define EEPROM_ADD_ADC3_P_LO       0x1E
#define EEPROM_ADD_ADC3_P_HI       0x1F
#define EEPROM_ADD_ADC3_S          0x20
#define EEPROM_ADD_ADC3_F          0x21

#define EEPROM_ADD_RPM            0x22
#define EEPROM_ADD_PRESS          0x23

//#define EEPROM_ADD_MAX          0xFA // 250

// Values
#define EEPROM_VAL_OK             0xA1

//#define EEPROM_VAL_RESERVA      
#define EEPROM_VAL_MODBUS_ID      0x01

#define EEPROM_VAL_ADC0_M         50	// 5V
#define EEPROM_VAL_ADC0_B         0
#define EEPROM_VAL_ADC0_P         10000
#define EEPROM_VAL_ADC0_S         0     // +/-  1/0
#define EEPROM_VAL_ADC0_F         0     // si/no 1/0

#define EEPROM_VAL_ADC1_M         100	// 10V
#define EEPROM_VAL_ADC1_B         0
#define EEPROM_VAL_ADC1_P         10000
#define EEPROM_VAL_ADC1_S         0     // +/-  1/0
#define EEPROM_VAL_ADC1_F         0     // si/no 1/0

#define EEPROM_VAL_ADC2_M         200	// 20V
#define EEPROM_VAL_ADC2_B         0
#define EEPROM_VAL_ADC2_P         10000
#define EEPROM_VAL_ADC2_S         0     // +/-  1/0
#define EEPROM_VAL_ADC2_F         0     // si/no 1/0

#define EEPROM_VAL_ADC3_M         300	// 30V
#define EEPROM_VAL_ADC3_B         0
#define EEPROM_VAL_ADC3_P         10000
#define EEPROM_VAL_ADC3_S         0     // +/-  1/0
#define EEPROM_VAL_ADC3_F         0     // si/no 1/0

#define EEPROM_VAL_RPM            100
#define EEPROM_VAL_PRESS          100

#endif // _E2PROM_H_

#ifdef __cplusplus
} // extern "C"
#endif
