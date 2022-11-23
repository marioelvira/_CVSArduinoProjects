
void _LEDTest (void)
{
  if (ledTest == 0)
  {
    boardLed1 = OUT_OFF;
    boardLed2 = OUT_OFF;
    boardLed3 = OUT_OFF;
  }
  else if (ledTest == 1)
  {
    boardLed1 = OUT_ON;
    boardLed2 = OUT_OFF;
    boardLed3 = OUT_OFF;
  }
  else if (ledTest == 2)
  {
    boardLed1 = OUT_OFF;
    boardLed2 = OUT_ON;
    boardLed3 = OUT_OFF;
  }
  else if (ledTest == 3)
  {
    boardLed1 = OUT_ON;
    boardLed2 = OUT_ON;
    boardLed3 = OUT_OFF;
  }
  else if (ledTest == 4)
  {
    boardLed1 = OUT_OFF;
    boardLed2 = OUT_OFF;
    boardLed3 = OUT_ON;
  }
  else if (ledTest == 5)
  {
    boardLed1 = OUT_ON;
    boardLed2 = OUT_OFF;
    boardLed3 = OUT_ON;
  }
  else if (ledTest == 6)
  {
    boardLed1 = OUT_ON;
    boardLed2 = OUT_ON;
    boardLed3 = OUT_OFF;
  }
  else if (ledTest == 7)
  {
    boardLed1 = OUT_ON;
    boardLed2 = OUT_ON;
    boardLed3 = OUT_ON;
  }
  
  ledTest++;
  if (ledTest > 7)
   ledTest = 0;
}
