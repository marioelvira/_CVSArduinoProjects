#include "main.h"
#include "triac.h"

#if (_USE_TRIAC_ == 1)

///////////////
// Variables //
///////////////
const int triacZCPin = PIN_ZD1;
int   TriacPin[TRIAC_NUMBER];
int   TriacDig[TRIAC_NUMBER];

int triacZCPeriod;
unsigned long triacTick = 0;

int triacCtr1 = 0;
const int triacPin1 = PIN_TRIAC1;
hw_timer_t * triacTimer1 = NULL;
int timeDelay1 = 0;
int triacCicle1 = 50;

////////////////
// Interrupts //
////////////////
void IRAM_ATTR isrZeroCross()
{ 
  if (triacCtr1 == OUT_ON)
  {
    timerRestart(triacTimer1);
    // timerAlarm(timer, valor_alarma, autoreload, reload_count)
    timerAlarm(triacTimer1, timeDelay1, false, 0);
  }

  // ZC Periodo
  triacZCPeriod = int (millis() - triacTick);
  triacTick = millis();
}

void IRAM_ATTR isrTriacTimer1()
{
  digitalWrite(triacPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triacPin1, LOW);
}

//////////////////
// TRIAC set up //
//////////////////
void _TRIACSetup()
{
  // Pin definition
  //triacZCPin = PIN_ZD1;

  TriacPin[0] = PIN_TRIAC1;
  TriacPin[1] = PIN_TRIAC2;
  TriacPin[2] = PIN_TRIAC3;

  // TRIAC
  pinMode(triacPin1, OUTPUT);

  // NUEVA API v3.0: timerBegin solo recibe la FRECUENCIA en Hz
  // Configuramos 1MHz para que cada "tick" sea de 1 microsegundo
  triacTimer1 = timerBegin(1000000);
  timerAttachInterrupt(triacTimer1, &isrTriacTimer1);

  // ZERO detector
  pinMode(triacZCPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(triacZCPin), isrZeroCross, RISING);

  // Cálculo del periodo
  triacZCPeriod = 0;
  triacTick = millis();
}

void _TRIACLoop()
{
  // TODO a CFG
  if (triacCtr1 == OUT_ON)
  {
    // En v3.0, el tiempo se maneja según la frecuencia configurada en timerBegin
    // Si configuramos 1,000,000 Hz, 1 tick = 1 microsegundo.
    timeDelay1 = map(triacCicle1, 0, 100, 8000, 100); 
  }

  /*
  int i;

  for (i = 0; i < TRIAC_NUMBER; i++)
  {
    if (TriacDig[i] == OUT_ON)
      // TODO
    else
      // TODO
  }
  */
}

#endif // (_USE_TRIAC_ == 1)