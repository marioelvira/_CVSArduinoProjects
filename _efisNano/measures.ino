
#include "main.h"
#include "adcs.h"

/////////
// Iac //
/////////
void _IrmsSetup()
{
  for (int i = 0; i < EMON_NUMBER; i++)
    emonState[i] = EMON_INIT;

  //AdcEmon[0].current(AdcPin[0], cfgEmonR[0]);
  //AdcEmon[1].current(AdcPin[1], cfgEmonR[1]);
}

void _IrmsLoop()
{
  // Iacs
  if (millis() - AdcTick[0] >= ADC_TICK)
  {
    AdcDig[0] = analogRead(AdcPin[0]);

    if (cfgEmonType[0] == 0)
      Is[0] = calcIrms(0);
    else
      Is[0] = (float)AdcDig[0]*((float)cfgEmonIDCm[0])/(float)10000 + (float)cfgEmonIDCm[0]/1000;

    AdcTick[0] = millis();
  }

  //loopIrms(0);

  if (millis() - AdcTick[1] >= ADC_TICK)
  {
    AdcDig[1] = analogRead(AdcPin[1]);

    if (cfgEmonType[1] == 0)
      Is[1] = calcIrms(1);
    else
      Is[1] = (float)AdcDig[1]*((float)cfgEmonIDCm[1])/(float)10000 + (float)cfgEmonIDCm[1]/1000;

    AdcTick[1] = millis();
  }
  
  //loopIrms(1);
}

/*
int loopIrms(int i)
{
  double offsetI, filteredI, dIratio;
  double sqI, dIrms;
  int    sampleI, adcPin;

  offsetI = ADC_COUNTS>>1;

  switch (emonState[i])
  {
    case EMON_INIT:
        emonSumI[i] = 0;
        emonSamples[i] = 0;

        emonState[i] = EMON_READ;
        break;

    case EMON_READ:
        adcPin = AdcPin[i + ADC_EMON_OFFSET];
        sampleI = analogRead(adcPin);

        AdcDig[i + ADC_EMON_OFFSET] = sampleI;

        // Digital low pass filter extracts the 2.5 V or 1.65 V dc offset,
        offsetI = (offsetI + ((double)sampleI - offsetI)/1024);
        // Subtract this - signal is now centered on 0 counts.
        filteredI = (double)sampleI - offsetI;

        // Root-mean-square method current
        sqI = filteredI * filteredI;
        emonSumI[i] += sqI;

        emonSamples[i]++;
        if (emonSamples[i] > cfgEmonS[i])
          emonState[i] = EMON_RESULT;
        break;

    case EMON_RESULT:
        dIratio = cfgEmonR[i] *((SUPP_VOLTAGE/1000.0) / (ADC_COUNTS));
        dIrms = dIratio * sqrt(emonSumI[i] / cfgEmonS[i]);

        Irms[i] = (int)(dIrms*1000) + cfgEmonO[i];
        emonState[i] = EMON_INIT;
        break;
    }
}
*/
int calcIrms(int i)
{
  int sampleI, nSamples, adcPin, Irms;
  double offsetI, filteredI, dIratio;
  double sqI, sumI, dIrms;

  sumI = 0;
  offsetI = ADC_COUNTS>>1;
  nSamples = cfgEmonS[i];
  adcPin = AdcPin[i];

  for (unsigned int n = 0; n < nSamples; n++)
  {
    sampleI = analogRead(adcPin);

    // Digital low pass filter extracts the 2.5 V or 1.65 V dc offset,
    offsetI = (offsetI + ((double)sampleI - offsetI)/1024);
    // Subtract this - signal is now centered on 0 counts.
    filteredI = (double)sampleI - offsetI;

    // Root-mean-square method current
    sqI = filteredI * filteredI;
    sumI += sqI;
  }

  dIratio = cfgEmonR[i] *((SUPP_VOLTAGE/1000.0) / (ADC_COUNTS));
  dIrms = dIratio * sqrt(sumI / nSamples);

  Irms = (int)(dIrms*1000) + cfgEmonO[i];

  return Irms;
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
}