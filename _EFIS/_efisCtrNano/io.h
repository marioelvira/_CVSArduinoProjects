#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////

// Arduino AVR boards -> Arduino Nano
// Procesador ATmega328P (Old Bootloader)

/*                           |--------|
 *                        ---|   USB  |--- 
 *                        |  |--------|  |
 *                        |              |
 *        (LED*) SPI-SCK -| D13      D12 |- SPI-MISO
 *                       -| 3V3      D11 |- SPI-MOSI
 *                       -| AREF     D10 |- SPI-SS
 *                   D14 -| A0        D9 |-                 <- IN0
 *                   D15 -| A1        D8 |-                 <- IN1
 *                   D16 -| A2        D7 |-                 <- IN2
 *                   D17 -| A3        D6 |- (PWM)           -> OUT0
 *               SDA/D18 -| A4        D5 |- (PWM)           -> OUT1
 *               SCL/D19 -| A5        D4 |-                 -> OUT3
 *                   D20 -| A6  [  ]  D3 |- INT1 (PWM)      <- INT1
 *                   D21 -| A7  ****  D2 |- INT0            <- INT0
 *                    5V -| 5V       GND |- GND  
 *                 RESET -| RST      RST |-   
 *                   GND -| GND      RX0 |- UART IN
 *                   VIN -| 5V       TX1 |- UART OUT  
 *                        ---------------
 */

////////////////////
// PIN definition //
////////////////////

// LED
#define PIN_LED        13

// ADCs
#define ADC_NUMBER     4 // MAX 8

#define PIN_ADC0       A0
#define PIN_ADC1       A1
#define PIN_ADC2       A2
#define PIN_ADC3       A3
//#define PIN_ADC4     A4
//#define PIN_ADC5     A5
//#define PIN_ADC6     A6
//#define PIN_ADC7     A7

// OUTs
#define OUT_NUMBER      3

#define PIN_OUT0        6
#define PIN_OUT1        5
#define PIN_OUT2        4

//#define PIN_RS485_RXTX  XX

// INs
#define IN_NUMBER       3

#define PIN_IN0         9
#define PIN_IN1         8
#define PIN_IN2         7

// Status OUTs
#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

// Status Pull-up INs
#define PIN_IN_OFF        0   
#define PIN_IN_ON         1

// IO definition
#define IO_OFF            0
#define IO_ON             1

#define OUT_OFF           0
#define OUT_ON            1

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
