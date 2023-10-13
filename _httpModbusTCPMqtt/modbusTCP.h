#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MODBUS_H_
#define _MODBUS_H_

///////////////////////
// Modbus TCP server //
///////////////////////
#define MODBUSTCP_PORT                 8502

#define MODBUSTCP_INIT                 0
#define MODBUSTCP_CLIENT_WAITING       1
#define MODBUSTCP_CLIENT_CONNECTED     2
#define MODBUSTCP_ON_RX                3
#define MODBUSTCP_ON_ANALYSIS          4
#define MODBUSTCP_ON_TX                5

// MODBUS functions
#define MB_FC_NONE                     0
#define MB_FC_READ_REGISTERS           3
#define MB_FC_WRITE_REGISTER           6
#define MB_FC_WRITE_MULTIPLE_REGISTERS 16

// MODBUS Error Codes
#define MB_EC_NONE                    0
#define MB_EC_ILLEGAL_FUNCTION        1
#define MB_EC_ILLEGAL_DATA_ADDRESS    2
#define MB_EC_ILLEGAL_DATA_VALUE      3
#define MB_EC_SLAVE_DEVICE_FAILURE    4

// MODBUS MBAP offsets
//#define MB_TCP_TID            0
//#define MB_TCP_PID            2
//#define MB_TCP_LEN            4
//#define MB_TCP_UID            6
#define MB_TCP_FUNC             7
#define MB_TCP_REGISTER_STR     8
#define MB_TCP_REGISTER_NUM    10

#define MB_MAX_BTYE  260 
#define MB_MAX_HR    5

#endif // _MODBUS_H_

#ifdef __cplusplus
} // extern "C"
#endif
