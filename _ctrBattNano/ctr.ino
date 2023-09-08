////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ctrInClock = IN_CLOCK_INVERTER_DIS;
  ctrOutRele = OUT_RELE_INVERTER_OFF;
  ctrDisplay = 0;

  ctrMode = MODE_AUTO;
}

void _ctrPuls(void)
{
  if (inPulsState == LONG_PULS)
  {
    ctrDisplay = 0;
    ctrDisplaySec = 0;
  }
  else if (inPulsState == SHORT_PULS)
  {
    ctrDisplay++;
    if (ctrDisplay >= 9)
      ctrDisplay = 9;

    ctrDisplaySec = ctrDisplay*X_3600;
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
  else if (ctrDisplaySec > 9*X_3600)
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
  else if (ctrDisplaySec > 8*X_3600)
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
  else if (ctrDisplaySec > 7*X_3600)
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
  else if (ctrDisplaySec > 6*X_3600)
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
  else if (ctrDisplaySec > 5*X_3600)
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
  else if (ctrDisplaySec > 4*X_3600)
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
  else if (ctrDisplaySec > 3*X_3600)
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
  else if (ctrDisplaySec > 2*X_3600)
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
  else if (ctrDisplaySec > 1*X_3600)
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
  // In Clock
  ctrInClock = InDig[1];

  // Inverter disabled
  if (ctrInClock == IN_CLOCK_INVERTER_DIS)
    ctrOutRele = OUT_RELE_INVERTER_OFF;
  // Inverter enabled
  else
  {
    // if Display on count down
    if (ctrDisplay != 0)
      ctrOutRele = OUT_RELE_INVERTER_OFF;
    else
    {
      // TODO
      // Current control
      // Voltage control
      ctrOutRele = OUT_RELE_INVERTER_ON;
    }
  }

  _ctrLcdLoop();
  // Out relé update
  OutDig[8] = ctrOutRele;
}
