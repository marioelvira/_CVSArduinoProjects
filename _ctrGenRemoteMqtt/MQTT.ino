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

  if(rtopicStr.equals(TOPIC_GENCTR))
  {
    Serial.print(" ");
    if(rpayloadStr.equals("1"))
    {
      if (ControlState == STATE_STANDBY)
        ControlState = STATE_GEN_PULSE;
    
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_GENCTR ->> 1");
      #endif
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_GENCTR ->> Error");
      #endif
    }
  }
  else if(rtopicStr.equals(TOPIC_GENSTOP))
  {
    Serial.print(" ");
    if(rpayloadStr.equals("1"))
    {
      if (ControlState == STATE_STANDBY)
        ControlState = STATE_STOP_PULSE;

      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_GENSTOP ->> 1");
      #endif
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_GENSTOP ->> Error");
      #endif
    }
  }
  else if (rtopicStr.equals(TOPIC_LUZCTR))
  {
    if(rpayloadStr.equals("1"))
    {
      if (LuzState == STATE_STANDBY)
        LuzState = STATE_LUZ_OFF;

      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_LUZCTR ->> 1");
      #endif
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_LUZCTR ->> Error");
      #endif
    }
  }
  else if (rtopicStr.equals(TOPIC_LUZSTANBY))
  {
    if(rpayloadStr.equals("1"))
    {
      LuzState = STATE_STANDBY;
    
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_LUZSTANBY ->> 1");
      #endif
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_LUZSTANBY ->> Error");
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
  char    spayload[10];
  String  str;
  int     str_len;

  if (mqttTopic2send == 1)
  {    
    str = String(VbattIn);
    str_len = str.length() + 1;
    str.toCharArray(spayload, str_len);
        
    if(mqttPublish(TOPIC_VBATT, (char*)spayload))
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_VBATT publish was succeeded");
      Serial.println(spayload);
      #endif
    }

  } else if (mqttTopic2send == 2) {
    
    str = String(DisplayIndicador);
    str_len = str.length() + 1;
    str.toCharArray(spayload, str_len);

    if(mqttPublish(TOPIC_GENDISP, (char*)spayload))
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_GENDISP publish was succeeded");
      Serial.println(spayload);
      #endif
    }

  } else if (mqttTopic2send == 3) {

    if (DisplayIndicador == 0)
      str = String(0);
    else
      str = String(1);
      
    str_len = str.length() + 1;
    str.toCharArray(spayload, str_len);

    if(mqttPublish(TOPIC_GENSTATE, (char*)spayload))
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_GENSTATE publish was succeeded");
      Serial.println(spayload);
      #endif
    }

  } else if (mqttTopic2send == 4) {

    if (LuzState == STATE_STANDBY)
      str = String(0);
    else
      str = String(1);

    str_len = str.length() + 1;
    str.toCharArray(spayload, str_len);

    if(mqttPublish(TOPIC_LUZSTATE, (char*)spayload))
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_LUZSTATE publish was succeeded");
      Serial.println(spayload);
      #endif
    }
  }

  // Next topic
  mqttTopic2send ++;
  if (mqttTopic2send > 4)
    mqttTopic2send = 1;
}

/////////////////
// MQTT set up //
/////////////////
void _MQTTSetup(void)
{
  mqttClient.setServer(MQTT_BROKER, MQTT_BROKER_PORT);
  mqttClient.setCallback(mqttDataCallback);
  
  mqttStatus = MQTT_NOT_CONNECTED;
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
        
        if (mqttSubscribe(TOPIC_GENCTR)  &&
            mqttSubscribe(TOPIC_GENSTOP) &&
            mqttSubscribe(TOPIC_LUZCTR)  &&
            mqttSubscribe(TOPIC_LUZSTANBY))
        {
          mqttStatus = MQTT_SUBSCRIBED;
          mqttTopic2send = 1;
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
