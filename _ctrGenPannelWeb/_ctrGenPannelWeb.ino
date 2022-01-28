
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include "__ver.h"

#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "ctr.h"
#include "wifi.h"
#include "mRAM.h"
#include "wde.h"

/////////////
// Version //
/////////////
const char* FW_Version = FW_VERSION;

////////////////////
// DIO definition //
////////////////////
int   OutGen;
int   OutBomba;
int   OutDisp;
int   OutZumb;
int   OutAutoOn;

int   OutA;
int   OutB;
int   OutC;
int   OutD;

int   InStartVal = 0;
int   InStartVal_ant = 0;
int   InStartCounter = 0;
int   InStartState = 0;

int   InEndVal = 0;
int   InEndVal_ant = 0;
int   InEndCounter = 0;
int   InEndState = 0;

int   boardLed;

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

int   TimeGenerador1P;
int   TimeGenerador2P;
int   TimeGenerador3P;
int   TimeGenerador4P;
int   TimeGenerador5P;
int   TimeGenerador6P;
int   TimeGenerador7P;
int   TimeGenerador8P;
int   TimeGenerador9P;

int   TimeBuzzerOn;
int   TimeOutStart;
int   TimeOutStop;
int   DebugVal = 0;

int X_60 = 60;
int X_3600 = 3600;

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

///////////////
// PIN steup //
///////////////
void _PINSetup(void)
{ 
  //------//
  // OUTS //
  //------//

  if (DebugVal == 69)
  {
    // Ledboard
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, PIN_OUT_OFF);
    boardLed = OUT_OFF;  
  } else {
    // Zum OFF
    pinMode(PIN_ZUMB, OUTPUT);
    digitalWrite(PIN_ZUMB, PIN_OUT_OFF);
    OutZumb  = OUT_OFF;
  }

  // Gen OFF
  pinMode(PIN_GEN, OUTPUT);
  digitalWrite(PIN_GEN, PIN_OUT_OFF);
  OutGen   = OUT_OFF;

  // Bomba ON
  pinMode(PIN_BOMBA, OUTPUT);
  digitalWrite(PIN_BOMBA, PIN_OUT_ON);
  OutBomba  = OUT_ON;

  // Disp ON
  pinMode(PIN_DISP, OUTPUT);
  digitalWrite(PIN_DISP, PIN_OUT_ON);
  OutDisp  = OUT_ON;

  // AutoOn ON
  pinMode(PIN_AUTOON, OUTPUT);
  digitalWrite(PIN_AUTOON, PIN_OUT_ON);
  OutAutoOn  = OUT_ON;
  
  pinMode(PIN_A, OUTPUT);
  digitalWrite(PIN_A, PIN_OUT_OFF);
  pinMode(PIN_B, OUTPUT);
  digitalWrite(PIN_B, PIN_OUT_OFF);
  pinMode(PIN_C, OUTPUT);
  digitalWrite(PIN_C, PIN_OUT_OFF);
  pinMode(PIN_D, OUTPUT);
  digitalWrite(PIN_D, PIN_OUT_OFF);

  OutA = OUT_OFF;
  OutB = OUT_OFF;
  OutC = OUT_OFF;
  OutD = OUT_OFF;

  //-----//
  // INS //
  //-----//
  pinMode(PIN_PULSADOR, INPUT);
  pinMode(PIN_END, INPUT);
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

  // PIN & IO Setup
  _PINSetup();
  _IOSetup();

  // Wi-Fi setup
  _WifiSetup();

  // Http setup
  _HttpSetup();

  // Time Setup
  _TimeSetup();

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

  if (DebugVal == 69)
  {
    if (boardLed == OUT_OFF)
      digitalWrite(PIN_LED, PIN_OUT_ON);
    else
      digitalWrite(PIN_LED, PIN_OUT_OFF);    
  } else {
    if (OutZumb == OUT_ON)
      digitalWrite(PIN_ZUMB, PIN_OUT_ON);
    else if (OutZumb == IO_OFF)
      digitalWrite(PIN_ZUMB, PIN_OUT_OFF);
  }
    
  if (OutGen == OUT_ON)
    digitalWrite(PIN_GEN, PIN_OUT_ON);
  else
    digitalWrite(PIN_GEN, PIN_OUT_OFF);
  
  if (OutBomba == OUT_ON)
    digitalWrite(PIN_BOMBA, PIN_OUT_ON);
  else
    digitalWrite(PIN_BOMBA, PIN_OUT_OFF);

  if (OutDisp == OUT_ON)
    digitalWrite(PIN_DISP, PIN_OUT_ON);
  else if (OutDisp == IO_OFF)
    digitalWrite(PIN_DISP, PIN_OUT_OFF);
  
  if (OutAutoOn == OUT_ON)
    digitalWrite(PIN_AUTOON, PIN_OUT_ON);
  else if (OutDisp == IO_OFF)
    digitalWrite(PIN_AUTOON, PIN_OUT_OFF);

  if (OutA == OUT_ON)
    digitalWrite(PIN_A, PIN_OUT_ON);
  else
    digitalWrite(PIN_A, PIN_OUT_OFF);

  if (OutB == OUT_ON)
    digitalWrite(PIN_B, PIN_OUT_ON);
  else
    digitalWrite(PIN_B, PIN_OUT_OFF);

  if (OutC == OUT_ON)
    digitalWrite(PIN_C, PIN_OUT_ON);
  else
    digitalWrite(PIN_C, PIN_OUT_OFF);

  if (OutD == OUT_ON)
    digitalWrite(PIN_D, PIN_OUT_ON);
   else
    digitalWrite(PIN_D, PIN_OUT_OFF);   

  //-----//
  // INS //
  //-----//
  
  if (digitalRead(PIN_PULSADOR) == PIN_IN_OFF)
    InStartVal = IO_OFF;
  else
    InStartVal = IO_ON;

  if (digitalRead(PIN_END) == PIN_IN_OFF)
    InEndVal = IO_OFF;
  else
    InEndVal = IO_ON;
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
  if (DebugVal == 69)
  _WifiLedLoop();
  
  if ((wifiStatus == WIFI_ON_ACCESSPOINT) /*|| (wifiStatus == WIFI_STATION_CONNECTED)*/)
  {
    _HttpLoop();
  }

  _CtrLoop();
  
  _TimeLoop();
}
