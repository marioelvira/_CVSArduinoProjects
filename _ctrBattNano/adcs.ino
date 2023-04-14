
/////////////////
// ADCs set up //
/////////////////
void _ADCsSetup()
{
  int i, j;

  for (i = 0; i < ADC_NUMBER; i++)
    AdcDig[i] = 0;

  // No bigger than ADC_NUMBER
  AdcPin[0] = PIN_ADC0;
  AdcPin[1] = PIN_ADC1;
  //AdcPin[2] = PIN_ADC2;
  //AdcPin[3] = PIN_ADC3;
  //AdcPin[4] = PIN_ADC4;
  //AdcPin[5] = PIN_ADC5;
  //AdcPin[6] = PIN_ADC6;
  //AdcPin[7] = PIN_ADC7; 
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

    AdcDig[i] = analogRead(pin);
  
    if (cfgADCs[i] == 0)
      AdcVal[i] = (float)AdcDig[i]*((float)cfgADCm[i])/(float)10000 - (float)cfgADCb[i]/1000;
    else
      AdcVal[i] = (float)AdcDig[i]*((float)cfgADCm[i])/(float)10000 + (float)cfgADCb[i]/1000;
  }  
}
