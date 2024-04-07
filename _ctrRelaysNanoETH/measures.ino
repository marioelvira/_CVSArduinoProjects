#include "main.h"
#include "adcs.h"

//////////
// Irms //
//////////
void _IrmsSetup()
{
  for (int i = 0; i < IRMS_NUMBER; i++)
  {
    IrmsRead[i].begin(IrmsVoltRange, IRMS_WINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
    IrmsRead[i].start();
  
    IrmsuTick[i] = micros() + IRMS_UTICK + (IRMS_UTICK>>2)*i;
    IrmsCont[i] = 0;
    Irms[i] = 0;
  }
}

void _IrmsLoop()
{
  int adcDig;

  for (int i = 0; i < IRMS_NUMBER; i++)
  {
    if (micros() - IrmsuTick[i] >= IRMS_UTICK)
    {
      AdcDig[i + ADC_EMON_OFFSET] = analogRead(AdcPin[i + ADC_EMON_OFFSET]);
      adcDig = AdcDig[i + ADC_EMON_OFFSET];

      IrmsRead[i].update(adcDig);
      IrmsuTick[i] = micros();

      IrmsCont[i]++;
      if (IrmsCont[i] > IRMS_CONT)
      {
        IrmsRead[i].publish();
        Irms[i] = (int)(IrmsRead[i].rmsVal*1000);
        IrmsCont[i] = 0;
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
