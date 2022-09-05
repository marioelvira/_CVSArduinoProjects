#ifdef __cplusplus
extern "C" {
#endif

#ifndef _HTTP_H_
#define _HTTP_H_

#include "main.h"

///////////
// Wi-Fi //
///////////
#define WIFI_BLINK_ACCESSPOINT     1000
#define WIFI_BLINK_CONNECTING      100
#define WIFI_BLINK_STATION         2000

#define WIFI_ACCESSPOINT_TIMEOUT  120 // 120 sec
/*
#define SSIDST   "SSID"
#define PSKST    "password"
*/
#define SSIDAP    "DYNBROKER8266"
#define PSKAP     "topsecret"

#define WIFI_START_ACCESSPOINT     0
#define WIFI_ON_ACCESSPOINT        1
#define WIFI_START_STATION         2
#define WIFI_ON_STATION            3
#define WIFI_STATION_CONNECTING    4
#define WIFI_STATION_CONNECTED     5

#endif // _HTTP_H_

#ifdef __cplusplus
} // extern "C"
#endif
