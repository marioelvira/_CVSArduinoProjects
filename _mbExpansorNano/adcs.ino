
/////////////////
// ADCs set up //
/////////////////
void _ADCsSetup()
{
  int i;
  
  Adc0InDig = 0;
  for (i = 0; i < ADC0_ARRAY_SIZE; i++)
    Adc0InArray[i] = 0;

  Adc0InPointer = 0;
}

////////////////////////
// ADCs state machine //
////////////////////////
void _ADCsLoop()
{
  if (cfgADC0 == 1)
  {
    int digAcc0 = 0;
    
    Adc0InArray[Adc0InPointer] = analogRead(PIN_ADC0_IN);
    Adc0InPointer++;
    if (Adc0InPointer >= ADC0_ARRAY_SIZE)
      Adc0InPointer = 0;
  
    // Media del Array...
    for (int i = 0; i < ADC0_ARRAY_SIZE; i++)
      digAcc0 = digAcc0 + Adc0InArray[i];
    
    Adc0InDig = digAcc0/ADC0_ARRAY_SIZE;
  }
  else
    Adc0InDig = analogRead(PIN_ADC0_IN);

  /*
  if (cfgADCs == 0)
    Adc0InVal = (float)Adc0InDig*((float)cfgADC0m)/(float)cfgADC0p - (float)cfgADC0b/1000;
  else
    Adc0InVal = (float)Adc0InDig*((float)cfgADC0m)/(float)cfgADC0p + (float)cfgADC0b/1000;
  */
}
