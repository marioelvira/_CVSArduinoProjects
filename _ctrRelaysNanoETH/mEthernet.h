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
#define ETH_START       0
#define ETH_OK          1
#define ETH_ERROR	      2

#endif // _METH_H_

#ifdef __cplusplus
} // extern "C"
#endif
