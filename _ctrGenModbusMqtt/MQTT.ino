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
  else if (rtopicStr.equals(TOPIC_LUZSTANDBY))
  {
    if(rpayloadStr.equals("1"))
    {
      LuzState = STATE_STANDBY;
    
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_LUZSTANDBY ->> 1");
      #endif
    }
    else
    {
      #if (_MQTT_SERIAL_DEBUG_ == 1)
      Serial.println("TOPIC_LUZSTANDBY ->> Error");
      #endif
    }
  }

  else if (rtopicStr.equals(TOPIC_O1ON))
  {
    if(rpayloadStr.equals("1"))
    {
      mbOutNum = 0;
      mbOutVal = MB_OUT_ON;

      if (mbState == MB_STANDBY)
        mbState = MB_WRITEOUT;
    }
  }
  else if (rtopicStr.equals(TOPIC_O1OFF))
  {
    if(rpayloadStr.equals("1"))
    {
      mbOutNum = 0;
      mbOutVal = MB_OUT_OFF;

      if (mbState == MB_STANDBY)
        mbState = MB_WRITEOUT;
    }
  }
  
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
      Serial.println("TOPIC_LUZSTANDBY ->> Error");
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
  str = str + "\"mRAM\":";
  str = str + String(freeRam);
  str = str + ",\n";

  // vBatt
  str = str + "\"vbatt\":";
  str = str + String(VbattIn);
  str = str + ",\n";

  // vBattADC
  str = str + "\"vbattADC\":";
  str = str + String(VbattInADC);
  str = str + ",\n";

  // DispIndicator
  str = str + "\"genDisp\":";
  str = str + String(DisplayIndicador);
  str = str + ",\n";

  // genInState
  if (genInStatus == 0)
    str = str + "\"genState\":0";
  else
    str = str + "\"genState\":1";
  str = str + ",\n";

  // genMinOn
  str = str + "\"genMinOn\":\"";
  str = str + String(genMinOn);
  str = str + "m\",\n";

  // genOff
  str = str + "\"genOff\":\"";
  str = str + String(genTimeDay) + "d " + String(genTimeHour) + " : " + String(genTimeMin) + " : " + String(genTimeSec);
  str = str + "\",\n";
  
  // remote Activation
  if (remAct == 1)
    str = str + "\"rem\":1";
  else
    str = str + "\"rem\":0";
  str = str + ",\n";

  // luzState
  if (LuzState == STATE_STANDBY)
    str = str + "\"luzState\":0";
  else
    str = str + "\"luzState\":1";
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
        
        if (mqttSubscribe(TOPIC_GENCTR)     &&
            mqttSubscribe(TOPIC_GENSTOP)    &&
            mqttSubscribe(TOPIC_LUZCTR)     &&
            mqttSubscribe(TOPIC_LUZSTANDBY) &&
            
            mqttSubscribe(TOPIC_O1ON)       &&
            mqttSubscribe(TOPIC_O1OFF)      &&
            mqttSubscribe(TOPIC_O2ON)       &&
            mqttSubscribe(TOPIC_O3OFF)      &&
            mqttSubscribe(TOPIC_O4ON)       &&
            mqttSubscribe(TOPIC_O4OFF)      &&
            mqttSubscribe(TOPIC_O5ON)       &&
            mqttSubscribe(TOPIC_O5OFF)      &&
            mqttSubscribe(TOPIC_O6ON)       &&
            mqttSubscribe(TOPIC_O6OFF)      &&
            mqttSubscribe(TOPIC_O7ON)       &&
            mqttSubscribe(TOPIC_O7OFF)      &&
            mqttSubscribe(TOPIC_O8ON )      &&
            mqttSubscribe(TOPIC_O8OFF)      &&
            
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
