#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////

/*                           |--------|
 *                        ---|   USB  |--- 
 *                        |  |--------|  |
 *                        |              |
 *        (LED*) SPI-SCK -| D13      D12 |- SPI-MISO        -> OUTDP
 *                       -| 3V3      D11 |- SPI-MOSI (PWM)  -> OUTG
 *                       -| AREF     D10 |- SPI-SS   (PWM)  -> OUTF
 *                   D14 -| A0        D9 |- PWM      (PWM)  -> OUTE
 *                   D15 -| A1        D8 |-                 -> OUTD
 *                   D16 -| A2        D7 |-                 -> OUTC
 *                   D17 -| A3        D6 |- (PWM)           -> OUTB
 *               SDA/D18 -| A4        D5 |- (PWM)           -> OUTA
 *               SCL/D19 -| A5        D4 |-                 <- IN1
 *                   D20 -| A6  [  ]  D3 |- INT1 (PWM)      <- IN0 
 *                   D21 -| A7  ****  D2 |- INT0            -> OUT RELE
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

// OUTs
#define OUT_NUMBER      9

#define PIN_OUTA        5
#define PIN_OUTB        6
#define PIN_OUTC        7
#define PIN_OUTD        8
#define PIN_OUTE        9
#define PIN_OUTF        10
#define PIN_OUTG        11
#define PIN_OUTDP       12
#define PIN_OUTRELE     2

//#define PIN_RS485_RXTX  4

// INs
#define IN_NUMBER       2

#define PIN_IN0         3
#define PIN_IN1         4

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
