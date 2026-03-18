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
  // No bigger than OUT_NUMBER
  OutPin[0] = PIN_OUT1;
  OutPin[1] = PIN_OUT2;
  OutPin[2] = PIN_OUT3;
  OutPin[3] = PIN_OUT4;
  OutPin[4] = PIN_OUT5;
  OutPin[5] = PIN_OUT6;
    
  // No bigger than IN_NUMBER
  InPin[0] = PIN_IN1;
  InPin[1] = PIN_IN2;
  InPin[2] = PIN_IN3;
  InPin[3] = PIN_IN4;

  // No bigger than TRIAC_NUMBER
  /*
  TriacPin[0] = PIN_TRIAC1;
  TriacPin[1] = PIN_TRIAC2;
  TriacPin[2] = PIN_TRIAC3;
  */
}

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
