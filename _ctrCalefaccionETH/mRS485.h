#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MRS485_H_
#define _MRS485_H_

#define MRS485_ARRAY_SIZE       200

#define MRS485_BACK_TOUT_MS     500
#define MRS485_RX_TOUT_MS       5
#define MRS485_INIT_TX_MS       2
#define MRS485_END_TX_MS        1 //10

// Status
#define MRS485_STANDBY	  1
#define MRS485_ONRX		    2
#define MRS485_FRAME_RX   3
#define MRS485_INITTX     4
#define MRS485_ONTX		    5
#define MRS485_ENDTX      6

#define OUT_RS485_RX      0
#define OUT_RS485_TX      1

extern int             mrs485State;
extern String          mrs485RxBuffer;
extern unsigned long   mrs485tick;
extern char            mrs485TxBuffer[MRS485_ARRAY_SIZE];
extern int             mrs485TxNumBytes;

extern int             OutRS485rxtx;

#endif // _MRS485_H_

#ifdef __cplusplus
} // extern "C"
#endif
