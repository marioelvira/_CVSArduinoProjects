
//////////////////////
// IO state machine //
//////////////////////
void _IOSetup(int i)
{
  inState[i] = IN_STATUS_INIT;
  outValue[i] = OUT_OFF;
  outAlarm[i] = OUT_OFF;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop(int i)
{
  switch (inState[i])
  {
	  case IN_STATUS_INIT:
      inTimeTick[i] = millis();
      if (inValue[i] == IN_ON)
        inState[i] = IN_STATUS_ON;
      else
        inState[i] = IN_STATUS_OFF;

      break;
      
	  case IN_STATUS_ON:
      if (inValue[i] == IN_OFF)
      {
        inState[i] = IN_STATUS_INIT;
        outValue[i] = OUT_OFF;
        outAlarm[i] = OUT_OFF;
      }
      else
      {
        if (millis() - inTimeTick[i] >= (inTimeoutSec[i]*1000))
        {
          // Rele de corte
          outValue[i] = OUT_ON;

          // Indicar Alarma
          outAlarm[i] = OUT_ON;
        }
      }
      break;
      
	  case IN_STATUS_OFF:

      outValue[i] = OUT_OFF;
      outAlarm[i] = OUT_OFF;
   
      inTimeTick[i] = millis();
      if (inValue[i] == IN_ON)
        inState[i] = IN_STATUS_ON;

	    break;
  }
}

void _OUTSLoop (void)
{
  int i;

  outReleCorte = OUT_OFF;
  outAlarma = OUT_OFF;
  
  for (i = 0; i < 4; i++)
  {
    if (outValue[i] == OUT_ON)
      outReleCorte |= OUT_ON;

    if (outAlarm[i] == OUT_ON)
      outAlarma |= OUT_ON;
  }
}
