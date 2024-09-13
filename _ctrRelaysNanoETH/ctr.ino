////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ctrMode = MODE_AUTO;

  ctrInState = IN_STATE0;
  ctrOutState = OUT_STATE0;

  ctrInState_ant = ctrInState;
  ctrOutTick = millis();

  crtCIrmsState = IRMS_STATE0;
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  // Control de Entradas
  if ((InDig[0] == IN_OFF) && (InDig[1] == IN_OFF))
    ctrInState = IN_STATE0;
  else if (InDig[0] == IN_ON)
    ctrInState = IN_STATE1;
  else if ((InDig[0] == IN_OFF) && (InDig[1] == IN_ON))
    ctrInState = IN_STATE2;

  _ctrADCCurret();

  if (ctrInState_ant != ctrInState)
    _ctrOutReset();

  ctrInState_ant = ctrInState;

  // Control de Salidas
  if (ctrInState == IN_STATE0)
    _ctrOutState0();
  else if (ctrInState == IN_STATE1)
    _ctrOutState1();
  else /* ctrInState == IN_STATE2 */
    _ctrOutState2();
}

void _ctrADCCurret() {

  switch (crtCIrmsState)
  {
    case IRMS_STATE0:
      if ((InDig[0] == IN_OFF) && (InDig[1] == IN_OFF))
      {
        if ((Ival[0] > cfgIlim[0]) || (Ival[1] > cfgIlim[1]))
        {
          ctrCIrmsTick = millis();
          crtCIrmsState = IRMS_STATE1;
        }
      }
      break;

    case IRMS_STATE1:
        if ((Ival[0] < cfgIlim[0]) && (Ival[1] < cfgIlim[1]))
          crtCIrmsState = IRMS_STATE0;

        if (millis() - ctrCIrmsTick >= IRMS_STATE1_TICKS)
        {
          ctrCIrmsTick = millis();
          ctrCIrmsSec = timeSecTick;
          crtCIrmsState = IRMS_STATE2;
        }
        break;

    case IRMS_STATE2:
        // Forced
        ctrInState = IN_STATE1;

        if (timeSecTick - ctrCIrmsSec >= IRMS_STATE2_SECS)
          crtCIrmsState = IRMS_STATE0;
        break;
  }
}

void _ctrOutReset() {

  OutDig[0] = OUT_OFF;
  OutDig[1] = OUT_OFF;
  OutDig[2] = OUT_OFF;
  OutDig[3] = OUT_OFF;
  OutDig[4] = OUT_OFF;

  ctrOutState = OUT_STATE0;
  ctrOutTick = millis();
}

////////////////////////////////////////////////
//  In1 In2 |   Out1  Out2  Out3  Out4  Out5  //
//  ----------------------------------------  //
//  0   0   |   1     1     0     0     0     //
////////////////////////////////////////////////
void _ctrOutState0 () {

  switch (ctrOutState)
  {
    case OUT_STATE0:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_OFF;
      OutDig[2] = OUT_OFF;
      OutDig[3] = OUT_OFF;
      OutDig[4] = OUT_OFF;
    
      if (millis() - ctrOutTick >= STATE0_0_1_TICKS)
      {
        ctrOutTick = millis();
        ctrOutState = OUT_STATE1;
      }
      break;

    case OUT_STATE1:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_ON;
      OutDig[2] = OUT_OFF;
      OutDig[3] = OUT_OFF;
      OutDig[4] = OUT_OFF;
          
      if (millis() - ctrOutTick >= STATE0_1_2_TICKS)
      {
        ctrOutTick = millis();
        ctrOutState = OUT_STATE2;
      }
      
      break;

    case OUT_STATE2:
      OutDig[0] = OUT_ON;
      OutDig[1] = OUT_ON;
      OutDig[2] = OUT_OFF;
      OutDig[3] = OUT_OFF;
      OutDig[4] = OUT_OFF;

      ctrOutTick = millis();

      break;
  }
}

////////////////////////////////////////////////
//  In1 In2 |   Out1  Out2  Out3  Out4  Out5  //
//  ----------------------------------------  //
//  1   0   |   0     0     1     1     0     //
//  1   1   |   0     0     1     1     0     //
////////////////////////////////////////////////
void _ctrOutState1 () {

  switch (ctrOutState)
  {
    case OUT_STATE0:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_OFF;
      OutDig[2] = OUT_OFF;
      OutDig[3] = OUT_OFF;
      OutDig[4] = OUT_OFF;
    
      if (millis() - ctrOutTick >= STATE1_0_1_TICKS)
      {
        ctrOutTick = millis();
        ctrOutState = OUT_STATE1;
      }
      break;

    case OUT_STATE1:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_OFF;
      OutDig[2] = OUT_ON;
      OutDig[3] = OUT_OFF;
      OutDig[4] = OUT_OFF;
          
      if (millis() - ctrOutTick >= STATE1_1_2_TICKS)
      {
        ctrOutTick = millis();
        ctrOutState = OUT_STATE2;
      }
      
      break;

    case OUT_STATE2:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_OFF;
      OutDig[2] = OUT_ON;
      OutDig[3] = OUT_ON;
      OutDig[4] = OUT_OFF;

      ctrOutTick = millis();

      break;
  }
}

////////////////////////////////////////////////
//  In1 In2 |   Out1  Out2  Out3  Out4  Out5  //
//  ----------------------------------------  //
//  0   1   |   0     0     0     1     1     //
////////////////////////////////////////////////
void _ctrOutState2 () {

  switch (ctrOutState)
  {
    case OUT_STATE0:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_OFF;
      OutDig[2] = OUT_OFF;
      OutDig[3] = OUT_OFF;
      OutDig[4] = OUT_OFF;
    
      if (millis() - ctrOutTick >= STATE2_0_1_TICKS)
      {
        ctrOutTick = millis();
        ctrOutState = OUT_STATE1;
      }
      break;

    case OUT_STATE1:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_OFF;
      OutDig[2] = OUT_OFF;
      OutDig[3] = OUT_OFF;
      OutDig[4] = OUT_ON;
          
      if (millis() - ctrOutTick >= STATE2_1_2_TICKS)
      {
        ctrOutTick = millis();
        ctrOutState = OUT_STATE2;
      }
      
      break;

    case OUT_STATE2:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_OFF;
      OutDig[2] = OUT_OFF;
      OutDig[3] = OUT_ON;
      OutDig[4] = OUT_ON;

      ctrOutTick = millis();

      break;
  }
}
