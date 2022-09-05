
///////////////////////
// ADC state machine //
///////////////////////
void _ADCSetup()
{
  AdcIn = 0;

  for (int i = 0; i < ADC_ARRAY_SIZE; i++)
    AdcInArray[i] = 0;

  AdcInPointer = 0;
}

///////////////////////
// ADC state machine //
///////////////////////
// Nota: Se ejecuta dentro de _TimeLoop
void _ADCLoop()
{
  if (cfgADCf == 1)
  {
    int   adcAcc = 0;
    
    AdcInArray[AdcInPointer] = analogRead(PIN_ADC_IN);
    AdcInPointer++;
    if (AdcInPointer >= ADC_ARRAY_SIZE)
      AdcInPointer = 0;
  
    // Calculamos la media del Array...
    for (int i = 0; i < ADC_ARRAY_SIZE; i++)
      adcAcc = adcAcc + AdcInArray[i];
    
    AdcIn = adcAcc/ADC_ARRAY_SIZE;
  }
  else
    AdcIn = analogRead(PIN_ADC_IN);

  if (cfgADCs == 0)
    AdcVal = (float)AdcIn*((float)cfgADCm)/(float)cfgADCp - (float)cfgADCb/1000;
  else
    AdcVal = (float)AdcIn*((float)cfgADCm)/(float)cfgADCp + (float)cfgADCb/1000;
}
