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
 *                    A0 -|      |- GPIO16 -> GEN
 *                    G  -|      |- GPIO5  -> DISP
 *                    VU -|      |- GPIO4  -> ZUMB
 *         AS3 <- GPIO10 -|      |- GPIO0  <- PULSADOR
 *         AS2 <-  GPIO9 -|      |- GPIO2  -> LED INTERNO*
 *          S1 <-   MOSI -|      |- 3V
 *                    CS -|      |- G
 *          S0 <-   MISO -|      |- GPIO14 -> D3
 *          SK <-   SCLK -|      |- GPIO12 -> D4
 *                     G -|      |- GPIO13 -> D5
 *                    3V -|      |- GPIO15 -> D6
 *                    EN -|      |- GPIO3 
 *                   RST -|      |- GPIO1
 *                     G -|      |- G
 *                   VIN -|      |- 3V
 *                        --------
 */

/*
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

#define PIN_LED           2
*/


/*
 *                        --------
 *                    A0 -|      |- GPIO16 -> LED EXT
 *                    G  -|      |- GPIO5  -> GEN
 *                    VU -|      |- GPIO4  -> D3
 *         AS3 <- GPIO10 -|      |- GPIO0  -> D4
 *         AS2 <-  GPIO9 -|      |- GPIO2  -> D5
 *          S1 <-   MOSI -|      |- 3V
 *                    CS -|      |- G
 *          S0 <-   MISO -|      |- GPIO14 -> D6
 *          SK <-   SCLK -|      |- GPIO12 -> DISP
 *                     G -|      |- GPIO13 <- PULSADOR
 *                    3V -|      |- GPIO15 -> ZUMB
 *                    EN -|      |- GPIO3  
 *                   RST -|      |- GPIO1  
 *                     G -|      |- G
 *                   VIN -|      |- 3V
 *                        --------
 */

#define PIN_GEN           5
#define PIN_DISP          12   
#define PIN_ZUMB          15
#define PIN_D3            4
#define PIN_D4            0
#define PIN_D5            2
#define PIN_D6            14
#define PIN_PULSADOR      13

#define PIN_LED           16

#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

#define PIN_IN_OFF        1 // 1

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
