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
 *                    A0 -|      |- GPIO16 -> D0 -> RELE CORTE
 *                    G  -|      |- GPIO5  -> D1 <- AUX1
 *                    VU -|      |- GPIO4  -> D2 <- AUX2
 *         AS3 <- GPIO10 -|      |- GPIO0  -> D3 - FLASH (No usar)
 *         AS2 <-  GPIO9 -|      |- GPIO2  -> D4 -> LED*
 *          S1 <-   MOSI -|      |- 3V
 *                    CS -|      |- G
 *          S0 <-   MISO -|      |- GPIO14 -> D5 <- AGUA
 *          SK <-   SCLK -|      |- GPIO12 -> D6 -> ALARMA
 *                     G -|      |- GPIO13 -> D7 <- ACEITE
 *                    3V -|      |- GPIO15 -> D8 <- MOTOR MARCHA
 *                    EN -|      |- GPIO3  -> RX
 *                   RST -|      |- GPIO1  -> TX
 *                     G -|      |- G
 *                   VIN -|      |- 3V
 *                        --------
 */

// PIN definition
#define PIN_MOTOR         15  // inValue[4]
#define PIN_RELE_CORTE    16
#define PIN_LED            2
#define PIN_AGUA          14  // inValue[0]
#define PIN_ALARMA        12  
#define PIN_ACEITE        13  // inValue[1]
#define PIN_AUX1          5//10  // inValue[2]
#define PIN_AUX2          4// 9  // inValue[3]

#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

#define PIN_IN_OFF        1

// IO definition
#define IN_ON             1
#define IN_OFF            0

#define OUT_ON            1
#define OUT_OFF           0

#define IN_STATUS_INIT    0
#define IN_STATUS_ON      1
#define IN_STATUS_OFF     2

#define INDEX_AGUA        0
#define INDEX_ACEITE      1
#define INDEX_AUX1        2
#define INDEX_AUX2        3
#define INDEX_MOTOR       4

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
