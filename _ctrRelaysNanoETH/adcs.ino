
/////////////////
// ADCs set up //
/////////////////
void _ADCsSetup()
{
  for (int i = 0; i < ADC_NUMBER; i++)
    AdcDig[i] = 0;

  // No bigger than ADC_NUMBER
  AdcPin[0] = PIN_ADC0;
  AdcPin[1] = PIN_ADC1;
  AdcPin[2] = PIN_ADC2;
  AdcPin[3] = PIN_ADC3;
  AdcPin[4] = PIN_ADC4;
  AdcPin[5] = PIN_ADC5;
  AdcPin[6] = PIN_ADC6;
  AdcPin[7] = PIN_ADC7;

  _ISetup();
  _VSetup();
}

////////////////////////
// ADCs state machine //
////////////////////////
void _ADCsLoop()
{
  _ILoop();
  _VLoop();
}
