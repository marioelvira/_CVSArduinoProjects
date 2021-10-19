
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
      ControlTick = millis();
      break;
      
    case STATE_RPULS_ON:
      OutGenPuls = OUT_ON;

      if (millis() - ControlTick >= (RemotePulsTick*100))
        ControlState = STATE_STANDBY;      
      
      break;
  }
}
