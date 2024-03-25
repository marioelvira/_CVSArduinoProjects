
////////////////////
// INTISRs set up //
////////////////////
void _INTISRsSetup()
{
  RpmTickD2 = millis();
  RpmCounterD2 = 0;
  attachInterrupt(digitalPinToInterrupt(PIN_D02), interruptD2, RISING);

  RpmTickD3 = millis();
  RpmCounterD3 = 0;
  attachInterrupt(digitalPinToInterrupt(PIN_D03), interruptD3, RISING);
}

///////////////////////////
// INTISRs state machine //
///////////////////////////
void _INTISRsLoop()
{
  detachInterrupt(digitalPinToInterrupt(PIN_D02));
  pulsesD2 =  inPulseD2 - inPulseAntD2;
  inPulseAntD2 = inPulseD2;
  
  RpmPeriodD2 = millis() - RpmTickD2;
  RpmCounterD2 = (pulsesD2*_SEC_TO_RPM_)/RpmPeriodD2;
  
  RpmTickD2 = millis();
  attachInterrupt(digitalPinToInterrupt(PIN_D02), interruptD2, RISING);
  
  detachInterrupt(digitalPinToInterrupt(PIN_D03));
  pulsesD3 =  inPulseD3 - inPulseAntD3;
  inPulseAntD3 = inPulseD3;
  
  RpmPeriodD3 = millis() - RpmTickD3;
  RpmCounterD3 = (pulsesD3*_SEC_TO_RPM_)/RpmPeriodD3;
    
  RpmTickD3 = millis();  
  attachInterrupt(digitalPinToInterrupt(PIN_D03), interruptD3, RISING);
}

////////////////
// Interrupts //
////////////////
void interruptD2()
{
   inPulseD2++;
}

void interruptD3()
{
   inPulseD3++;
}
