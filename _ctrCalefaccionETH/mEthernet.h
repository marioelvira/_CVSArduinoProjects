#ifdef __cplusplus
extern "C" {
#endif

#ifndef _METH_H_
#define _METH_H_

// https://www.simplymodbus.ca/index.html

#include "main.h"

//////////////
// IP Modes //
//////////////
#define DHCP_MODE       0
#define FIXIP_MODE      1

//////////////
// Ethernet //
//////////////
#define ETH_START         0
#define ETH_STARTED       1
#define ETH_CONNECTED     2
#define ETH_GOT_IP        3
#define ETH_ON_SERVICE    4
#define ETH_DISCONNECTED  5

#endif // _METH_H_

#ifdef __cplusplus
} // extern "C"
#endif
