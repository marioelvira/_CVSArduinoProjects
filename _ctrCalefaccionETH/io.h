
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////
/* Strapping: GPIO34, 35, 36, 37 y 38 */

/*                                    |--------|
 *                              ------| USB  C |------
 *                              |     |--------|     |
 *                              |                    |
 *      (Reset Quemador) O5 <- -| GPIO54        VUBS |-
 *       (Bomba Drenaje) O3 <- -| GPIO19        VSYS |-
 *                             -| GND            GND |-
 *                       AUX # -| GPIO18          EN |-
 *                       AUX # -| GPIO17         3V3 |-
 *                       AUX # -| GPIO16      GPIO20 |- # AUX
 *   (Bomba Recirc Agua) O4 <- -| GPIO15      GPIO21 |- # AUX
 *                             -| GND            GND |-
 *                 (RL1) O6 <- -| GPIO14      GPIO22 |- <- ZD1 (Detector de paso por cero)
 *                             -| GPIO06      GPIO23 |- # AUX
 *            (In Aux1) IN1 -> -| GPIO05*        RUN |- System Control
 *            (In Aux2) IN2 -> -| GPIO04*     GPIO26 |- -> LED (Estado)
 *                             -| GND            GND |-
 *         (In On Fire) IN3 -> -| GPIO03*     GPIO27 |- -> TR3 (Res. Auxiliar)
 *      (In Termostato) IN4 -> -| GPIO02*     GPIO32 |- -> TR2 (Res. Inyector)
 *                       DIO # -| SCL/GPIO08  GPIO33 |- -> TR1 (Res. Principal)
 *                       DIO # -| SCL/GPIO07  GPIO46 |- -> RTS_RS485
 *                             -| GND            GND |-
 *            (Out Aux1) O1 <- -| DM/GPIO24   GPIO47 |- -> TX_RS485
 *            (Out Aux2) O2 <- -| DP/GPIO25   GPIO48 |- <- RX_RS485
 *                             -|                    |-
 *                             -|    ------------    |-
 *                             -|    |          |    |-
 *                             -|    |   ETH    |    |-
 *                             -|    |          |    |-
 *                              ----------------------
 */

////////////////////
// PIN definition //
////////////////////

// LED
#define PIN_LED         26

// OUTs
#define OUT_NUMBER      7
#define PIN_OUT1        24  // O1 24
#define PIN_OUT2        25  // O2 25
#define PIN_OUT3        19  // O3 19 Bomba Achique
#define PIN_OUT4        15  // O4 15 Bomba Recirc
#define PIN_OUT5        54  // O5 54 
#define PIN_OUT6        14  // RL1 14 Reset Quemador
#define PIN_OUT7        6   // RL2 06

#define TRIAC_NUMBER    3
#define PIN_TRIAC1      33
#define PIN_TRIAC2      32
#define PIN_TRIAC3      27

// INs
#define IN_NUMBER       4
#define PIN_IN1         5
#define PIN_IN2         4
#define PIN_IN3         3
#define PIN_IN4         2

// ZDs
#define PIN_ZD1         22

// RS485
#define PIN_RS485_RX    48
#define PIN_RS485_TX    47
#define PIN_RS485_RXTX  46

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

#if (_USE_LED_ == 1)
extern int   boardLed;
#endif

extern int   OutPin[];
extern int   OutDig[];
extern int   InPin[];
extern int   InDig[];

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
