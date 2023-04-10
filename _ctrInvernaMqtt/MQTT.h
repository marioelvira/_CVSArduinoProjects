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
#define MQTT_BROKER         "ahiclavijo.webhop.me"
#define MQTT_BROKER_PORT    7001
#define MQTT_USERNAME       "ahiclavijo@gmail.com"

#define MQTT_KEY            "MQTTSup3rP@@sw0rd"

// MQTT Topics
#define TOPIC_STATE        "ahiclavijo@gmail.com/state"
#define TOPIC_FANCTR       "ahiclavijo@gmail.com/fanCtr"
#define TOPIC_FANSTBY      "ahiclavijo@gmail.com/fanStby"
#define TOPIC_PUMPCTR      "ahiclavijo@gmail.com/pumpCtr"
#define TOPIC_PUMPSTBY     "ahiclavijo@gmail.com/pumpStby"
#define TOPIC_IRRICTR      "ahiclavijo@gmail.com/irriCtr"
#define TOPIC_IRRISTBY     "ahiclavijo@gmail.com/irriStby"

#define TOPIC_OPCTR        "ahiclavijo@gmail.com/oOpCtr"
#define TOPIC_CLCTR        "ahiclavijo@gmail.com/oClCtr"

#define TOPIC_RESTORE      "ahiclavijo@gmail.com/restore"
#define TOPIC_WATCHDOG     "ahiclavijo@gmail.com/watchdog"

#define TOPIC_OFFSET            21

#define MQTT_BLINK_CONNECTING   3000

#endif // _MQTT_H_

#ifdef __cplusplus
} // extern "C"
#endif
