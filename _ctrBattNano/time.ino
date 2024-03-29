
/////////////////
// Time set up //
/////////////////
void _TimeSetup(void)
{
  timeTick = millis();
  timeSec = 0;
  timeMin = 0;
  timeHour = 0;

  ctrDisplaySec = 0;

  #if (_USE_FREERAM_ == 1)
  // RAM setup
  _RAMSetup();
  #endif
}

////////////////////////
// Time state machine //
////////////////////////
void _TimeLoop(void)
{
  if (millis() - timeTick >= 1000)
  {
    if (ctrDisplaySec != 0)
      ctrDisplaySec--;
    
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

    //_ADCsLoop();

    #if (_USE_FREERAM_ == 1)
    _FreeRAM();
    #endif

    #if (_USE_WDE_ == 1)
    _WDELoop();
    #endif

    if (boardLed == OUT_OFF)
      boardLed = OUT_ON;
    else
      boardLed = OUT_OFF;

    #if (_STATUS_SERIAL_DEBUG_ == 1)
    
    int i;
    
    #if (_USE_FREERAM_ == 1)
    Serial.print("Free RAM: ");
    Serial.println(freeRam);
    #endif

    // ADC
    for (i = 0; i< ADC_NUMBER; i++)
    {
      Serial.print("ADC");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(AdcDig[i]);
    }

    // OUTs
    for (i = 0; i< OUT_NUMBER; i++)
    {
      Serial.print("OUT");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(OutDig[i]);
    }

    // INs
    for (i = 0; i< IN_NUMBER; i++)
    {
      Serial.print(" IN");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(InDig[i]);
    }
    
    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
