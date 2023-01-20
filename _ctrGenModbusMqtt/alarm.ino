
/////////////////////////
// ALARM state machine //
/////////////////////////
void _ALARMSetup()
{
  int i;

  for (i = 0; i < AL_ARRAY_SIZE; i++)
   alarm[i] = 0;

  alSecond = 0;
  alState = STATE_AL_LOOP;
}

/////////////////////////
// ALARM state machine //
/////////////////////////
void _ALARMLoop()
{
  int i, balarm;
        
  switch (alState)
  {
    case STATE_AL_LOOP:
    case STATE_AL_ON:

      // Presscaler
      alSecond++;
      if (alSecond < AL_SEC_LOOP)
        break;

      alSecond = 0;

     #if (_ALARM_SERIAL_DEBUG_ == 1)
     Serial.println("Alarm Check !!!!");
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
      {
        // Came from alarm on
        if (alState == STATE_AL_ON)
          alState = STATE_AL_OFF_NOTIFY;  // Notify alarms off
      }

      // Have to notify??
      if (alNotify > AL_NOTIFY_CONT);
      {
        if (alState == STATE_AL_LOOP)
        {
          alState = STATE_AL_ON_NOTIFY;  // Notify alarm on
          
          #if (_ALARM_SERIAL_DEBUG_ == 1)
          Serial.println("!!!!!!!!!!!!!!!!");
          Serial.println("MQTT Alarm notify");
          Serial.println("!!!!!!!!!!!!!!!!");
          #endif
        }
        else
          // Can't notify...
          alNotify = 0;  // Reset alarm notification.
      }
 
      break;

    case STATE_AL_ON_NOTIFY:
    case STATE_AL_OFF_NOTIFY:
      // MQTT
      mqttPayload = 3;  // Notify alarm

      alSecond = 0;
      alNotify = 0;
      
      if (alState == STATE_AL_ON_NOTIFY)
        alState = STATE_AL_ON;    // Under alarm
      else
        alState = STATE_AL_LOOP;  // No alarm

      break;   
  }

   
}
