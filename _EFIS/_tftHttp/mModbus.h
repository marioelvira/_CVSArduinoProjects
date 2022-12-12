#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MMODBUS_H_
#define _MMODBUS_H_

#define CRCSIZE       2

#define MB_TSLEEP     5
#define MB_RXLOOP     500
#define MB_RXTOUT	    1000

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

// Mapa
#define MB_ADD_CTR      0
#define MB_NREG_CTR     10
#define MB_ADD_INS      1000
#define MB_NREG_INS     2
#define MB_ADD_OUTS     1010
#define MB_NREG_OUTS    3
#define MB_ADD_ADC      1020
#define MB_NREG_ADC     4
#define MB_ADD_PULS     1030
#define MB_NREG_PULS    2

// Erase TODO
#define MB_NUM_IOS    8

#define MB_OUT1       0
#define MB_OUT2       1
#define MB_OUT3       2
#define MB_OUT4       3
#define MB_OUT5       4
#define MB_OUT6       5
#define MB_OUT7       6
#define MB_OUT8       7
#define MB_OUTALL     8       


extern void _MBCRC(void);

#endif // _MMODBUS_H_

#ifdef __cplusplus
} // extern "C"
#endif
