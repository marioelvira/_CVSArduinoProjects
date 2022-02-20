#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <EEPROM.h>

#include "__ver.h"

#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "ctr.h"
#include "wifi.h"
#include "MQTT.h"
#include "mRAM.h"
#include "wde.h"

/////////////
// Version //
/////////////
const char* FW_Version = FW_VERSION;

////////////////////
// DIO definition //
////////////////////
int   InA;
int   InB;
int   InC;
int   InD;

int   OutBattA;
int   OutBattB;
int   OutBattC;
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
#define DEVICENAME      "chargerCtr8266"
char* deviceName = DEVICENAME;

/////////////////
// Http server //
/////////////////
ESP8266WebServer httpServer(HTTP_PORT);

int httpStatus;

//////////
// MQTT //
//////////
const char* brokerSt = MQTT_BROKER;
char brokerUrl[BROKER_MAX];
int brokerPort;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

String mqttClientId = "remoteMQTT-" + String(ESP.getChipId());

int mqttStatus;
unsigned long mqttTick = 0;

//////////
// Time //
//////////
unsigned long timeTick = 0;
int timeSec = 0;
int timeMin = 0;
int timeHour = 0;
int timeDay = 0;

/////////////
// Control //
/////////////
int   controlMode = MODE_AUTO;
unsigned long ControlTick = 0;
int   ControlState;
int   TimeControlSec;

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
int     cfgBattTsecs;

int     cfgBattAvolts;
int     cfgBattAmins;
int     cfgBattBvolts;
int     cfgBattBmins;
int     cfgBattCvolts;
int     cfgBattCmins;

int     cfgLogicIns;
int     cfgLogicOuts;

int     cfgADCm;
int     cfgADCb;
int     cfgADCs;
int     cfgADCf;

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

  pinMode(PIN_BATT_A, OUTPUT);
  digitalWrite(PIN_BATT_A, !cfgLogicOuts);
  OutBattA = OUT_OFF;
  
  pinMode(PIN_BATT_B, OUTPUT);
  digitalWrite(PIN_BATT_B, !cfgLogicOuts);
  OutBattB = OUT_OFF;
    
  pinMode(PIN_BATT_C, OUTPUT);
  digitalWrite(PIN_BATT_C, !cfgLogicOuts);
  OutBattC = OUT_OFF;
 
  //-----//
  // INS //
  //-----//
  pinMode(PIN_A, INPUT);      InA = IO_OFF;
  pinMode(PIN_B, INPUT);      InB = IO_OFF;
  pinMode(PIN_C, INPUT);      InC = IO_OFF;
  pinMode(PIN_D, INPUT);      InD = IO_OFF;
}

//============//
// MAIN SETUP //
//============//
void setup(void)
{ 
  #if (_SERIAL_DEBUG_ == 1)
  delay(100);  // 100ms
  Serial.begin(115200);
  Serial.print("Project: ");
  Serial.println(PROJECT);
  Serial.print("Version: ");
  Serial.println(FW_VERSION);
  #endif
  
  // Config setup
  _ConfigSetup();

  // IO setup
  _PINSetup();
  //_IOSetup();
  _ADCSetup();

  // Wi-Fi setup
  _WifiSetup();

  // Http setup
  _HttpSetup();

  // Time setup
  _TimeSetup();

  // MQTT setup
  _MQTTSetup();
  
  // Ctr setup
  _CtrSetup();

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

  if (OutBattA == cfgLogicOuts)
    digitalWrite(PIN_BATT_A, PIN_OUT_ON);
  else
    digitalWrite(PIN_BATT_A, PIN_OUT_OFF);

  if (OutBattB == cfgLogicOuts)
    digitalWrite(PIN_BATT_B, PIN_OUT_ON);
  else
    digitalWrite(PIN_BATT_B, PIN_OUT_OFF);
    
  if (OutBattC == cfgLogicOuts)
    digitalWrite(PIN_BATT_C, PIN_OUT_ON);
  else
    digitalWrite(PIN_BATT_C, PIN_OUT_OFF); 
  
  //-----//
  // INS //
  //-----//
  if (digitalRead(PIN_A) == PIN_IN_ON /*cfgLogicIns*/)
    InA = IO_ON;
  else
    InA = IO_OFF;

  if (digitalRead(PIN_B) == PIN_IN_ON /*cfgLogicIns*/)
    InB = IO_ON;
  else
    InB = IO_OFF;

  if (digitalRead(PIN_C) == PIN_IN_ON /*cfgLogicIns*/)
    InC = IO_ON;
  else
    InC = IO_OFF;

  if (digitalRead(PIN_D) == PIN_IN_ON /*cfgLogicIns*/)
    InD = IO_ON;
  else
    InD = IO_OFF;
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();
  //_IOLoop();

  _WifiLoop();
  _WifiLedLoop();

  if ((wifiStatus == WIFI_ON_ACCESSPOINT) || (wifiStatus == WIFI_STATION_CONNECTED))
    _HttpLoop();

  if (wifiStatus == WIFI_STATION_CONNECTED)
    _MQTTLoop();
  else
    mqttStatus = MQTT_NOT_CONNECTED;
  
  if (controlMode == MODE_AUTO)
    _CtrLoop();
  
  _TimeLoop();
}
