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
  timeDay = 0;
  
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
	  timeTickSec++;	// Forever
	
    timeSec++;
    if (timeSec >= 60)
    {
      timeSec = 0;
      timeMin++;
      if (timeMin >= 60)
      {
        timeMin = 0;
        timeHour++;
        if (timeHour >= 24)
        {
          timeHour = 0;
          timeDay++;
        }
      }
      
      // Check each minute
      #if (_USE_MB_ == 1)
      _mbInsAlarmCheck();
      #endif
    }
      
    _timeOnString();
    timeTick = millis();

    _ADCsLoop();
    _INTISRsLoop();

    #if (_USE_FREERAM_ == 1)
    _FreeRAM();
    #endif

    #if (_USE_WDE_ == 1)
    _WDELoop();
    #endif
    
    #if (_STATUS_SERIAL_DEBUG_ == 1)
    
    Serial.println("<><><><><><><>");
    Serial.print("Tiempo Encendio: ");
    Serial.print(timeDay); Serial.print("d "); Serial.print(timeOnString);
    Serial.println(" ");

    #if (_USE_FREERAM_ == 1)
    Serial.print("Free RAM: ");
    Serial.println(freeRam);
    #endif

    Serial.print("Wi-Fi Status: ");
    Serial.println(wifiStatus);

    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
