#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////

/*
 *                        ----------
 *                    A0 -| A0    D0 |- GPIO16 -> A
 *                    G  -| G     D1 |- GPIO5  -> B
 *                    VU -| VU    D2 |- GPIO4  -> C
 *       BOMBA <- *GPIO9 -| S3    D3 |- GPIO0  -> D
 *                 GPIO? -| S2    D4 |- GPIO2  -> ZUMB* // LED
 *          S1 <-   MOSI -| S1    3V |- 3V
 *                    CS -| SC     G |- G
 *          S0 <-   MISO -| SD    D5 |- GPIO14 -> GEN
 *       RESET ->*GPIO10 -| SK    D6 |- GPIO12 -> DISP
 *                     G -| G     D7 |- GPIO13 <- PULSADOR
 *                    3V -| 3V    D8 |- GPIO15 -> AUTOOFF
 *                    EN -| EN    RX |- GPIO3  
 *                   RST -| RST   TX |- GPIO1  
 *                     G -| G      G |- G
 *                   VIN -| VIN   3V |- 3V
 *                        ------------
 */

// PIN definition
#define PIN_A             16  // A
#define PIN_B             5   // B
#define PIN_C             4   // C
#define PIN_D             0   // D

#define PIN_ZUMB          2
#define PIN_LED           2

#define PIN_GEN           14
#define PIN_DISP          12

#define PIN_PULSADOR      13
#define PIN_END           10  // Cambiar a 9

#define PIN_AUTOON        15
#define PIN_BOMBA         9   // Cambiar a 10

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
