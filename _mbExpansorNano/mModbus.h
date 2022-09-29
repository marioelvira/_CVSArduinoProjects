#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MMODBUS_H_
#define _MMODBUS_H_

#define CRCSIZE       2

#define MB_RXTOUT	    1000

#define MB_RX_OK      0
#define MB_RX_NOK     1

// Status
#define MB_STANDBY	        1
#define MB_ANALYSE_FRAME	  2
#define MB_SEND_RESPONSE    3

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

// Meteo
#define MB_FUNC_METEO_CONF                    0x46
#define MB_SFUNC_METEO_SN                     0x08

// Mapa
#define MB_ADD_METEO    0
#define MB_NREG_METEO   9
#define MB_ADD_INS      100
#define MB_NREG_INS     2
#define MB_ADD_OUTS     110
#define MB_NREG_OUTS    3
#define MB_ADD_ADC      120
#define MB_NREG_ADC     4
#define MB_ADD_PULS     130
#define MB_NREG_PULS    2

extern void _MBCRC(void);

#endif // _MMODBUS_H_

#ifdef __cplusplus
} // extern "C"
#endif
