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
 *                   LED -| D13      D12 |- -> OUTD
 *                       -| 3V3      D11 |- -> OUTC
 *                       -| AREF     D10 |- -> OUTB
 *             CURRENT 1 -| A0        D9 |- -> OUTA
 *             CURRENT 2 -| A1        D8 |- <- IN3
 *                    V1 -| A2        D7 |- <- IN2
 *                    V2 -| A3        D6 |- <- IN1
 *                 AAUX1 -| A4        D5 |- <- IN0
 *                 AAUX2 -| A5        D4 |- <- RS485 RX_TX
 *                 AAUX2 -| A6  [  ]  D3 |- <- INT 1
 *                 AAUX4 -| A7  ****  D2 |- <- INT 0
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
#define IRMS_NUMBER    2

// ADCs
#define ADC_NUMBER     4 // MAX 8

#define PIN_ADC0       A0
#define PIN_ADC1       A1
#define PIN_ADC2       A2
#define PIN_ADC3       A3

// OUTs
#define OUT_NUMBER      4

#define PIN_OUTA        9
#define PIN_OUTB        10
#define PIN_OUTC        11
#define PIN_OUTD        12

#define PIN_RS485_RXTX  4

// INs
#define IN_NUMBER       4

#define PIN_IN0         5
#define PIN_IN1         6
#define PIN_IN2         7
#define PIN_IN3         8

// INTs
#define PIN_INT0        2
#define PIN_INT1        3

// Status OUTs
#define PIN_OUT_ON      1
#define PIN_OUT_OFF     0

// Status Pull-up INs
#define PIN_IN_OFF      1
#define PIN_IN_ON       0

// IO definition
#define IN_OFF          0
#define IN_ON           1

#define OUT_OFF         0
#define OUT_ON          1

// States and Times
//#define IO_LOOP_TICK      100   // 100ms

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
