#include <EEPROM.h>

#include "__ver.h"

#include "adcs.h"
#include "ctr.h"
#include "e2prom.h"
#include "io.h"
#include "main.h"
#include "mModbus.h"
#include "mRAM.h"
#include "mRS485.h"
#include "wde.h"

/////////////
// Version //
/////////////
const char* FW_Version = FW_VERSION;

////////////////////
// DIO definition //
////////////////////
int   InPuls = 0;
int   InPuls_ant = 0;
int   InPulsCounter = 0;
int   InPulsState = 0;

///////////////
// Board Led //
///////////////
int   boardLed;

//////////
// ADCs //
//////////
int   AdcDig[ADC_NUMBER];
int   AdcPin[ADC_NUMBER];
int   AdcVal[ADC_NUMBER];

/////////////
// IO Tick //
/////////////
unsigned long ioTick = 0;

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
int   ControlMode;
unsigned long ControlTick = 0;
int     ControlState;
//int   TimeControlSec;

////////////
// Config //
////////////
int cfgMbId = 0;
int cfgLogicIns;
int cfgLogicOuts;

int cfgADCm[ADC_NUMBER];
int cfgADCb[ADC_NUMBER];
int cfgADCs[ADC_NUMBER];

int cfgADCt[ADC_NUMBER];

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
int             mbState;
unsigned long   mbTick;
byte            mbCRC[2];
#endif
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
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, PIN_OUT_OFF);
  boardLed = OUT_OFF;

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
  #endif
  OutRS485rxtx = OUT_RS485_RX;

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
  #if (_USE_MUART_ == 1)
  _MUARTSetup();
  #endif
  
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
  _IOSetup();
  _PINSetup();
  _ADCsSetup();
  
  // Time Setup
  _TimeSetup();

  #if (_USE_RS485_ == 1)
  _RS485Setup();
  #if (_USE_MB_ == 1)
  _MBSetup();
  #endif
  #endif

  // Ctr setup
  //_CtrSetup();

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

  //-----------//
  // Board Led //
  //-----------//
  if (boardLed == OUT_OFF)
    digitalWrite(PIN_LED, PIN_OUT_ON);
  else
    digitalWrite(PIN_LED, PIN_OUT_OFF);

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
  _IOLoop();

  if (ControlMode == MODE_AUTO)
    _CtrLoop();

  _TimeLoop();

  #if (_USE_RS485_ == 1)
  _RS485Loop();
  #if (_USE_MB_ == 1)
  _MBLoop();
  #endif
  #endif
}
