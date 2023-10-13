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
#define MQTT_NUM_TOPICS   2
#define TOPIC_STATUS      "sdpelicanos@gmail.com/stat"  // 1
#define TOPIC_IOS         "sdpelicanos@gmail.com/ios"   // 2

#define TOPIC_OON         "sdpelicanos@gmail.com/oon"
#define TOPIC_OOFF        "sdpelicanos@gmail.com/ooff"

#define TOPIC_WATCHDOG    "sdpelicanos@gmail.com/owd"

#define MQTT_BLINK_CONNECTING   3000

#endif // _MQTT_H_

#ifdef __cplusplus
} // extern "C"
#endif
