#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MODBUS_H_
#define _MODBUS_H_

///////////////////////
// Modbus TCP server //
///////////////////////
#define MB_PORT                 502
#define MB_RX_MAX_BTYE          150
#define MB_TX_MAX_BTYE          150

#define MB_CONNECTION_TIMEOUT   5000
#define MB_RX_TIMEOUT           200

#define MB_SERVER_INIT          0
#define MB_SERVER_ON            1

#define MB_CLIENT_INIT          0
#define MB_CLIENT_CONNECTED     1
#define MB_CLIENT_ON_RX         2
#define MB_CLIENT_ON_ANALYSIS   3
#define MB_CLIENT_ON_TX         4

// Modbus Address definitions
#define MB_ADDRESS_BROADCAST                  ( 0 )
#define MB_ADDRESS_MIN                        ( 1 )
#define MB_ADDRESS_MAX                        ( 247 )

#define MB_NACK                               0x80
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

// Input Registers
#define MB_IR_ADD_ONLINE   0
#define MB_IR_NREG_ONLINE  24
#define MB_IR_ADD_INS      100
#define MB_IR_NREG_INS     2
#define MB_IR_ADD_OUTS     110
#define MB_IR_NREG_OUTS    6
#define MB_IR_ADD_ADCS     120
#define MB_IR_NREG_ADCS    8

// Holding Registers
#define MB_HR_ADD_CFG      0
#define MB_HR_NREG_CFG     30
#define MB_HR_ADD_IP       50
#define MB_HR_NREG_IP      14
#define MB_HR_ADD_OUTS     110
#define MB_HR_NREG_OUTS    6
#if (_USE_WDE_ == 1)
#define MB_HR_ADD_WD       200
#define MB_HR_NREG_WD      1
#endif

// MODBUS Error Codes
#define MB_EC_NONE                    0
#define MB_EC_ILLEGAL_FUNCTION        1
#define MB_EC_ILLEGAL_DATA_ADDRESS    2
#define MB_EC_ILLEGAL_DATA_VALUE      3
#define MB_EC_SLAVE_DEVICE_FAILURE    4

// MB TCP offsets
#define MB_TCP_TID              0
#define MB_TCP_PID              2
#define MB_TCP_LEN              4
#define MB_TCP_UID              6
// MB
#define MB_TCP_FUNC             7
// MB offsets RX
#define MB_TCP_REGS_ADD         8
#define MB_TCP_REGS_NUM        10
// MB offsets TX
#define MB_TCP_NBYTES           8
#define MB_TCP_REGS             9

#endif // _MODBUS_H_

#ifdef __cplusplus
} // extern "C"
#endif
