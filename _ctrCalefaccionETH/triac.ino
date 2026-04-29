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

const int triacZCPin = PIN_ZDA;
int triacZCAlarmSec = 0;
uint32_t triacZCTickUs = 0;
int triacZCPeriodUs;
float triacZCFrec = 0;
int triacZCcount = 0;

int triac1Delay = 0;
int triac1Cicle = 50;
int triac2Delay = 0;
int triac2Cicle = 50;
int triac3Delay = 0;
int triac3Cicle = 50;

#if (_TRIAC_PIN_DEBUG_ == 1)
bool triacZCdebug = false;
#endif

////////////////
// Interrupts //
////////////////
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

void IRAM_ATTR isrZeroCross()
{
  uint32_t nowUs = micros();

  #if (_TRIAC_PIN_DEBUG_ == 1)
  if (triacZCdebug == false)
  {
    digitalWrite(PIN_DEBUG, PIN_OUT_OFF);
    triacZCdebug = true;
  }
  else
  {
    digitalWrite(PIN_DEBUG, PIN_OUT_ON);
    triacZCdebug = false;
  }
  #endif

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

  // ZC Period
  triacZCPeriodUs = int (nowUs - triacZCTickUs);

  // Ruido
  if (triacZCPeriodUs < 8000)
    return;

  triacZCTickUs = nowUs;
  triacZCAlarmSec = 0;
  triacZCcount++;
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

  _TRIACUpdate();

  /////////////////
  // ZC detector //
  /////////////////
  pinMode(triacZCPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(triacZCPin), isrZeroCross, FALLING /*RISING*/);

  triacZCFrec = 0;
  triacZCPeriodUs = 0;
  triacZCTickUs = micros();
  triacZCAlarmSec = 0;
  triacZCcount = 0;
  /*
  // ZC detector
  pinMode(triac2ZCPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(triac2ZCPin), isr2ZeroCross, RISING);
  triac2ZCFrec = 0;
  triac2ZCPeriodUs = 0;
  triac2ZCTickUs = micros();
  triac2ZCcount = 0;
  */
  #if (_TRIAC_PIN_DEBUG_ == 1)
  pinMode(PIN_DEBUG, OUTPUT);
  digitalWrite(PIN_DEBUG, PIN_OUT_OFF);
  triacZCdebug = false;
  #endif
}

////////////////
// TRIAC loop //
////////////////
void _TRIACLoop()
{
  // Check Alarm
  triacZCAlarmSec++;
  if (triacZCAlarmSec > TRIAC_ALARM_ZC_SEC)
  {
    triacZCFrec = 0;
    triacZCPeriodUs = 0;
    
    #if (_USE_ALARM_ == 1)
    alarmOn[AL_ERROR1] = 1;
    #endif
  }
  else
  {
    triacZCFrec = 1000000.0 / triacZCPeriodUs;

    #if (_USE_ALARM_ == 1)
    alarmOn[AL_ERROR1] = 0;
    #endif
  }

  //triac2ZCFrec = 1000000.0 / triac2ZCPeriodUs;
}

void _TRIACUpdate()
{
  triac1Cicle = (int)(cfgTriacVout[0]*100)/230;
  triac2Cicle = (int)(cfgTriacVout[1]*100)/230;
  triac3Cicle = (int)(cfgTriacVout[2]*100)/230;

  // En v3.0, el tiempo se maneja según la frecuencia configurada en timerBegin
  // Si configuramos 1,000,000 Hz, 1 tick = 1 microsegundo.
  triac1Delay = map(triac1Cicle, 0, 100, 8000, 100);
  triac2Delay = map(triac2Cicle, 0, 100, 8000, 100);
  triac3Delay = map(triac3Cicle, 0, 100, 8000, 100);

  #if (_TRIAC_SERIAL_DEBUG_ == 1)
  Serial.print("triac1Cicle: ");     Serial.println (triac1Cicle);
  Serial.print("triac2Cicle: ");     Serial.println (triac2Cicle);
  Serial.print("triac3Cicle: ");     Serial.println (triac3Cicle);
  
  Serial.print("triac1Delay: ");     Serial.println (triac1Delay);
  Serial.print("triac2Delay: ");     Serial.println (triac2Delay);
  Serial.print("triac3Delay: ");     Serial.println (triac3Delay);
  #endif
}

#endif // (_USE_TRIAC_ == 1)