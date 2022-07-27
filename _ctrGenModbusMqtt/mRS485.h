#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MRS485_H_
#define _MRS485_H_

#define MRS485_ARRAY_SIZE   200
#define MRS485_TOUT_MS      10

// Status
#define MRS485_STANDBY	  1
#define MRS485_ONRX		    2
#define MRS485_FRAME_RX   3
#define MRS485_ONTX		    4
#define MRS485_ENDTX      5

#define OUT_RS485_RX      0
#define OUT_RS485_TX      1

#endif // _MRS485_H_

#ifdef __cplusplus
} // extern "C"
#endif
