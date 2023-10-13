#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <NTPClient.h>
#include <PubSubClient.h>
#include <EEPROM.h>

#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "wifi.h"
#include "MQTT.h"
#include "mNTP.h"
#include "modbusTCP.h"
#include "mRAM.h"
#include "wde.h"

/////////////
// Version //
/////////////
// Get from compile time
const char* compdate = __DATE__;
const char* comptime = __TIME__;

////////////////////
// DIO definition //
////////////////////
int   ioInA;
//int   ioInB;
//int   ioInC;

int   ioOutA;
//int   ioOutB;
//int   ioOutC;

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
#define DEVICENAME      "mbtcpmqtt8266"
char* deviceName = DEVICENAME;

/////////////////
// Http server //
/////////////////
ESP8266WebServer httpServer(HTTP_PORT);

int httpStatus;

//////////
// MQTT //
//////////
const char* brokerUrlSt = MQTT_BROKER;
char brokerUrl[MQTT_URL_MAX];
int brokerPort;
const char* brokerUserSt = MQTT_USERNAME;
char brokerUser[MQTT_USER_MAX];
const char* brokerPswdSt = MQTT_PASSWORD;
char brokerPswd[MQTT_PSWD_MAX];

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

String mqttClientId = "mbMQTT-" + String(ESP.getChipId());

int mqttStatus;
unsigned long mqttTick = 0;
int mqttTopic;

//////////
// Time //
//////////
String timeOnString;
unsigned long timeTick = 0;
int timeSec = 0;
int timeMin = 0;
int timeHour = 0;
int timeDay = 0;

int timeTickSec = 0;

//////////
// mNTP //
//////////
String mntpTimeString;
int mntpSec = 0;
int mntpMin = 0;
int mntpHour = 0;

int mntpStatus;
int mntpUpdated = 0;
WiFiUDP mNtpUDP;
NTPClient mNtpClient(mNtpUDP, "pool.ntp.org", 3600);

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
int cfgLogicIns;
int cfgLogicOuts;

///////////////////////
// Modbus TCP server //
///////////////////////
WiFiServer modbusTcpServer(MODBUSTCP_PORT);
int modbusTcpStatus;

WiFiClient modbusTcpClient;

byte         modbusTcpByteArray[MB_MAX_BTYE];
int          modbusTcpIndex;
unsigned int modbusHoldingRegs[MB_MAX_HR];

byte mbFunction;
int  mbStartAddress;
int  mbNumRegisters;
int  mbNumBytes;
int  mbResponseLength;

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

  pinMode(PIN_OUTA, OUTPUT);
  digitalWrite(PIN_OUTA, !cfgLogicOuts);
  ioOutA = OUT_OFF;
  /*
  pinMode(PIN_OUTB, OUTPUT);
  digitalWrite(PIN_OUTB, !cfgLogicOuts);
  ioOutB = OUT_OFF;
  
  pinMode(PIN_OUTC, OUTPUT);
  digitalWrite(PIN_OUTC, !cfgLogicOuts);
  ioOutC = OUT_OFF;
  */

  //-----//
  // INS //
  //-----//
  pinMode(PIN_INA, INPUT);  ioInA = IO_OFF;
  //pinMode(PIN_INB, INPUT);  ioInB = IO_OFF;
  //pinMode(PIN_INC, INPUT);  ioInC = IO_OFF;
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
  Serial.println(compdate);
  #endif
  
  // Config setup
  _ConfigSetup();

  // IO setup
  _PINSetup();
  //_IOSetup();

  // Wi-Fi setup
  _WifiSetup();

  // Http setup
  _HttpSetup();

  // Modbus TCP setup
  _ModbusTcpSetup();

  // Time setup
  _TimeSetup();

  // MQTT setup
  _MQTTSetup();

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

  if (ioOutA == cfgLogicOuts)
    digitalWrite(PIN_OUTA, PIN_OUT_ON);
  else
    digitalWrite(PIN_OUTA, PIN_OUT_OFF);
  /*
  if (ioOutB == cfgLogicOuts)
    digitalWrite(PIN_OUTB, PIN_OUT_ON);
  else
    digitalWrite(PIN_OUTB, PIN_OUT_OFF);

  if (ioOutC == cfgLogicOuts)
    digitalWrite(PIN_OUTC, PIN_OUT_ON);
  else
    digitalWrite(PIN_OUTC, PIN_OUT_OFF); 
  */

  //-----//
  // INS //
  //-----//
  if (digitalRead(PIN_INA) == cfgLogicIns)
    ioInA = IO_ON;
  else
    ioInA = IO_OFF;
  /*
  if (digitalRead(PIN_INB) == cfgLogicIns)
    ioInB = IO_ON;
  else
    ioInB = IO_OFF;

  if (digitalRead(PIN_INC) == cfgLogicIns)
    ioInC = IO_ON;
  else
    ioInC = IO_OFF;
  */
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
  {
    _HttpLoop();
    _ModbusTcpLoop();
  }

  if (wifiStatus == WIFI_STATION_CONNECTED)
    _MQTTLoop();
  else
    mqttStatus = MQTT_NOT_CONNECTED;
  
  _TimeLoop();
}
