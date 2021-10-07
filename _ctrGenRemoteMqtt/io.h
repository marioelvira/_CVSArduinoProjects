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
 *                    A0 -|      |- GPIO16 <-- A
 *                    G  -|      |- GPIO5  <-- B
 *                    VU -|      |- GPIO4  <-- C
 *                GPIO10 -|      |- GPIO0  <-- D
 *                 GPIO9 -|      |- GPIO2  --> LED*
 *          S1 <-   MOSI -|      |- 3V
 *                    CS -|      |- G
 *          S0 <-   MISO -|      |- GPIO14 --> REM PULS
 *          SK <-   SCLK -|      |- GPIO12
 *                     G -|      |- GPIO13 <-- BOMBAA
 *                    3V -|      |- GPIO15
 *                    EN -|      |- GPIO3  
 *                   RST -|      |- GPIO1  
 *                     G -|      |- G
 *                   VIN -|      |- 3V
 *                        --------
 */

// PIN definition
#define PIN_VBATT_IN      A0  // Entrada

#define PIN_A             16  // A
#define PIN_B             5   // B
#define PIN_C             4   // C
#define PIN_D             0   // D
#define PIN_LED           2

#define PIN_RPULS         14

#define PIN_BOMBAA        10

#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

#define VBATT_ARRAY_SIZE  5

// Pull-up INs
#define PIN_IN_OFF        1   
#define PIN_IN_ON         0

// IO definition
#define IO_ON             1
#define IO_OFF            0

#define OUT_OFF           0
#define OUT_ON            1

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
