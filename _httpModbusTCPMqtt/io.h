#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

#include "main.h"

///////////////////
// IO definition //
///////////////////

/* ----------------------------------
 *   |                      --------
 *   |__  |      RX -GPIO3 -||     º|- VCC----
 *    __| |          GPIO0 -|º     º|- RST   |
 *   |__  |          GPIO2 -|º     º|- CH_PD--
 *    __| |            GND -||     º|- GPIO1 - TX
 *   |____|                 --------
 *  ---------------------------------
 */

#if (ROOM_PINOUT == 1)
#define PIN_OUTA          1
#define PIN_LED           2
#define PIN_INA           3
#endif

#if (ELIGHT_PINOUT == 1)
#define PIN_OUTA          0
#define PIN_LED           2
#define PIN_INA           3
#endif

/*
 *                         ----------
 *                    A0 -| A0    D0 |- GPIO16 -> OA
 *                    G  -| G     D1 |- GPIO5  -> OB
 *                    VU -| VU    D2 |- GPIO4  -> OC
 *                 GPIO9 -| S3    D3 |- GPIO0  -> 
 *                 GPIO? -| S2    D4 |- GPIO2  -> LED*
 *          S1 <-   MOSI -| S1    3V |- 3V
 *                    CS -| SC     G |- G
 *          S0 <-   MISO -| SD    D5 |- GPIO14 <- A
 *           E -> GPIO10 -| SK    D6 |- GPIO12 <- B
 *                     G -| G     D7 |- GPIO13 <- C
 *                    3V -| 3V    D8 |- GPIO15 <- D
 *                    EN -| EN    RX |- GPIO3  
 *                   RST -| RST   TX |- GPIO1  
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
#if (LOLIN_PINOUT == 1)
#define PIN_LED         2
#define PIN_OUTA        16
//#define PIN_OUTB      5
//#define PIN_OUTC      4
#define PIN_INA         14
//#define PIN_INB       12
//#define PIN_INC       13
#endif

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
