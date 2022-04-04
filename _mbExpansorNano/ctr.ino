/*
////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ControlState = STATE_START;
  ControlTick = millis();
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  switch (ControlState)
  {
    case STATE_START:
      if (millis() - ControlTick >= (TimeOutStart*1000))
        ControlState = STATE_XXXX;
      break;

    case STATE_XXXX:  
      TimeControlSec = 0;
      ControlTick = millis();
      break;
  }
}
*/
