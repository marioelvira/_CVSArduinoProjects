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

#define MQTT_CONNECTION_TIMEOUT       10000     // 120000    // 2 min
#define MQTT_SUBSCRIBE_TIMEOUT        1000      // 1 sec
#define MQTT_PUBLISH_TIMEOUT          500       // 500 ms

// MQTT broker credentials
#define MQTT_BROKER         "sdpelicanos.webhop.me"
#define MQTT_BROKER_PORT    1883
#define MQTT_USERNAME       "sdpelicanos@gmail.com"
#define MQTT_PASSWORD       "MQTTSup3rP@@sw0rd"

#define _USE_MQTT_DEBUG_    0

// MQTT Topics
#define MQTT_NUM_TOPICS    2

#if (_USE_MQTT_DEBUG_ == 1)
#define TOPIC_RCTR         "sdpelicanos@gmail.com/drel_ctr"  // 0
#define TOPIC_RIOS         "sdpelicanos@gmail.com/drel_ios"  // 1
#else
#define TOPIC_RCTR         "sdpelicanos@gmail.com/rel_ctr"   // 0
#define TOPIC_RIOS         "sdpelicanos@gmail.com/rel_ios"   // 1
#endif

#define TOPIC_RON          "sdpelicanos@gmail.com/rel_ron"
#define TOPIC_ROFF         "sdpelicanos@gmail.com/rel_roff"

#define TOPIC_RWD          "sdpelicanos@gmail.com/rel_rwd"

#define MQTT_BLINK_CONNECTING   3000

#endif // _MQTT_H_

#ifdef __cplusplus
} // extern "C"
#endif
