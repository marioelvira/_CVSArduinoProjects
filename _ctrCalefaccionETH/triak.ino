#include "main.h" 

#if (_USE_TRIAC_ == 1)

////////////////
// Interrupts //
////////////////
void IRAM_ATTR isrTriacTimer()
{
  digitalWrite(triacCtrPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triacCtrPin, LOW);
}

void IRAM_ATTR isrZeroCross()
{
  if (triacDimming > 100)
  { 
    // En v3.0+, timerAlarm configura y activa el disparo
    // Parámetros: timer, valor_alarma, autoreload, reload_count
    timerAlarm(triacTimer, triacDimming, false, 0); 
    timerRestart(triacTimer);
  } else {
    digitalWrite(triacCtrPin, HIGH); 
  }

  // ZC Period
  triacZCPeriod = int (millis() - triacTick);
  triacTick = millis();
}

//////////////////
// TRIAC set up //
//////////////////
void _TRIACSetup()
{
  pinMode(triacCtrPin, OUTPUT);
  pinMode(triacZCPin, INPUT_PULLUP);

  // Nueva sintaxis timerBegin: solo recibe la frecuencia en Hz (1MHz = 1us por tick)
  triacTimer = timerBegin(1000000); 
  
  // Nueva sintaxis timerAttachInterrupt: ya no requiere el tercer parámetro (edge)
  timerAttachInterrupt(triacTimer, &isrTriacTimer);

  attachInterrupt(digitalPinToInterrupt(triacZCPin), isrZeroCross, RISING);

  triacTick = millis();
}

#endif // (_USE_TRIAC_ == 1)