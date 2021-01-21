
//////////////////////
// IO state machine //
//////////////////////
void _IOSetup(void)
{
  inState = IN_STATUS_INIT;
  
  outReleCorte = OUT_OFF;
  outLedInd = OUT_OFF;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop(void)
{
  switch (inState)
  {
	  case IN_STATUS_INIT:
      inTimeTick = millis();
      if (inValue == IN_ON)
        inState = IN_STATUS_ON;
      else
        inState = IN_STATUS_OFF;

      break;
      
	  case IN_STATUS_ON:
      if (inValue == IN_OFF)
      {
        inState = IN_STATUS_INIT;
        outReleCorte = OUT_OFF;
        outLedInd = OUT_OFF;
      }
      else
      {
        if (millis() - inTimeTick >= (inTimeoutSec*1000))
        {
          // Rele de corte
          outReleCorte = OUT_ON;

          // Indicar Led
          outLedInd = OUT_ON;
        }
      }
      break;
      
	  case IN_STATUS_OFF:

      outReleCorte = OUT_OFF;
      outLedInd = OUT_OFF;
   
      inTimeTick = millis();
      if (inValue == IN_ON)
        inState = IN_STATUS_ON;

      _TimeSetup();

	    break;
  }
}
