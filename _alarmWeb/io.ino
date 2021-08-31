
//////////////////////
// IO state machine //
//////////////////////
void _IOSetup(void)
{
  inState = IN_STATUS_STANDBY;
  
  outReleBatt = OUT_OFF;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop(void)
{
  switch (inState)
  {
	  case IN_STATUS_STANDBY:

      _TimeSetup();
      inTimeoutTick = millis();
      
      // Relé Batt a Off
      outReleBatt = OUT_OFF;
            
      if (inValue == IN_ON)
        inState = IN_STATUS_FILTER;
      
      break;

    case IN_STATUS_FILTER:

      // Relé Batt a Off
      outReleBatt = OUT_OFF;

      if (inValue == IN_OFF)
        inState = IN_STATUS_STANDBY;

      if (millis() - inTimeoutTick >= (cfgTimeAntiSec*1000))
        inState = IN_STATUS_TIMEOUT;

      break;

    case IN_STATUS_TIMEOUT:
    
      // Relé Batt a Off
      outReleBatt = OUT_OFF;
    
      if (millis() - inTimeoutTick >= (cfgTimeoutSec*1000))
        inState = IN_STATUS_ON;
     
      break;

	  case IN_STATUS_ON:

      // Relé Batt a On
      outReleBatt = OUT_ON;

      if (inValue == IN_OFF)
        inState = IN_STATUS_STANDBY;
      
      break;            
  }
}
