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
 *        (LED*) SPI-SCK -| D13      D12 |- SPI-MISO        <- END
 *                       -| 3V3      D11 |- SPI-MOSI (PWM)  <- PULS
 *                       -| AREF     D10 |- SPI-SS   (PWM)  -> DISP
 *                   D14 -| A0        D9 |- PWM      (PWM)  -> GEN
 *                   D15 -| A1        D8 |-                 -> ZUMB
 *                   D16 -| A2        D7 |-                 -> A
 *                   D17 -| A3        D6 |- (PWM)           -> B
 *               SDA/D18 -| A4        D5 |- (PWM)           -> C
 *               SCL/D19 -| A5        D4 |-                 -> D
 *                   D20 -| A6  [  ]  D3 |- INT1 (PWM)      <- 
 *                   D21 -| A7  ****  D2 |- INT0            <-
 *                    5V -| 5V       GND |- GND  
 *                 RESET -| RST      RST |-   
 *                   GND -| GND      RX0 |- UART IN
 *                   VIN -| 5V       TX1 |- UART OUT  
 *                        ---------------
 */

// PIN definition
#define PIN_ADC0_IN       A0  // Entrada

#define PIN_A             4  // A
#define PIN_B             5  // B
#define PIN_C             6  // C
#define PIN_D             7  // D

#define PIN_ZUMB          8
#define PIN_GEN           9
#define PIN_DISP          10

#define PIN_PULSADOR      11
#define PIN_END           12

#define PIN_LED           13  // PIN LED NANO

#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

// Pull-up INs
#define PIN_IN_OFF        1   
#define PIN_IN_ON         0

// IO definition
#define IO_ON             1
#define IO_OFF            0

#define OUT_OFF           0
#define OUT_ON            1

#define IN_STATUS_INIT    0
#define IN_STATUS_ON      1
#define IN_STATUS_OFF     2

// Pulsación
#define NO_PULSACION        0   // x10ms
#define PULSACION_OK        75  // x10ms

#define FLANCO_UP     0
#define FLANCO_DOWN   1
#define FLANCO        FLANCO_UP  // FLANCO_DOWN

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
