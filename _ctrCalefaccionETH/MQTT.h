#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MQTT_H_
#define _MQTT_H_

#define MQTT_NOT_CONNECTED   0
#define MQTT_CONNECTING      1
#define MQTT_CONNECTED_OK    2
#define MQTT_SUBSCRIBED      3

#define MQTT_CONNECTION_TIMEOUT       120000    // 2 min
#define MQTT_SUBSCRIBE_TIMEOUT        1000      // 1 sec
#define MQTT_PUBLISH_TIMEOUT          500       // 500 ms

// MQTT broker credentials
#define MQTT_BROKER         "sdpelicanos.webhop.me"
#define MQTT_BROKER_PORT    1883
#define MQTT_USERNAME       "sdpelicanos@gmail.com"
#define MQTT_PASSWORD       "MQTTSup3rP@@sw0rd"

// MQTT Topics publish
#define MQTT_LAST_TOPIC    3
#define TOPIC_CCTR         "sdpelicanos@gmail.com/cal_ctr"   // 0
#define TOPIC_CIOS         "sdpelicanos@gmail.com/cal_ios"   // 1
#define TOPIC_CALARM       "sdpelicanos@gmail.com/cal_al"    // Last one always
// MQTT Topics subscribe
#define TOPIC_CON          "sdpelicanos@gmail.com/cal_ron"
#define TOPIC_COFF         "sdpelicanos@gmail.com/cal_roff"

#define TOPIC_CWD          "sdpelicanos@gmail.com/rwd"

#define MQTT_BLINK_CONNECTING   3000


extern const char* brokerUrlSt;
extern char brokerUrl[];
extern int brokerPort;
extern const char* brokerUserSt;
extern char brokerUser[];
extern const char* brokerPswdSt;
extern char brokerPswd[];

extern String mqttClientId;

extern int mqttStatus;

#endif // _MQTT_H_

#ifdef __cplusplus
} // extern "C"
#endif
