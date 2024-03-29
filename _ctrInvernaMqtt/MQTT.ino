#include "MQTT.h"

void mqttDataCallback(char* rtopic, byte* rpayload, unsigned int rlength)
{
  String rtopicStr((char*)rtopic);
  String rpayloadStr((char*)rpayload);
  rpayloadStr[rlength] = 0;
    
  #if (_MQTT_SERIAL_DEBUG_ == 1)
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.print (" Topic :");    Serial.println (rtopic);
  Serial.print (" Payload :");  Serial.println (rpayloadStr);
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  #endif

  // FAN
  if (rtopicStr.equals(TOPIC_FANCTR))
  {
    if(rpayloadStr.equals("1"))
    {
      if ((cfgFanTempHi == 0) && (cfgFanTempLo == 0))
      {
        if (FanState == STATE_STANDBY)
          FanState = STATE_OUT_ON;

        #if (_MQTT_SERIAL_DEBUG_ == 1)
        Serial.println("TOPIC_FANCTR ->> 1");
        #endif
      }
      else
      {
        #if (_MQTT_SERIAL_DEBUG_ == 1)
        Serial.println("NOT POSSIBLE");
        #endif
      }
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_FANCTR ->> Error");
      #endif
    }
  }
  else if (rtopicStr.equals(TOPIC_FANSTBY))
  {
    if ((cfgFanTempHi == 0) && (cfgFanTempLo == 0))
    {
      if(rpayloadStr.equals("1"))
      {
        FanState = STATE_STANDBY;
    
        #if (_MQTT_SERIAL_DEBUG_ == 1)
        Serial.println("TOPIC_FANSTBY ->> 1");
        #endif
      }
       else
      {
        #if (_MQTT_SERIAL_DEBUG_ == 1)
        Serial.println("TOPIC_FANCTR ->> Error");
        #endif
      }   
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_FANSTBY ->> Error");
      #endif
    }
  }
  // PUMP
  else if (rtopicStr.equals(TOPIC_PUMPCTR))
  {
    if(rpayloadStr.equals("1"))
    {
      if (PumpState == STATE_STANDBY)
        PumpState = STATE_OUT_ON;

      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_PUMPCTR ->> 1");
      #endif
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_PUMPCTR ->> Error");
      #endif
    }
  }
  else if (rtopicStr.equals(TOPIC_PUMPSTBY))
  {
    if(rpayloadStr.equals("1"))
    {
      PumpState = STATE_STANDBY;
    
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_PUMPSTBY ->> 1");
      #endif
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_PUMPSTBY ->> Error");
      #endif
    }
  }
  // IRRI
  else if (rtopicStr.equals(TOPIC_IRRICTR))
  {
    if(rpayloadStr.equals("1"))
    {
      if (IrriState == STATE_STANDBY)
        IrriState = STATE_OUT_ON;

      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_IRRICTR ->> 1");
      #endif
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_IRRICTR ->> Error");
      #endif
    }
  }
  else if (rtopicStr.equals(TOPIC_IRRISTBY))
  {
    if(rpayloadStr.equals("1"))
    {
      IrriState = STATE_STANDBY;
    
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_IRRISTBY ->> 1");
      #endif
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_IRRISTBY ->> Error");
      #endif
    }
  }
  
  // Open
  else if (rtopicStr.equals(TOPIC_OPCTR))
  {
    if(rpayloadStr.equals("1"))
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_OPCTR ->> 1");
      #endif

      // Solo si NO estamos abriendo...
      if (windowState != STATE_WOPENING)
      {
        #if (_PULS_SERIAL_DEBUG_ == 1)
        Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> Opening");
        #endif
        windowState = STATE_WOPENING;
      }
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_OPCTR ->> Error");
      #endif
    }
  }
  // Close
  else if (rtopicStr.equals(TOPIC_CLCTR))
  {
    if(rpayloadStr.equals("1"))
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_CLCTR ->> 1");
      #endif
      
      // Solo si NO estamos cerrando...
      if (windowState != STATE_WCLOSING)
      {
        #if (_PULS_SERIAL_DEBUG_ == 1)
        Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> Closing");
        # endif
        windowState = STATE_WCLOSING;
      }
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_CLCTR ->> Error");
      #endif
    }
  }

  // Restore
  else if (rtopicStr.equals(TOPIC_RESTORE))
  {
    if(rpayloadStr.equals("1"))
    {
      _ResetEEPROM();
      
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_RESTORE ->> 1");
      #endif
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_RESTORE ->> Error");
      #endif
    }
  }
  
  // Watchdog
  else if (rtopicStr.equals(TOPIC_WATCHDOG))
  {
    if(rpayloadStr.equals("1"))
    {
      #if (_USE_WDE_ == 1)
      wdeForceReset = 1;
      #endif
      
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_WATCHDOG ->> 1");
      #endif
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_WATCHDOG ->> Error");
      #endif
    }
  }  
}

boolean mqttPublish(const char* topic, char* payload)
{
  boolean retval = false;
  retval = mqttClient.publish(topic, payload);
  return retval;
}

boolean mqttSubscribe(const char* topicToSubscribe)
{
  boolean retval = false;
  retval = mqttClient.subscribe(topicToSubscribe);
  return retval;
}


///////////////
// MQTT send //
///////////////
void _MQTTSend(void)
{
  char    spayload[200];
  String  str;
  int     str_len;

  str = "{\n";

  str = str + "\"tOn\":\"";
  str = str + String(timeDay) + "d " + String(timeHour) + " : " + String(timeMin) + " : " + String(timeSec);
  str = str + "\",\n";

  // mRAM
  str = str + "\"mR\":";
  str = str + String(freeRam);
  str = str + ",\n";

  // NTC Analog
  str = str + "\"ntc\":";
  str = str + String(NtcIn);
  str = str + ",\n";
  /*
  // NTC ADC
  str = str + "\"adc\":";
  str = str + String(NtcInADC);
  str = str + ",\n";
  */
  // Control
  if (ControlState == STATE_TEMPHI)
  {
    if (openLoopState == OPEN_WINDOW)
      str = str + "\"ctr\":\"Abriendo\"";
    else
      str = str + "\"ctr\":\"Espera Apertura\"";
  }
  else if (ControlState == STATE_TEMPLO)
  {
    if (closeLoopState == CLOSE_WINDOW)
      str = str + "\"ctr\":\"Cerrando\"";
    else
      str = str + "\"ctr\":\"Espera Cierre\"";
  }
  else
    str = str + "\"ctr\":\"Standby\"";
  str = str + ",\n";

  // Control timer
  if (ControlState == STATE_TEMPHI)
    str = str + "\"tm\":" + String((millis() - openLoopTick)/1000);
  else if (ControlState == STATE_TEMPLO)
    str = str + "\"tm\":" + String((millis() - closeLoopTick)/1000);
  else
    str = str + "\"tm\":0";
  str = str + ",\n";

  // Window timer
  if (windowState == STATE_WCLOSING)
    str = str + "\"wt\":" + String( ((cfgTimeCloseMin*60000) - (millis() - windowControlTick))/1000 );
  else if (windowState == STATE_WOPENING)
    str = str + "\"wt\":" + String( ((cfgTimeOpenMin*60000) - (millis() - windowControlTick))/1000 );
  else
    str = str + "\"wt\":0";
  str = str + ",\n";
  
  // FC WClose
  if (InWClose == IOW_OFF /*IO_OFF*/)
    str = str + "\"fcC\":0";
  else
    str = str + "\"fcC\":1";
  str = str + ",\n";
  
  // FC WOpen
  if (InWOpen == IOW_OFF /*IO_OFF*/)
    str = str + "\"fcO\":0";
  else
    str = str + "\"fcO\":1";
  str = str + ",\n";

  // In puslador Open
  if (InOpen == IO_OFF)
    str = str + "\"iO\":0";
  else
    str = str + "\"iO\":1";
  str = str + ",\n";

  // In puslador Close
  if (InClose == IO_OFF)
    str = str + "\"iC\":0";
  else
    str = str + "\"iC\":1";
  str = str + ",\n";

  // Out Close
  if (OutClose == OUT_OFF)
    str = str + "\"oC\":0";
  else
    str = str + "\"oC\":1";
  str = str + ",\n";

  // Out Open
  if (OutOpen == OUT_OFF)
    str = str + "\"oO\":0";
  else
    str = str + "\"oO\":1";
  str = str + ",\n";

  // fanState
  if (FanState == STATE_STANDBY)
    str = str + "\"fa\":0";
  else
    str = str + "\"fa\":1";
  str = str + ",\n";

  // pumpState
  if (PumpState == STATE_STANDBY)
    str = str + "\"bo\":0";
  else
    str = str + "\"bo\":1";
  str = str + ",\n";

  // irriState
  if (IrriState == STATE_STANDBY)
    str = str + "\"ir\":0";
  else
    str = str + "\"ir\":1";
  str = str + ",\n";

  // ipAdd
  str = str + "\"ipAdd\":\"";
  str = str + String(ipAddress.toString());
  str = str + "\"\n";

  str = str + "}";

  str_len = str.length() + 1;
  str.toCharArray(spayload, str_len);

  if(mqttPublish(TOPIC_STATE, (char*)spayload))
  {
    #if (_MQTT_SERIAL_DEBUG_ == 1)
    Serial.println("TOPIC_STATE publish was succeeded");
    Serial.println(spayload);
    #endif
  }
  else
  {
    #if (_MQTT_SERIAL_DEBUG_ == 1)
    Serial.println("TOPIC_STATE publish was error");
    Serial.println(spayload);
    #endif  
  }
}

/////////////////
// MQTT set up //
/////////////////
void _MQTTSetup(void)
{ 
  String  str = "";
  int     str_len;
   
  //mqttClient.setServer(MQTT_BROKER, MQTT_BROKER_PORT);
  mqttClient.setServer(brokerUrl, brokerPort);
  mqttClient.setCallback(mqttDataCallback);
  
  mqttStatus = MQTT_NOT_CONNECTED;

  /*
  if (DebugVal == 69)
  {
    str = _TOPIC_STATE;
    str_len = str.length() + 1;
    str.toCharArray(topic_state, str_len);

    str = _TOPIC_GENCTR;
    str_len = str.length() + 1;
    str.toCharArray(topic_genctr, str_len);
    
    str = _TOPIC_GENSTOP;
    str_len = str.length() + 1;
    str.toCharArray(topic_genstop, str_len);
    
    str = _TOPIC_LUZCTR;
    str_len = str.length() + 1;
    str.toCharArray(topic_luzctr, str_len);
         
    str = _TOPIC_LUZSTANDBY;
    str_len = str.length() + 1;
    str.toCharArray(topic_luzstandby, str_len);
  }
  else
  {
    str = TOPIC_STATE;
    str_len = str.length() + 1;
    str.toCharArray(topic_state, str_len);

    str = TOPIC_GENCTR;
    str_len = str.length() + 1;
    str.toCharArray(topic_genctr, str_len);
    
    str = TOPIC_GENSTOP;
    str_len = str.length() + 1;
    str.toCharArray(topic_genstop, str_len);
    
    str = TOPIC_LUZCTR;
    str_len = str.length() + 1;
    str.toCharArray(topic_luzctr, str_len);
         
    str = TOPIC_LUZSTANDBY;
    str_len = str.length() + 1;
    str.toCharArray(topic_luzstandby, str_len);
  }
  */
}

////////////////////////
// MQTT state machine //
////////////////////////
void _MQTTLoop(void)
{
 
  switch (mqttStatus)
  {
    case MQTT_NOT_CONNECTED:
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.printf("MQTT Not connected...\n");
      #endif
      
      mqttStatus = MQTT_CONNECTING;
      mqttTick = millis();
      break;
      
    case MQTT_CONNECTING:
      // if NOT conected
      if (!mqttClient.connected())
      {
        if (millis() - mqttTick < MQTT_CONNECTION_TIMEOUT)
          break;
        
        #if (_MQTT_SERIAL_DEBUG_ == 1)
        Serial.printf("Attempting MQTT connection...\n");
        #endif
      
        if (mqttClient.connect(mqttClientId.c_str(), MQTT_USERNAME, MQTT_KEY))
        {
          #if (_MQTT_SERIAL_DEBUG_ == 1)
          Serial.printf("MQTT connected!!!...\n");
          #endif
          
          mqttStatus = MQTT_CONNECTED;
        }
        else
        {
          mqttTick = millis();
          
          #if (_MQTT_SERIAL_DEBUG_ == 1)
          Serial.printf("Error!  : MQTT Connect failed, rc = %d\n", mqttClient.state());
          #endif
        }
      }
      break;
      
    case MQTT_CONNECTED:
      if (mqttClient.connected())
      {
        if (millis() - mqttTick < MQTT_SUBSCRIBE_TIMEOUT)
          break;
        
        mqttTick = millis();
        
        if (// FAN
            mqttSubscribe(TOPIC_FANCTR)    &&
            mqttSubscribe(TOPIC_FANSTBY)   &&
            // PUMP
            mqttSubscribe(TOPIC_PUMPCTR)   &&
            mqttSubscribe(TOPIC_PUMPSTBY)  &&
            // IRRI
            mqttSubscribe(TOPIC_IRRICTR)   &&
            mqttSubscribe(TOPIC_IRRISTBY)  &&
            // Open
            mqttSubscribe(TOPIC_OPCTR)     &&
            // Close
            mqttSubscribe(TOPIC_CLCTR)     &&
            // Restore
            mqttSubscribe(TOPIC_RESTORE)   &&
            // Watchdog
            mqttSubscribe(TOPIC_WATCHDOG))
        {
          mqttStatus = MQTT_SUBSCRIBED;
        }
      }
      else
      {
        #if (_MQTT_SERIAL_DEBUG_ == 1)
        Serial.printf("Error!  : MQTT Connect failed, rc = %d\n", mqttClient.state());
        #endif

        mqttStatus = MQTT_CONNECTING;
        mqttTick = millis();
      }
      break;

    case MQTT_SUBSCRIBED:
      if (mqttClient.connected())
      {
        if (millis() - mqttTick < MQTT_PUBLISH_TIMEOUT)
          break;
        
        mqttTick = millis();
        
        mqttClient.loop();
        _MQTTSend();        
      }
      else
      {
        #if (_MQTT_SERIAL_DEBUG_ == 1)
        Serial.printf("Error!  : MQTT Connect failed, rc = %d\n", mqttClient.state());
        #endif

        mqttStatus = MQTT_CONNECTING;
        mqttTick = millis();
      }      
      break;  
  }
}

//////////////
// MQTT Led //
//////////////
void _MQTTLedLoop()
{
  switch (mqttStatus)
  {
    case MQTT_NOT_CONNECTED:
    case MQTT_CONNECTING:
      if (millis() - wifiLEDTick >= MQTT_BLINK_CONNECTING)
      {
        if (outLed == OUT_ON)
          outLed = OUT_OFF;
        else
          outLed = OUT_ON;

        wifiLEDTick = millis();
      } 
      break;

    case MQTT_CONNECTED:
    case MQTT_SUBSCRIBED:
    
      outLed = IO_ON;
      break;
  }
}
