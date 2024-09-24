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
    int outNum = 0;
    int outVal = 0;
  
    // Value
    if (rtopicStr.equals(TOPIC_RON))
      outVal = OUT_ON;
    else
      outVal = OUT_OFF;

    if(rpayloadStr.equals("1"))
      outNum = 0;
    //else if (rpayloadStr.equals("2"))
    //  outNum = 1;
    //else if (rpayloadStr.equals("3"))
    //  outNum = 2;

    if ((outNum == 0) && (outVal == OUT_ON))
      ioOutA = OUT_ON;
    else if ((outNum == 0) && (outVal == OUT_OFF))
      ioOutA = OUT_OFF;
    /*
    else if ((outNum == 1) && (outVal == OUT_ON))
      ioOutB = OUT_ON;
    else if ((outNum == 1) && (outVal == OUT_OFF))
      ioOutB = OUT_OFF;    
    else if ((outNum == 2) && (outVal == OUT_ON))
      ioOutC = OUT_ON;
    else if ((outNum == 2) && (outVal == OUT_OFF))
      ioOutC = OUT_OFF;    
    */
  }
 
  // Watchdog
  else if (rtopicStr.equals(TOPIC_RWD))
  {
	/*
    if(rpayloadStr.equals("1"))
    {
      #if (_USE_WDE_ == 1)
      wdeForceReset = 1;
      #endif
    }
	*/
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
  
  ///////////////////
  // TOPIC_RSTATUS //
  ///////////////////
  if (itopic == 0)
  {
    /* 
    str = str + "\"tOn\":\"";
    str = str + String(timeDay) + "d " + timeOnString;
    str = str + "\",\n";
   
    str = str + "\"tU\":\"";
    str = str + mntpTimeString;
    str = str + "\",\n";
    
    str = str + "\"ip\":\"";
    str = str + String(ipAddress.toString());
    str = str + "\",\n"; 
    */
  }
  ////////////////
  // TOPIC_RIOS //
  ////////////////
  else if (itopic == 1)
  {
    /////////
    // IOs //
    /////////
    /*
    str = str + "\"bO\":\"";
    str = str + String(ioOutA) + String(ioOutB) + String(ioOutC);
    str = str + "\",\n";

    str = str + "\"bI\":\"";
    str = str + String(ioInC) + String(ioInB) + String(ioInA);
    str = str + "\",\n";
    */
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
    str = TOPIC_RSTATUS;
  
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
  String  str = "";
  int     str_len;
   
  mqttClient.setServer(brokerUrl, brokerPort);
  mqttClient.setCallback(mqttDataCallback);
  
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
      
        if (mqttClient.connect(mqttClientId.c_str(), brokerUser, brokerPswd))
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
        _MQTTSend(mqttTopic);
        
		    mqttTopic++;
		    if (mqttTopic > MQTT_NUM_TOPICS)
		      mqttTopic = 0;

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