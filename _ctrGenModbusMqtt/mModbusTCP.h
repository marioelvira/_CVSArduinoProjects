#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MMODBUS_TCP_H_
#define _MMODBUS_TCP_H_

#define MBTCP_CONNECT_MS          10000
#define MBTCP_ROUND_CONNETED_MS   4000
#define MBTCP_RESPONSE_MS         500

#define MBTCP_WAIT_TO_CONNECT   1
#define MBTCP_CONNECT           2
#define MBTCP_WAIT_TX           3
#define MBTCP_TX                4
#define MBTCP_RX                5
#define MBTCP_STOP              6

#endif // _MMODBUS_TCP_H_

#ifdef __cplusplus
} // extern "C"
#endif
