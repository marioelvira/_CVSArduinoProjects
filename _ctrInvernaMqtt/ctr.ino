
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

  fanTempState = STATE_TFOFF;

  // Reset outs
  OutClose = OUT_OFF;
  OutOpen = OUT_OFF;

  // Outs  
  FanState  = STATE_STANDBY;
  PumpState = STATE_STANDBY;
  IrriState = STATE_STANDBY;
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

      // Permitimos control
      _IOPulsLoop();
      _CtrWindowLoop();
      break;
      
    case STATE_TEMPLO:
      // Ciclos cierre
      _CtrCloseLoop();

      if (NtcIn > (cfgTempLo + 2))  // Histéres
      {
        // Reset outs
        OutClose = OUT_OFF;
        OutOpen = OUT_OFF;
        ControlState = STATE_STANDBY;
      }

      // Permitimos control
      _IOPulsLoop();  
      _CtrWindowLoop();
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
      else if (NtcIn <= cfgTempHi - 2)
      {
        // Permitimos control
        _IOPulsLoop();  
        _CtrWindowLoop();
      }    
      break;    
  }

  // Control Ventilador
  _CtrFanLoop();

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
        OutOpen = OUT_OFF;      
        openLoopTick = millis();
        openLoopState = WAIT_TO_NOPEN;
      }
        
      break;

    case WAIT_TO_NOPEN:
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
        OutClose = OUT_OFF;       
        closeLoopTick = millis();
        closeLoopState = WAIT_TO_NCLOSE;
      }
        
      break;

    case WAIT_TO_NCLOSE:
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
      windowControlTick = millis();
      break;

    case STATE_WCLOSING:
      OutClose = OUT_ON;
      OutOpen = OUT_OFF;
      
      if (millis() - windowControlTick >= (cfgTimeCloseMin*60000))
      {
        OutClose = OUT_OFF;
        windowState = STATE_WSTANDBY;
      }
      break;
      
    case STATE_WOPENING:
      OutClose = OUT_OFF;
      OutOpen = OUT_ON;
      
      if (millis() - windowControlTick >= (cfgTimeOpenMin*60000))
      {
        OutOpen = OUT_OFF;
        windowState = STATE_WSTANDBY;
      }
      break;
  }
}

void _CtrFanLoop(void)
{
  if ((cfgFanTempHi != 0) && (cfgFanTempLo != 0))
  {
    switch (fanTempState)
    {
      case STATE_TFOFF:
        OutFan = OUT_OFF;
        if (NtcIn >= cfgFanTempHi)
          fanTempState = STATE_TFON;
        break;

      case STATE_TFON:
        OutFan = OUT_ON;
        if (NtcIn <= cfgFanTempLo)
          fanTempState = STATE_TFOFF;
        break;
    }
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
}
