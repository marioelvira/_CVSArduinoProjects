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
 *                    A0 -|      |- GPIO16 <-- BOMBA
 *                    G  -|      |- GPIO5  <-- A
 *                    VU -|      |- GPIO4  <-- B
 *                GPIO10 -|      |- GPIO0  --> GEN PULS
 *                 GPIO9 -|      |- GPIO2  --> LED*
 *          S1 <-   MOSI -|      |- 3V
 *                    CS -|      |- G
 *          S0 <-   MISO -|      |- GPIO14 <-- C
 *          SK <-   SCLK -|      |- GPIO12 <-- D
 *                     G -|      |- GPIO13 --> BOM PULS
 *                    3V -|      |- GPIO15
 *                    EN -|      |- GPIO3  
 *                   RST -|      |- GPIO1  
 *                     G -|      |- G
 *                   VIN -|      |- 3V
 *                        --------
 */

// PIN definition
#define PIN_VBATT_IN      A0  // Entrada

#define PIN_BOMBA         16

#define PIN_A             5   // A
#define PIN_B             4   // B
#define PIN_C             14  // C
#define PIN_D             12  // D

#define PIN_GEN_PULS      0
#define PIN_LED           2

#define PIN_BOM_PULS      13

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

#define VBATT_DIG_OFFSET          0     // Digital Offset
#define VBATT_DIG_EOS             1024  // Digital End Of Scale
#define VBATT_ANA_EOS             2400  // Analog Enf Of Scale
#define VBATT_SCALE               100

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
