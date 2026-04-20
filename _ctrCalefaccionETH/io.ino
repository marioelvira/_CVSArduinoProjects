#include "main.h"
#include "io.h"

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

///////////////
// IO set up //
///////////////
void _IOSetup()
{ 
  int i;

  // Pin definition
  // No bigger than OUT_NUMBER
  OutPin[0] = PIN_OUT1; // O1
  OutPin[1] = PIN_OUT2; // O2
  OutPin[2] = PIN_OUT3; // O3
  OutPin[3] = PIN_OUT4; // O4
  OutPin[4] = PIN_OUT5; // O5
  OutPin[5] = PIN_OUT6; // RL1
  OutPin[6] = PIN_OUT7; // RL2

  // No bigger than IN_NUMBER
  InPin[0] = PIN_IN1;
  InPin[1] = PIN_IN2;
  InPin[2] = PIN_IN3;
  InPin[3] = PIN_IN4;

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

  //-----//
  // INS //
  //-----//
  for (i = 0; i < IN_NUMBER; i++)
  {
    pinMode(InPin[i], INPUT /*INPUT_PULLUP*/);
    InDig[i] = 0;
  }
}

//////////////////////
// HW state machine //
//////////////////////
void _IOLoop()
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
