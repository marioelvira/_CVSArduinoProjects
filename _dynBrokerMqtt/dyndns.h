#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DYNDNS_H_
#define _DYNDNS_H_

// Documentation on:
// https://www.noip.com/es-MX/integrate/request

#include "main.h"

// Estados principales...
#define DYNDNS_STANDBY        0
#define DYNDNS_CHECK          1

#define DYNDNS_TIMEOUT        60000 // 60seg

#define DYNDS_USER        "sdpelicanos"
#define DYNDS_PASSWORD    "DDNSSup3rP66sw0rd"
#define DYNDS_URL         "sdpelicanos.webhop.me"

#endif // _DYNDNS_H_

#ifdef __cplusplus
} // extern "C"
#endif
