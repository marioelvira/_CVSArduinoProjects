
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
  /*
  switch (ControlState)
  {
    case STATE_STANDBY:
      ControlTick = millis();
      break;

    case STATE_GEN_PULSE:
      if (millis() - ControlTick >= (cfgRemotePulsTick*100))
        ControlState = STATE_STANDBY;      
      break;

    case STATE_STOP_PULSE:
      if (millis() - ControlTick >= (cfgRemotePulsTick*100))
        ControlState = STATE_STANDBY;
      break;
  }
  */
}
