#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////

/*
 *                        --------
 *                    A0 -|      |- GPIO16 -> A
 *                    G  -|      |- GPIO5  -> B
 *                    VU -|      |- GPIO4  -> C
 *       BOMBA <- GPIO10 -|      |- GPIO0  -> D
 *       RESET ->  GPIO9 -|      |- GPIO2  -> ZUMB*
 *          S1 <-   MOSI -|      |- 3V
 *                    CS -|      |- G
 *          S0 <-   MISO -|      |- GPIO14 -> GEN
 *          SK <-   SCLK -|      |- GPIO12 -> DISP
 *                     G -|      |- GPIO13 <- PULSADOR
 *                    3V -|      |- GPIO15 -> AUTOOFF
 *                    EN -|      |- GPIO3  
 *                   RST -|      |- GPIO1  
 *                     G -|      |- G
 *                   VIN -|      |- 3V
 *                        --------
 */

// PIN definition
#define PIN_A             16  // A
#define PIN_B             5   // B
#define PIN_C             4   // C
#define PIN_D             0   // D

#define PIN_ZUMB          2

#define PIN_GEN           14
#define PIN_DISP          12

#define PIN_PULSADOR      13
#define PIN_END           9

#define PIN_AUTOON        15
#define PIN_BOMBA         10

//#define PIN_LED         2

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
#define AUTOMAN_FILTRO      25  // x10ms

#define FLANCO_UP     0
#define FLANCO_DOWN   1
#define FLANCO        FLANCO_UP  // FLANCO_DOWN

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
