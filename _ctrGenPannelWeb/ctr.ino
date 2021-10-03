
////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ControlState = STATE_START;
  ControlTick = millis();
  
  TimeControlSec = TimeGenerador1P*X_60;
  DisplayIndicador = 1;

  // Control
  OutAutoOn = OUT_ON;
  OutBomba = OUT_ON;
  OutGen = OUT_OFF;
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{

  switch (ControlState)
  {
    case STATE_START:
      // Control
      OutAutoOn = OUT_ON;
      OutBomba = OUT_OFF;
      OutGen = OUT_OFF;
      
      // Indicadores
      OutDisp = OUT_ON;
      OutZumb = OUT_OFF;

      if (millis() - ControlTick >= (TimeOutStart*1000))
        ControlState = STATE_GEN_ON;
      break;

    case STATE_GEN_ON:
      // Control
      OutAutoOn = OUT_ON;
      OutBomba = OUT_ON;
      OutGen = OUT_ON;
      
      // Indicadores
      OutDisp = OUT_ON;
      OutZumb = OUT_OFF;
             
      if (TimeControlSec <= TimeBuzzerOn)
        ControlState = STATE_GEN_ZUMB;

      ControlTick = millis();
      break;

    case STATE_GEN_ZUMB:
      // Control
      OutAutoOn = OUT_ON;
      OutBomba = OUT_ON;
      OutGen = OUT_ON;

      // Indicadores
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
      // Control
      OutAutoOn = OUT_ON;
      
      OutBomba = OUT_ON;
      OutGen = OUT_OFF;

      // Indicadores
      OutZumb = OUT_OFF;
      OutDisp = OUT_OFF;

      TimeControlSec = 0;

      if (millis() - ControlTick >= (TimeOutStop*1000))
        ControlState = STATE_AUTO_OFF;

      break;

    case STATE_AUTO_OFF:
      // Control
      OutAutoOn = OUT_OFF;
      
      OutBomba = OUT_OFF;
      OutGen = OUT_OFF;

      // Indicadores
      OutZumb = OUT_OFF;
      OutDisp = OUT_OFF;
    
      TimeControlSec = 0;
      ControlTick = millis();
      break;
  }
}
