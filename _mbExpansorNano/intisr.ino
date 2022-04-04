
////////////////////
// INTISRs set up //
////////////////////
void _INTISRsSetup()
{
  //attachInterrupt(digitalPinToInterrupt(2), interruptD2, RISING);

  // RPM test
  RmpTick = millis();
  RpmCounter = 0;
  attachInterrupt(digitalPinToInterrupt(3), interruptD3, RISING);
}

///////////////////////////
// INTISRs state machine //
///////////////////////////
void _INTISRsLoop()
{
  unsigned long rmpPeriod;
  int pulses;
  
  //detachInterrupt(digitalPinToInterrupt(3));
  pulses =  inPulseD3 - inPulseAntD3;
  rmpPeriod = millis() - RmpTick;
  RpmCounter = (pulses/rmpPeriod)*_SEC_TO_RPM_;
  inPulseAntD3 = inPulseD3;
  RmpTick = millis();
  //inPulseD3 = 0;
  
  //attachInterrupt(digitalPinToInterrupt(3), interruptD3, RISING);
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
