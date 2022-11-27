#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////
// Board Select: ESP 32 Arduino -> DEV ESP32 Module

/*                       esp32-2432s028
 *                         ----------
 *                        |        39 |- GND
 *                   GND -| 1      38 |- GND
 *                  3V3  -| 2      37 |- IO23
 *               TFT RST -| 3      36 |- IO22  - IO2
 *              VP  IO36 -| 4      35 |- U0TXD
 *              VN  IO39 -| 5      34 |- U0RXD
 *           ANA0 - IO34 -| 6      33 |- IO21  - IO1
 *            IO3 - IO35 -| 7      32 |- 
 *                  IO32 -| 8      31 |- IO19
 *                  IO33 -| 9      30 |- IO18
 *                  IO25 -| 10     29 |- IO5
 *                  IO26 -| 11     28 |- IO17 - LED3
 *           ANA1 - IO27 -| 12     27 |- IO16 - LED2
 *                  IO14 -| 13     26 |- IO4  - LED1
 *                  IO12 -| 14     25 |- IO0
 *                   GND -| 15     24 |- IO2
 *                  IO13 -| 16     23 |- IO15
 *                   SD3 -| 17     22 |- SD1
 *                   SD2 -| 18     21 |- SDO
 *                   SCS -| 19     20 |- SCK
 *                        ------------
 */

/*
 * C1T
 * ---
 * 1 - 3V3  ----|      |----------> GND 
 * 2 - IO27     |------|----------> 5V
 * 3                   |  |-------> Vx
 * 4 - GND ------------|  |         Vy
 *                        |   |---> SW
 * P3                     |   |
 * --                     |   |
 * 1 - IO21 (No usar)     |   |
 * 2 - IO22 --------------|---|
 * 3 - IO35 --------------|
 * 4 - GND
 * 
 */

// PIN definition
#define PIN_LED1          4   // RED
#define PIN_LED2          16  // GREEN
#define PIN_LED3          17  // BLUE

#define PIN_CN12          27  // CN1: Pin 2

//#define PIN_P3P1        21  // P3: Pin 1 (No usar)
#define PIN_P3P2          22  // P3: Pin 2 (As Digital)
#define PIN_P3P3          35  // P3: Pin 3 (As Analog)

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
