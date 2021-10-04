
//////////////////////
// IO state machine //
//////////////////////
void _IOSetup(void)
{
  inState = IN_STATUS_OFF;
  
  outRele = OUT_OFF;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop(void)
{
  switch (inState)
  {
	  case IN_STATUS_OFF:

      //_TimeSetup();
      inTimeoutTick = millis();

      countDownSec = cfgTimeoutSec;
      
      // Relé a Off
      outRele = OUT_OFF;
            
      if (inValue == IN_ON)
        inState = IN_STATUS_ON;
      
      break;
    
    case IN_STATUS_ON:

      // Relé a On
      outRele = OUT_ON;
    
      if (millis() - inTimeoutTick >= (cfgTimeoutSec*1000))
        inState = IN_STATUS_OFF;
     
      break;

  }
}
