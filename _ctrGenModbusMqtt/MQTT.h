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
#define MQTT_PUBLISH_TIMEOUT      500   // 500 ms

// MQTT broker credentials
#define MQTT_BROKER         "sdpelicanos.webhop.me"
#define MQTT_BROKER_PORT    1883 // 7000
#define MQTT_USERNAME       "sdpelicanos@gmail.com"
#define MQTT_PASSWORD       "MQTTSup3rP@@sw0rd"

// MQTT Topics
#define TOPIC_SCTR        "sdpelicanos@gmail.com/sctr"
#define TOPIC_SINS        "sdpelicanos@gmail.com/sins"
#define TOPIC_TEST        "sdpelicanos@gmail.com/test"
#define TOPIC_ALARM       "sdpelicanos@gmail.com/alarm"

#define TOPIC_OON         "sdpelicanos@gmail.com/Oon"
#define TOPIC_OOFF        "sdpelicanos@gmail.com/Ooff"

#define TOPIC_MODE_AUTO   "sdpelicanos@gmail.com/mda"
#define TOPIC_MODE_TEST   "sdpelicanos@gmail.com/mdt"

#define TOPIC_WATCHDOG    "sdpelicanos@gmail.com/wd"

#define TOPIC_GENON       "sdpelicanos@gmail.com/gOn"
#define TOPIC_GENOFF      "sdpelicanos@gmail.com/gOff"
#define TOPIC_OUTON       "sdpelicanos@gmail.com/oOn"
#define TOPIC_OUTOFF      "sdpelicanos@gmail.com/oOff"

#define MQTT_BLINK_CONNECTING   3000

#endif // _MQTT_H_

#ifdef __cplusplus
} // extern "C"
#endif
