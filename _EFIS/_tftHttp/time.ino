
void _timeOnString(void)
{
    if (timeHour < 10)
      timeOnString = "0" + String(timeHour);
    else
      timeOnString = String(timeHour);

    timeOnString = timeOnString + ":";

    if (timeMin < 10)
      timeOnString = timeOnString + "0" + String(timeMin);
    else
      timeOnString = timeOnString + String(timeMin);

    timeOnString = timeOnString + ":";

    if (timeSec < 10)
      timeOnString = timeOnString + "0" + String(timeSec);
    else
      timeOnString = timeOnString + String(timeSec);
}

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
    _timeOnString();
        
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

    _FreeRAM();

    _LEDTest();

    #if (_USE_WDE_ == 1)
    _WDELoop();
    #endif
    
    #if (_STATUS_SERIAL_DEBUG_ == 1)
    
    Serial.println("<><><><><><><>");
    Serial.print("Time On: ");
    Serial.println(timeOnString);

    Serial.print("Free RAM: ");
    Serial.println(freeRam);

    Serial.printf("OUT(%d): %d\n", PIN_CN12, boardCN1P2); 
    Serial.printf("IN(%d): %d\n",  PIN_P3P2, boardP3P2);
    Serial.printf("ANA(%d): ",     PIN_P3P3); Serial.println(sAnalog);
    
    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
