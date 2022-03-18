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
#include "ntc.h"
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
int   OutFan;
int   OutClose;
int   OutOpen;
int   OutPump;
int   outLed;

int   OutIrri;
int   OutAux1;
int   OutAux2;

int   InOpen = 0;
int   InOpen_ant = 0;
int   InOpenCounter = 0;
int   InOpenState = 0;

int   InClose = 0;
int   InClose_ant = 0;
int   InCloseCounter = 0;
int   InCloseState = 0;

////////////////
// NTC Analog //
////////////////
int    NtcInADC;
int    NtcInArray[NTC_ARRAY_SIZE];
int    NtcInPointer;
float  NtcIn;

// NTC constantes
float Rc = 10000; // 10k
float Vcc = 3.3;  // Vcc

float A = 1.11492089e-3;
float B = 2.372075385e-4;
float C = 6.954079529e-8;
float K = 2.5;    // factor de disipacion en mW/C

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
#define DEVICENAME      "inv8266"
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
//int TimeControlSec;

int   windowState;
unsigned long windowControlTick = 0;

int   FanState;
unsigned long FanTick = 0;
int   PumpState;
unsigned long PumpTick = 0;
int   IrriState;
unsigned long IrriTick = 0;
int   Aux1State;
unsigned long Aux1Tick = 0;
int   Aux2State;
unsigned long Aux2Tick = 0;

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
int     cfgScaleMin;
int     cfgFanTick;
int     cfgPumpTick;
int     cfgIrriTick;
int     cfgAux1Tick;
int     cfgAux2Tick;

int     cfgLogicIns;
int     cfgLogicOuts;

int     cfgADCf;

int     cfgTempHi;
int     cfgTempLo;
int     cfgTimeOpenMin;
int     cfgTimeCloseMin;
int     cfgTimeCicloMin;

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

  pinMode(PIN_FAN, OUTPUT);
  digitalWrite(PIN_FAN, !cfgLogicOuts);
  OutFan = OUT_OFF; 

  pinMode(PIN_CLOSE, OUTPUT);
  digitalWrite(PIN_CLOSE, !cfgLogicOuts);
  OutClose = OUT_OFF;

  pinMode(PIN_OPEN, OUTPUT);
  digitalWrite(PIN_OPEN, !cfgLogicOuts);
  OutOpen = OUT_OFF;

  pinMode(PIN_PUMP, OUTPUT);
  digitalWrite(PIN_PUMP, !cfgLogicOuts);
  OutPump = OUT_OFF;
  
  pinMode(PIN_IRRI, OUTPUT);
  digitalWrite(PIN_IRRI, !cfgLogicOuts);
  OutIrri = OUT_OFF;

  pinMode(PIN_AUX1, OUTPUT);
  digitalWrite(PIN_AUX1, !cfgLogicOuts);
  OutAux1 = OUT_OFF;

  pinMode(PIN_AUX2, OUTPUT);
  digitalWrite(PIN_AUX2, !cfgLogicOuts);
  OutAux2 = OUT_OFF;
  
  //-----//
  // INS //
  //-----//
  pinMode(PIN_INOPEN, INPUT);
  pinMode(PIN_INCLOSE, INPUT);
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
  _IOSetup();
  _NTCSetup();

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

  if (OutFan == cfgLogicOuts)
    digitalWrite(PIN_FAN, PIN_OUT_ON);
  else
    digitalWrite(PIN_FAN, PIN_OUT_OFF);

  if (OutClose == cfgLogicOuts)
    digitalWrite(PIN_CLOSE, PIN_OUT_ON);
  else
    digitalWrite(PIN_CLOSE, PIN_OUT_OFF);
  
  if (OutOpen == cfgLogicOuts)
    digitalWrite(PIN_OPEN, PIN_OUT_ON);
  else
    digitalWrite(PIN_OPEN, PIN_OUT_OFF); 

  if (OutPump == cfgLogicOuts)
    digitalWrite(PIN_PUMP, PIN_OUT_ON);
  else
    digitalWrite(PIN_PUMP, PIN_OUT_OFF); 
  
  if (OutIrri == cfgLogicOuts)
    digitalWrite(PIN_IRRI, PIN_OUT_ON);
  else
    digitalWrite(PIN_IRRI, PIN_OUT_OFF); 

  if (OutAux1 == cfgLogicOuts)
    digitalWrite(PIN_AUX1, PIN_OUT_ON);
  else
    digitalWrite(PIN_AUX1, PIN_OUT_OFF); 

  if (OutAux2 == cfgLogicOuts)
    digitalWrite(PIN_AUX2, PIN_OUT_ON);
  else
    digitalWrite(PIN_AUX2, PIN_OUT_OFF); 

  //-----//
  // INS //
  //-----//
  if (digitalRead(PIN_INOPEN) == PIN_IN_OFF /*cfgLogicIns*/)
    InOpen = IO_OFF;
  else
    InOpen = IO_ON;

  if (digitalRead(PIN_INCLOSE) == PIN_IN_OFF /*cfgLogicIns*/)
    InClose = IO_OFF;
  else
    InClose = IO_ON;
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
    _MQTTLoop();
  else
    mqttStatus = MQTT_NOT_CONNECTED;

  if (controlMode == MODE_AUTO)
    _CtrLoop();
  
  _TimeLoop();
}
