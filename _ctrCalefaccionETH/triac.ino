#include "main.h"
#include "triac.h"

#if (_USE_TRIAC_ == 1)

///////////////
// Variables //
///////////////
int   TriacCtr[TRIAC_NUMBER];
hw_timer_t * triac1Timer = NULL;
hw_timer_t * triac2Timer = NULL;
hw_timer_t * triac3Timer = NULL;

int triacZCPeriod;
unsigned long triacTick = 0;

int triac1Delay = 0;
int triac1Cicle = 50;
int triac2Delay = 0;
int triac2Cicle = 50;
int triac3Delay = 0;
int triac3Cicle = 50;

////////////////
// Interrupts //
////////////////
void IRAM_ATTR isrZeroCross()
{ 
  if (TriacCtr[0] == TRIAC_ON)
  {
    timerRestart(triac1Timer);
    // timerAlarm(timer, valor_alarma, autoreload, reload_count)
    timerAlarm(triac1Timer, triac1Delay, false, 0);
  }

  if (TriacCtr[1] == TRIAC_ON)
  {
    timerRestart(triac2Timer);
    // timerAlarm(timer, valor_alarma, autoreload, reload_count)
    timerAlarm(triac2Timer, triac2Delay, false, 0);
  }

  if (TriacCtr[2] == TRIAC_ON)
  {
    timerRestart(triac3Timer);
    // timerAlarm(timer, valor_alarma, autoreload, reload_count)
    timerAlarm(triac3Timer, triac3Delay, false, 0);
  }

  // ZC Periodo
  triacZCPeriod = int (millis() - triacTick);
  triacTick = millis();
}

void IRAM_ATTR isrTriac1Timer()
{
  digitalWrite(PIN_TRIAC1, PIN_TRIAC_ON);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIAC1, PIN_TRIAC_OFF);
}

void IRAM_ATTR isrTriac2Timer()
{
  digitalWrite(PIN_TRIAC2, PIN_TRIAC_ON);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIAC2, PIN_TRIAC_OFF);
}

void IRAM_ATTR isrTriac3Timer()
{
  digitalWrite(PIN_TRIAC3, PIN_TRIAC_ON);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIAC3, PIN_TRIAC_OFF);
}

//////////////////
// TRIAC set up //
//////////////////
void _TRIACSetup()
{
  // TRIAC
  pinMode(PIN_TRIAC1, OUTPUT);
  pinMode(PIN_TRIAC2, OUTPUT);
  pinMode(PIN_TRIAC3, OUTPUT);

  digitalWrite(PIN_TRIAC1, PIN_TRIAC_OFF);
  digitalWrite(PIN_TRIAC2, PIN_TRIAC_OFF);
  digitalWrite(PIN_TRIAC3, PIN_TRIAC_OFF);
  
  for (int i = 0; i < TRIAC_NUMBER; i++)
    TriacCtr[i] = TRIAC_OFF;
  
  // NUEVA API v3.0: timerBegin solo recibe la FRECUENCIA en Hz
  // Configuramos 1MHz para que cada "tick" sea de 1 microsegundo
  triac1Timer = timerBegin(1000000);
  timerAttachInterrupt(triac1Timer, &isrTriac1Timer);
  triac2Timer = timerBegin(1000000);
  timerAttachInterrupt(triac2Timer, &isrTriac2Timer);
  triac3Timer = timerBegin(1000000);
  timerAttachInterrupt(triac3Timer, &isrTriac3Timer);

  // En v3.0, el tiempo se maneja según la frecuencia configurada en timerBegin
  // Si configuramos 1,000,000 Hz, 1 tick = 1 microsegundo.
  triac1Delay = map(triac1Cicle, 0, 100, 8000, 100); 
  triac2Delay = map(triac2Cicle, 0, 100, 8000, 100);
  triac3Delay = map(triac3Cicle, 0, 100, 8000, 100);
  
  /////////////////
  // ZC detector //
  /////////////////
  pinMode(PIN_ZD1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_ZD1), isrZeroCross, RISING);

  // Cálculo del periodo
  triacZCPeriod = 0;
  triacTick = millis();
}

#endif // (_USE_TRIAC_ == 1)