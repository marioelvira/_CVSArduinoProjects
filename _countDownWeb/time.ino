
/////////////////
// Time set up //
/////////////////
void _TimeSetup(void)
{
  timeTick = millis();
  timeSec = 0;
  timeMin = 0;
  timeHour = 0;
}

////////////////////////
// Time state machine //
////////////////////////
void _TimeLoop(void)
{
  if (millis() - timeTick >= 1000)
  {
    timeSec++;
    if (timeSec >= 60)
    {
      timeSec = 0;
      timeMin++;
      if (timeMin >= 60)
      {
        timeMin = 0;
        timeHour++;
      }
    }
    
    timeTick = millis();

    // Solo descontamos aqui ...
    if (inState == IN_STATUS_ON)
    {
      countDownSec--;
      if (countDownSec <= 0)
        countDownSec = 0;
    }
    
  }
}
