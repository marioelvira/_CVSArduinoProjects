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
    if (TimeControlSec != 0)
      TimeControlSec--;
    
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
      
      // Gen control
      _GenMinLoop();

      // NTP loop
      _mNTPloop();
    }

    // Gen control
    _GenTimeLoop();

    // NTP fake clock
    _mNTPfakeSec();
      
    _timeOnString();
    timeTick = millis();

    _ADCLoop();

    _FreeRAM();

    _ALARMLoop();

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
    
    Serial.print("Indicador LCD: ");
    Serial.print(DisplayIndicador);
    Serial.println(" ");
    
    Serial.print("Control Status: ");
    Serial.println(ControlState);  

    Serial.print("Alarm: ");
    Serial.print("0x"); 
    Serial.print(alarm[0]); Serial.print(alarm[1]); Serial.print(alarm[2]); Serial.print(alarm[3]);
    Serial.print(alarm[4]); Serial.print(alarm[5]); Serial.print(alarm[6]); Serial.print(alarm[7]);
    Serial.println(" ");
    
    Serial.print("Gen Status: ");
    Serial.print(genMinOn); Serial.println("m ");
    Serial.print(genTimeDay); Serial.print("d "); Serial.print(genTimeOnString);
    Serial.println(" ");
 
    Serial.print("Wi-Fi Status: ");
    Serial.println(wifiStatus);

    Serial.print("AdcVal: ");
    Serial.println(AdcIn);
    Serial.print("AdcIn: ");
    Serial.println(AdcVal);    

    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
