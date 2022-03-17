#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

#include "main.h"

///////////////////
// IO definition //
///////////////////

/*
 *                         ----------
 *              NTC - A0 -| A0    D0 |- GPIO16 -> FAN
 *                    G  -| G     D1 |- GPIO5  -> CLOSE
 *                    VU -| VU    D2 |- GPIO4  -> OPEN
 *                 GPIO9 -| S3    D3 |- GPIO0  -> PUMP
 *                 GPIO? -| S2    D4 |- GPIO2  -> LED*
 *          S1 <-   MOSI -| S1    3V |- 3V
 *                    CS -| SC     G |- G
 *          S0 <-   MISO -| SD    D5 |- GPIO14 -> AUX1
 *         IRR <- GPIO10 -| SK    D6 |- GPIO12 -> AUX2
 *                     G -| G     D7 |- GPIO13 <- INCLOSE
 *                    3V -| 3V    D8 |- GPIO15 <- INOPEN
 *                    EN -| EN    RX |- GPIO3  
 *                   RST -| RST   TX |- GPIO1  
 *                     G -| G      G |- G
 *                   VIN -| VIN   3V |- 3V
 *                        ------------
 */

// PIN definition
#define PIN_NTC_IN      A0  // Entrada

#define PIN_FAN           16
#define PIN_CLOSE         5
#define PIN_OPEN          4
#define PIN_PUMP          0
#define PIN_LED           2

#define PIN_AUX1          14
#define PIN_AUX2          12

#define PIN_INCLOSE       13
#define PIN_INOPEN        15

#define PIN_IRRI          10

#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

// Pull-up INs
#define PIN_IN_OFF        0   
#define PIN_IN_ON         1

// IO definition
#define IO_ON             1
#define IO_OFF            0

#define OUT_OFF           0
#define OUT_ON            1

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
