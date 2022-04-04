#include <EEPROM.h>

#include "__ver.h"

#include "adcs.h"
#include "ctr.h"
#include "e2prom.h"
#include "io.h"
#include "intisr.h"
#include "main.h"
#include "mRAM.h"
#include "wde.h"

/////////////
// Version //
/////////////
const char* FW_Version = FW_VERSION;

////////////////////
// DIO definition //
////////////////////
int   OutGen;
int   OutDisp;
int   OutZumb;

int   OutA;
int   OutB;
int   OutC;
int   OutD;

int   InStartVal = 0;
int   InStartVal_ant = 0;
int   InStartCounter = 0;
int   InStartState = 0;

int   InEndVal = 0;
int   InEndVal_ant = 0;
int   InEndCounter = 0;
int   InEndState = 0;

int   boardLed;

//////////
// ADCs //
//////////
int   Adc0InDig;
int   Adc0InArray[ADC0_ARRAY_SIZE];
int   Adc0InPointer;
float Adc0InVal;

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
//int   controlMode = MODE_AUTO;
unsigned long ControlTick = 0;
int   ControlState;
int   TimeControlSec;

int   TimeGenerador1P;
int   TimeGenerador2P;
int   TimeGenerador3P;
int   TimeGenerador4P;
int   TimeGenerador5P;
int   TimeGenerador6P;
int   TimeGenerador7P;
int   TimeGenerador8P;
int   TimeGenerador9P;

int   TimeBuzzerOn;
int   TimeOutStart;
int   TimeOutStop;

////////////
// Config //
////////////
int cfgADC0 = 0;
/*
int     cfgADCm;
int     cfgADCb;
int     cfgADCp;
int     cfgADCs;
int     cfgADCf;
*/

/////////
// ISR //
/////////
//int inPulseD2 = 0;
#define _SEC_TO_RPM_  60000

int   inPulseD3 = 0;
int   inPulseAntD3 = 0;
int   RpmCounter = 0;
unsigned long RmpTick = 0;

// Debug
int X_60 = 60;
int X_3600 = 3600;

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
  //------//
  // OUTS //
  //------//

  // Ledboard
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, PIN_OUT_OFF);
  boardLed = OUT_OFF;  
  
  // Zum OFF
  pinMode(PIN_ZUMB, OUTPUT);
  digitalWrite(PIN_ZUMB, PIN_OUT_OFF);
  OutZumb  = OUT_OFF;
  
  // Gen OFF
  pinMode(PIN_GEN, OUTPUT);
  digitalWrite(PIN_GEN, PIN_OUT_OFF);
  OutGen   = OUT_OFF;

  // Disp ON
  pinMode(PIN_DISP, OUTPUT);
  digitalWrite(PIN_DISP, PIN_OUT_ON);
  OutDisp  = OUT_ON;
  
  pinMode(PIN_A, OUTPUT);
  digitalWrite(PIN_A, PIN_OUT_OFF);
  pinMode(PIN_B, OUTPUT);
  digitalWrite(PIN_B, PIN_OUT_OFF);
  pinMode(PIN_C, OUTPUT);
  digitalWrite(PIN_C, PIN_OUT_OFF);
  pinMode(PIN_D, OUTPUT);
  digitalWrite(PIN_D, PIN_OUT_OFF);

  OutA = OUT_OFF;
  OutB = OUT_OFF;
  OutC = OUT_OFF;
  OutD = OUT_OFF;

  //-----//
  // INS //
  //-----//
  pinMode(PIN_PULSADOR, INPUT);
  pinMode(PIN_END, INPUT);
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
  Serial.println(FW_VERSION);
  #endif
    
  // Config setup
  _ConfigSetup();

  // PIN & IO Setup
  _PINSetup();
  _IOSetup();
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
  //------//
  // OUTS //
  //------//

  if (boardLed == OUT_OFF)
    digitalWrite(PIN_LED, PIN_OUT_ON);
  else
    digitalWrite(PIN_LED, PIN_OUT_OFF);    

  if (OutZumb == OUT_ON)
    digitalWrite(PIN_ZUMB, PIN_OUT_ON);
  else if (OutZumb == IO_OFF)
    digitalWrite(PIN_ZUMB, PIN_OUT_OFF);
      
  if (OutGen == OUT_ON)
    digitalWrite(PIN_GEN, PIN_OUT_ON);
  else
    digitalWrite(PIN_GEN, PIN_OUT_OFF);
  
  if (OutDisp == OUT_ON)
    digitalWrite(PIN_DISP, PIN_OUT_ON);
  else if (OutDisp == IO_OFF)
    digitalWrite(PIN_DISP, PIN_OUT_OFF);

  if (OutA == OUT_ON)
    digitalWrite(PIN_A, PIN_OUT_ON);
  else
    digitalWrite(PIN_A, PIN_OUT_OFF);

  if (OutB == OUT_ON)
    digitalWrite(PIN_B, PIN_OUT_ON);
  else
    digitalWrite(PIN_B, PIN_OUT_OFF);

  if (OutC == OUT_ON)
    digitalWrite(PIN_C, PIN_OUT_ON);
  else
    digitalWrite(PIN_C, PIN_OUT_OFF);

  if (OutD == OUT_ON)
    digitalWrite(PIN_D, PIN_OUT_ON);
   else
    digitalWrite(PIN_D, PIN_OUT_OFF);   

  //-----//
  // INS //
  //-----//
  
  if (digitalRead(PIN_PULSADOR) == PIN_IN_OFF)
    InStartVal = IO_OFF;
  else
    InStartVal = IO_ON;

  if (digitalRead(PIN_END) == PIN_IN_OFF)
    InEndVal = IO_OFF;
  else
    InEndVal = IO_ON;
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();
  _IOLoop();
  
  _IOPulsLoop();

  //if (controlMode == MODE_AUTO)
  // _OUTSLoop();

  //_CtrLoop();
  
  _TimeLoop();
}
