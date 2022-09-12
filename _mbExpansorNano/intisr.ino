
////////////////////
// INTISRs set up //
////////////////////
void _INTISRsSetup()
{
  //attachInterrupt(digitalPinToInterrupt(2), interruptD2, RISING);

  // RPM test
  RpmTickD3 = millis();
  RpmCounterD3 = 0;
  attachInterrupt(digitalPinToInterrupt(3), interruptD3, RISING);
}

///////////////////////////
// INTISRs state machine //
///////////////////////////
void _INTISRsLoop()
{
 
  detachInterrupt(digitalPinToInterrupt(3));
  
  pulsesD3 =  inPulseD3 - inPulseAntD3;
  RpmPeriodD3 = millis() - RpmTickD3;
  
  RpmCounterD3 = (pulsesD3*_SEC_TO_RPM_)/RpmPeriodD3;
  inPulseAntD3 = inPulseD3;
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
