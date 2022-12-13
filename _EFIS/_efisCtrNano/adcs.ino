
/////////////////
// ADCs set up //
/////////////////
void _ADCsSetup()
{
  int i, j;

  for (i = 0; i < ADC_NUMBER; i++)
  {
    AdcDig[i] = 0;
    for (j = 0; j < ADC_ARRAY_SIZE; j++)
      AdcArray[i][j] = 0;

    AdcPointer[i] = 0;  
  }

  // No bigger than ADC_NUMBER
  AdcPin[0] = PIN_ADC0;
  AdcPin[1] = PIN_ADC1;
  AdcPin[2] = PIN_ADC2;
  AdcPin[3] = PIN_ADC3;
}

////////////////////////
// ADCs state machine //
////////////////////////
void _ADCsLoop()
{
  int i, j, acc, pin;

  for (i = 0; i < ADC_NUMBER; i++)
  {
    pin = AdcPin[i];

    // Filter
    if (cfgADCf[i] == 1)
    {
      acc = 0;
      AdcArray[i][AdcPointer[i]] = analogRead(pin);
      AdcPointer[i]++;
      if (AdcPointer[i] >= ADC_ARRAY_SIZE)
        AdcPointer[i] = 0;
    
      // Media del Array...
      for (j = 0; j < ADC_ARRAY_SIZE; j++)
        acc = acc + AdcArray[i][j];
      
      AdcDig[i] = acc/ADC_ARRAY_SIZE;
    }
    // No filter
    else
      AdcDig[i] = analogRead(pin);
  }

  // Ctr conversion
  EnginePres =  (AdcDig[0]*cfgPres)/100;

}
