#include "main.h"
#include "adcs.h"

/////////
// Iac //
/////////
void _IrmsSetup()
{
  for (int i = 0; i < EMON_NUMBER; i++)
    emonState[i] = EMON_INIT;
}

void _IrmsLoop()
{
  double offsetI, filteredI, sqI, sumI;
  int    adcDig;
  offsetI = ADC_COUNTS>>1;

  for (int i = 0; i < EMON_NUMBER; i++)
  {
    switch (emonState[i])
    {
      case EMON_INIT:
        emonSumI[i] = 0;
        emonSamples[i] = 0;

        emonState[i] = EMON_READ;
        break;

      case EMON_READ:
        AdcDig[i + ADC_EMON_OFFSET] = analogRead(AdcPin[i + ADC_EMON_OFFSET]);
        adcDig = AdcDig[i + ADC_EMON_OFFSET];

        // Digital low pass filter extracts the 2.5 V or 1.65 V dc offset,
        //  then subtract this - signal is now centered on 0 counts.
        offsetI = (offsetI + (adcDig - offsetI)/1024);
        filteredI = adcDig - offsetI;

        // Root-mean-square method current
        // 1) square current values
        sqI = filteredI * filteredI;
        // 2) sum
        emonSumI[i] += sqI;

        emonSamples[i]++;
        if (emonSamples[i] > cfgEmonS[i])
          emonState[i] = EMON_RESULT;
        break;

      case EMON_RESULT:
        double I_RATIO = double(cfgEmonR[i]) *((ADC_SUPPLY_VOLTAGE/1000.0) / (ADC_COUNTS));
        emonIRMS[i] = I_RATIO * sqrt(emonSumI[i] / cfgEmonS[i]);
        Irms[i] = (int)(emonIRMS[i]*1000) + cfgEmonO[i];

        emonState[i] = EMON_INIT;
        break;
    }
  }
}

/////////
// Vdc //
/////////
void _VdcSetup ()
{
  for (int i = 0; i < VDC_NUMBER; i++)
    Vdc[i] = 0;
}

void _VdcLoop ()
{
  int  adcDig;

  for (int i = 0; i < VDC_NUMBER; i++)
  {
    if (millis() - AdcTick[i + ADC_VDC_OFFSET] >= ADC_TICK)
    {
      AdcDig[i + ADC_VDC_OFFSET] = analogRead(AdcPin[i + ADC_VDC_OFFSET]);
      adcDig = AdcDig[i + ADC_VDC_OFFSET];

      Vdc[i] = (float)adcDig*((float)cfgVADCm[i])/(float)10000 + (float)cfgVADCb[i]/1000;

      AdcTick[i + ADC_VDC_OFFSET] = millis();
    }
  }
}
