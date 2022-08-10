#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <EEPROM.h>

#include "__ver.h"

#include "adcs.h"
#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "ctr.h"
#include "wifi.h"
#include "MQTT.h"
#include "mModbus.h"
#include "mRAM.h"
#include "mRS485.h"
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
int   InE;

int   OutA;
int   OutB;
int   OutC;

int   outLed;

///////////
// Adc //
///////////
int    AdcIn;
int    AdcInArray[ADC_ARRAY_SIZE];
int    AdcInPointer;
float  AdcVal;

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
#define DEVICENAME      "mbmqtt8266"
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

String mqttClientId = "mbMQTT-" + String(ESP.getChipId());

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

///////////
// RS485 //
///////////
#if (_USE_RS485_ == 1)
// RS485
int             mrs485State;
String          mrs485RxBuffer = "";
unsigned long   mrs485tick;
char            mrs485TxBuffer[MRS485_ARRAY_SIZE];
int             mrs485TxNumBytes;

int             OutRS485rxtx;

////////////
// Modbus //
////////////
#if (_USE_MB_ == 1)
int             mbState;
unsigned long   mbTick;
byte            mbCRC[2];

// Modbus DIOs
int             mbInBoard = 0;
int             mbIns[MB_NUM_IOS][MB_NUM_BRS];
int             mbOuts[MB_NUM_IOS][MB_NUM_BRS];

int             mbOutBoard = 0;
int             mbOutNum = 0;
int             mbOutVal = 0x00;
#endif
#endif

////////
// WD //
////////
#if (_USE_WDE_ == 1)
int wdeForceReset;
#endif

////////////
// Config //
////////////
int     cfgLogicIns;
int     cfgLogicOuts;
int     cfgMB1Add;
int     cfgMB2Add;

int     cfgADCm;
int     cfgADCb;
int     cfgADCp;
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

  pinMode(PIN_OA, OUTPUT);
  digitalWrite(PIN_OA, !cfgLogicOuts);
  OutA = OUT_OFF;

  pinMode(PIN_OB, OUTPUT);
  digitalWrite(PIN_OB, !cfgLogicOuts);
  OutB = OUT_OFF;
  
  pinMode(PIN_OC, OUTPUT);
  digitalWrite(PIN_OC, !cfgLogicOuts);
  OutC = OUT_OFF;

  #if (_USE_RS485_ == 1)
  pinMode(PIN_RS485_RXTX, OUTPUT);
  digitalWrite(PIN_RS485_RXTX, HIGH);
  OutRS485rxtx = OUT_RS485_RX;
  #endif
  
  //-----//
  // INS //
  //-----//
  pinMode(PIN_A, INPUT);  InA = IO_OFF;
  pinMode(PIN_B, INPUT);  InB = IO_OFF;
  pinMode(PIN_C, INPUT);  InC = IO_OFF;
  pinMode(PIN_D, INPUT);  InD = IO_OFF;
  pinMode(PIN_E, INPUT);  InE = IO_OFF;
}

//============//
// MAIN SETUP //
//============//
void setup(void)
{  
  #if (_SERIAL_DEBUG_ == 1)
  delay(100);  // 100ms
  Serial.begin(9600);
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

  #if (_USE_RS485_ == 1)
  _RS485Setup();
  #if (_USE_MB_ == 1)
  _MBSetup();
  #endif
  #endif
  
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

  if (OutA == cfgLogicOuts /*OUT_ON*/)
    digitalWrite(PIN_OA, PIN_OUT_ON);
  else
    digitalWrite(PIN_OA, PIN_OUT_OFF);

  if (OutB == cfgLogicOuts /*OUT_ON*/)
    digitalWrite(PIN_OB, PIN_OUT_ON);
  else
    digitalWrite(PIN_OB, PIN_OUT_OFF);

  if (OutC == cfgLogicOuts /*OUT_ON*/)
    digitalWrite(PIN_OC, PIN_OUT_ON);
  else
    digitalWrite(PIN_OC, PIN_OUT_OFF); 

  #if (_USE_RS485_ == 1)
  if (OutRS485rxtx == OUT_RS485_RX)
    digitalWrite(PIN_RS485_RXTX, LOW);
  else
    digitalWrite(PIN_RS485_RXTX, HIGH);
  #endif

  //-----//
  // INS //
  //-----//
  if (digitalRead(PIN_A) == cfgLogicIns /*PIN_IN_ON*/)
    InA = IO_ON;
  else
    InA = IO_OFF;

  if (digitalRead(PIN_B) == cfgLogicIns /*PIN_IN_ON*/)
    InB = IO_ON;
  else
    InB = IO_OFF;

  if (digitalRead(PIN_C) == cfgLogicIns /*PIN_IN_ON*/)
    InC = IO_ON;
  else
    InC = IO_OFF;

  if (digitalRead(PIN_D) == cfgLogicIns /*PIN_IN_ON*/)
    InD = IO_ON;
  else
    InD = IO_OFF;

  if (digitalRead(PIN_E) == cfgLogicIns /*PIN_IN_ON*/)
    InE = IO_ON;
  else
    InE = IO_OFF;
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

  #if (_USE_RS485_ == 1)
  _RS485Loop();
  #if (_USE_MB_ == 1)
  _MBLoop();
  #endif
  #endif
}
