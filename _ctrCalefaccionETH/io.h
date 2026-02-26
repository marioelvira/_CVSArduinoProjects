
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////
/* Strapping: GPIO34, 35, 36, 37 y 38 */
/*                              |--------|
 *                        ------| USB  C |------
 *                        |     |--------|     |
 *                        |                    |
 *               OUT0 <- -| GPIO54        VUBS |-
 *               OUT1 <- -| GPIO19        VSYS |-
 *                       -| GND            GND |-
 *                ADC IO -| GPIO18          EN |-
 *                ADC IO -| GPIO17         3V3 |-
 *                ADC IO -| GPIO16      GPIO20 |- IO ADC
 *               OUT3 <- -| GPIO15      GPIO21 |- IO ADC -> PWM DBG
 *                       -| GND            GND |-
 *               OUT4 <- -| GPIO14      GPIO22 |- IO ADC <- ZD0
 *                       -| GPIO06      GPIO23 |- IO ADC <- ZD1
 *                IN3 -> -| GPIO05*        RUN |- System Control
 *                IN2 -> -| GPIO04*     GPIO26 |- -> LED
 *                       -| GND            GND |-
 *                IN1 -> -| GPIO03*     GPIO27 |- -> TR2
 *                IN0 -> -| GPIO02*     GPIO32 |- -> TR1
 *                       -| SCL/GPIO08  GPIO33 |- -> TR0
 *                       -| SCL/GPIO07  GPIO46 |- -> RTS_RS485
 *                       -| GND            GND |-
 *                       -| DM/GPIO24   GPIO47 |- <- RX_RS485
 *                       -| DP/GPIO25   GPIO48 |- -> TX_RS485
 *                       -|                    |-
 *                       -|    ------------    |-
 *                       -|    |          |    |-
 *                       -|    |   ETH    |    |-
 *                       -|    |          |    |-
 *                        ----------------------
 */

////////////////////
// PIN definition //
////////////////////

// LED
#define PIN_LED         26

// OUTs
#define OUT_NUMBER      4
#define PIN_OUT0        54
#define PIN_OUT1        19
#define PIN_OUT2        15
#define PIN_OUT3        14

//#define TR_NUMBER       3
#define PIN_TR0         33
//#define PIN_TR1         32
//#define PIN_TR2         27

// INs
#define IN_NUMBER       4
#define PIN_IN0         2
#define PIN_IN1         3
#define PIN_IN2         4
#define PIN_IN3         5

// ZDs
#define ZD_NUMBER       2
#define PIN_ZD0         22
//#define PIN_ZD1         23

//#define PIN_RS485_RXTX  46
//#define PIN_RS485_RX    47
//#define PIN_RS485_RX    48

// PWM
#define PIN_PWM0        21

///////////////
// PIN Logic //
///////////////
// Status OUTs
#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0
// Status Pull-up INs
//#define PIN_IN_OFF      1
//#define PIN_IN_ON       0

///////////////////
// IO definition //
///////////////////
#define IN_OFF            0
#define IN_ON             1

#define OUT_OFF           0
#define OUT_ON            1

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
