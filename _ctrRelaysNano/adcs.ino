
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
  AdcPin[2] = PIN_ADC2;
  AdcPin[3] = PIN_ADC3;
  //AdcPin[4] = PIN_ADC4;
  //AdcPin[5] = PIN_ADC5;
  //AdcPin[6] = PIN_ADC6;
  //AdcPin[7] = PIN_ADC7;
 
  // Emon
  C0AdcEmon.current(AdcPin[0], cfgC0ADCEmonR); // ADC_EMON_RATIO
  C0AdcIrms = 0;
  C0AdcIrmsInt = 0;

  C1AdcEmon.current(AdcPin[0], cfgC1ADCEmonR); // ADC_EMON_RATIO
  C1AdcIrms = 0;
  C1AdcIrmsInt = 0;
}

////////////////////////
// ADCs state machine //
////////////////////////
void _ADCsLoop()
{
  // ADC0 - Consumo Iac 0
  if (millis() - AdcTick[0] >= ADC0_TICK)
  {
    AdcDig[0] = analogRead(AdcPin[0]);

    C0AdcIrms = C0AdcEmon.calcIrms(cfgC0ADCEmonS);
    C0AdcIrmsInt = (int)(C0AdcIrms*1000) + cfgC0ADCEmonO;

    AdcTick[0] = millis();
  }
  
  // ADC1 - Consumo Iac 1
  if (millis() - AdcTick[1] >= ADC1_TICK)
  {
    AdcDig[1] = analogRead(AdcPin[1]);

    C1AdcIrms = C1AdcEmon.calcIrms(cfgC1ADCEmonS);
    C1AdcIrmsInt = (int)(C1AdcIrms*1000) + cfgC1ADCEmonO;

    AdcTick[1] = millis();
  }

  // ADC 2 - Tension Vdc 0
  if (millis() - AdcTick[2] >= ADC2_TICK)
  {
    AdcDig[2] = analogRead(AdcPin[2]);

    V0AdcVdc = (float)AdcDig[2]*((float)cfgV0ADCm)/(float)10000 + (float)cfgV0ADCb/1000;

    AdcTick[2] = millis();
  }

  // ADC 3 - Tension Vdc 1
  if (millis() - AdcTick[3] >= ADC3_TICK)
  {
    AdcDig[3] = analogRead(AdcPin[3]);

    V1AdcVdc = (float)AdcDig[3]*((float)cfgV1ADCm)/(float)10000 + (float)cfgV1ADCb/1000;

    AdcTick[3] = millis();
  }

}
