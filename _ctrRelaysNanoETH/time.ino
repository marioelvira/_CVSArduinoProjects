
/////////////////
// Time set up //
/////////////////
void _TimeSetup(void)
{
  timeTick = millis();
  timeSecTick = 0;
  timeSec = 0;
  timeMin = 0;
  timeHour = 0;
  
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
    timeSecTick++;
    
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

    #if (_USE_LED_ == 1)
    if (boardLed == OUT_OFF)
      boardLed = OUT_ON;
    else
      boardLed = OUT_OFF;
    #endif

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
      Serial.print("IN");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(InDig[i]);
    }
    
    // I
    for (i = 0; i< I_NUMBER; i++)
    {
      Serial.print("I");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(Ival[i]);
    }

    // V
    for (i = 0; i< V_NUMBER; i++)
    {
      Serial.print("V");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(Vval[i]);
    }

    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
