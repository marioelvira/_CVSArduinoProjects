#include <EEPROM.h>

#include "__ver.h"

#include "adcs.h"
#include "ctr.h"
#include "e2prom.h"
#include "io.h"
#include "intisr.h"
#include "main.h"
#include "mRAM.h"
#include "mUart.h"
#include "wde.h"

/////////////
// Version //
/////////////
const char* FW_Version = FW_VERSION;

////////////////////
// DIO definition //
////////////////////
int   InStartVal = 0;
int   InStartVal_ant = 0;
int   InStartCounter = 0;
int   InStartState = 0;

int   InEndVal = 0;
int   InEndVal_ant = 0;
int   InEndCounter = 0;
int   InEndState = 0;

///////////////
// Board Led //
///////////////
int   boardLed;

//////////
// ADCs //
//////////
int   AdcDig[ADC_NUMBER];
int   AdcPin[ADC_NUMBER];
int   AdcArray[ADC_NUMBER][ADC_ARRAY_SIZE];
int   AdcPointer[ADC_NUMBER];

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
//unsigned long ControlTick = 0;
//int   ControlState;
//int   TimeControlSec;

////////////
// Config //
////////////
int cfgMbId = 0;
int cfgADCf[ADC_NUMBER];

/////////
// ISR //
/////////
//int inPulseD2 = 0;
#define _SEC_TO_RPM_  60000

unsigned long   inPulseD3 = 0;
unsigned long   inPulseAntD3 = 0;
unsigned long   pulsesD3;
unsigned long   RpmCounterD3 = 0;
unsigned long   RpmTickD3 = 0;
unsigned long   RpmPeriodD3 = 0;

///////////
// MUART //
///////////
#if (_USE_MUART_ == 1)
String uartBuffer = "";
bool uartCMD;
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
    OutDig[i] = 0;
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
  _INTISRsSetup();

  // Time Setup
  _TimeSetup();

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
    else if (OutDig[i] == IO_OFF)
      digitalWrite(OutPin[i], PIN_OUT_OFF);
  }

  //-----//
  // INS //
  //-----//
  for (i = 0; i < IN_NUMBER; i++)
  {
    //if (digitalRead(PIN_IN0) == PIN_IN_OFF)
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

  //if (controlMode == MODE_AUTO)
  // _OUTSLoop();

  //_CtrLoop();

  _TimeLoop();

  #if (_USE_MUART_ == 1)
  _MUARTLoop();
  #endif
}
