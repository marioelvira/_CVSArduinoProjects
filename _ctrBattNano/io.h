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
 *               SCL/D19 -| A5        D4 |-                 <- IN1 - IN CLOCK
 *                   D20 -| A6  [  ]  D3 |- INT1 (PWM)      <- IN0 - PULSADOR
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
#define ADC_NUMBER     2 // MAX 8

#define PIN_ADC0       A0
#define PIN_ADC1       A1
//#define PIN_ADC2     A2
//#define PIN_ADC3     A3

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

#define PIN_IN0         4
#define PIN_IN1         3

// Status OUTs
#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

// Status Pull-up INs
#define PIN_IN_OFF        1
#define PIN_IN_ON         0

// IO definition
#define IO_OFF            0
#define IO_ON             1

#define OUT_OFF           0
#define OUT_ON            1

// States and Times
#define IO_LOOP_TICK      100   // 100ms
#define NO_PULS           0

#define TOOLONG_PULS      100   // x100ms
#define LONG_PULS         10    // x100ms
#define SHORT_PULS        1     // x100ms
//#define TOOSHORT_PULS   0     // x100ms

#define IN_UP             1//0
#define IN_DOWN           0//1

#define IN_PULS_STANDBY  0
#define IN_PULS_FLANCO   1
#define IN_PULS_CTR      2

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
