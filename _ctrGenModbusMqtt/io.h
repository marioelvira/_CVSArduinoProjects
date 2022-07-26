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
 *                    A0 -| A0    D0 |- GPIO16 -> LUZ OFF
 *                    G  -| G     D1 |- GPIO5  -> GEN STOP
 *                    VU -| VU    D2 |- GPIO4  -> GEN PULS
 *                 GPIO9 -| S3    D3 |- GPIO0  -> 
 *                 GPIO? -| S2    D4 |- GPIO2  -> LED*
 *          S1 <-   MOSI -| S1    3V |- 3V
 *                    CS -| SC     G |- G
 *          S0 <-   MISO -| SD    D5 |- GPIO14 <- A
 *      GEN ON -> GPIO10 -| SK    D6 |- GPIO12 <- B
 *                     G -| G     D7 |- GPIO13 <- C
 *                    3V -| 3V    D8 |- GPIO15 <- D
 *                    EN -| EN    RX |- GPIO3  
 *                   RST -| RST   TX |- GPIO1  
 *                     G -| G      G |- G
 *                   VIN -| VIN   3V |- 3V
 *                        ------------
 */

// PIN definition
#define PIN_VBATT_IN      A0  // Entrada

#define PIN_STOP_PULS     5
#define PIN_GEN_PULS      4
#define PIN_LUZ_OFF       16 // 0
#define PIN_LED           2

#define PIN_A             14  // A
#define PIN_B             12  // B
#define PIN_C             13  // C
#define PIN_D             15  // D

#define PIN_GENON         10

#define PIN_RS485_RXTX    0

#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

#define VBATT_ARRAY_SIZE  5

// Pull-up INs
#define PIN_IN_OFF        0   
#define PIN_IN_ON         1

// IO definition
#define IO_ON             1
#define IO_OFF            0

#define OUT_OFF           0
#define OUT_ON            1

//#define VBATT_DIG_OFFSET        0     // Digital Offset
//#define VBATT_DIG_EOS           1024  // Digital End Of Scale
//#define VBATT_ANA_EOS           24    // Analog Enf Of Scale

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
