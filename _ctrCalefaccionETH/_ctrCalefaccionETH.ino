#include "main.h"

#include <EEPROM.h>
#include <UIPEthernet.h>

#if (_USE_MQTT_ == 1)
#include <PubSubClient.h>
#endif
#if (_USE_NTP_ == 1)
#include <NTPClient.h>
#endif

#if (_USE_WDE_ == 1)
#include <avr/io.h>
#include <avr/wdt.h>
#endif

#include "ctr.h"
#include "e2prom.h"
#if (_USE_HTTP_ == 1)
#include "http.h"
#endif
#include "io.h"
#include "ip.h"
#include "mEthernet.h"
#if (_USE_MBRTU_ == 1)
#include "modbusRTU.h"
#endif
#if (_USE_MQTT_ == 1)
#include "MQTT.h"
#endif
#if (_USE_NTP_ == 1)
#include "mNTP.h"
#endif
#if (_USE_RS485_ == 1)
#include "mRS485.h"
#endif
#if (_USE_WDE_ == 1)
#include "wde.h"
#endif

/////////////
// Version //
/////////////
// Get from compile time
const char* compdate = __DATE__;
const char* comptime = __TIME__;

///////////////
// Board Led //
///////////////
#if (_USE_LED_ == 1)
int   boardLed;
#endif

/////////////
// IO Tick //
/////////////
//unsigned long ioTick = 0;

//////////
// OUTs //
//////////
int   OutPin[OUT_NUMBER];
int   OutDig[OUT_NUMBER];

//////////
// INs //
//////////
int   InPin[IN_NUMBER];
int   InDig[IN_NUMBER];

//////////
// Time //
//////////
String timeOnString;
unsigned long timeTick = 0;
unsigned long timeSecTick = 0;
int timeSec = 0;
int timeMin = 0;
int timeHour = 0;
int timeDay = 0;

/////////////
// Control //
/////////////
String ctrStateString;
int ctrMode;
int ctrInState;
int ctrOutState;

int ctrTempPrin = 0;
int ctrTemp = 0;

////////////
// Config //
////////////
bool cfgLogicIns;
bool cfgLogicOuts;

int cfgResPrim1Vout;
int cfgResPrim2Vout;
int cfgResInyeVout;
int cfgResPrimInyeTemp;
int cfgResPrimConsTemp;
int cfgResPrimHystTemp;
int cfgResInyeConsTemp;
int cfgResInyeHystTemp;
int cfgAguaConsTemp;
int cfgAguaHystTemp;

int cfgResPrimAlarMin;
int cfgResInyeAlarMin;
int cfgAguaAlarMin;

//////////////
// Ethernet //
//////////////
#if (_USE_ETHERNET_ == 1)
int       ipMode;

uint8_t macAddress[6] = {0xF8, 0xDC, 0x7A, 0x00, 0x02, 0x04};
uint8_t ipAddress[4]  = {192,168,1,50};
uint8_t gateWay[4]    = {192,168,1,1};
uint8_t netMask[4]    = {255,255,255,0};
uint8_t dnsAddress[4]; // No incializar

int ethStatus;
#endif

//////////
// mNTP //
//////////
#if (_USE_NTP_ == 1)
String mntpTimeString;
int mntpSec = 0;
int mntpMin = 0;
int mntpHour = 0;

int mntpStatus;
int mntpUpdated = 0;
EthernetUDP mNtpUDP;
NTPClient mNtpClient(mNtpUDP, "pool.ntp.org", 3600);
#endif

//////////
// MQTT //
//////////
#if (_USE_MQTT_ == 1)
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

String mqttClientId = "caleMQTT-INIT";

int mqttStatus;
unsigned long mqttTick = 0;

int mqttTopic;
#endif

//////////
// HTTP //
//////////
#if (_USE_HTTP_ == 1)
EthernetServer httpServer(HTTP_PORT);
int httpServerStatus;

EthernetClient httpClient;
int httpClientStatus;
bool httpClientConnected;

byte  http1stline;
String httpRxString;
unsigned long   httpRxTick;

int   httpTxPage;

String httpRxConfig[HTTP_RX_MAX_CONF];

#endif

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

////////////////
// Modbus RTU //
////////////////
#if (_USE_MB_ == 1)
int mbState;
int mbSWake;
unsigned long mbTick;
byte mbCRC[2];

// Modbus DIOs
int mbInNBoard = 0;
int mbIns[MB_NUM_IOS][MB_NUM_BRS];
int mbOutNBoard = 0;
int mbOuts[MB_NUM_IOS][MB_NUM_BRS];
int mbROuts[MB_NUM_IOS][MB_NUM_BRS];

int mbOutBoard = 0;
int mbOutNum = 0;
int mbOutVal = 0x00;

int mbNError = 0;
int mbNReply = 0;
int mbNRetry = 0;
int mbRetry = 0;

int mbWhat2read = 0;

int mbInsAlarm[MB_NUM_IOS][MB_NUM_BRS];
#endif
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
  int i;

  // Ledboard
  #if (_USE_LED_ == 1)
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, PIN_OUT_OFF);
  boardLed = OUT_OFF;
  #endif

  //------//
  // OUTS //
  //------//
  for (i = 0; i < OUT_NUMBER; i++)
  {
    pinMode(OutPin[i], OUTPUT);
    digitalWrite(OutPin[i], !cfgLogicOuts /*PIN_OUT_OFF*/);
    OutDig[i] = OUT_OFF;
  }

  #if (_USE_RS485_RXTX_ == 1)
  pinMode(PIN_RS485_RXTX, OUTPUT);
  digitalWrite(PIN_RS485_RXTX, HIGH);
  OutRS485rxtx = OUT_RS485_RX;
  #endif

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
  delay(100);  // 100ms
  Serial.begin(9600);
  Serial.print("Project: ");
  Serial.println(PROJECT);
  Serial.print("Version: ");
  Serial.println(compdate);
  Serial.print("Time: ");
  Serial.println(comptime);
  #endif

  // Config setup
  _ConfigSetup();

  // PIN & IO Setup
  _IOSetup();
  _PINSetup();

  // Time Setup
  _TimeSetup();

  // Ctr setup
  _CtrSetup();

  #if (_USE_WDE_ == 1)
  _WDESetup();
  #endif

  #if (_USE_ETHERNET_ == 1)
  _ETHSetup();
  #endif
}

///////////////////////
// PIN state machine //
///////////////////////
void _PINLoop()
{
  int i;

  //-----------//
  // Board Led //
  //-----------//
  #if (_USE_LED_ == 1)
  if (boardLed == OUT_OFF)
    digitalWrite(PIN_LED, PIN_OUT_ON);
  else
    digitalWrite(PIN_LED, PIN_OUT_OFF);
  #endif

  //------//
  // OUTS //
  //------//
  for (i = 0; i < OUT_NUMBER; i++)
  {
    if (OutDig[i] == OUT_ON)
      digitalWrite(OutPin[i], !cfgLogicOuts /*PIN_OUT_ON*/);
    else
      digitalWrite(OutPin[i], cfgLogicOuts /*PIN_OUT_OFF*/);
  }

  #if (_USE_RS485_RXTX_ == 1)
  if (OutRS485rxtx == OUT_RS485_RX)
    digitalWrite(PIN_RS485_RXTX, LOW);
  else
    digitalWrite(PIN_RS485_RXTX, HIGH);
  #endif

  //-----//
  // INS //
  //-----//
  for (i = 0; i < IN_NUMBER; i++)
  {
    if (digitalRead(InPin[i]) == cfgLogicIns /*PIN_IN_OFF*/)
      InDig[i] = IN_OFF;
    else
      InDig[i] = IN_ON;
  }
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();

  if (ctrMode == MODE_AUTO)
    _CtrLoop();

  _TimeLoop();

  #if (_USE_ETHERNET_ == 1)
  _ETHLoop();
  #endif
}
