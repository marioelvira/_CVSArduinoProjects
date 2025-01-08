#ifdef __cplusplus
extern "C" {
#endif

#ifndef _mWIFI_H_
#define _mWIFI_H_

///////////
// Wi-Fi //
///////////
#define WIFI_BLINK_ACCESSPOINT     1000
#define WIFI_BLINK_CONNECTING      100
#define WIFI_BLINK_STATION         2000

#define WIFI_ACCESSPOINT_TIMEOUT  60000 // 60 sec
/*
#define SSIDST   "SSID"
#define PSKST    "password"
*/

#define SSIDAP    "MBMQTT8266"
#define PSKAP     "topsecret"

#define WIFI_START_ACCESSPOINT     0
#define WIFI_ON_ACCESSPOINT        1
#define WIFI_START_STATION         2
#define WIFI_ON_STATION            3
#define WIFI_STATION_CONNECTING    4
#define WIFI_STATION_CONNECTED     5

#endif // _WIFI_H_

#ifdef __cplusplus
} // extern "C"
#endif
