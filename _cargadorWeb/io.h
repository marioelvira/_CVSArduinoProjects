#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////
/* ----------------------------------
 *   |                      --------
 *   |__  |     GPIO3 - RX -|7    8|- VCC-----
 *    __| |          GPIO0 -|5    6|- RST    |
 *   |__  |    LED - GPIO2 -|3    4|- CH_PD---
 *    __| |            GND -|1*   2|- GPIO1 - TX
 *   |____|                 --------
 *  ---------------------------------
 */

// PIN definition
#define PIN_RELE_CORTE    1  // OUT
//#define PIN_LED         2
#define PIN_LED_IND       2 // LED IND
#define PIN_AUX1          3 // IN

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

#define INDEX_AUX1        0

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
