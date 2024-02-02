
#include "main.h"
#include "adcs.h"

/////////
// Iac //
/////////
void _IrmsSetup()
{
  for (int i = 0; i < EMON_NUMBER; i++)
    emonState[i] = EMON_INIT;

  AdcEmon[0].current(AdcPin[0], cfgEmonR[0]);
  AdcEmon[1].current(AdcPin[1], cfgEmonR[1]);
}

void _IrmsLoop()
{
  
  // Iacs
  if (millis() - AdcTick[0] >= ADC_TICK)
  {
    AdcDig[0] = analogRead(AdcPin[0]);

    emonIRMS[0] = AdcEmon[0].calcIrms(cfgEmonS[0]);
    Irms[0] = (int)(emonIRMS[0]*1000) + cfgEmonO[0];

    AdcTick[0] = millis();
  }

  if (millis() - AdcTick[1] >= ADC_TICK)
  {
    AdcDig[1] = analogRead(AdcPin[1]);

    emonIRMS[1] = AdcEmon[1].calcIrms(cfgEmonS[1]);
    Irms[1] = (int)(emonIRMS[1]*1000) + cfgEmonO[1];

    AdcTick[1] = millis();
  }

  /*
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
  }*/
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
  // Vdcs
  if (millis() - AdcTick[2] >= ADC_TICK)
  {
    AdcDig[2] = analogRead(AdcPin[2]);

    Vdc[0] = (float)AdcDig[2]*((float)cfgVADCm[0])/(float)10000 + (float)cfgVADCb[0]/1000;

    AdcTick[2] = millis();
  }

  if (millis() - AdcTick[3] >= ADC_TICK)
  {
    AdcDig[3] = analogRead(AdcPin[3]);

    Vdc[1] = (float)AdcDig[3]*((float)cfgVADCm[1])/(float)10000 + (float)cfgVADCb[1]/1000;

    AdcTick[3] = millis();
  }

  /*
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
  */
}