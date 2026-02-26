#include "main.h"

#include <EEPROM.h>

#if (_USE_ETHERNET_ == 1)
#include <ETH.h>
#endif

#if (_USE_MQTT_ == 1)
#include <NetworkClient.h>
#include <PubSubClient.h>
#endif
#if (_USE_HTTP_ == 1)
#include <WebServer.h>
#endif
#if (_USE_NTP_ == 1)
#include <NTPClient.h>
#endif

#if (_USE_WDE_ == 1)
//TODO
#endif

#if (_USE_UID_ == 1)
#include <ArduinoUniqueID.h>
#endif

#include "alarm.h"
#include "ctr.h"
#include "e2prom.h"
#include "io.h"
#include "ip.h"

#if (_USE_ETHERNET_ == 1)
#include "mEthernet.h"
#endif

#if (_USE_MQTT_ == 1)
#include "MQTT.h"
#endif
#if (_USE_HTTP_ == 1)
#include "http.h"
#endif
#if (_USE_NTP_ == 1)
#include "mNTP.h"
#endif

#if (_USE_RS485_ == 1)
#include "mRS485.h"
#endif
#if (_USE_MBRTU_ == 1)
#include "modbusRTU.h"
#endif

#if (_USE_TRIAC_ == 1)
#include "triac.h"
#endif

#if (_USE_PWM_ == 1)
#include "pwm.h"
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
#if (_USE_UID_ == 1)
String UniqueIdStr;
#endif

///////////////
// Board Led //
///////////////
#if (_USE_LED_ == 1)
int   boardLed;
#endif

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

///////////
// Alarm //
///////////
int    alState;
int    alSecond;
int    alNotify;
int    alarmOn[AL_ARRAY_SIZE];
int    alarmCpy[AL_ARRAY_SIZE];

String alarmStr[AL_ARRAY_SIZE];

///////////
// TRIAC //
///////////
#if (_USE_TRIAC_ == 1)
const int triacZCPin = PIN_ZD0;    
const int triacCtrPin = PIN_TR0;

hw_timer_t * triacTimer = NULL;
volatile uint32_t triacDimming = 5000; // Microsegundos

unsigned long triacTick = 0;
int triacZCPeriod;
#endif

/////////
// PWM //
/////////
#if (_USE_PWM_ == 1)
const int pwmPin = PIN_PWM0; 

const int pwmFreq = 50; // Frecuencia (Hz)
const int pwmResolution = 14;  // Resolución de 8 bits (valores de 0 a 255)

int pwmDutyCycle = 5000;       // 50%
#endif

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

int cfgResPrimVout;
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
int ipMode;
int ethStatus;

//uint8_t macAddress[6] = {0xF8, 0xDC, 0x7A, 0x00, 0x02, 0x04};
IPAddress ipAddress  (192, 168, 1, 200);
IPAddress gateWay    (192, 168, 1, 1);
IPAddress netMask    (255, 255, 255, 0);
IPAddress dnsAddress;  // No incializar
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
const char* brokerUrlSt = MQTT_BROKER;
char brokerUrl[MQTT_URL_MAX];
int brokerPort;
const char* brokerUserSt = MQTT_USERNAME;
char brokerUser[MQTT_USER_MAX];
const char* brokerPswdSt = MQTT_PASSWORD;
char brokerPswd[MQTT_PSWD_MAX];

NetworkClient  ethClient;
PubSubClient mqttClient(ethClient);

String mqttClientId;

int mqttStatus;
unsigned long mqttTick = 0;

int mqttTopic;
#endif

//////////
// HTTP //
//////////
#if (_USE_HTTP_ == 1)
WebServer httpServer(HTTP_PORT);
int httpStatus;
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
    digitalWrite(OutPin[i], PIN_OUT_OFF /*!cfgLogicOuts*/);
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
    pinMode(InPin[i], INPUT_PULLUP);
    InDig[i] = 0;
  }
}

//============//
// MAIN SETUP //
//============//
void setup(void)
{
  #if (_SERIAL_DEBUG_ == 1)
  delay(2000);  // 100ms
  Serial.begin(115200);
  Serial.print("Project: ");
  Serial.println(PROJECT);
  Serial.print("Version: ");
  Serial.println(compdate);
  Serial.print("Time: ");
  Serial.println(comptime);
  #endif

  #if (_USE_UID_ == 1)
  UniqueIdStr = "";
  for (size_t i = 0; i < UniqueIDsize; i++) {
    if (UniqueID[i] < 0x10) UniqueIdStr += "0";
    UniqueIdStr += String(UniqueID[i], HEX);
  }

  #if (_SERIAL_DEBUG_ == 1)
  Serial.print("UniqueID: ");
  Serial.println(UniqueIdStr);
  #endif
  #endif

  // PIN & IO Setup
  _IOSetup();
  _PINSetup();

  // Config setup
  _ConfigSetup();

  _ALARMSetup();

  #if (_USE_TRIAC_ == 1)
  _TRIACSetup();
  #endif

  #if (_USE_PWM_ == 1)
  _PWMSetup();
  #endif

  // Time setup
  _TimeSetup();

  // Ctr setup
  _CtrSetup();

  #if (_USE_WDE_ == 1)
  _WDESetup();
  #endif

  #if (_USE_ETHERNET_ == 1)
  _ETHSetup();

  #if (_USE_HTTP_ == 1)
  _HTTPSetup();
  #endif

  #if (_USE_MQTT_ == 1)
  _MQTTSetup();
  #endif

  #if (_USE_NTP_ == 1)
  _mNTPSetup();
  #endif

  #endif // _USE_ETHERNET_
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
