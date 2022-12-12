
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

#include <SPI.h>
#include <TFT_eSPI.h>

#include <esp_task_wdt.h>

#include "alarm.h"
#include "ana.h"
#include "ctr.h"
#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "joystick.h"
#include "leds.h"
#include "main.h"
#include "mModbus.h"
#include "mRAM.h"
#include "mRS485.h"
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
//int boardCN1P2;
int   boardP3P2;

int   boardLed1;  // RED
int   boardLed2;  // GREEN
int   boardLed3;  // BLUE

int   ledTest = 0;

///////////
// Alarm //
///////////
int    alarms[AL_ARRAY_SIZE];

////////////
// Analog //
////////////
unsigned long ANTick = 0;
int     boardP3P3;
String  sAnalog;

//////////////
// Joystick //
//////////////
unsigned long joystickTick = 0;
int joystickState;

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
int cfgMbId;

/////////
// TFT //
/////////
TFT_eSPI tft = TFT_eSPI();

unsigned long tftTick = 0;
int   tftState;

unsigned long tftScreenUpdateTick = 0;

unsigned long tftScreenTick = 0;
int tftScreenState;

// Menu
unsigned long tftMenuTick = 0;
int tftMenuState;
int tftMenuSelection;

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
int mbState;
int mbSWake;
unsigned long mbTick;
byte mbCRC[2];

// Modbus DIOs
int mbIns[MB_NUM_IOS];
int mbOuts[MB_NUM_IOS];
int mbROuts[MB_NUM_IOS];

int mbOutBoard = 0;
int mbOutNum = 0;
int mbOutVal = 0x00;

int mbNError = 0;
int mbNReply = 0;
int mbNRetry = 0;
int mbRetry = 0;

#endif
#endif

//////////
// mRAM //
//////////
#if (_USE_RAM_ == 1)
unsigned long freeRam;
#endif

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
  pinMode(PIN_P3P3, INPUT);
  
  //------//
  // LEDS //
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
  // OUT //
  //-----//
  /*
  pinMode(PIN_CN12, OUTPUT);
  digitalWrite(PIN_CN12, PIN_OUT_OFF);
  boardCN1P2 = OUT_OFF;
  */
  //----//
  // IN //
  //----//
  pinMode(PIN_P3P2, INPUT_PULLUP);
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

  // PIN & IO Setup
  _PINSetup();
  _IOSetup();
  _ANASetup();
  _JOYSTICKSetup();

  _ALARMSetup();

  // Wi-Fi setup
  _WifiSetup();

  // Http setup
  _HttpSetup();

  // Time Setup
  _TimeSetup();

  #if (_USE_RS485_ == 1)
  _RS485Setup();
  #if (_USE_MB_ == 1)
  _MBSetup();
  #endif
  #endif

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
  // LEDS //
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
  // OUT //
  //-----//
  /*
  if (boardCN1P2 == OUT_OFF)
    digitalWrite(PIN_CN12, PIN_OUT_ON);
  else
    digitalWrite(PIN_CN12, PIN_OUT_OFF); 
  */
  //----//
  // IN //
  //----//
  
  if (digitalRead(PIN_P3P2) == PIN_IN_OFF)
    boardP3P2 = IO_OFF;
  else
    boardP3P2 = IO_ON;

}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();
  _IOLoop();
  _ANALoop();
  _JOYSTICKLoop();
  
  //if (ctrMode == MODE_AUTO)
  //  _OUTSLoop();

  _WifiLoop();
  //_WifiLedLoop();
  
  if ((wifiStatus == WIFI_ON_ACCESSPOINT) /*|| (wifiStatus == WIFI_STATION_CONNECTED)*/)
    _HttpLoop();
  
  _CtrLoop();
  _mTftLoop();
  
  _TimeLoop();
  
  #if (_USE_RS485_ == 1)
  _RS485Loop();
  #if (_USE_MB_ == 1)
  _MBLoop();
  #endif
  #endif

  //_ALARMLoop();
}
