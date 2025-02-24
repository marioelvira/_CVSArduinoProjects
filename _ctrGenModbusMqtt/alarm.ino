
/////////////////////////
// ALARM state machine //
/////////////////////////
void _ALARMSetup()
{
  int i;

  for (i = 0; i < AL_ARRAY_SIZE; i++)
    alarm[i] = 0;

  alNotify = 0;
  alSecond = 0;
  alState = STATE_AL_OFF;

  #if (_USE_MB_ == 1)
  _mbInsAlarmInit();
  #endif
  
  alarmStr[0] = AL_ERROR0_STR;
  alarmStr[1] = AL_ERROR1_STR;
  alarmStr[2] = AL_ERROR2_STR;
  alarmStr[3] = AL_ERROR3_STR;
  alarmStr[4] = AL_ERROR4_STR;
  alarmStr[5] = AL_ERROR5_STR;
  alarmStr[6] = AL_ERROR6_STR;
  alarmStr[7] = AL_ERROR7_STR;

  alarmStr[8] = AL_ERROR8_STR;
  alarmStr[9] = AL_ERROR9_STR;
  alarmStr[10] = AL_ERROR10_STR;
  alarmStr[11] = AL_ERROR11_STR;
  alarmStr[12] = AL_ERROR12_STR;
  alarmStr[13] = AL_ERROR13_STR;
  alarmStr[14] = AL_ERROR14_STR;
  alarmStr[15] = AL_ERROR15_STR;

  alarmStr[16] = AL_ERROR16_STR;
  alarmStr[17] = AL_ERROR17_STR;
  alarmStr[18] = AL_ERROR18_STR;
  alarmStr[19] = AL_ERROR19_STR;
  alarmStr[20] = AL_ERROR20_STR;
  alarmStr[21] = AL_ERROR21_STR;
  alarmStr[22] = AL_ERROR22_STR;
  alarmStr[23] = AL_ERROR23_STR;
}

/////////////////////////
// ALARM state machine //
/////////////////////////
void _ALARMLoop()
{
  int i, j, balarm;
        
  switch (alState)
  {
	  case STATE_AL_OFF:

      // Presscaler
      alSecond++;
      if (alSecond < AL_SEC_LOOP)
        break;

      alSecond = 0;

      #if (_ALARM_SERIAL_DEBUG_ == 1)
      Serial.println("Alarm OFF: Check !!!!");
      #endif
    
      // Check if any alarm...
      balarm = 0;
      for (i = 0; i < AL_ARRAY_SIZE; i++)
      {
        if (alarm[i] != 0)
          balarm = 1;
      }

      // if alarm...
      if (balarm == 1)
        alNotify++;
      else
		    alNotify = 0;	// Reset alarm
      
      // Have to notify??
      if (alNotify >= AL_NOTIFY_CONT)
      {
        alState = STATE_AL_ON_NOTIFY;  // Notify alarm on

        // Make a Copy
        for (i = 0; i < AL_ARRAY_SIZE; i++)
          alarmCpy[i] = alarm[i];
          
        #if (_ALARM_SERIAL_DEBUG_ == 1)
        Serial.println("!!!!!!!!!!!!!!!!");
        Serial.println("MQTT Alarm ON notify");
        Serial.println("!!!!!!!!!!!!!!!!");
        #endif
      }
 
      break;	  

    case STATE_AL_ON:

      // Presscaler
      alSecond++;
      if (alSecond < AL_SEC_LOOP)
        break;

      alSecond = 0;

      #if (_ALARM_SERIAL_DEBUG_ == 1)
      Serial.println("Alarm ON: Check !!!!");
      #endif

      // Check if NO alarm...
      balarm = 0;
      for (i = 0; i < AL_ARRAY_SIZE; i++)
      {
        if (alarm[i] != 0)
          balarm = 1;
      }

	    // If NO alarm
	    if (balarm == 0)
	    {
		   #if (_ALARM_SERIAL_DEBUG_ == 1)
		   Serial.println("Alarm OFF notify !!!!");
		   #endif
		   alState = STATE_AL_OFF_NOTIFY;  // Notify NO alarm change
		   break;
	    }
	    else
	    {
		    j = 0;
		    // Check if alarm change
		    for (i = 0; i < AL_ARRAY_SIZE; i++)
		    {
			    if (alarmCpy[i] != alarm[i])
			      j = 1;
		    }
		
    		// Alarm change
  		  if (j == 1)
		    {
			    alState = STATE_AL_ON_NOTIFY;  // Notify alarm change

			    // Make a Copy
			    for (i = 0; i < AL_ARRAY_SIZE; i++)
				    alarmCpy[i] = alarm[i];
          
          #if (_ALARM_SERIAL_DEBUG_ == 1)
          Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!");
          Serial.println("MQTT Alarm change notify");
          Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!");
          #endif
		  }
		  // else
		  // alarm stays the same
		
     } 
     break;

    case STATE_AL_ON_NOTIFY:
    case STATE_AL_OFF_NOTIFY:
      // MQTT
      #if (_USE_MQTT_ == 1)
      mqttTopic = MQTT_LAST_TOPIC;  // Notify alarm
      #endif
      alSecond = 0;
      alNotify = 0;
      
      if (alState == STATE_AL_ON_NOTIFY)
        alState = STATE_AL_ON;    // Under alarm
      else
        alState = STATE_AL_OFF;  // No alarm

      break;   
  }   
}
