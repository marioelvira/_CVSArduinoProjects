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
#define MQTT_BROKER         "sdpelicanos.webhop.me"
#define MQTT_BROKER_PORT    1883 // 7000
#define MQTT_USERNAME       "sdpelicanos@gmail.com"
#define MQTT_PASSWORD       "MQTTSup3rP@@sw0rd"

// MQTT Topics
#if (_MQTT_DEBUG_ == 1)
#define TOPIC_STATE       "sdpelicanos@gmail.com/_state"
#define TOPIC_GENCTR      "sdpelicanos@gmail.com/_genCtr"
#define TOPIC_GENSTOP     "sdpelicanos@gmail.com/_genStop"
#define TOPIC_LUZCTR      "sdpelicanos@gmail.com/_luzCtr"
#define TOPIC_LUZSTANDBY  "sdpelicanos@gmail.com/_luzStandby"
#define TOPIC_WATCHDOG    "sdpelicanos@gmail.com/_watchdog"
#else
#define TOPIC_STATE       "sdpelicanos@gmail.com/state"
#define TOPIC_GENCTR      "sdpelicanos@gmail.com/genCtr"
#define TOPIC_GENSTOP     "sdpelicanos@gmail.com/genStop"
#define TOPIC_LUZCTR      "sdpelicanos@gmail.com/luzCtr"
#define TOPIC_LUZSTANDBY  "sdpelicanos@gmail.com/luzStandby"
#define TOPIC_WATCHDOG    "sdpelicanos@gmail.com/watchdog"
#endif

#define TOPIC_OFFSET            21

#define MQTT_BLINK_CONNECTING   3000

#endif // _MQTT_H_

#ifdef __cplusplus
} // extern "C"
#endif
