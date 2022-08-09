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

  // Outs
  if (rtopicStr.equals(TOPIC_OON) ||
      rtopicStr.equals(TOPIC_OOFF))
  {
    int board = 2; // MB
    int outNum = 0;
    int outVal = 0;

    // Value
    if (rtopicStr.equals(TOPIC_OON))
      outVal = OUT_ON;
    else
      outVal = OUT_OFF;

    // Board 2
    if(rpayloadStr.equals("1"))
      outNum = 0;
    else if (rpayloadStr.equals("2"))
      outNum = 1;
    else if (rpayloadStr.equals("3"))
      outNum = 2;
    else if (rpayloadStr.equals("4"))
      outNum = 3;
    else if (rpayloadStr.equals("5"))
      outNum = 4;      
    else if (rpayloadStr.equals("6"))
      outNum = 5;
    else if (rpayloadStr.equals("7"))
      outNum = 6;
    else if (rpayloadStr.equals("8"))
      outNum = 7;
    // Board 1
    else if (rpayloadStr.equals("A"))
    {
      board = 1; 
      outNum = 0;
    }
    else if (rpayloadStr.equals("B"))
    {
      board = 1; 
      outNum = 1;
    }
    else if (rpayloadStr.equals("C"))
    {
      board = 1; 
      outNum = 2;
    }
    else if (rpayloadStr.equals("D"))
    {
      board = 1; 
      outNum = 3;
    }
    // Error
    else
      board = 0;  // No board

    // Board
    if (board == 1) // Own
    {
      if ((outNum == 0) && (outVal == OUT_ON))
        OutA = OUT_ON;
      else if ((outNum == 0) && (outVal == OUT_OFF))
        OutA = OUT_OFF;
      else if ((outNum == 1) && (outVal == OUT_ON))
        OutB = OUT_ON;
      else if ((outNum == 1) && (outVal == OUT_OFF))
        OutB = OUT_OFF;    
      else if ((outNum == 2) && (outVal == OUT_ON))
        OutC = OUT_ON;
      else if ((outNum == 2) && (outVal == OUT_OFF))
        OutC = OUT_OFF;    
    }
    else if (board == 2) // MB
    {
      mbOutNum = outNum;
      mbOutVal = outVal;

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

  str = str + "\"bO\":\"";
  str = str + String(OutA) + String(OutB) + String(OutC);
  str = str + "\",\n";

  str = str + "\"mbO\":\"";
  str = str + String(mbOuts[0]) + String(mbOuts[1]) + String(mbOuts[2]) + String(mbOuts[3]);
  str = str + String(mbOuts[4]) + String(mbOuts[5]) + String(mbOuts[6]) + String(mbOuts[7]);
  str = str + "\",\n";

  str = str + "\"bI\":\"";
  str = str + String(InA) + String(InB) + String(InC) + String(InD) + String(InE);
  str = str + "\",\n";
  
  str = str + "\"mbI\":\"";
  str = str + String(mbIns[0]) + String(mbIns[1]) + String(mbIns[2]) + String(mbIns[3]);
  str = str + String(mbIns[4]) + String(mbIns[5]) + String(mbIns[6]) + String(mbIns[7]);
  str = str + "\",\n";
  
  // Adc
  str = str + "\"adc\":";
  str = str + String(AdcVal);
  str = str + ",\n";

  // AdcDig
  str = str + "\"adcDig\":";
  str = str + String(AdcIn);
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
        
        if (mqttSubscribe(TOPIC_OON)    &&
            mqttSubscribe(TOPIC_OOFF)   &&
            
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
