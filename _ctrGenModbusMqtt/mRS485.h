#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MRS485_H_
#define _MRS485_H_

#define MRS485_ARRAY_SIZE       200

#define MRS485_BACK_TOUT_MS     500
#define MRS485_RX_TOUT_MS       5
#define MRS485_TX_TOUT_MS       10
#define MRS485_INITTX_TOUT_MS   2

// Status
#define MRS485_STANDBY	  1
#define MRS485_ONRX		    2
#define MRS485_FRAME_RX   3
#define MRS485_INITTX     4
#define MRS485_ONTX		    5
#define MRS485_ENDTX      6

#define OUT_RS485_RX      0
#define OUT_RS485_TX      1

#endif // _MRS485_H_

#ifdef __cplusplus
} // extern "C"
#endif
