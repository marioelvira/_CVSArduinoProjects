
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "manitou.h"
#include "wifi.h"

////////////////////
// DIO definition //
////////////////////
int outReleCorte;
int outLed;
int outAlarma;

/////////////////////////
// IO State definition //
/////////////////////////
int inValue[5];
int inState[4];
unsigned long inTimeTick[4];
int outValue[4];
int outAlarm[4];
unsigned long inTimeoutSec[4];

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
#define DEVICENAME      "mani8266"
char* deviceName = DEVICENAME;

/////////////////
// Http server //
/////////////////
ESP8266WebServer httpServer(HTTP_PORT);

int httpStatus;

/////////////////////
// Manitou Control //
/////////////////////
int manitouControlMode = MODE_AUTO;
int manitouNumberOfOns = 0;
int manitouNumberOfOns2Save = 1;
int manitouNumberOfHours = 0;
int manitouNumberOfMins = 0;
int manitouNumberOfMins2Increment = 1;
int manitouOnFilter = 0;

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
  
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, PIN_OUT_OFF);
  outLed = OUT_OFF;

  pinMode(PIN_RELE_CORTE, OUTPUT);
  digitalWrite(PIN_RELE_CORTE, PIN_OUT_OFF);
  outReleCorte = OUT_OFF;

  pinMode(PIN_ALARMA, OUTPUT);
  digitalWrite(PIN_ALARMA, PIN_OUT_OFF);
  outAlarma = OUT_OFF;

  //-----//
  // INS //
  //-----//
  
  pinMode(PIN_MOTOR, INPUT);
  inValue[INDEX_MOTOR] = IN_OFF;

  pinMode(PIN_AGUA, INPUT);
  inValue[INDEX_AGUA] = IN_OFF;

  pinMode(PIN_ACEITE, INPUT);
  inValue[INDEX_ACEITE] = IN_OFF;

  pinMode(PIN_AUX1, INPUT);
  inValue[INDEX_AUX1] = IN_OFF;

  pinMode(PIN_AUX2, INPUT);
  inValue[INDEX_AUX2] = IN_OFF;
}

//============//
// MAIN SETUP //
//============//
void setup(void)
{ 
  _PINSetup();
  
  _IOSetup(INDEX_AGUA);   // Agua
  _IOSetup(INDEX_ACEITE); // Aceite
  _IOSetup(INDEX_AUX1);   // Aux1
  _IOSetup(INDEX_AUX2);   // Aux2

  #if (_SERIAL_DEBUG_ == 1)
  delay(5000);  // 5 secs
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

  // Manitou setup
  _ManitouSetup();
}

///////////////////////
// PIN state machine //
///////////////////////
void _PINLoop()
{
  //------//
  // OUTS //
  //------//
  
  if (outLed == OUT_OFF)
    digitalWrite(PIN_LED, PIN_OUT_OFF);
  else
    digitalWrite(PIN_LED, PIN_OUT_ON);

  if (outAlarma == OUT_OFF)
    digitalWrite(PIN_ALARMA, PIN_OUT_OFF);
  else
    digitalWrite(PIN_ALARMA, PIN_OUT_ON);

  if (outReleCorte == OUT_OFF)
    digitalWrite(PIN_RELE_CORTE, PIN_OUT_OFF);
  else
    digitalWrite(PIN_RELE_CORTE, PIN_OUT_ON);

  //-----//
  // INS //
  //-----//
  
  if (digitalRead(PIN_MOTOR) == PIN_IN_OFF)
    inValue[INDEX_MOTOR] = IN_OFF;
  else
    inValue[INDEX_MOTOR] = IN_ON;

  if (digitalRead(PIN_AGUA) == PIN_IN_OFF)
    inValue[INDEX_AGUA] = IN_OFF;
  else
    inValue[INDEX_AGUA] = IN_ON;

  if (digitalRead(PIN_ACEITE) == PIN_IN_OFF)
    inValue[INDEX_ACEITE] = IN_OFF;
  else
    inValue[INDEX_ACEITE] = IN_ON;

  if (digitalRead(PIN_AUX1) == PIN_IN_OFF)
    inValue[INDEX_AUX1] = IN_OFF;
  else
    inValue[INDEX_AUX1] = IN_ON;

  if (digitalRead(PIN_AUX2) == PIN_IN_OFF)
    inValue[INDEX_AUX2] = IN_OFF;
  else
    inValue[INDEX_AUX2] = IN_ON;
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();
  
  _IOLoop(INDEX_AGUA);    // Agua
  _IOLoop(INDEX_ACEITE);  // Aceite
  _IOLoop(INDEX_AUX1);    // Aux1
  _IOLoop(INDEX_AUX2);    // Aux2

  if (manitouControlMode == MODE_AUTO)
    _OUTSLoop();

  _WifiLoop();
  _WifiLedLoop();

  if ((wifiStatus == WIFI_ON_ACCESSPOINT) /*|| (wifiStatus == WIFI_STATION_CONNECTED)*/)
  {
    _HttpLoop();
  }

  _ManitouLoop();
  _TimeLoop();
}
