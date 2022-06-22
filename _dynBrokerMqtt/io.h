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
 *                    A0 -| A0    D0 |- GPIO16 
 *                    G  -| G     D1 |- GPIO5  
 *                    VU -| VU    D2 |- GPIO4  
 *                 GPIO9 -| S3    D3 |- GPIO0  
 *                 GPIO? -| S2    D4 |- GPIO2  -> LED*
 *          S1 <-   MOSI -| S1    3V |- 3V
 *                    CS -| SC     G |- G
 *          S0 <-   MISO -| SD    D5 |- GPIO14
 *                GPIO10 -| SK    D6 |- GPIO12 
 *                     G -| G     D7 |- GPIO13 
 *                    3V -| 3V    D8 |- GPIO15 
 *                    EN -| EN    RX |- GPIO3  
 *                   RST -| RST   TX |- GPIO1  
 *                     G -| G      G |- G
 *                   VIN -| VIN   3V |- 3V
 *                        ------------
 */

/* ----------------------------------
 *   |                      --------
 *   |__  |      RX -GPIO3 -||     º|- VCC----
 *    __| |          GPIO0 -|º     º|- RST   |
 *   |__  |          GPIO2 -|º     º|- CH_PD--
 *    __| |            GND -||     º|- GPIO1 - TX
 *   |____|                 --------
 *  ---------------------------------
 */
// PIN definition
//#define PIN_ADC_IN      A0  // Entrada
#define PIN_LED           1   // 1 - ESP01 // 2 - ESP8266

//#define PIN_A           14  // A

// OUTs
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
