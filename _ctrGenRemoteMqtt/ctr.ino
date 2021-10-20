
////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ControlState = STATE_STANDBY;
  ControlTick = millis();
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  switch (ControlState)
  {
    case STATE_STANDBY:
      OutGenPuls = OUT_OFF;
      OutBomPuls = OUT_OFF;
      ControlTick = millis();
      break;
      
    case STATE_GEN_PULSE:
      OutGenPuls = OUT_ON;
      OutBomPuls = OUT_OFF;
      if (millis() - ControlTick >= (cfgRemotePulsTick*100))
        ControlState = STATE_STANDBY;      
      
      break;

    case STATE_BOM_PULSE:
      OutGenPuls = OUT_OFF;
      OutBomPuls = OUT_ON;

      if (millis() - ControlTick >= (cfgRemotePulsTick*100))
        ControlState = STATE_STANDBY;      
      
      break;

  }
}
