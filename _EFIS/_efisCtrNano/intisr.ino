#include "main.h"

////////////////////
// INTISRs set up //
////////////////////
void _INTISRsSetup()
{
  #if ( _USE_INT0_  == 1)
  RpmTickD2 = millis();
  RpmCounterD2 = 0;
  attachInterrupt(digitalPinToInterrupt(2), interruptD2, RISING);
  #endif

  #if ( _USE_INT1_  == 1)
  RpmTickD3 = millis();
  RpmCounterD3 = 0;
  attachInterrupt(digitalPinToInterrupt(3), interruptD3, RISING);
  #endif
}

///////////////////////////
// INTISRs state machine //
///////////////////////////
void _INTISRsLoop()
{
  #if ( _USE_INT0_  == 1)
  detachInterrupt(digitalPinToInterrupt(2));
  pulsesD2 =  inPulseD2 - inPulseAntD2;
  inPulseAntD2 = inPulseD2;
  
  RpmPeriodD2 = millis() - RpmTickD2;
  RpmCounterD2 = (pulsesD2*_SEC_TO_RPM_)/RpmPeriodD2;
  
  RpmTickD2 = millis();
  attachInterrupt(digitalPinToInterrupt(2), interruptD2, RISING);
  #endif

  // Ctr conversion
  EngineRpm = (RpmCounterD2*cfgRpm)/100;

  #if ( _USE_INT1_  == 1)
  detachInterrupt(digitalPinToInterrupt(3));
  pulsesD3 =  inPulseD3 - inPulseAntD3;
  inPulseAntD3 = inPulseD3;
  
  RpmPeriodD3 = millis() - RpmTickD3;
  RpmCounterD3 = (pulsesD3*_SEC_TO_RPM_)/RpmPeriodD3;
    
  RpmTickD3 = millis();  
  attachInterrupt(digitalPinToInterrupt(3), interruptD3, RISING);
  #endif
}

////////////////
// Interrupts //
////////////////
#if ( _USE_INT0_  == 1)
void interruptD2()
{
   inPulseD2++;
}
#endif

#if ( _USE_INT1_  == 1)
void interruptD3()
{
   inPulseD3++;
}
#endif
