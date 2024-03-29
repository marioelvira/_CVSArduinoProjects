#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MMODBUS_H_
#define _MMODBUS_H_

// https://a.aliexpress.com/_vN7zfb

// Nodo 1
// send :   00 10 00 00 00 01 02 00 01 6A 00
// return : 00 10 00 00 00 01 02 00 01 6A 00
// Nodo 2
// send :   00 10 00 00 00 01 02 00 02 6A 01
// return : 00 10 00 00 00 01 02 00 02 6A 01

#define NUM_W2R       2

#define CRCSIZE       2

#define MB_TSLEEP     5
#define MB_RXLOOP     500
#define MB_RXTOUT	    1000

#define MB_NUM_IOS    8
#define MB_NUM_BRS    2

#define MB_OUT1       0
#define MB_OUT2       1
#define MB_OUT3       2
#define MB_OUT4       3
#define MB_OUT5       4
#define MB_OUT6       5
#define MB_OUT7       6
#define MB_OUT8       7
#define MB_OUTALL     8       

//#define MB_OUT_OFF  0
//#define MB_OUT_ON   1

#define MB_RX_OK      0
#define MB_RX_NOK     1

// Status
#define MB_STANDBY	      1
#define MB_READINS	      2
#define MB_INSSTATUS      3
#define MB_READOUTS       4
#define MB_OUTSSTATUS     5
#define MB_WRITEOUT       6
#define MB_OUTSTATUS      7
#define MB_SLEEP          10

#define MB_NUM_RETRY      2

#define MB_IN_AL_VAL_0		0
#define MB_IN_AL_VAL_1		1
#define MB_IN_AL_DISABLE	2

extern void _MBCRC(void);

#endif // _MMODBUS_H_

#ifdef __cplusplus
} // extern "C"
#endif
