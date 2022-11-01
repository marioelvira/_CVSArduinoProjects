
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
  //genMinOn++;
}

void _GenMinLoop(void)
{
  if (genState != STATE_GEN_OFF)
    genMinOn++;
}
