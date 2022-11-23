void _genTimeOnString(void)
{
    if (genTimeHour < 10)
      genTimeOnString = "0" + String(genTimeHour);
    else
      genTimeOnString = String(genTimeHour);

    genTimeOnString = genTimeOnString + ":";

    if (genTimeMin < 10)
      genTimeOnString = genTimeOnString + "0" + String(genTimeMin);
    else
      genTimeOnString = genTimeOnString + String(genTimeMin);

    genTimeOnString = genTimeOnString + ":";

    if (genTimeSec < 10)
      genTimeOnString = genTimeOnString + "0" + String(genTimeSec);
    else
      genTimeOnString = genTimeOnString + String(genTimeSec);
}

/////////////////
// Time set up //
/////////////////
void _GenTimeReset(void)
{
  genTimeSec = 0;
  genTimeMin = 0;
  genTimeHour = 0;
  genTimeDay = 0;

  //genMinOn = 0;
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
  
  _genTimeOnString();
}

void _GenMinLoop(void)
{
  if (InGen == IO_ON)
    genMinOn++;
}
