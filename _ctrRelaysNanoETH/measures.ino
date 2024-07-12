#include "main.h"
#include "adcs.h"


//////////
// Irms //
//////////
void _IrmsSetup()
{
  Ioffset = ADC_COUNTS>>1;

  for (int i = 0; i < IRMS_NUMBER; i++)
  { 
    nSamples[i] = 0;
    Iratio[i] = cfgIACr[i] *((ADC_SUPPLY_VOLTAGE/1000.0)/(ADC_COUNTS));

    IrmsuTick[i] = micros() + samplePeriod + (samplePeriod>>2)*i;
    IrmsCont[i] = 0;

    IrmsTick[i] = millis() + samplePeriod + (samplePeriod>>2)*i;
    Irms[i] = 0;
  }
}

void _IrmsLoop()
{
  int adcDig, i, j;
  double add, sqr;

  for (i = 0; i < IRMS_NUMBER; i++)
  {
    if (micros() - IrmsuTick[i] >= samplePeriod)
    {
      AdcDig[i + ADC_EMON_OFFSET] = analogRead(AdcPin[i + ADC_EMON_OFFSET]);
      adcDig = AdcDig[i + ADC_EMON_OFFSET];

      // Digital low pass filter extracts the 1.65 V dc offset,
      // then subtract this - signal is now centered on 0 counts.
      Ioffset = (Ioffset + (adcDig - Ioffset)/1024);
      Isamples[nSamples[i]][i] = (double)adcDig - Ioffset;
      nSamples[i]++;

      IrmsuTick[i] = micros();

      if (nSamples[i] >= numSamples)
      {
        add = 0;

        for (int j = 0; j < numSamples; j++)
          add += Isamples[j][i] * Isamples[j][i];
  
        sqr = sqrt(add / double(numSamples));

        Irms[i] = Iratio[i] * 1000 * sqr;
        nSamples[i] = 0;
      }
    }
  }
}

/////////
// Vdc //
/////////
void _VdcSetup()
{
  for (int i = 0; i < VDC_NUMBER; i++)
  {
    VdcTick[i] = millis() + VDC_MTICK + (VDC_MTICK>>2)*i;
    Vdc[i] = 0;
  }
}

void _VdcLoop()
{
  int  adcDig;

  for (int i = 0; i < VDC_NUMBER; i++)
  {
    if (millis() - VdcTick[i] >= VDC_MTICK)
    {
      AdcDig[i + ADC_VDC_OFFSET] = analogRead(AdcPin[i + ADC_VDC_OFFSET]);
      adcDig = AdcDig[i + ADC_VDC_OFFSET];

      Vdc[i] = (float)adcDig*((float)cfgVDCm[i])/(float)10000 + (float)cfgVDCb[i]/1000;

      VdcTick[i] = millis();
    }
  }
}
