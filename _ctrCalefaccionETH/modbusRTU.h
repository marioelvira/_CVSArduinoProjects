#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MBRTU_H_
#define _MBRTU_H_

// https://a.aliexpress.com/_vN7zfb

// Nodo 1
// send :   00 10 00 00 00 01 02 00 01 6A 00
// return : 00 10 00 00 00 01 02 00 01 6A 00
// Nodo 2
// send :   00 10 00 00 00 01 02 00 02 6A 01
// return : 00 10 00 00 00 01 02 00 02 6A 01

#define CRCSIZE       2

#define MB_TSLEEP     5
#define MB_RXLOOP     2000 //500
#define MB_RXTOUT	    5000 //1000

#define MB_RX_OK      0
#define MB_RX_NOK     1

// Status
#define MB_STANDBY	      1
#define MB_READTEMPS      2
#define MB_TEMPSTATUS     3
#define MB_SLEEP          4

extern int mbState;
extern unsigned long mbTick;

extern int mbNError;
extern int mbNReply;
extern int mbNRetry;
extern int mbRetry;

#define MB_NUM_TEMPS  4
extern int mbTemp[];

#endif // _MBRTU_H_

#ifdef __cplusplus
} // extern "C"
#endif
