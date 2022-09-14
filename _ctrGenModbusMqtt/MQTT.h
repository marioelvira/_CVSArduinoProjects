#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MQTT_H_
#define _MQTT_H_

#include "main.h"

#define MQTT_NOT_CONNECTED   0
#define MQTT_CONNECTING      1
#define MQTT_CONNECTED       2
#define MQTT_SUBSCRIBED      3

#define MQTT_CONNECTION_TIMEOUT   5000  // 5 sec
#define MQTT_SUBSCRIBE_TIMEOUT    1000  // 1 sec
#define MQTT_PUBLISH_TIMEOUT      800   // 800 ms

// MQTT broker credentials
//#define MQTT_BROKER       "maqiatto.com"
//#define MQTT_BROKER_PORT  1883
#define MQTT_BROKER         "sdpelicanos.webhop.me"
#define MQTT_BROKER_PORT    7000

#define MQTT_USERNAME     "sdpelicanos@gmail.com"
#define MQTT_KEY          "MQTTSup3rP@ssw0rd"

// MQTT Topics
#define TOPIC_STATE       "sdpelicanos@gmail.com/st"

#define TOPIC_OON         "sdpelicanos@gmail.com/Oon"
#define TOPIC_OOFF        "sdpelicanos@gmail.com/Ooff"

#define TOPIC_MODE_AUTO   "sdpelicanos@gmail.com/mda"
#define TOPIC_MODE_TEST   "sdpelicanos@gmail.com/mdt"

#define TOPIC_WATCHDOG    "sdpelicanos@gmail.com/wd"

#define TOPIC_GENCTR      "sdpelicanos@gmail.com/gOn"
#define TOPIC_GENSTOP     "sdpelicanos@gmail.com/gOff"
//#define TOPIC_LUZCTR    "sdpelicanos@gmail.com/lOn"
//#define TOPIC_LUZSTOP   "sdpelicanos@gmail.com/lOff"

#define MQTT_BLINK_CONNECTING   3000

#endif // _MQTT_H_

#ifdef __cplusplus
} // extern "C"
#endif
