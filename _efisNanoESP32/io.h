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
 *        (LED*) SPI-SCK -| D13      D12 |- -> OUT4
 *             (OUT) 3V3 -| 3V3      D11 |- -> OUT2
 *                       -| B1       D10 |- -> OUT1 
 *                  ADC0 -| A0        D9 |- -> OUT0
 *                  ADC1 -| A1        D8 |- <- IN3 
 *                  ADC2 -| A2        D7 |- <- IN2
 *                  ADC3 -| A3        D6 |- <- IN1
 *                  ADC4 -| A4        D5 |- <- IN0 
 *                  ADC5 -| A5        D4 |-                 
 *                  ADC6 -| A6        D3 |- <- INT1 
 *                  ADC7 -| A7  ****  D2 |- <- INT0
 *            (OUT) VUSB -| VU  **** GND |- GND  
 *                 RESET -| RST **** RST |-   
 *                   GND -| GND **** RX0 |- UART IN
 *                   VIN -| 5V       TX1 |- UART OUT  
 *                        ---------------
 */

// PIN definition
#define PIN_RGB_B         16
#define PIN_RGB_G         15
#define PIN_RGB_R         14

#define PIN_LED_BUILTIN  13

#define PIN_D12          12
#define PIN_D11          11
#define PIN_D10          10
#define PIN_D09           9
#define PIN_D08           8
#define PIN_D07           7
#define PIN_D06           6
#define PIN_D05           5
#define PIN_D04           4
#define PIN_D03           3
#define PIN_D02           2

#define PIN_A0           A0
#define PIN_A1           A1
#define PIN_A2           A2
#define PIN_A3           A3
#define PIN_A4           A4
#define PIN_A5           A5
#define PIN_A6           A6
#define PIN_A7           A7

// PIN Asignation
#define PIN_LED        PIN_LED_BUILTIN

// ADCs
#define ADC_NUMBER      4 // MAX 8

// OUTs
#define OUT_NUMBER      4

#define PIN_OUT0        PIN_D09
#define PIN_OUT1        PIN_D10
#define PIN_OUT2        PIN_D11
#define PIN_OUT3        PIN_D12

// INs
#define IN_NUMBER       4

#define PIN_IN0         PIN_D05
#define PIN_IN1         PIN_D06
#define PIN_IN2         PIN_D07
#define PIN_IN3         PIN_D08

// Config OUTs
#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

#define RGB_OUT_ON        0
#define RGB_OUT_OFF       1

// Config Pull-up INs
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
