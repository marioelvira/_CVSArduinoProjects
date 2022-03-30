#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////

/*
 *                         ----------                                         ----------------
 *                    A0 -| A0    D0 |- GPIO16 <- BUSY ------------- <- BUSY -|              |
 *                    G  -| G     D1 |- GPIO5  -> RES  ------------- -> RES  -|              |
 *                    VU -| VU    D2 |- GPIO4  -> DC   ------------- -> DC   -|              |
 *                 GPIO9 -| S3    D3 |- GPIO0  -> GEN    |---------- -> CS   -|     EPD      |
 *                 GPIO? -| S2    D4 |- GPIO2 * LED      | |-------- -> SCK  -|              |
 *                  MOSI -| S1    3V |- 3V               | | |------ -> SDI  -|              |
 *                    CS -| SC     G |- G                | | | |---- -> GND  -|              |
 *                  MISO -| SD    D5 |- GPIO14 -> CS   --| | | | |-- -> 3V3  -|              |
 *                GPIO10 -| SK    D6 |- GPIO12 -> SCK  ----| | | |            ----------------
 *                     G -| G     D7 |- GPIO13 -> SDI  ------| | |
 *                    3V -| 3V    D8 |- GPIO15 <- PULSADOR     | |
 *                    EN -| EN    RX |- GPIO3                  | |
 *                   RST -| RST   TX |- GPIO1                  | |
 *                     G -| G      G |- G              --------| |
 *                   VIN -| VIN   3V |- 3V             ----------|
 *                        ------------
 */


// PIN definition
#define PIN_LED         2

#define PIN_GEN         0
#define PIN_PULSADOR    15

// EPD Pinout
#define BUSY_Pin      D0
#define RES_Pin       D1
#define DC_Pin        D2
#define CS_Pin        D5
#define SCK_Pin       D6
#define SDI_Pin       D7

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
