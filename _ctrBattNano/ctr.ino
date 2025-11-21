////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ctrInClock = IN_CLOCK_INVERTER_DIS;
  ctrOutRele = OUT_RELE_INVERTER_OFF;
  ctrDisplay = 0;

  ctrMode = MODE_AUTO;

  crtIrmsState = CTR_INV_STANDBY;
  crtIrmstick = millis();

  crtVdcState = CTR_INV_STANDBY;
  crtVdctick = millis();

  crtDisplayState = CTR_INV_STANDBY;
}

void _ctrPuls(void)
{
  if (inPulsType == LONG_PULS)
  {
    ctrDisplay = 0;
    ctrDisplaySec = 0;
  }
  else if (inPulsType == SHORT_PULS)
  {
    ctrDisplay++;
    if (ctrDisplay >= 9)
      ctrDisplay = 9;

    ctrDisplaySec = ctrDisplay*cfgNTimeSecs /*X_3600*/;
  }
}

// Lcd
void _ctrLcdLoop(void) {

  if (ctrDisplaySec == 0)
  {
    ctrDisplay = 0; // a-b-c-d-e-f
    OutDig[0] = OUT_ON;
    OutDig[1] = OUT_ON;
    OutDig[2] = OUT_ON;
    OutDig[3] = OUT_ON;
    OutDig[4] = OUT_ON;
    OutDig[5] = OUT_ON;
    OutDig[6] = OUT_OFF;
    OutDig[7] = OUT_OFF;
  }
  else if (ctrDisplaySec > 9*cfgNTimeSecs /*X_3600*/)
  {
    ctrDisplay = 10;  // a-b-c-d-f-g-dp
    OutDig[0] = OUT_ON;
    OutDig[1] = OUT_ON;
    OutDig[2] = OUT_ON;
    OutDig[3] = OUT_ON;
    OutDig[4] = OUT_OFF;
    OutDig[5] = OUT_ON;
    OutDig[6] = OUT_ON;
    OutDig[7] = OUT_ON;
  }
  else if (ctrDisplaySec > 8*cfgNTimeSecs /*X_3600*/)
  {
    ctrDisplay = 9; // a-b-c-d-f-g
    OutDig[0] = OUT_ON;
    OutDig[1] = OUT_ON;
    OutDig[2] = OUT_ON;
    OutDig[3] = OUT_ON;
    OutDig[4] = OUT_OFF;
    OutDig[5] = OUT_ON;
    OutDig[6] = OUT_ON;
    OutDig[7] = OUT_OFF;
  }
  else if (ctrDisplaySec > 7*cfgNTimeSecs /*X_3600*/)
  {
    ctrDisplay = 8; // a-b-c-d-e-f-g
    OutDig[0] = OUT_ON;
    OutDig[1] = OUT_ON;
    OutDig[2] = OUT_ON;
    OutDig[3] = OUT_ON;
    OutDig[4] = OUT_ON;
    OutDig[5] = OUT_ON;
    OutDig[6] = OUT_ON;
    OutDig[7] = OUT_OFF;
  }
  else if (ctrDisplaySec > 6*cfgNTimeSecs /*X_3600*/)
  {
    ctrDisplay = 7; // a-b-c
    OutDig[0] = OUT_ON;
    OutDig[1] = OUT_ON;
    OutDig[2] = OUT_ON;
    OutDig[3] = OUT_OFF;
    OutDig[4] = OUT_OFF;
    OutDig[5] = OUT_OFF;
    OutDig[6] = OUT_OFF;
    OutDig[7] = OUT_OFF;
  }
  else if (ctrDisplaySec > 5*cfgNTimeSecs /*X_3600*/)
  {
    ctrDisplay = 6; // a-c-d-e-f-g
    OutDig[0] = OUT_ON;
    OutDig[1] = OUT_OFF;
    OutDig[2] = OUT_ON;
    OutDig[3] = OUT_ON;
    OutDig[4] = OUT_ON;
    OutDig[5] = OUT_ON;
    OutDig[6] = OUT_ON;
    OutDig[7] = OUT_OFF;
  }
  else if (ctrDisplaySec > 4*cfgNTimeSecs /*X_3600*/)
  {
    ctrDisplay = 5; // a-c-d-f-g
    OutDig[0] = OUT_ON;
    OutDig[1] = OUT_OFF;
    OutDig[2] = OUT_ON;
    OutDig[3] = OUT_ON;
    OutDig[4] = OUT_OFF;
    OutDig[5] = OUT_ON;
    OutDig[6] = OUT_ON;
    OutDig[7] = OUT_OFF;
  }
  else if (ctrDisplaySec > 3*cfgNTimeSecs /*X_3600*/)
  {
    ctrDisplay = 4; // b-c-f-g
    OutDig[0] = OUT_OFF;
    OutDig[1] = OUT_ON;
    OutDig[2] = OUT_ON;
    OutDig[3] = OUT_OFF;
    OutDig[4] = OUT_OFF;
    OutDig[5] = OUT_ON;
    OutDig[6] = OUT_ON;
    OutDig[7] = OUT_OFF;
  }
  else if (ctrDisplaySec > 2*cfgNTimeSecs /*X_3600*/)
  {
    ctrDisplay = 3; // a-b-c-d-g
    OutDig[0] = OUT_ON;
    OutDig[1] = OUT_ON;
    OutDig[2] = OUT_ON;
    OutDig[3] = OUT_ON;
    OutDig[4] = OUT_OFF;
    OutDig[5] = OUT_OFF;
    OutDig[6] = OUT_ON;
    OutDig[7] = OUT_OFF;
  }
  else if (ctrDisplaySec > 1*cfgNTimeSecs /*X_3600*/)
  {
    ctrDisplay = 2; // a-b-d-e-g
    OutDig[0] = OUT_ON;
    OutDig[1] = OUT_ON;
    OutDig[2] = OUT_OFF;
    OutDig[3] = OUT_ON;
    OutDig[4] = OUT_ON;
    OutDig[5] = OUT_OFF;
    OutDig[6] = OUT_ON;
    OutDig[7] = OUT_OFF;   
  }
  else
  {
    ctrDisplay = 1; // b-c
    OutDig[0] = OUT_OFF;
    OutDig[1] = OUT_ON;
    OutDig[2] = OUT_ON;
    OutDig[3] = OUT_OFF;
    OutDig[4] = OUT_OFF;
    OutDig[5] = OUT_OFF;
    OutDig[6] = OUT_OFF;
    OutDig[7] = OUT_OFF;
  }

}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  // Read Clock in
  ctrInClock = InDig[1];
  // Display control
  _ctrDisplay();
  // Irms control
  _ctrIrms();
  // Vdc control
  _ctrVdc();
  // LCD control
  _ctrLcdLoop();

  _ctrIO2();

  // Inverter disabled
  if (ctrInClock == IN_CLOCK_INVERTER_DIS)
    ctrOutRele = OUT_RELE_INVERTER_OFF;
  // Inverter enabled
  else
  {
    if ((crtIrmsState == CTR_INV_STANDBY) && (crtVdcState == CTR_INV_STANDBY) && (crtDisplayState == CTR_INV_STANDBY))
     ctrOutRele = OUT_RELE_INVERTER_ON;
    else
     ctrOutRele = OUT_RELE_INVERTER_OFF;
  }

  // Out relé update
  OutDig[8] = ctrOutRele;
}

void _ctrIrms(void)
{
  switch (crtIrmsState)
  {
    case CTR_INV_STANDBY:
      // Check 
      if (AdcIrmsInt > cfgADCEmonL)
        crtIrmsState = CTR_INV_OFF;

      crtIrmstick = millis();
      break;

    case CTR_INV_OFF:
      // Hysteresis 
      if (millis() - crtIrmstick < (((unsigned long)cfgADCEmonSec)*1000))
        break;

      // Check 
      if (AdcIrmsInt <= cfgADCEmonL)
        crtIrmsState = CTR_INV_STANDBY;  

      break;
  }
}

void _ctrVdc(void)
{
  switch (crtVdcState)
  {
    case CTR_INV_STANDBY:
      // Check 
      if (AdcVdc < cfgADCVdcL1)
        crtVdcState = CTR_INV_OFF;

      crtVdctick = millis();
      break;

    case CTR_INV_OFF:
      // Hysteresis 
      if (millis() - crtVdctick < (((unsigned long)cfgADCVdcSec)*1000))
        break;

      // Check 
      if (AdcVdc >= cfgADCVdcL2)
       crtVdcState = CTR_INV_STANDBY;  

      break;
  }
}

void _ctrDisplay(void)
{
  switch (crtDisplayState)
  {
    case CTR_INV_STANDBY:
      if (ctrDisplay != 0)
        crtDisplayState = CTR_INV_OFF;
      break;

    case CTR_INV_OFF:
      if (ctrDisplay == 0)
        crtDisplayState = CTR_INV_STANDBY;  

      break;
  }
}

void _ctrIO2(void)
{
  ctrIn2 = InDig[IND_PULS_BLINK];

  if (ctrIn2 == IN_DOWN)
  {
    ctrOut2 = OUT_OFF;
    crtOut2tick = millis();
    crtOut2State = OUT_ON;
  }
  else
  {
    switch (crtOut2State)
    {
      case OUT_ON:
        ctrOut2 = OUT_ON;
        if (millis() - crtOut2tick > (((unsigned long)cfgLuzOnSec)*1000)) // CTR_TICK_OUT2_ON
        {
          crtOut2tick = millis();
          crtOut2State = OUT_OFF;
        }
        break;

      case OUT_OFF:
        ctrOut2 = OUT_OFF;
        if (millis() - crtOut2tick > (((unsigned long)cfgLuzOffSec)*1000)) // CTR_TICK_OUT2_OFF
        {
          crtOut2tick = millis();
          crtOut2State = OUT_ON;
        }
        break;
    }
  }

  OutDig[9] = ctrOut2;
}
