
////////////////////
// INTISRs set up //
////////////////////
void _INTISRsSetup()
{
  /*
  RpmTickD2 = millis();
  RpmCounterD2 = 0;
  attachInterrupt(digitalPinToInterrupt(2), interruptD2, RISING);
  */
  RpmTickD3 = millis();
  RpmCounterD3 = 0;
  attachInterrupt(digitalPinToInterrupt(3), interruptD3, RISING);
}

///////////////////////////
// INTISRs state machine //
///////////////////////////
void _INTISRsLoop()
{
  /*
  detachInterrupt(digitalPinToInterrupt(2));
  pulsesD2 =  inPulseD2 - inPulseAntD2;
  inPulseAntD2 = inPulseD2;
  // TODO
  RpmTickD2 = millis();
  attachInterrupt(digitalPinToInterrupt(2), interruptD2, RISING);
  */
  
  detachInterrupt(digitalPinToInterrupt(3));
  pulsesD3 =  inPulseD3 - inPulseAntD3;
  inPulseAntD3 = inPulseD3;
  
  RpmPeriodD3 = millis() - RpmTickD3;
  RpmCounterD3 = (pulsesD3*_SEC_TO_RPM_)/RpmPeriodD3;
    
  RpmTickD3 = millis();  
  attachInterrupt(digitalPinToInterrupt(3), interruptD3, RISING);
}

////////////////
// Interrupts //
////////////////
/*
void interruptD2()
{
   inPulseD2++;
}
*/

void interruptD3()
{
   inPulseD3++;
}
