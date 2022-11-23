
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

#include <SPI.h>
#include <TFT_eSPI.h>

#include <esp_task_wdt.h>

#include "ana.h"
#include "ctr.h"
#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "leds.h"
#include "main.h"
#include "mRAM.h"
#include "mTft.h"
#include "wde.h"
#include "wifi.h"

/////////////
// Version //
/////////////
// Get from compile time
const char* compdate = __DATE__;
const char* comptime = __TIME__;

////////////////////
// DIO definition //
////////////////////
int   boardIO1;
int   boardIO2;

int   boardLed1;  // RED
int   boardLed2;  // GREEN
int   boardLed3;  // BLUE

int   ledTest = 0;

////////////
// Analog //
////////////
unsigned long ANTick = 0;
int     boardAN0;
String  sAnalog;

///////////
// Wi-Fi //
///////////
unsigned long wifiAPTick = 0;
unsigned long wifiLEDTick = 0;

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
#define DEVICENAME      "tftESP32"
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

/////////////
// Control //
/////////////
int ctrMode = MODE_AUTO;
unsigned long ctrTick = 0;
int ctrState;

// Variables
int engineRMP;
int carbPreasure;
int batteryVolt;
int batteryAmp;

////////////
// Config //
////////////
int   TimeGenerador1P;
int   TimeGenerador2P;
int   TimeGenerador3P;
int   TimeGenerador4P;
int   TimeGenerador5P;
int   TimeGenerador6P;
int   TimeGenerador7P;
int   TimeGenerador8P;
int   TimeGenerador9P;

/////////
// TFT //
/////////
TFT_eSPI tft = TFT_eSPI();
unsigned long tftTick = 0;
int   tftState;

unsigned long screenTick = 0;

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
  //-----//
  // ADC //
  //-----//
  pinMode(PIN_ANA0, INPUT);
  //pinMode(PIN_ANA1, INPUT);
  
  //------//
  // OUTS //
  //------//

  // Ledboards
  pinMode(PIN_LED1, OUTPUT);
  digitalWrite(PIN_LED1, PIN_OUT_OFF);
  boardLed1 = OUT_OFF;

  pinMode(PIN_LED2, OUTPUT);
  digitalWrite(PIN_LED2, PIN_OUT_OFF);
  boardLed2 = OUT_OFF;

  pinMode(PIN_LED3, OUTPUT);
  digitalWrite(PIN_LED3, PIN_OUT_OFF);
  boardLed3 = OUT_OFF;

  //-----//
  // INS //
  //-----//
  pinMode(PIN_IO1, INPUT);
  pinMode(PIN_IO2, INPUT);
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
  Serial.println(compdate);
  #endif
    
  // Config setup
  _ConfigSetup();

  // PIN & IO Setup
  _PINSetup();
  _IOSetup();
  _ANASetup();

  // Wi-Fi setup
  _WifiSetup();

  // Http setup
  _HttpSetup();

  // Time Setup
  _TimeSetup();

  // Ctr setup
  _CtrSetup();

  // TFT setup
  _mTftSetup();
  
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

  if (boardLed1 == OUT_OFF)
    digitalWrite(PIN_LED1, PIN_OUT_ON);
  else
    digitalWrite(PIN_LED1, PIN_OUT_OFF);    

  if (boardLed2 == OUT_OFF)
    digitalWrite(PIN_LED2, PIN_OUT_ON);
  else
    digitalWrite(PIN_LED2, PIN_OUT_OFF);  

  if (boardLed3 == OUT_OFF)
    digitalWrite(PIN_LED3, PIN_OUT_ON);
  else
    digitalWrite(PIN_LED3, PIN_OUT_OFF);  

  //-----//
  // INS //
  //-----//
  if (digitalRead(PIN_IO1) == PIN_IN_OFF)
    boardIO1 = IO_OFF;
  else
    boardIO1 = IO_ON;

  if (digitalRead(PIN_IO2) == PIN_IN_OFF)
    boardIO2 = IO_OFF;
  else
    boardIO2 = IO_ON;
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();
  _IOLoop();
  _ANALoop();
  
  //if (ctrMode == MODE_AUTO)
  //  _OUTSLoop();

  _WifiLoop();
  //_WifiLedLoop();
  
  if ((wifiStatus == WIFI_ON_ACCESSPOINT) /*|| (wifiStatus == WIFI_STATION_CONNECTED)*/)
    _HttpLoop();
  
  _CtrLoop();
  _mTftLoop();
  
  _TimeLoop();
}
