////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ControlMode = MODE_AUTO;
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
      //if (millis() - ControlTick >= (TimeOutStart*1000))
      //  ControlState = STATE_XXXX;
      break;

    case STATE_XXXX:  
      //ControlTick = millis();
      break;
  }
}
