#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "wifi.h"

////////////////////
// DIO definition //
////////////////////
int outRele;
int outLed; // Led Interno
int outLedInd;

/////////////////////////
// IO State definition //
/////////////////////////
int inValue;
int inState;
unsigned long inTimeoutTick;

unsigned long cfgTimeoutSec;
int cfgLogicIns;
int cfgLogicOuts;

unsigned long countDownSec;

///////////
// Wi-Fi //
///////////
//unsigned long wifiAPTick = 0;
unsigned long wifiLEDTick = 0;

/*
#if (_WRITE_SSID_EEPROM_ == 1)
const char* ssidSt = SSIDST;
const char* passwordSt = PSKST;
#endif
*/

// Station Mode
//char ssid[WIFI_SSID_MAX];
//char password[WIFI_PSWD_MAX];

IPAddress wifiIP;

// Accesspoint Mode
const char* ssidAp = SSIDAP;
const char* passwordAp = PSKAP;

int wifiStatus;
//int wifiMode;

////////////////
// IP Address //
////////////////
/*
int       ipMode;

IPAddress ipAddress (192, 168, 43, 200);
IPAddress gateWay   (192, 168, 43, 1);
IPAddress netMask   (255, 255, 255, 0);

byte mac[6];
*/

/////////////////
// Device Name //
/////////////////
#define DEVICENAME      "batt8266"
char* deviceName = DEVICENAME;

/////////////////
// Http server //
/////////////////
ESP8266WebServer httpServer(HTTP_PORT);

int httpStatus;

/////////////////////
// Charger Control //
/////////////////////
int controlMode = MODE_AUTO;

//////////
// Time //
//////////
unsigned long timeTick = 0;
int timeSec = 0;
int timeMin = 0;
int timeHour = 0;

///////////////
// PIN steup //
///////////////
void _PINSetup(void)
{ 
  //------//
  // OUTS //
  //------//
  
  //pinMode(PIN_LED, OUTPUT);
  //digitalWrite(PIN_LED, PIN_OUT_OFF);
  outLed = OUT_OFF;

  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, PIN_OUT_OFF);
  outRele = OUT_OFF;
  
  pinMode(PIN_LED_IND, OUTPUT);
  digitalWrite(PIN_LED_IND, PIN_OUT_OFF);
  outLedInd = OUT_OFF;

  //-----//
  // INS //
  //-----//
  
  pinMode(PIN_AUX1, INPUT);
  inValue = IN_OFF;
}

//============//
// MAIN SETUP //
//============//
void setup(void)
{ 
  _PINSetup();
  
  _IOSetup();

  delay(500);  // 0.5 secs
  
  #if (_SERIAL_DEBUG_ == 1)
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
}

///////////////////////
// PIN state machine //
///////////////////////
void _PINLoop()
{
  //------//
  // OUTS //
  //------//
  /*
  if (outLed == cfgLogicOuts)
    digitalWrite(PIN_LED, PIN_OUT_OFF);
  else
    digitalWrite(PIN_LED, PIN_OUT_ON);
  */
  if (outLedInd == cfgLogicOuts)
    digitalWrite(PIN_LED_IND, PIN_OUT_OFF);
  else
    digitalWrite(PIN_LED_IND, PIN_OUT_ON);

  if (outRele == cfgLogicOuts)
    digitalWrite(PIN_RELE, PIN_OUT_OFF);
  else
    digitalWrite(PIN_RELE, PIN_OUT_ON);

  //-----//
  // INS //
  //-----//
  
  if (digitalRead(PIN_AUX1) == cfgLogicOuts /*PIN_IN_OFF*/)
    inValue = IN_OFF;
  else
    inValue = IN_ON;
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();

  if (controlMode == MODE_AUTO)
    _IOLoop();
  else
    _TimeSetup();

  _WifiLoop();
  _WifiLedLoop();

  if ((wifiStatus == WIFI_ON_ACCESSPOINT) /*|| (wifiStatus == WIFI_STATION_CONNECTED)*/)
  {
    _HttpLoop();
  }

  _TimeLoop();
}
