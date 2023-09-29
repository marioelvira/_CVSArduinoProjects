
/////////////////
// ADCs set up //
/////////////////
void _ADCsSetup()
{
  int i, j;

  for (i = 0; i < ADC_NUMBER; i++)
  {
    AdcDig[i] = 0;
    AdcTick[i] = millis() + i*(ADC0_TICK/2);
  }

  // No bigger than ADC_NUMBER
  AdcPin[0] = PIN_ADC0;
  AdcPin[1] = PIN_ADC1;
  //AdcPin[2] = PIN_ADC2;
  //AdcPin[3] = PIN_ADC3;
  //AdcPin[4] = PIN_ADC4;
  //AdcPin[5] = PIN_ADC5;
  //AdcPin[6] = PIN_ADC6;
  //AdcPin[7] = PIN_ADC7;

  // Vdc
  AdcVdc = EEPROM_VAL_ADC_VDC_L1;

  // Emon
  AdcEmon.current(AdcPin[0], cfgADCEmonR); // ADC_EMON_RATIO
  AdcIrms = 0;
  AdcIrmsInt = 0;
}

////////////////////////
// ADCs state machine //
////////////////////////
void _ADCsLoop()
{
  // ADC 0 - Consumo Iac
  if (millis() - AdcTick[0] >= ADC0_TICK)
  {
    AdcDig[0] = analogRead(AdcPin[0]);

    AdcIrms = AdcEmon.calcIrms(cfgADCEmonS); // ADC_EMON_SAMPLES
    AdcIrmsInt = (int)(AdcIrms*1000) + cfgADCEmonO;

    AdcTick[0] = millis();
  }

  // ADC 1 - Tension Vdc
  if (millis() - AdcTick[1] >= ADC1_TICK)
  {
    AdcDig[1] = analogRead(AdcPin[1]);

    AdcVdc = (float)AdcDig[1]*((float)cfgADCm)/(float)10000 + (float)cfgADCb/1000;

    AdcTick[1] = millis();
  }

}
