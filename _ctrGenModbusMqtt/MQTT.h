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
#define TOPIC_GENCTR      "sdpelicanos@gmail.com/gCtr"
#define TOPIC_GENSTOP     "sdpelicanos@gmail.com/gStop"
#define TOPIC_LUZCTR      "sdpelicanos@gmail.com/luzCtr"
#define TOPIC_LUZSTANDBY  "sdpelicanos@gmail.com/luzSy"
#define TOPIC_WATCHDOG    "sdpelicanos@gmail.com/wd"

#define TOPIC_O1ON        "sdpelicanos@gmail.com/O1on"
#define TOPIC_O1OFF       "sdpelicanos@gmail.com/O1off"
#define TOPIC_O2ON        "sdpelicanos@gmail.com/O2on"
#define TOPIC_O3OFF       "sdpelicanos@gmail.com/O3off"
#define TOPIC_O4ON        "sdpelicanos@gmail.com/O4on"
#define TOPIC_O4OFF       "sdpelicanos@gmail.com/O4off"
#define TOPIC_O5ON        "sdpelicanos@gmail.com/O5on"
#define TOPIC_O5OFF       "sdpelicanos@gmail.com/O5off"
#define TOPIC_O6ON        "sdpelicanos@gmail.com/O6on"
#define TOPIC_O6OFF       "sdpelicanos@gmail.com/O6off"
#define TOPIC_O7ON        "sdpelicanos@gmail.com/O7on"
#define TOPIC_O7OFF       "sdpelicanos@gmail.com/O7off"
#define TOPIC_O8ON        "sdpelicanos@gmail.com/O8on"
#define TOPIC_O8OFF       "sdpelicanos@gmail.com/O8off"

#define TOPIC_OFFSET            21

#define MQTT_BLINK_CONNECTING   3000

#endif // _MQTT_H_

#ifdef __cplusplus
} // extern "C"
#endif
