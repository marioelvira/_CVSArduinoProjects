
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////
/* Strapping: GPIO34,35, 36, 37 y 38   */
/*                              |--------|
 *                        ------| USB  C |------
 *                        |     |--------|     |
 *                        |                    |
 *               OUT0 <- -| GPIO54        VUBS |-
 *               OUT1 <- -| GPIO19        VSYS |-
 *                       -| GND            GND |-
 *               IN0 ->  -| GPIO18          EN |-
 *               IN1 ->  -| GPIO17         3V3 |-
 *                       -| GPIO16      GPIO20 |- -> Led status
 *                       -| GPIO15      GPIO21 |-
 *                       -| GND            GND |-
 *                       -| GPIO14      GPIO22 |-
 *                       -| GPIO06      GPIO23 |-
 *                       -| GPIO05         RUN |- System Control
 *               PWM0 <- -| GPIO04      GPIO26 |-
 *                       -| GND            GND |-
 *                TR0 <- -| GPIO03      GPIO27 |-
 *                 ZC -> -| GPIO02      GPIO32 |-
 *                       -| SCL/GPIO08  GPIO33 |-
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
#define PIN_LED        20 // Pin J1 - GPIO20

// OUTs
#define OUT_NUMBER      2

#define PIN_OUT0        54
#define PIN_OUT1        19

#define PIN_TR0         3

#define PIN_PWM0        4

//#define PIN_RS485_RXTX  X

// INs
#define IN_NUMBER       2

#define PIN_IN0         17
#define PIN_IN1         18

#define PIN_ZC          2

// Status OUTs
#define PIN_OUT_ON     1
#define PIN_OUT_OFF    0

// Status Pull-up INs
//#define PIN_IN_OFF      1
//#define PIN_IN_ON       0

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
