
////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ControlState = STATE_STANDBY;
  ControlTick = millis();

  // Outs  
  FanState = STATE_STANDBY;
  PumpState = STATE_STANDBY;
  IrriState = STATE_STANDBY;
  Aux1State = STATE_STANDBY;
  Aux2State = STATE_STANDBY;
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  switch (ControlState)
  {
    case STATE_STANDBY:
      //ControlTick = millis();
      
      // Control de Temperatura
      if (NtcIn >= cfgTempHi)
        ControlState = STATE_TEMPHI;

      // Control entradas 
      _IOPulsLoop();
      
      break;

    case STATE_TEMPHI:
      //if (millis() - ControlTick >= (cfgRemotePulsTick*100))
      //  ControlState = STATE_STANDBY;

      // Control de Temperatura
      if (NtcIn <= cfgTempLo)
        ControlState = STATE_STANDBY;
        
      break;
  }

  _CtrOutsLoop();
  _CtrWindowLoop();
}

void _CtrOutsLoop(void)
{
  // Fan
  switch (FanState)
  {
    case STATE_STANDBY:
      OutFan = OUT_OFF;      
      FanTick = millis();
      break;

    case STATE_OUT_ON:
      OutFan = OUT_ON;
      if (millis() - FanTick >= (cfgFanTick*cfgScaleMin*60000))
        FanState = STATE_STANDBY;      
      
      break;
  }

  // Pump
  switch (PumpState)
  {
    case STATE_STANDBY:
      OutPump = OUT_OFF;      
      PumpTick = millis();
      break;

    case STATE_OUT_ON:
      OutPump = OUT_ON;
      if (millis() - PumpTick >= (cfgPumpTick*cfgScaleMin*60000))
        PumpState = STATE_STANDBY;
      
      break;
  }

  // Irri
  switch (IrriState)
  {
    case STATE_STANDBY:
      OutIrri = OUT_OFF;      
      IrriTick = millis();
      break;

    case STATE_OUT_ON:
      OutIrri = OUT_ON;
      if (millis() - IrriTick >= (cfgIrriTick*cfgScaleMin*60000))
        IrriState = STATE_STANDBY;
      
      break;
  }

  // Aux1
  switch (Aux1State)
  {
    case STATE_STANDBY:
      OutAux1 = OUT_OFF;      
      Aux1Tick = millis();
      break;

    case STATE_OUT_ON:
      OutAux1 = OUT_ON;
      if (millis() - Aux1Tick >= (cfgAux1Tick*cfgScaleMin*60000))
        Aux1State = STATE_STANDBY;
      
      break;
  }

  // Aux2
  switch (Aux2State)
  {
    case STATE_STANDBY:
      OutAux2 = OUT_OFF;      
      Aux2Tick = millis();
      break;

    case STATE_OUT_ON:
      OutAux2 = OUT_ON;
      if (millis() - Aux2Tick >= (cfgAux2Tick*cfgScaleMin*60000))
        Aux2State = STATE_STANDBY;
      
      break;
  }
}

void _CtrWindowLoop(void)
{
  switch (windowState)
  {
    case STATE_WSTANDBY:
      OutClose = OUT_OFF;
      OutOpen = OUT_OFF;
      windowControlTick = millis();
      break;

    case STATE_WCLOSING:
      OutClose = OUT_ON;
      OutOpen = OUT_OFF;
      if (millis() - windowControlTick >= (cfgTimeCloseMin*60000))
        windowState = STATE_WSTANDBY;
      break;
      
    case STATE_WOPENING:
      OutClose = OUT_OFF;
      OutOpen = OUT_ON;
      if (millis() - windowControlTick >= (cfgTimeOpenMin*60000))
        windowState = STATE_WSTANDBY;
      break;
  }
}
