
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "ctr.h"
#include "wifi.h"

////////////////////
// DIO definition //
////////////////////
int   OutGen;
int   OutDisp;
int   OutZumb;

int   OutD3;
int   OutD4;
int   OutD5;
int   OutD6;

int   PulsadorDigInStatus = 0;
int   PulsadorDigInStatus_ant = 0;
int   PulsadorDigInCounter = 0;
int   PulsadorPulsacion = 0;

int   outLed;

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
#define DEVICENAME      "pannel8266"
char* deviceName = DEVICENAME;

/////////////////
// Http server //
/////////////////
ESP8266WebServer httpServer(HTTP_PORT);

int httpStatus;

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

int   TimeBuzzerOn;

int   TimeGenerador1P;
int   TimeGenerador2P;
int   TimeGenerador3P;
int   TimeGenerador4P;
int   TimeGenerador5P;
int   TimeGenerador6P;
int   TimeGenerador7P;
int   TimeGenerador8P;
int   TimeGenerador9P;

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
  outLed = IO_OFF;

  pinMode(PIN_GEN, OUTPUT);
  digitalWrite(PIN_GEN, PIN_OUT_ON);
  OutGen   = OUT_ON;

  pinMode(PIN_DISP, OUTPUT);
  digitalWrite(PIN_DISP, PIN_OUT_ON);
  OutDisp  = OUT_ON;

  pinMode(PIN_ZUMB, OUTPUT);
  digitalWrite(PIN_ZUMB, PIN_OUT_OFF);
  OutZumb  = OUT_OFF;

  pinMode(PIN_D3, OUTPUT);
  digitalWrite(PIN_D3, PIN_OUT_OFF);
  pinMode(PIN_D4, OUTPUT);
  digitalWrite(PIN_D4, PIN_OUT_OFF);
  pinMode(PIN_D5, OUTPUT);
  digitalWrite(PIN_D5, PIN_OUT_OFF);
  pinMode(PIN_D6, OUTPUT);
  digitalWrite(PIN_D6, PIN_OUT_OFF);

  OutD3 = OUT_OFF;
  OutD4 = OUT_OFF;
  OutD5 = OUT_OFF;
  OutD6 = OUT_OFF;

  //-----//
  // INS //
  //-----//
  pinMode(PIN_PULSADOR, INPUT);
}

//============//
// MAIN SETUP //
//============//
void setup(void)
{ 
  _PINSetup();
  
  _IOSetup();

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

  if (outLed == OUT_OFF)
    digitalWrite(PIN_LED, PIN_OUT_ON);
  else
    digitalWrite(PIN_LED, PIN_OUT_OFF);
    
  if (OutGen == OUT_ON)
    digitalWrite(PIN_GEN, PIN_OUT_ON);
  else
    digitalWrite(PIN_GEN, PIN_OUT_OFF);

  if (OutZumb == OUT_ON)
    digitalWrite(PIN_ZUMB, PIN_OUT_ON);
  else if (OutZumb == IO_OFF)
    digitalWrite(PIN_ZUMB, PIN_OUT_OFF);

  if (OutDisp == OUT_ON)
    digitalWrite(PIN_DISP, PIN_OUT_ON);
  else if (OutDisp == IO_OFF)
    digitalWrite(PIN_DISP, PIN_OUT_OFF);

  if (OutD3 == OUT_ON)
    digitalWrite(PIN_D3, PIN_OUT_ON);
  else
    digitalWrite(PIN_D3, PIN_OUT_OFF);

  if (OutD4 == OUT_ON)
    digitalWrite(PIN_D4, PIN_OUT_ON);
  else
    digitalWrite(PIN_D4, PIN_OUT_OFF);

  if (OutD5 == OUT_ON)
    digitalWrite(PIN_D5, PIN_OUT_ON);
  else
    digitalWrite(PIN_D6, PIN_OUT_OFF);

  if (OutD6 == OUT_ON)
    digitalWrite(PIN_D6, PIN_OUT_ON);
   else
    digitalWrite(PIN_D6, PIN_OUT_OFF);   

  //-----//
  // INS //
  //-----//
  
  if (digitalRead(PIN_PULSADOR) == PIN_IN_OFF)
    PulsadorDigInStatus = IO_OFF;
  else
    PulsadorDigInStatus = IO_ON;
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();
  _IOLoop();
  _IOPulsLoop();
  _IOLcdLoop();

  //if (controlMode == MODE_AUTO)
  //  _OUTSLoop();

  _WifiLoop();
  _WifiLedLoop();

  if ((wifiStatus == WIFI_ON_ACCESSPOINT) /*|| (wifiStatus == WIFI_STATION_CONNECTED)*/)
  {
    _HttpLoop();
  }

  _CtrLoop();
  _TimeLoop();
}
