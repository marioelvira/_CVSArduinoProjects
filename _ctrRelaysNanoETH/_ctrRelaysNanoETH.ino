#include <EEPROM.h>
#include <UIPEthernet.h>

#include "__ver.h"

#include "adcs.h"
#include "ctr.h"
#include "e2prom.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "measures.h"
#include "mEthernet.h"
#include "modbusTCP.h"
#include "mRAM.h"
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
unsigned long AdcTick[ADC_NUMBER];

///////////
// mEMON //
///////////
int     emonState[EMON_NUMBER];
int     emonSumI[EMON_NUMBER];
int     emonSamples[EMON_NUMBER];
double  emonIRMS[EMON_NUMBER];
int     Irms[EMON_NUMBER];

/////////
// Vdc //
/////////
int     Vdc[VDC_NUMBER];

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
unsigned long timeTick = 0;
int timeSec = 0;
int timeMin = 0;
int timeHour = 0;

/////////////
// Control //
/////////////
int   ctrMode;
int   ctrInState;
int   ctrInState_ant;
int   ctrOutState;

unsigned long ctrOutTick = 0;

int   crtCIrmsState[IRMS_NUMBER];

////////////
// Config //
////////////
int cfgMbId = 0;
int cfgLogicIns;
int cfgLogicOuts;

int cfgC0ADCEmonR;
int cfgC0ADCEmonS;
int cfgC0ADCEmonO;
int cfgC0ADCEmonL;
int cfgC0ADCEmonSec;

int cfgC1ADCEmonR;
int cfgC1ADCEmonS;
int cfgC1ADCEmonO;
int cfgC1ADCEmonL;
int cfgC1ADCEmonSec;

int cfgV0ADCm;
int cfgV0ADCb;

int cfgV1ADCm;
int cfgV1ADCb;

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

uint8_t myMAC[6]  = { 0xF8, 0xDC, 0x7A, 0x45, 0xAD, 0xC5 };
uint8_t myIP[4]   = {172,19,1,200};
uint8_t myMASK[4] = {255,255,255,0};
uint8_t myDNS[4]  = {172,19,1,8};
uint8_t myGW[4]   = {172,19,1,8};

int ethStatus;
unsigned long   ethTick;
#endif

//////////
// mRAM //
//////////
#if (_USE_FREERAM_ == 1)
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
    digitalWrite(OutPin[i], PIN_OUT_OFF);
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
      digitalWrite(OutPin[i], PIN_OUT_ON);
    else
      digitalWrite(OutPin[i], PIN_OUT_OFF);
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
    if (digitalRead(InPin[i]) == PIN_IN_OFF)
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
