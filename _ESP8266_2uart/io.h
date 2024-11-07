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
 *                    A0 -| A0    D0 |- GPIO16 -> OA
 *                    G  -| G     D1 |- GPIO5  -> RXTX0
 *                    VU -| VU    D2 |- GPIO4  -> RXTX2
 *                 GPIO9 -| S3    D3 |- GPIO0  -> OB
 *                 GPIO? -| S2    D4 |- GPIO2  -> LED*
 *          S1 <-   MOSI -| S1    3V |- 3V
 *                    CS -| SC     G |- G
 *          S0 <-   MISO -| SD    D5 |- GPIO14 <- IA
 *           E -> GPIO10 -| SK    D6 |- GPIO12 <- IB
 *                     G -| G     D7 |- GPIO13 <- RXD2
 *                    3V -| 3V    D8 |- GPIO15 -> TXD2
 *                    EN -| EN    RX |- GPIO3 <- RXD0
 *                   RST -| RST   TX |- GPIO1 -> TXD0
 *                     G -| G      G |- G
 *                   VIN -| VIN   3V |- 3V
 *                        ------------
 */

/*
Pins used during Boot
The ESP8266 can be prevented from booting if some pins are pulled LOW or HIGH.
The following list shows the state of the following pins on BOOT:

 GPIO0: boot failure if pulled LOW
 GPIO2: pin is high on BOOT, boot failure if pulled LOW
 GPIO15: boot failure if pulled HIGH
 GPIO1: pin is high at BOOT, boot failure if pulled LOW
 GPIO16: pin is high at BOOT
 GPIO10: pin is high at BOOT
 GPIO9: pin is high at BOOT
 GPIO3: pin is high at BOOT
*/

// PIN definition
#define PIN_LED             2

//#define PIN_OA            16
//#define PIN_OB            0

//#define PIN_A             14
//#define PIN_B             12

#define PIN_RXTX_INV      5 // D1 
#define PIN_RXTX_OF       4 // D2

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

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
