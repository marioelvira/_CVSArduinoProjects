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

  // NTP Stop
  _mNTPSetup();
  
  // RAM setup
  _RAMSetup();
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
      
      // NTP loop
      _mNTPloop();

      // Check each minute
      #if (_USE_MB_ == 1)
      _mbInsAlarmCheck();
      #endif
    }

    // NTP fake clock
    _mNTPfakeSec();
      
    _timeOnString();
    timeTick = millis();

    _FreeRAM();

    #if (_USE_WDE_ == 1)
    _WDELoop();
    #endif
    
    #if (_STATUS_SERIAL_DEBUG_ == 1)
    
    Serial.println("<><><><><><><>");
    Serial.print("Tiempo Encendio: ");
    Serial.print(timeDay); Serial.print("d "); Serial.print(timeOnString);
    Serial.println(" ");

    Serial.print("Tiempo NTP: ");
    Serial.print(mntpTimeString);
    Serial.println(" ");

    Serial.print("Free RAM: ");
    Serial.println(freeRam);

    Serial.print("MQTT Status: ");
    Serial.print(mqttStatus); Serial.print(" - pl ");Serial.println(mqttTopic);
 
    Serial.print("Wi-Fi Status: ");
    Serial.println(wifiStatus);

    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
