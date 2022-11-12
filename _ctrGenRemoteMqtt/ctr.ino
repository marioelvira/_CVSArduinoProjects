
////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ControlState = STATE_STANDBY;
  ControlTick = millis();

  genState = STATE_GEN_OFF;
  genInStatus = 0;

  remPulse = 0;
  remAct = 0;
  
  LuzState = STATE_STANDBY;
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  _GenLoop();

  // Control de Generador
  switch (ControlState)
  {
    case STATE_STANDBY:
      OutGenPuls = OUT_OFF;
      OutStopPuls = OUT_OFF;     
      ControlTick = millis();
      break;

    case STATE_GEN_PULSE:
      OutGenPuls = OUT_ON;
      OutStopPuls = OUT_OFF;
      if (millis() - ControlTick >= (cfgRemotePulsTick*100))
        ControlState = STATE_STANDBY;      

      remPulse = 1;
      break;

    case STATE_STOP_PULSE:
      OutGenPuls = OUT_OFF;
      OutStopPuls = OUT_ON;
      if (millis() - ControlTick >= (cfgRemotePulsTick*100))
        ControlState = STATE_STANDBY;      

      remPulse = 0;
      break;
  }

  // Control de Luz
  switch (LuzState)
  {
    case STATE_STANDBY:
      OutLuzOff = OUT_OFF;      
      LuzTick = millis();
      break;

    case STATE_LUZ_OFF:
      OutLuzOff = OUT_ON;
      if (millis() - LuzTick >= (cfgLuzOutTick*900000))
        LuzState = STATE_STANDBY;      
      
      break;
  }
}
