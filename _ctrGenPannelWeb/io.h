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
 *                    A0 -|      |- GPIO16 -> D0 -> GEN
 *                    G  -|      |- GPIO5  -> D1 -> DISP
 *                    VU -|      |- GPIO4  -> D2 -> ZUMB
 *         AS3 <- GPIO10 -|      |- GPIO0  -> D3 <- PULSADOR
 *         AS2 <-  GPIO9 -|      |- GPIO2  -> D4 -> LED*
 *          S1 <-   MOSI -|      |- 3V
 *                    CS -|      |- G
 *          S0 <-   MISO -|      |- GPIO14 -> D5 -> D3
 *          SK <-   SCLK -|      |- GPIO12 -> D6 -> D4
 *                     G -|      |- GPIO13 -> D7 -> D5
 *                    3V -|      |- GPIO15 -> D8 -> D6
 *                    EN -|      |- GPIO3  -> RX
 *                   RST -|      |- GPIO1  -> TX
 *                     G -|      |- G
 *                   VIN -|      |- 3V
 *                        --------
 */

// PIN definition
#define PIN_GEN           16
#define PIN_DISP          5    
#define PIN_ZUMB          4     
#define PIN_D3            14
#define PIN_D4            12
#define PIN_D5            13
#define PIN_D6            15
#define PIN_PULSADOR      0
//#define PIN_LED_STATUS  9

#define PIN_LED            2

#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

#define PIN_IN_OFF        1

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
