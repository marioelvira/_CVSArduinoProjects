
#if (_USE_MQTT_ == 1)
void _ctrStateString (void)
{
  switch (ctrInState)
  {
    case IN_STATE0:
      ctrStateString = "BAT";
      break;

    case IN_STATE1:
      ctrStateString = "DIESEL";
      break;

    case IN_STATE2:
      ctrStateString = "GAS";
      break;   
  }
}
#endif

////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ctrMode = MODE_AUTO;

  ctrInState = IN_STATE0;
  ctrOutState = OUT_STATE0;

  ctrInState_ant = ctrInState;
  ctrOutSecTick = timeSecTick;

  crtCIrmsState[0] = IRMS_STATE0;
  crtCIrmsState[1] = IRMS_STATE0;
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

  if (ctrInState == IN_STATE0)
  {
    _ctrADCCurret(0);
    _ctrADCCurret(1);
  }

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

void _ctrADCCurret(int i) {

  switch (crtCIrmsState[i])
  {
    case IRMS_STATE0:
      if (Ival[i] > cfgIlim[i])
      {
        ctrCIrmsUpSecTick[i] = timeSecTick;
        ctrCIrmsDownSecTick[i] = timeSecTick;
        crtCIrmsState[i] = IRMS_STATE1;
      }
      break;

    case IRMS_STATE1:
      if (Ival[i] > cfgIlim[i])
      {
        ctrCIrmsDownSecTick[i] = timeSecTick;
        
        if (timeSecTick - ctrCIrmsUpSecTick[i] >=  (unsigned long)cfgIsec[i])
        {
          ctrOutState = OUT_STATE0;
          ctrOutSecTick = timeSecTick;
        
          ctrCIrmsUpSecTick[i] = timeSecTick;
          crtCIrmsState[i] = IRMS_STATE2;
        }
      }
      else
      {
        if (timeSecTick - ctrCIrmsDownSecTick[i] >=  (unsigned long)cfgIsec[i])
          crtCIrmsState[i] = IRMS_STATE0;
      }
      break;

    case IRMS_STATE2:
        if (timeSecTick - ctrCIrmsUpSecTick[i] >=  (unsigned long)cfgCtrSecs[6])
          crtCIrmsState[i] = IRMS_STATE0;
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
  ctrOutSecTick = timeSecTick;
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
    
      if (timeSecTick - ctrOutSecTick >=  (unsigned long)cfgCtrSecs[0])
      {
        ctrOutSecTick = timeSecTick;
        ctrOutState = OUT_STATE1;
      }
      break;

    case OUT_STATE1:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_ON;
      OutDig[2] = OUT_OFF;
      OutDig[3] = OUT_OFF;
      OutDig[4] = OUT_OFF;

      if (timeSecTick - ctrOutSecTick >=  (unsigned long)cfgCtrSecs[1])
      {
        ctrOutSecTick = timeSecTick;
        ctrOutState = OUT_STATE2;
      }
      
      break;

    case OUT_STATE2:
      OutDig[0] = OUT_ON;
      OutDig[1] = OUT_ON;
      OutDig[2] = OUT_OFF;
      OutDig[3] = OUT_OFF;
      OutDig[4] = OUT_OFF;

      ctrOutSecTick = timeSecTick;
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
    
      if (timeSecTick - ctrOutSecTick >=  (unsigned long)cfgCtrSecs[2])
      {
        ctrOutSecTick = timeSecTick;
        ctrOutState = OUT_STATE1;
      }
      break;

    case OUT_STATE1:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_OFF;
      OutDig[2] = OUT_ON;
      OutDig[3] = OUT_OFF;
      OutDig[4] = OUT_OFF;
      
      if (timeSecTick - ctrOutSecTick >=  (unsigned long)cfgCtrSecs[3])
      {
        ctrOutSecTick = timeSecTick;
        ctrOutState = OUT_STATE2;
      }
      
      break;

    case OUT_STATE2:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_OFF;
      OutDig[2] = OUT_ON;
      OutDig[3] = OUT_ON;
      OutDig[4] = OUT_OFF;

      ctrOutSecTick = timeSecTick;
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
    
      if (timeSecTick - ctrOutSecTick >=  (unsigned long)cfgCtrSecs[4])
      {
        ctrOutSecTick = timeSecTick;
        ctrOutState = OUT_STATE1;
      }
      break;

    case OUT_STATE1:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_OFF;
      OutDig[2] = OUT_OFF;
      OutDig[3] = OUT_OFF;
      OutDig[4] = OUT_ON;
  
      if (timeSecTick - ctrOutSecTick >=  (unsigned long)cfgCtrSecs[5])
      {
        ctrOutSecTick = timeSecTick;
        ctrOutState = OUT_STATE2;
      }
      
      break;

    case OUT_STATE2:
      OutDig[0] = OUT_OFF;
      OutDig[1] = OUT_OFF;
      OutDig[2] = OUT_OFF;
      OutDig[3] = OUT_ON;
      OutDig[4] = OUT_ON;

      ctrOutSecTick = timeSecTick;
      break;
  }
}
