#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <EEPROM.h>

#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "ctr.h"
#include "wifi.h"
#include "MQTT.h"

////////////////////
// DIO definition //
////////////////////
int   InA;
int   InB;
int   InC;
int   InD;
int   InBomba;

int   OutGenPuls;
int   OutBomPuls;
int   outLed;

///////////
// Vbatt //
///////////
int    VbattInADC;
int    VbattInArray[VBATT_ARRAY_SIZE];
int    VbattInPointer;
float  VbattIn;

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
#define DEVICENAME      "rem8266"
char* deviceName = DEVICENAME;

/////////////////
// Http server //
/////////////////
ESP8266WebServer httpServer(HTTP_PORT);

int httpStatus;

//////////
// MQTT //
//////////
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

String mqttClientId = "remoteMQTT-" + String(ESP.getChipId());

int mqttStatus;
int mqttTopic2send;
unsigned long mqttTick = 0;

//////////
// Time //
//////////
unsigned long timeTick = 0;
int timeSec = 0;
int timeMin = 0;
int timeHour = 0;

/////////////
// Control //
/////////////
//int   controlMode = MODE_AUTO;
unsigned long ControlTick = 0;
int   ControlState;
int   TimeControlSec;
int   DisplayIndicador;

////////////
// Config //
////////////
int     cfgRemotePulsTick;
float   cfgVbatEOS;

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

  pinMode(PIN_GEN_PULS, OUTPUT);
  digitalWrite(PIN_GEN_PULS, PIN_OUT_ON);
  OutGenPuls = OUT_ON;

  pinMode(PIN_BOM_PULS, OUTPUT);
  digitalWrite(PIN_BOM_PULS, PIN_OUT_ON);
  OutBomPuls = OUT_ON; 
  
  //-----//
  // INS //
  //-----//
  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  pinMode(PIN_C, INPUT);
  pinMode(PIN_D, INPUT);

  pinMode(PIN_BOMBA, INPUT);
}

//============//
// MAIN SETUP //
//============//
void setup(void)
{ 
  _PINSetup();

  _IOSetup();

  #if (_SERIAL_DEBUG_ == 1)
  delay(100);  // 100ms
  Serial.begin(115200);
  Serial.println("");
  #endif

  // Config setup
  _ConfigSetup();

  // Wi-Fi setup
  _WifiSetup();

  // Http setup
  _HttpSetup();

  // Time Setup
  _TimeSetup();

  // MQTT setup
  _MQTTSetup();
  
  // Ctr setup
  _CtrSetup();
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

  if (OutGenPuls == OUT_ON)
    digitalWrite(PIN_GEN_PULS, PIN_OUT_ON);
  else
    digitalWrite(PIN_GEN_PULS, PIN_OUT_OFF); 

  if (OutBomPuls == OUT_ON)
    digitalWrite(PIN_BOM_PULS, PIN_OUT_ON);
  else
    digitalWrite(PIN_BOM_PULS, PIN_OUT_OFF);
    
  //-----//
  // INS //
  //-----//
  if (digitalRead(PIN_A) == PIN_IN_OFF)
    InA = IO_OFF;
  else
    InA = IO_ON;

  if (digitalRead(PIN_B) == PIN_IN_OFF)
    InB = IO_OFF;
  else
    InB = IO_ON;

  if (digitalRead(PIN_C) == PIN_IN_OFF)
    InC = IO_OFF;
  else
    InC = IO_ON;

  if (digitalRead(PIN_D) == PIN_IN_OFF)
    InD = IO_OFF;
  else
    InD = IO_ON;

  if (digitalRead(PIN_BOMBA) == PIN_IN_OFF)
    InBomba = IO_OFF;
  else
    InBomba = IO_ON;
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();
  //_IOLoop();

  _IOLcdLoop();

  //if (controlMode == MODE_AUTO)
  //  _OUTSLoop();

  _WifiLoop();
  _WifiLedLoop();

  if ((wifiStatus == WIFI_ON_ACCESSPOINT) || (wifiStatus == WIFI_STATION_CONNECTED))
    _HttpLoop();

  if (wifiStatus == WIFI_STATION_CONNECTED)
    _MQTTLoop();
  else
    mqttStatus = MQTT_NOT_CONNECTED;
  
  _CtrLoop();
  
  _TimeLoop();
}
