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
 *                    A0 -|      |- GPIO16
 *                    G  -|      |- GPIO5  --> GEN STOP
 *                    VU -|      |- GPIO4  --> GEN PULS
 *                GPIO10 -|      |- GPIO0  --> LUZ OFF
 *                 GPIO9 -|      |- GPIO2  --> LED*
 *          S1 <-   MOSI -|      |- 3V
 *                    CS -|      |- G
 *          S0 <-   MISO -|      |- GPIO14 <-- A
 *          SK <-   SCLK -|      |- GPIO12 <-- B
 *                     G -|      |- GPIO13 <-- C
 *                    3V -|      |- GPIO15 <-- D
 *                    EN -|      |- GPIO3  
 *                   RST -|      |- GPIO1
 *                     G -|      |- G
 *                   VIN -|      |- 3V
 *                        --------
 */

// PIN definition
#define PIN_VBATT_IN      A0  // Entrada

#define PIN_STOP_PULS     5
#define PIN_GEN_PULS      4
#define PIN_LUZ_OFF       0
#define PIN_LED           2

#define PIN_A             14  // A
#define PIN_B             12  // B
#define PIN_C             13  // C
#define PIN_D             15  // D

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
#define VBATT_DIG_EOS             1024  // Digital End Of Scale
#define VBATT_ANA_EOS             24    // Analog Enf Of Scale

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
