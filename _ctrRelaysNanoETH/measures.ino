#include "main.h"
#include "adcs.h"

///////
// I //
///////
void _ISetup()
{
  Ioffset = ADC_COUNTS>>1;

  for (int i = 0; i < I_NUMBER; i++)
  { 
    // Irms
    if (cfgIType[i] == I_TYPE_IRMS)
    {
      nSamples[i] = 0;
      Iratio[i] = cfgIACr[i] *((ADC_SUPPLY_VOLTAGE/1000.0)/(ADC_COUNTS));

      IuTick[i] = micros() + samplePeriod + (samplePeriod>>I_NUMBER)*i;
      IrmsCont[i] = 0;
    }
    // Idc
    else
      IuTick[i] = micros() + IDC_MTICK + (IDC_MTICK>>I_NUMBER)*i;
    
    Ival[i] = 0;
  }
}

void _ILoop()
{
  int adcDig, i, j;
  double add, sqr;

  for (i = 0; i < I_NUMBER; i++)
  {
    // Irms
    if (cfgIType[i] == I_TYPE_IRMS)
    {
      if (micros() - IuTick[i] >= samplePeriod)
      {
        AdcDig[i + ADC_I_OFFSET] = analogRead(AdcPin[i + ADC_I_OFFSET]);
        adcDig = AdcDig[i + ADC_I_OFFSET];

        // Digital low pass filter extracts the 1.65 V dc offset,
        // then subtract this - signal is now centered on 0 counts.
        Ioffset = (Ioffset + (adcDig - Ioffset)/1024);
        Isamples[nSamples[i]][i] = (double)adcDig - Ioffset;
        nSamples[i]++;

        IuTick[i] = micros();

        if (nSamples[i] >= numSamples)
        {
          add = 0;

          for (int j = 0; j < numSamples; j++)
            add += Isamples[j][i] * Isamples[j][i];
    
          sqr = sqrt(add / double(numSamples));

          Ival[i] = Iratio[i] * 1000 * sqr;
          nSamples[i] = 0;
        }
      }
    }
    // Idc
    else
    {
      if (micros() - IuTick[i] >= IDC_MTICK)
      {
        AdcDig[i + ADC_I_OFFSET] = analogRead(AdcPin[i + ADC_I_OFFSET]);
        adcDig = AdcDig[i + ADC_I_OFFSET];

        Ival[i] = (float)adcDig*((float)cfgIDCm[i])/((float)10000*(float)ADC_FULL_SCALE) + (float)cfgIDCb[i]/1000;

        IuTick[i] = micros();
      }
    }
  }
}

///////
// V //
///////
void _VSetup()
{
  for (int i = 0; i < V_NUMBER; i++)
  {
    VuTick[i] = micros() + VDC_MTICK + (VDC_MTICK>>V_NUMBER)*i;
    Vval[i] = 0;
  }
}

void _VLoop()
{
  int   adcDig;
  float adcAna;

  for (int i = 0; i < V_NUMBER; i++)
  {
    if (micros() - VuTick[i] >= VDC_MTICK)
    {
      AdcDig[i + ADC_V_OFFSET] = analogRead(AdcPin[i + ADC_V_OFFSET]);
      adcDig = AdcDig[i + ADC_V_OFFSET];

      //adcAna = (((float)adcDig)*ADC_SUPPLY_VOLTAGE)/(float)ADC_FULL_SCALE;  // (mV).
      //Vval[i] = adcAna*((float)cfgVDCm[i])/(float)10000 + (float)cfgVDCb[i]/1000;

      Vval[i] = (float)adcDig*((float)cfgVDCm[i])/(float)10000 + (float)cfgVDCb[i]/1000;

      VuTick[i] = micros();
    }
  }
}
