#include <WiFi.h>
//#include <WiFiUdp.h>
#include <WebServer.h>
#include <EEPROM.h>

#include "adcs.h"
#include "ctr.h"
#include "e2prom.h"
#include "http.h"
#include "intisr.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "wifi.h"
#include "mRAM.h"
#include "wde.h"

/////////////
// Version //
/////////////
// Get from compile time
const char* compdate = __DATE__;
const char* comptime = __TIME__;

//////////
// ADCs //
//////////
int   AdcDig[ADC_NUMBER];
int   AdcPin[ADC_NUMBER];
//int   AdcArray[ADC_NUMBER][ADC_ARRAY_SIZE];
//int   AdcPointer[ADC_NUMBER];

//////////
// OUTs //
//////////
int   OutPin[OUT_NUMBER];
int   OutDig[OUT_NUMBER];

int   outLed;
int   rgbPin[3];
int   rgbDig[3];

//////////
// INs //
//////////
int   InPin[IN_NUMBER];
int   InDig[IN_NUMBER];

/////////
// ISR //
/////////
unsigned long   inPulseD2 = 0;
unsigned long   inPulseAntD2 = 0;
unsigned long   pulsesD2;
unsigned long   RpmCounterD2 = 0;
unsigned long   RpmTickD2 = 0;
unsigned long   RpmPeriodD2 = 0;

unsigned long   inPulseD3 = 0;
unsigned long   inPulseAntD3 = 0;
unsigned long   pulsesD3;
unsigned long   RpmCounterD3 = 0;
unsigned long   RpmTickD3 = 0;
unsigned long   RpmPeriodD3 = 0;

/////////////
// Control //
/////////////
int   controlMode;

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
#define DEVICENAME      "EFISnanoESP32"
char* deviceName = DEVICENAME;

/////////////////
// Http server //
/////////////////
WebServer httpServer(HTTP_PORT);

int httpStatus;

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
int cfgTimefOuts;

///////////////
// PIN steup //
///////////////
void _PINSetup(void)
{ 
  int i;

  //------//
  // OUTS //
  //------//

  #if (_USE_LED_INDICATOR_ == 1)
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, PIN_OUT_OFF);
  outLed = IO_OFF;
  #endif

  #if (_USE_RGB_ == 1)
  for (i = 0; i < 3; i++)
  {
    pinMode(rgbPin[i], OUTPUT);
    digitalWrite(rgbPin[i], PIN_OUT_OFF);
    rgbDig[i] = OUT_OFF;
  }
  #endif

  for (i = 0; i < OUT_NUMBER; i++)
  {
    pinMode(OutPin[i], OUTPUT);
    digitalWrite(OutPin[i], PIN_OUT_OFF);
    OutDig[i] = OUT_OFF;
  }

  //-----//
  // INS //
  //-----//
  for (i = 0; i < IN_NUMBER; i++)
  {
    pinMode(InPin[i], INPUT);
    InDig[i] = 0;
  }
}

//============//
// MAIN SETUP //
//============//
void setup(void)
{  
  #if (_SERIAL_DEBUG_ == 1)
  delay(5000);
  Serial.begin(9600);
  Serial.print("Project: ");
  Serial.println(PROJECT);
  Serial.print("Version: ");
  Serial.println(compdate);
  #endif
  
  // Config setup
  _ConfigSetup();

  /// PIN & IO Setup
  _IOSetup();
  _PINSetup();
  _ADCsSetup();
  _INTISRsSetup();

  // Control
  _CtrSetup();

  // Wi-Fi setup
  _WifiSetup();

  // Http setup
  _HttpSetup();

  // Time setup
  _TimeSetup();

  #if (_USE_WDE_ == 1)
  _WDESetup();
  #endif
}

///////////////////////
// PIN state machine //
///////////////////////
void _PINLoop()
{
  int i;
  
  //------//
  // OUTS //
  //------//
  #if (_USE_LED_INDICATOR_ == 1)
  if (outLed == OUT_OFF)
    digitalWrite(PIN_LED, PIN_OUT_ON);
  else
    digitalWrite(PIN_LED, PIN_OUT_OFF);
  #endif

  #if (_USE_RGB_ == 1)
  for (i = 0; i < 3; i++)
  {
    if (rgbDig[i] == OUT_ON)
      digitalWrite(rgbPin[i], RGB_OUT_ON);
    else
      digitalWrite(rgbPin[i], RGB_OUT_OFF);
  }
  #endif

  for (i = 0; i < OUT_NUMBER; i++)
  {
    if (OutDig[i] == OUT_ON)
      digitalWrite(OutPin[i], PIN_OUT_ON);
    else
      digitalWrite(OutPin[i], PIN_OUT_OFF);
  }

  //-----//
  // INS //
  //-----//
  for (i = 0; i < IN_NUMBER; i++)
  {
    if (digitalRead(InPin[i]) == PIN_IN_OFF)
      InDig[i] = IO_OFF;
    else
      InDig[i] = IO_ON;
  }
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
  
  if (controlMode == MODE_AUTO)
    _CtrLoop();

  _TimeLoop();
}
