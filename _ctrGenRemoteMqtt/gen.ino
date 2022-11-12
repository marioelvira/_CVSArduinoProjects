
/////////////////
// Time set up //
/////////////////
void _GenTimeReset(void)
{
  genTimeSec = 0;
  genTimeMin = 0;
  genTimeHour = 0;
  genTimeDay = 0;
}

////////////////////////
// Time state machine //
////////////////////////
void _GenTimeLoop(void)
{
	genTimeSec++;
  if (genTimeSec >= 60)
  {
    genTimeSec = 0;
    genTimeMin++;
    if (genTimeMin >= 60)
    {
      genTimeMin = 0;
      genTimeHour++;
      if (genTimeHour >= 24)
      {
        genTimeHour = 0;
        genTimeDay++;
      }
    }
  }
  //gentimeMinOn++;
}

void _GenMinLoop(void)
{
  if (genState == STATE_GEN_ON)
    gentimeMinOn++;
}

void _GenLoop(void)
{
  // Gen State
  if (cfgGenOnPin == 1)
  {
    if (InGenOn == IO_OFF)
      genInStatus = 0;
    else
      genInStatus = 1;
  }
  else
  {
    if (DisplayIndicador == 0)
      genInStatus = 0;
    else
      genInStatus = 1;
  }

  if (genState != STATE_GEN_OFF)
    _GenTimeReset();

  switch (genState)
  {
    case STATE_GEN_OFF:
      remAct = 0;
      if (genInStatus == 1)
      {
        if (remPulse == 1)
          remAct = 1;
        else
          remAct = 0;

        genTick = millis();
        genState = STATE_GEN_OFF2ON;
        remPulse = 0; //BUG
      }
      break;

    case STATE_GEN_OFF2ON:
      gentimeMinOn = 0;
      if (millis() - genTick >= 500)
        genState = STATE_GEN_ON;
 
      break;

    case STATE_GEN_ON:
      if (genInStatus == 0)
      {
        remPulse = 0; //BUG
        genTick = millis();
        genState = STATE_GEN_ON2OFF;
      }
      break;

    case STATE_GEN_ON2OFF:
      if (millis() - genTick >= 500)
        genState = STATE_GEN_OFF;
      break;
  }
}
