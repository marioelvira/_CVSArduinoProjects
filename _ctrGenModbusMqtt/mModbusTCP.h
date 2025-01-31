#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MMODBUS_TCP_H_
#define _MMODBUS_TCP_H_

#define MBTCP_INIT_MS         10000 //60000
#define MBTCP_TROUND_MS       10000

#define MBTCP_NOT_CONNECTED   0
#define MBTCP_CONNECT         1
#define MBTCP_CONNECTING      2
#define MBTCP_TX_RX           3
#define MBTCP_TX              4
#define MBTCP_RX              5
#define MBTCP_WAIT            6
#define MBTCP_DISCONNECT      7

#endif // _MMODBUS_TCP_H_

#ifdef __cplusplus
} // extern "C"
#endif
