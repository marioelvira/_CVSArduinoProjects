#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MQTT_H_
#define _MQTT_H_

#define MQTT_NOT_CONNECTED   0
#define MQTT_CONNECTING      1
#define MQTT_CONNECTED       2
#define MQTT_SUBSCRIBED      3

#define MQTT_CONNECTION_TIMEOUT   5000  // 5 sec
#define MQTT_SUBSCRIBE_TIMEOUT    1000  // 1 sec
#define MQTT_PUBLISH_TIMEOUT      1000  // 1 sec

// MQTT broker credentials
#define MQTT_BROKER       "maqiatto.com"
#define MQTT_BROKER_PORT  1883
#define MQTT_USERNAME     "sdpelicanos@gmail.com"
#define MQTT_KEY          "MQTTSup3rP@@sw0rd"

// MQTT Topics
#define TOPIC_VBATT       "sdpelicanos@gmail.com/vbatt"

#endif // _MQTT_H_

#ifdef __cplusplus
} // extern "C"
#endif