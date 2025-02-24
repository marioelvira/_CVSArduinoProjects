#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MMODBUS_TCP_H_
#define _MMODBUS_TCP_H_

#define MBTCP_ARRAY_SIZE        100

#define MBTCP_CONNECT_MS          10000
#define MBTCP_ROUND_CONNETED_MS   4000
#define MBTCP_RESPONSE_MS         500

#define MBTCP_WAIT_TO_CONNECT   1
#define MBTCP_CONNECT           2
#define MBTCP_WAIT_TX           3
#define MBTCP_TX                4
#define MBTCP_RX                5
#define MBTCP_ON_ANALYSIS       6
#define MBTCP_STOP              7


// Input Registers
#define MB_IR_ADD_ONLINE        0
#define MB_IR_NREG_ONLINE       21

// MB TCP offsets
//#define MB_TCP_TID            0
//#define MB_TCP_PID            2
#define MB_TCP_LEN              4
#define MB_TCP_UID              6
// MB
#define MB_TCP_FUNC             7
// MB offsets RX
//#define MB_TCP_REGS_ADD       8
//#define MB_TCP_REGS_NUM       10
// MB offsets TX
#define MB_TCP_NBYTES           8
#define MB_TCP_REGS             9

// Modbus functions list.
#define MB_FUNC_NONE                          ( 0 )
#define MB_FUNC_READ_COILS                    ( 1 )
#define MB_FUNC_READ_DISCRETE_INPUTS          ( 2 )
#define MB_FUNC_WRITE_SINGLE_COIL             ( 5 )
#define MB_FUNC_WRITE_MULTIPLE_COILS          ( 15 )
#define MB_FUNC_READ_HOLDING_REGISTER         ( 3 )   // 0x03
#define MB_FUNC_READ_INPUT_REGISTER           ( 4 )   // 0x04
#define MB_FUNC_WRITE_REGISTER                ( 6 )   // 0x06
#define MB_FUNC_WRITE_MULTIPLE_REGISTERS      ( 16 )  // 0x10
#define MB_FUNC_ING_WRITE_MULTIPLE_REGISTERS  ( 21 )  // 0x15
#define MB_FUNC_READWRITE_MULTIPLE_REGISTERS  ( 23 )
#define MB_FUNC_DIAG_READ_EXCEPTION           ( 7 )
#define MB_FUNC_DIAG_DIAGNOSTIC               ( 8 )
#define MB_FUNC_DIAG_GET_COM_EVENT_CNT        ( 11 )
#define MB_FUNC_DIAG_GET_COM_EVENT_LOG        ( 12 )
#define MB_FUNC_OTHER_REPORT_SLAVEID          ( 17 )  // 0x11
#define MB_FUNC_ERROR                         ( 128 )

#define MB_RMS_NUMBER      2
#define MB_DC_NUMBER       6

#endif // _MMODBUS_TCP_H_

#ifdef __cplusplus
} // extern "C"
#endif
