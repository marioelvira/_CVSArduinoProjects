#include "main.h"
#include "__ver.h"

#include <EEPROM.h>
#include <UIPEthernet.h>
#if (_USE_MQTT_ == 1)
#include <PubSubClient.h>
#endif
#if (_USE_NTP_ == 1)
#include <NTPClient.h>
#endif

#include "adcs.h"
#include "ctr.h"
#include "e2prom.h"
#include "io.h"
#include "ip.h"
#include "measures.h"
#include "mEthernet.h"
#if (_USE_MQTT_ == 1)
#include "MQTT.h"
#endif
#if (_USE_MBTCP_ == 1)
#include "modbusTCP.h"
#endif
#include "mRAM.h"
#if (_USE_NTP_ == 1)
#include "mNTP.h"
#endif
#include "wde.h"

/////////////
// Version //
/////////////
const char* FW_Version = FW_VERSION;

//////////
// ADCs //
//////////
int   AdcDig[ADC_NUMBER];
int   AdcPin[ADC_NUMBER];

//////////
// Irms //
//////////
const double  nCyclesToMeasure = 5;   // 1
const int     nSamplesPerCycle = 25; // 300
const int     numSamples = nSamplesPerCycle * nCyclesToMeasure;
const int     samplePeriod = ((1 / IRMS_FREQ_HZ) * nCyclesToMeasure * 1000000) / numSamples;
double        Isamples[numSamples][I_NUMBER];
int           nSamples[I_NUMBER];
double        Ioffset;
double        Iratio[I_NUMBER];

unsigned long IuTick[I_NUMBER];
int           IrmsCont[I_NUMBER];

int           Ival[I_NUMBER];

/////////
// Vdc //
/////////
unsigned long VuTick[V_NUMBER];
int           Vval[V_NUMBER];

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
int    ctrMode;
int    ctrInState;
int    ctrInState_ant;
int    ctrOutState;

unsigned long ctrOutTick = 0;

int   crtCIrmsState;
unsigned long ctrCIrmsTick = 0;
unsigned long ctrCIrmsSec = 0;

////////////
// Config //
////////////
bool cfgLogicIns;
bool cfgLogicOuts;

int cfgIType[I_NUMBER];
int cfgIACr[I_NUMBER];
int cfgIlim[I_NUMBER];
int cfgIsec[I_NUMBER];

int cfgVDCm[V_NUMBER];
int cfgVDCb[V_NUMBER];

int cfgCtrSecs[7];

#if (_USE_ETHERNET_ == 1)
int cfgModbusPORT = 502;
#endif

////////////////
// Modbus TCP //
////////////////
#if (_USE_MBTCP_ == 1)
EthernetServer modbusTcpServer(MODBUSTCP_PORT);
int modbusTcpStatus;

EthernetClient  modbusTcpClient;

byte         modbusTcpByteArray[MB_MAX_BTYE];
int          modbusTcpIndex;

byte mbFunction;
int  mbResponseLength;
#endif 

//////////////
// Ethernet //
//////////////
#if (_USE_ETHERNET_ == 1)
int       ipMode;

uint8_t macAddress[6] = {0xF8, 0xDC, 0x7A, 0x00, 0x02, 0x04};
uint8_t ipAddress[4]  = {192,168,100,200};
uint8_t gateWay[4]    = {192,168,100,1};
uint8_t netMask[4]    = {255,255,255,0};
uint8_t dnsAddress[4] = {8,8,8,8};

int ethStatus;
unsigned long   ethTick;
#endif

//////////
// MQTT //
//////////
#if (_USE_MQTT_ == 1)
IPAddress brokerIp(192, 168, 0, 200);

const char* brokerUrlSt = MQTT_BROKER;
char brokerUrl[MQTT_URL_MAX];
int brokerPort;
const char* brokerUserSt = MQTT_USERNAME;
char brokerUser[MQTT_USER_MAX];
const char* brokerPswdSt = MQTT_PASSWORD;
char brokerPswd[MQTT_PSWD_MAX];

EthernetClient  ethMqttClient;
PubSubClient mqttClient(ethMqttClient);

String mqttClientId = "relayMQTT-123dfqfvq234"; // TODO Add + String(ESP.getChipId());

int mqttStatus;
unsigned long mqttTick = 0;
int mqttTopic;
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
  Serial.println(FW_VERSION);
  #endif

  // Config setup
  _ConfigSetup();

  // PIN & IO Setup
  _IOSetup();
  _PINSetup();
  _ADCsSetup();

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
  _ADCsLoop();
  
  #if (_USE_ETHERNET_ == 1)
  _ETHLoop();
  #endif
}
