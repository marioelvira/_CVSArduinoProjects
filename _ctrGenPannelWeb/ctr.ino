
////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  //controlMode = MODE_AUTO;
  ControlState = STATE_GEN_ON;
  ControlTick = 0;
  TimeControlSec = TimeGenerador1P*60;
  DisplayIndicador = 1;
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{

  switch (ControlState)
  {
    case STATE_GEN_ON:
      OutGen = OUT_ON;
      OutZumb = OUT_OFF;
      OutDisp = OUT_ON;
       
      if (TimeControlSec <= TimeBuzzerOn) // TIMER_GEN_END_SEC
        ControlState = STATE_GEN_ON2OFF;

      ControlTick = millis();
      break;

    case STATE_GEN_ON2OFF:
      OutGen = OUT_ON;

      if (millis() - ControlTick >= CTR_BUZZER_TICK)
      {
        if (OutZumb == OUT_ON)
          OutZumb = OUT_OFF;
        else
          OutZumb = OUT_ON;

        if (OutDisp == OUT_ON)
          OutDisp = OUT_OFF;
        else
          OutDisp = OUT_ON;

        ControlTick = millis();
      } 

      if (TimeControlSec <= 0)
        ControlState = STATE_GEN_OFF;
    
      break;
   
    case STATE_GEN_OFF:
      OutGen = OUT_OFF;
      OutZumb = OUT_OFF;
      OutDisp = OUT_OFF;

      TimeControlSec = 0;
      ControlTick = millis();
      break;
  }
}
