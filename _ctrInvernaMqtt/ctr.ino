
////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ControlState = STATE_STANDBY;
  //ControlTick = millis();
  
  // Reset states
  closeLoopState = CLOSE_WINDOW;
  closeLoopTick = millis();
  openLoopState = OPEN_WINDOW;
  openLoopTick = millis();

  // Outs  
  FanState  = STATE_STANDBY;
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

      // Control de Temperatura
      if (NtcIn >= cfgTempHi)
      {
        openLoopState = OPEN_WINDOW;
        openLoopTick = millis();
        ControlState = STATE_TEMPHI;
      }
      else if (NtcIn <= cfgTempLo)
      {
        closeLoopState = CLOSE_WINDOW;
        closeLoopTick = millis();
        ControlState = STATE_TEMPLO;
      }
      
      _IOPulsLoop();  
      _CtrWindowLoop();
      break;
      
    case STATE_TEMPLO:
      // Ciclos cierre
      _CtrCloseLoop();

      if (NtcIn > (cfgTempLo + 2))  // Histéres
        ControlState = STATE_STANDBY;
        
      break;
      
    case STATE_TEMPHI:
      // Ciclos apertura
      _CtrOpenLoop();
    
      if (NtcIn <= cfgTempLo)
      {
        closeLoopState = CLOSE_WINDOW;
        closeLoopTick = millis();
        ControlState = STATE_TEMPLO;
      }    
      break;    
  }

  // Control Remoto por MQTT
  _CtRemOutsLoop();
}

void _CtrOpenLoop(void)
{
  switch (openLoopState)
  {
    case OPEN_WINDOW:
      OutClose = OUT_OFF;
      OutOpen = OUT_ON;
      
      if (millis() - openLoopTick >= (cfgTimeOpenMin*60000))
      {
        openLoopTick = millis();
        openLoopState = WAIT_TO_NOPEN;
      }
        
      break;

    case WAIT_TO_NOPEN:
      OutClose = OUT_OFF;
      OutOpen = OUT_OFF;
      
      if (millis() - openLoopTick >= (cfgTimeCicloMin*60000))
      {
        openLoopTick = millis();
        openLoopState = OPEN_WINDOW;
      }
      break; 
  }
}

void _CtrCloseLoop(void)
{
  switch (closeLoopState)
  {
    case CLOSE_WINDOW:
      OutClose = OUT_ON;
      OutOpen = OUT_OFF;
      
      if (millis() - closeLoopTick >= (cfgTimeCloseMin*60000))
      {
        closeLoopTick = millis();
        closeLoopState = WAIT_TO_NCLOSE;
      }
        
      break;

    case WAIT_TO_NCLOSE:
      OutClose = OUT_OFF;
      OutOpen = OUT_OFF;
      
      if (millis() - closeLoopTick >= (cfgTimeCicloMin*60000))
      {
        closeLoopTick = millis();
        closeLoopState = CLOSE_WINDOW;
      }
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

void _CtRemOutsLoop(void)
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
