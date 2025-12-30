#include "main.h"

#if (_USE_MQTT_ == 1)

#include "MQTT.h"

void mqttDataCallback(char* rtopic, byte* rpayload, unsigned int rlength)
{
  String rtopicStr((char*)rtopic);
  String rpayloadStr((char*)rpayload);
  
  rpayloadStr[rlength] = 0;
      
  #if (_MQTT_SERIAL_DEBUG_ == 1)
  Serial.println("$$$$$$$$$$$$$$$$ RX $$$$$$$$$$$$$$$$$$$$$");
  Serial.print (" Topic :");    Serial.println (rtopic);
  Serial.print (" Payload :");  Serial.println (rpayloadStr);
  Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  #endif

  // Outs
  if (rtopicStr.equals(TOPIC_RON) ||
      rtopicStr.equals(TOPIC_ROFF))
  {
	/*
    // Value
    if (rtopicStr.equals(TOPIC_RON))
      outVal = OUT_ON;
    else
      outVal = OUT_OFF;

    if (rpayloadStr.equals("0"))
      OutDig[0] = 1;
    else if (rpayloadStr.equals("1"))
      OutDig[1] = 1;
    else if (rpayloadStr.equals("2"))
      OutDig[2] = 1;
    else if (rpayloadStr.equals("3"))
      OutDig[3] = 1;
    else if (rpayloadStr.equals("4"))
      OutDig[4] = 1;
    else if (rpayloadStr.equals("5"))
      OutDig[5] = 1;
  */
  }
  // Watchdog
  else if (rtopicStr.equals(TOPIC_RWD))
  {
    if(rpayloadStr.equals("1"))
    {
      #if (_USE_WDE_ == 1)
      wdeForceReset = 1;
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
void _MQTTSend(int itopic)
{
  char    stopic[50];
  char    spayload[255];  // If more message not sent
  String  str;
  int     str_len;
  int     i;

  str = "{\n";
  
  ////////////////
  // TOPIC_RCTR //
  ////////////////
  if (itopic == 0)
  {
    str = str + "\"ctr\":\"";
    str = str + "Calef";
    str = str + "\",\n";

    #if (_USE_NTP_ == 1)
    str = str + "\"time\":\"";
    str = str + mntpTimeString;
    str = str + "\",\n";
    #endif

    str = str + "\"t\":\"";
    str = str + String(timeDay) + "d " + timeOnString;
    str = str + "\",\n";  

    str = str + "\"ctr\":\"";
    str = str + ctrStateString;
    str = str + "\",\n";

    str = str + "\"ip\":\"";
    str = str + String(ipAddress[3]); str = str + ".";
    str = str + String(ipAddress[2]); str = str + ".";
    str = str + String(ipAddress[1]); str = str + ".";
    str = str + String(ipAddress[0]);
    str = str + "\",\n";
  }
  ////////////////
  // TOPIC_RIOS //
  ////////////////
  else if (itopic == 1)
  {
    /*
    /////////
    // ADC //
    /////////
    str = str + "\"i0\":\"";
    str = str + Ival[0];
    str = str + "\",\n";
    
    str = str + "\"i1\":\"";
    str = str + Ival[1];
    str = str + "\",\n";

    str = str + "\"v0\":\"";
    str = str + Vval[0];
    str = str + "\",\n";
    
    str = str + "\"v1\":\"";
    str = str + Vval[1];
    str = str + "\",\n";

    str = str + "\"v2\":\"";
    str = str + Vval[2];
    str = str + "\",\n";
    
    str = str + "\"v3\":\"";
    str = str + Vval[3];
    str = str + "\",\n";

    str = str + "\"v4\":\"";
    str = str + Vval[4];
    str = str + "\",\n";
    
    str = str + "\"v5\":\"";
    str = str + Vval[5];
    str = str + "\",\n";
    */
    /////////
    // IOs //
    /////////
    str = str + "\"bO\":\"";
    for (i = 0; i < OUT_NUMBER; i++)
      str = str + String(OutDig[i]);
    str = str + "\",\n";

    str = str + "\"bI\":\"";
    for (i = 0; i < IN_NUMBER; i++)
      str = str + String(InDig[i]);
    str = str + "\",\n";
  }

  str_len = str.length();
  str = str + "\"len\":";
  str = str + String(str_len + 12);
  str = str + "\n";

  str = str + "}";

  str_len = str.length() + 1;
  str.toCharArray(spayload, str_len);

  if (itopic == 1)
    str = TOPIC_RIOS;
  else
    str = TOPIC_RCTR;
  
  str_len = str.length() + 1;
  str.toCharArray(stopic, str_len);

  if(mqttPublish((char*)stopic, (char*)spayload))
  {
    #if (_MQTT_SERIAL_DEBUG_ == 1)
    Serial.println("TOPIC_STATE publish was succeeded");
    Serial.println("$$$$$$$$$$$$$$$$ RX $$$$$$$$$$$$$$$$$$$$$");
    Serial.println(stopic);
    Serial.println(spayload);
    Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
    #endif
  } 
}

/////////////////
// MQTT set up //
/////////////////
void _MQTTSetup(void)
{ 
  String rIdStr((char*)compdate);

  mqttClient.setServer(MQTT_BROKER, MQTT_BROKER_PORT);
  
  mqttClient.setCallback(mqttDataCallback);

  mqttClientId = "caleMQTT-" + UniqueIdStr;
  #if (_MQTT_SERIAL_DEBUG_ == 1)
  Serial.print("MQTT Client ID: "); Serial.println(mqttClientId);
  #endif

  mqttStatus = MQTT_NOT_CONNECTED;
  mqttTopic = 0;
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
      Serial.println("MQTT Not connected...");
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
        Serial.println("Attempting MQTT connection...");
        #endif
      
        mqttTick = millis();
        if (mqttClient.connect(mqttClientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD))
        {
          #if (_MQTT_SERIAL_DEBUG_ == 1)
          Serial.println("MQTT connected!!!...");
          #endif
          
          mqttStatus = MQTT_CONNECTED;
        }
        else
        {        
          #if (_MQTT_SERIAL_DEBUG_ == 1)
          Serial.print("Error!  : MQTT Connect failed, rc = ");
          Serial.print(mqttClient.state());
          Serial.print(" timeout ");
          Serial.println((millis() - mqttTick)/ 1000); 
          #endif
          
          mqttTick = millis();
        }
      }
      break;
      
    case MQTT_CONNECTED:
      if (mqttClient.connected())
      {
        if (millis() - mqttTick < MQTT_SUBSCRIBE_TIMEOUT)
          break;
        
        mqttTick = millis();
        
        if (mqttSubscribe(TOPIC_RON)       &&
            mqttSubscribe(TOPIC_ROFF)      &&
            
            mqttSubscribe(TOPIC_RWD))
        {
          mqttStatus = MQTT_SUBSCRIBED;
        }
      }
      else
      {
        #if (_MQTT_SERIAL_DEBUG_ == 1)
        Serial.print("Error!  : MQTT Connect failed, rc = ");
        Serial.println(mqttClient.state());
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
        _MQTTSend(mqttTopic);
        
		    mqttTopic++;
		    if (mqttTopic > MQTT_NUM_TOPICS)
		      mqttTopic = 0;

      }
      else
      {
        #if (_MQTT_SERIAL_DEBUG_ == 1)
        Serial.print("Error!  : MQTT Connect failed, rc = ");
        Serial.println(mqttClient.state());
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
/*
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
*/

#endif // (_USE_MQTT_ == 1)