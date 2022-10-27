
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
  genMinOn = 0;
  
  LuzState = STATE_STANDBY;
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  // Gen State
  if (cfgGenOnPin == 1)
  {
    if (InGenOn == IO_OFF)
      genInStatus = 0;
    else
      genInStatus = 1;
  }
  else
  {
    if (DisplayIndicador == 0)
      genInStatus = 0;
    else
      genInStatus = 1;
  }

  // Gen Status
  switch (genState)
  {
    case STATE_GEN_OFF:
      remAct = 0;
      //genMinOn = 0;
      if (genInStatus == 1)
      {
        if (remPulse == 1)
          genState = STATE_GEN_REM_ON;
        else
          genState = STATE_GEN_ON;

        remPulse = 0; //BUG
        
        genMinOn = 0;
      }
      break;

    case STATE_GEN_REM_ON:
      remAct = 1;
      _GenTimeReset();
      if (genInStatus == 0)
      {
        remPulse = 0; //BUG
        genState = STATE_GEN_OFF;
      }
      break;

    case STATE_GEN_ON:
      remAct = 0;
      _GenTimeReset();
      if (genInStatus == 0)
      {
        remPulse = 0; //BUG
        genState = STATE_GEN_OFF;
      }
      break;
  }

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
