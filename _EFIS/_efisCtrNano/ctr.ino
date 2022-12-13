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
      if (millis() - ControlTick >= 1000)
        ControlState = STATE_TEST;
      break;

    case STATE_TEST:  
            
      ControlTick = millis();
      break;
  }
}
