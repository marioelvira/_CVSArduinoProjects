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

  #if (_USE_NTP_ == 1)
  // NTP Stop
  _mNTPSetup();
  #endif

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

      #if (_USE_NTP_ == 1)
      // NTP loop
      _mNTPloop();
      #endif

      // Check each minute
      #if (_USE_MB_ == 1)
      _mbInsAlarmCheck();
      #endif
    }

    // Gen control
    _GenTimeLoop();

    #if (_USE_NTP_ == 1)
    // NTP fake clock
    _mNTPfakeSec();
    #endif

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

    Serial.println("Solar Data: ");
    Serial.print("Sunrise: "); Serial.print(sunrise_h); Serial.print(":");Serial.println(sunrise_m);
    Serial.print("Sunset:  "); Serial.print(sunset_h);  Serial.print(":");Serial.println(sunset_m);
  
    Serial.print("Free RAM: ");
    Serial.println(freeRam);
    
    Serial.print("Indicador LCD: ");
    Serial.print(DisplayIndicador);
    Serial.println(" ");
    
    Serial.print("Control Status: ");
    Serial.println(ControlState);  

    Serial.print("Alarm Status: ");
    Serial.print(alState); Serial.print(" "); Serial.print(alNotify); Serial.print("-"); Serial.println(AL_NOTIFY_CONT);
    
    Serial.println("Alarms: ");
    Serial.print(alarm[0]); Serial.print(alarm[1]); Serial.print(alarm[2]); Serial.print(alarm[3]);Serial.print(alarm[4]); Serial.print(alarm[5]); Serial.print(alarm[6]); Serial.println(alarm[7]);
    Serial.print(alarm[8]); Serial.print(alarm[9]); Serial.print(alarm[10]); Serial.print(alarm[11]);Serial.print(alarm[12]); Serial.print(alarm[13]); Serial.print(alarm[14]); Serial.println(alarm[15]);
    Serial.print(alarm[16]); Serial.print(alarm[17]); Serial.print(alarm[18]); Serial.print(alarm[19]);Serial.print(alarm[20]); Serial.print(alarm[21]); Serial.print(alarm[22]); Serial.println(alarm[23]);
    
    Serial.print("Gen Status: "); Serial.print(genMinOn); Serial.print("m "); Serial.print(genTimeDay); Serial.print("d "); Serial.println(genTimeOnString);
    
    #if (_USE_MQTT_ == 1)
    Serial.print("MQTT Status: ");
    Serial.print(mqttStatus); Serial.print(" - pl ");Serial.println(mqttPayload);
    #endif

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
