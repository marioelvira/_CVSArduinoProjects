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
 *          ETH -SPI-SCK -| D13      D12 |- SPI-MISO -ETH
 *                       -| 3V3      D11 |- SPI-MOSI - ETH
 *                       -| AREF     D10 |- SPI-SS - ETH
 *             CURRENT 1 -| A0        D9 |- <- IN1
 *             CURRENT 2 -| A1        D8 |- <- IN0
 *                    V1 -| A2        D7 |- -> OUTF (AUX)
 *                    V2 -| A3        D6 |- -> OUTE 5
 *                 AAUX1 -| A4        D5 |- -> OUTD 4
 *                 AAUX2 -| A5        D4 |- -> OUTC 3
 *                 AAUX2 -| A6  [  ]  D3 |- -> OUTB 2
 *                 AAUX4 -| A7  ****  D2 |- -> OUTA 1
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
#define OUT_NUMBER      6

#define PIN_OUTA        2
#define PIN_OUTB        3
#define PIN_OUTC        4
#define PIN_OUTD        5
#define PIN_OUTE        6
#define PIN_OUTF        7

//#define PIN_RS485_RXTX  4
#define PIN_SPI_CLK     13
#define PIN_SPI_MISO    12
#define PIN_SPI_MOSI    11
#define PIN_SPI_CS      10

// INs
#define IN_NUMBER       2

#define PIN_IN0         8
#define PIN_IN1         9

// Status OUTs
#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

// Status Pull-up INs
#define PIN_IN_OFF        1
#define PIN_IN_ON         0

// IO definition
#define IN_OFF            0
#define IN_ON             1

#define OUT_OFF           0
#define OUT_ON            1

// States and Times
//#define IO_LOOP_TICK      100   // 100ms

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
