
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
  float adcAl;
      
  if (cfgADCf & 0x01)
  {
    int     adcAcc = 0;
    
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

  // Alarm
  adcAl = (float)(cfgADCal)/10;
  
  if (cfgADCf & 0x02)
  {
    if (AdcVal > adcAl)
      alarm[AL_ERROR3] = 1;
    else
      alarm[AL_ERROR3] = 0;
  }
  else
  {
    if (AdcVal < adcAl)
      alarm[AL_ERROR3] = 1;
    else
      alarm[AL_ERROR3] = 0;    
  }
}
