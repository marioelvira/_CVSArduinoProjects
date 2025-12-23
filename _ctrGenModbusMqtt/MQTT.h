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
//#define MQTT_BROKER       "192.168.0.200"
#define MQTT_BROKER         "sdpelicanos.webhop.me"
#define MQTT_BROKER_PORT    1883
#define MQTT_USERNAME       "sdpelicanos@gmail.com"
#define MQTT_PASSWORD       "MQTTSup3rP@@sw0rd"

// MQTT Topics publish
#if (_USE_MBTCP_ == 1)
#define MQTT_LAST_TOPIC   4
#else
#define MQTT_LAST_TOPIC   3
#endif

#if (_USE_MQTT_TEST_ == 1)

#define TOPIC_SCTR        "sdpelicanos@gmail.com/sctr_"  //0
#define TOPIC_SINS        "sdpelicanos@gmail.com/sins_"  //1
#define TOPIC_TEST        "sdpelicanos@gmail.com/test_"  //2
#define TOPIC_RCTR        "sdpelicanos@gmail.com/rctr_"  //3

#define TOPIC_ALARM       "sdpelicanos@gmail.com/alarm_" //4 - Siempre el último

// MQTT Topics subscribe
#define TOPIC_OON         "sdpelicanos@gmail.com/Oon_"
#define TOPIC_OOFF        "sdpelicanos@gmail.com/Ooff_"

#define TOPIC_MODE_AUTO   "sdpelicanos@gmail.com/mda_"
#define TOPIC_MODE_TEST   "sdpelicanos@gmail.com/mdt_"

#define TOPIC_WATCHDOG    "sdpelicanos@gmail.com/wd_"

#define TOPIC_GENON       "sdpelicanos@gmail.com/gOn_"
#define TOPIC_GENOFF      "sdpelicanos@gmail.com/gOff_"
#define TOPIC_OUTON       "sdpelicanos@gmail.com/oOn_"
#define TOPIC_OUTOFF      "sdpelicanos@gmail.com/oOff_"

#else // (_USE_MQTT_TEST_ == 1)

#define TOPIC_SCTR        "sdpelicanos@gmail.com/sctr"  //0
#define TOPIC_SINS        "sdpelicanos@gmail.com/sins"  //1
#define TOPIC_TEST        "sdpelicanos@gmail.com/test"  //2
#define TOPIC_RCTR        "sdpelicanos@gmail.com/rctr"  //3

#define TOPIC_ALARM       "sdpelicanos@gmail.com/alarm" //4 - Siempre el último

// MQTT Topics subscribe
#define TOPIC_OON         "sdpelicanos@gmail.com/Oon"
#define TOPIC_OOFF        "sdpelicanos@gmail.com/Ooff"

#define TOPIC_MODE_AUTO   "sdpelicanos@gmail.com/mda"
#define TOPIC_MODE_TEST   "sdpelicanos@gmail.com/mdt"

#define TOPIC_WATCHDOG    "sdpelicanos@gmail.com/wd"

#define TOPIC_GENON       "sdpelicanos@gmail.com/gOn"
#define TOPIC_GENOFF      "sdpelicanos@gmail.com/gOff"
#define TOPIC_OUTON       "sdpelicanos@gmail.com/oOn"
#define TOPIC_OUTOFF      "sdpelicanos@gmail.com/oOff"

#endif // (_USE_MQTT_TEST_ == 1)

#define MQTT_BLINK_CONNECTING   3000

#endif // _MQTT_H_

#ifdef __cplusplus
} // extern "C"
#endif
