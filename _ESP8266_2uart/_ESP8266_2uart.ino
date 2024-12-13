#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "wifi.h"
#include "mRAM.h"
#include "m2UART.h"
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
int   ioInB;

int   ioOutA;
int   ioOutB;

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

//String ChipId = String(ESP.getChipId());

// Accesspoint Mode
//const char* ssidAp = SSIDAP;
String ssidAp = "ESP-2uart" + String(ESP.getChipId());
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

byte mac[6] = {0xF8, 0xDC, 0x7A, 0x00, 0x02, 0x04};

/////////////////
// Device Name //
/////////////////
#define DEVICENAME      "ESP-2uart"
char* deviceName = DEVICENAME;

/////////////////
// Http server //
/////////////////
ESP8266WebServer httpServer(HTTP_PORT);

int httpStatus;

#if (_USE_2UART_ == 1)
//String        http2UartRxBuffer = "";
int             http2Uart0RxNumBytes = 0;
int             http2Uart0TxNumBytes = 0;
//String        http2UartTxBuffer = "";
int             http2Uart2RxNumBytes = 0;
int             http2Uart2TxNumBytes = 0;
#endif

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

///////////
// 2UART //
///////////
#if (_USE_2UART_ == 1)
int             m2UartState;
String          m2UartRxBuffer = "";
int             m2UartRxNumBytes;
unsigned long   m2Uarttick;
char            m2UartTxBuffer[M2UART_ARRAY_SIZE];
int             m2UartTxNumBytes;

int             m2UartTxFrames;
int             m2UartRxFrames;
int             m2UartNoResponses;

int             m2UartRXTX_INV;
int             m2UartRXTX_OF;

int             OUT_m2UART0_RX = 0;
int             OUT_m2UART0_TX = 1;
int             OUT_m2UART2_RX = 1;
int             OUT_m2UART2_TX = 0;

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
int cfgLogicRXTX0;
int cfgLogicRXTX2;
int cfgUart2ToutMs;

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

  /*
  pinMode(PIN_OA, OUTPUT);
  digitalWrite(PIN_OA, !cfgLogicOuts);
  ioOutA = OUT_OFF;

  pinMode(PIN_OB, OUTPUT);
  digitalWrite(PIN_OB, !cfgLogicOuts);
  ioOutB = OUT_OFF;
  */

  #if (_USE_2UART_ == 1)
  pinMode(PIN_RXTX_INV, OUTPUT);
  digitalWrite(PIN_RXTX_INV, HIGH);
  m2UartRXTX_INV = OUT_m2UART0_RX;

  pinMode(PIN_RXTX_OF, OUTPUT);
  digitalWrite(PIN_RXTX_OF, HIGH);
  m2UartRXTX_OF = OUT_m2UART2_RX;
  #endif
  
  //-----//
  // INS //
  //-----//
  /*
  pinMode(PIN_A, INPUT);  ioInA = IO_OFF;
  pinMode(PIN_B, INPUT);  ioInB = IO_OFF;
  */
}

//============//
// MAIN SETUP //
//============//
void setup(void)
{
  #if (_SERIAL_DEBUG_ == 1)
  delay(100);
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

  // Time setup
  _TimeSetup();

  #if (_USE_2UART_ == 1)
  _2UARTSetup();
  #endif
  
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
  /*
  if (ioOutA == cfgLogicOuts)
    digitalWrite(PIN_OA, PIN_OUT_ON);
  else
    digitalWrite(PIN_OA, PIN_OUT_OFF);

  if (ioOutB == cfgLogicOuts)
    digitalWrite(PIN_OB, PIN_OUT_ON);
  else
    digitalWrite(PIN_OB, PIN_OUT_OFF);
  */

  #if (_USE_2UART_ == 1)
  if (m2UartRXTX_INV == OUT_m2UART0_RX)
    digitalWrite(PIN_RXTX_INV, LOW);
  else
    digitalWrite(PIN_RXTX_INV, HIGH);

  if (m2UartRXTX_OF == OUT_m2UART2_RX)
    digitalWrite(PIN_RXTX_OF, LOW);
  else
    digitalWrite(PIN_RXTX_OF, HIGH);
  #endif

  //-----//
  // INS //
  //-----//
  /*
  if (digitalRead(PIN_A) == cfgLogicIns)
    ioInA = IO_ON;
  else
    ioInA = IO_OFF;

  if (digitalRead(PIN_B) == cfgLogicIns
    ioInB = IO_ON;
  else
    ioInB = IO_OFF;
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
    _HttpLoop();
  
  _TimeLoop();

  #if (_USE_2UART_ == 1)
  _2UARTLoop();
  #endif
}
