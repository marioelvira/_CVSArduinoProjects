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
#include "mRAM.h"

////////////////////
// DIO definition //
////////////////////
int   InA;
int   InB;
int   InC;
int   InD;

int   InGenOn;

int   OutGenPuls;
int   OutStopPuls;
int   OutLuzOff;
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
const char* brokerSt = MQTT_BROKER;
char brokerUrl[BROKER_MAX];
int brokerPort;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

String mqttClientId = "remoteMQTT-" + String(ESP.getChipId());

int mqttStatus;
unsigned long mqttTick = 0;

/*
char  topic_state[50];
char  topic_genctr[50];
char  topic_genstop[50];
char  topic_luzctr[50];
char  topic_luzstandby[50];
*/
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
int   DisplayIndicador;

int   genInStatus;
int   genState;
int   genMinOn;

int   remPulse;
int   remAct;

int   LuzState;
unsigned long LuzTick = 0;

//////////
// mRAM //
//////////
unsigned long freeRam;

////////////
// Config //
////////////
int     cfgRemotePulsTick;
int     cfgLuzOutTick;
int     cfgLogicIns;
int     cfgLogicOuts;
int     cfgGenOnPin;
int     cfgADCm;
int     cfgADCb;

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

  pinMode(PIN_GEN_PULS, OUTPUT);
  digitalWrite(PIN_GEN_PULS, !cfgLogicOuts);
  OutGenPuls = OUT_OFF;

  pinMode(PIN_STOP_PULS, OUTPUT);
  digitalWrite(PIN_STOP_PULS, !cfgLogicOuts);
  OutStopPuls = OUT_OFF;

  pinMode(PIN_LUZ_OFF, OUTPUT);
  digitalWrite(PIN_LUZ_OFF, !cfgLogicOuts);
  OutLuzOff = OUT_OFF; 
  
  //-----//
  // INS //
  //-----//
  pinMode(PIN_A, INPUT);      InA = IO_OFF;
  pinMode(PIN_B, INPUT);      InB = IO_OFF;
  pinMode(PIN_C, INPUT);      InC = IO_OFF;
  pinMode(PIN_D, INPUT);      InD = IO_OFF;
  pinMode(PIN_GENON, INPUT);  InGenOn = IO_OFF;
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

  if (OutGenPuls == cfgLogicOuts)
    digitalWrite(PIN_GEN_PULS, PIN_OUT_ON);
  else
    digitalWrite(PIN_GEN_PULS, PIN_OUT_OFF); 

  if (OutStopPuls == cfgLogicOuts)
    digitalWrite(PIN_STOP_PULS, PIN_OUT_ON);
  else
    digitalWrite(PIN_STOP_PULS, PIN_OUT_OFF);

  if (OutLuzOff == cfgLogicOuts)
    digitalWrite(PIN_LUZ_OFF, PIN_OUT_ON);
  else
    digitalWrite(PIN_LUZ_OFF, PIN_OUT_OFF);
  
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

  if (digitalRead(PIN_GENON) == cfgLogicIns)
    InGenOn = IO_ON;
  else
    InGenOn = IO_OFF;
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();
  //_IOLoop();

  _IOLcdLoop();

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
