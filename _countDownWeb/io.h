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
 *   |__  |      RX -GPIO3 -||     º|- VCC----
 *    __| |          GPIO0 -|º     º|- RST   |
 *   |__  |          GPIO2 -|º     º|- CH_PD--
 *    __| |            GND -||     º|- GPIO1 - TX
 *   |____|                 --------
 *  ---------------------------------
 */

// PIN definition
#define PIN_RELE          0  // GPIO0 - OUT
//#define PIN_LED         1  // GPIO1
#define PIN_LED_IND       1  //2  // GPIO2 - LED IND
#define PIN_AUX1          3  // GPIO3 - IN

#define PIN_OUT_ON        1
#define PIN_OUT_OFF       0

#define PIN_IN_OFF        0

// IO definition
#define IN_ON             1
#define IN_OFF            0

#define OUT_ON            1
#define OUT_OFF           0

#define IN_STATUS_OFF     0
#define IN_STATUS_ON      1

#define INDEX_AUX1        0

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
