#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <EEPROM.h>

#include<sMQTTBroker.h>

#include "ESP8266HTTPClient.h"
#include "base64.h"

#include "dyndns.h"
#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "MQTTBroker.h"
#include "mRAM.h"
#include "time.h"
#include "wde.h"
#include "wifi.h"

////////////////////
// DIO definition //
////////////////////
int   outLed;

///////////
// Wi-Fi //
///////////
unsigned long wifiAPTick = 0;
unsigned long wifiLEDTick = 0;

/*
  #if (_WRITE_SSID_EEPROM_ == 1)
  const char* ssidSt = SSIDST;
  const char* passwordSt = PSKST;
  #endif
*/

// Station Mode
char ssid[WIFI_SSID_MAX];
char password[WIFI_PSWD_MAX];

IPAddress wifiIP;

// Accesspoint Mode
const char* ssidAp = SSIDAP;
const char* passwordAp = PSKAP;

int wifiStatus;
int wifiMode;

////////////////
// IP Address //
////////////////
int       ipMode;

IPAddress ipAddress (192, 168, 43, 200);
IPAddress gateWay   (192, 168, 43, 1);
IPAddress netMask   (255, 255, 255, 0);

byte mac[6];

/////////////////
// Device Name //
/////////////////
#define DEVICENAME      "dynbroker8266"
char* deviceName = DEVICENAME;

/////////////////
// Http server //
/////////////////
ESP8266WebServer httpServer(HTTP_PORT);
int httpStatus;
int httpLockedSec;

//////////
// MQTT //
//////////
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

//////////
// Time //
//////////
unsigned long timeTick = 0;
int timeSec = 0;
int timeMin = 0;
int timeHour = 0;
int timeDay = 0;

/////////////
// Dyn Dns //
/////////////
unsigned long dyndnsTick = 0;
WiFiClient ifconfigClient;
HTTPClient ifconfigHttp;

WiFiClient dyndnsClient;
HTTPClient dyndnsHttp;
String new_ip = "";
String old_ip = "";
String update_url;
String ddns_u;
String ddns_p;
String ddns_d;
int ip_sent = 0;

/////////////////
// Broker MQTT //
/////////////////
int brokerStatus;
unsigned int brokerClients;

const char* brokerSt = DYNDS_URL;
char brokerUrl[BROKER_MAX];
int mqttPort;

class MyBroker: public sMQTTBroker
{
  public:
    bool onConnect(sMQTTClient *client, const std::string &username, const std::string &password)
    {
      #if (_BROKER_SERIAL_DEBUG_ == 1)
      Serial.println("Connect Client");
      Serial.print((String)&username[0]); Serial.print(":"); Serial.println((String)&password[0]);
      #endif
      /*
      if (brokerClients >= BROKER_NUM_CLIENTS)
      {
        #if (_BROKER_SERIAL_DEBUG_ == 1)
        Serial.println("Num MAX connected ");
        Serial.println(brokerClients);
        #endif
        return false;
      }
      */
      if (((char)username[0]  == 's') &&
          ((char)username[1]  == 'd') &&
          ((char)username[2]  == 'p') &&
          ((char)username[3]  == 'e') &&
          ((char)username[4]  == 'l') &&
          ((char)username[5]  == 'i') &&
          ((char)username[6]  == 'c') &&
          ((char)username[7]  == 'a') &&
          ((char)username[8]  == 'n') &&
          ((char)username[9]  == 'o') &&
          ((char)username[10] == 's') &&
          ((char)username[11] == '@') &&
          ((char)username[12] == 'g') &&
          ((char)username[13] == 'm') &&
          ((char)username[14] == 'a') &&
          ((char)username[15] == 'i') &&
          ((char)username[16] == 'l') &&
          ((char)username[17] == '.') &&
          ((char)username[18] == 'c') &&
          ((char)username[19] == 'o') &&
          ((char)username[20] == 'm'))
      {
        brokerClients++;
        #if (_BROKER_SERIAL_DEBUG_ == 1)
        Serial.print("Connected OK ");
        Serial.println(brokerClients);
        #endif
        return true;
      }
      else
      {
        #if (_BROKER_SERIAL_DEBUG_ == 1)
        Serial.print("Connected ERROR ");
        Serial.println(brokerClients);
        #endif
        return false;
      }
    };

    void onRemove(sMQTTClient*)
    {
      if (brokerClients != 0)
        brokerClients--;
      
      #if (_BROKER_SERIAL_DEBUG_ == 1)
      Serial.println("Remove Client");  
      Serial.print("Connected ");
      Serial.println(brokerClients);
      #endif
    };

    void onPublish(sMQTTClient *client, const std::string &topic, const std::string &payload)
    {     
      #if (_BROKER_SERIAL_DEBUG_ == 1)
      Serial.println("Client Publish Topic: ");
      Serial.print((String)&topic[0]); Serial.print(" payload: "); Serial.println((String)&payload[0]);
      #endif
    }
};

MyBroker broker;

//////////
// mRAM //
//////////
unsigned long freeRam;

////////
// WD //
////////
#if (_USE_WDE_ == 1)
int wdeForceReset;
#endif

////////////
// Config //
////////////
//int     DebugVal = 0;

///////////////
// PIN steup //
///////////////
void _PINSetup(void)
{
  //------//
  // OUTS //
  //------//

  #if (_USE_LED_INDICATOR_ == 1)
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, PIN_OUT_OFF);
  outLed = IO_OFF;
  #endif

  //-----//
  // INS //
  //-----//
  //pinMode(PIN_A, INPUT);      InA = IO_OFF;
}

//============//
// MAIN SETUP //
//============//
void setup(void)
{
  #if (_SERIAL_DEBUG_ == 1)
  delay(100);  // 100ms
  Serial.begin(115200);
  Serial.println("");
  #endif

  // Config setup
  _ConfigSetup();

  // IO setup
  _PINSetup();
  _IOSetup();

  // Wi-Fi setup
  _WifiSetup();

  // Http setup
  _HttpSetup();

  // Time setup
  _TimeSetup();

  // Mqtt broker setup
  //_BrokerSetup();

  // Dyndns setup
  _DyndnsSetup();

  #if (_USE_WDE_ == 1)
  _WDESetup();
  #endif
}

///////////////////////
// PIN state machine //
///////////////////////
void _PINLoop()
{
  //------//
  // OUTS //
  //------//

  #if (_USE_LED_INDICATOR_ == 1)
  if (outLed == OUT_OFF)
    digitalWrite(PIN_LED, PIN_OUT_ON);
  else
    digitalWrite(PIN_LED, PIN_OUT_OFF);
  #endif

  //-----//
  // INS //
  //-----//
  /*
    if (digitalRead(PIN_A) == PIN_IN_ON)
    InA = IO_ON;
    else
    InA = IO_OFF;
  */
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();
  _IOLoop();

  _WifiLoop();
  _WifiLedLoop();

  if ((wifiStatus == WIFI_ON_ACCESSPOINT) || (wifiStatus == WIFI_STATION_CONNECTED))
    _HttpLoop();

  if (wifiStatus == WIFI_STATION_CONNECTED)
  {
    _DyndnsLoop();
    _BrokerLoop();
  }
  else
    brokerStatus = BROKER_INIT;

  _TimeLoop();
}
