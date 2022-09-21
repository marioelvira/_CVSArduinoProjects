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
    int boardType = 2; // MB
    int outNum = 0;
    int outVal = 0;
  
    // Value
    if (rtopicStr.equals(TOPIC_OON))
      outVal = OUT_ON;
    else
      outVal = OUT_OFF;
  
    // mbInBoard 0 - boardType 2 MB
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
    // mbInBoard 1 - boardType 2 MB
    else if (rpayloadStr.equals("11"))
      outNum = 10;
    else if (rpayloadStr.equals("12"))
      outNum = 11;
    else if (rpayloadStr.equals("13"))
      outNum = 12;
    else if (rpayloadStr.equals("14"))
      outNum = 13;
    else if (rpayloadStr.equals("15"))
      outNum = 14;      
    else if (rpayloadStr.equals("16"))
      outNum = 15;
    else if (rpayloadStr.equals("17"))
      outNum = 16;
    else if (rpayloadStr.equals("18"))
      outNum = 17;
        
    // boardType 1
    else if (rpayloadStr.equals("41"))
    {
      boardType = 1;
      outNum = 0;
    }
    else if (rpayloadStr.equals("42"))
    {
      boardType = 1; 
      outNum = 1;
    }
    else if (rpayloadStr.equals("43"))
    {
      boardType = 1;
      outNum = 2;
    }
    // Error
    else
      boardType = 0;  // No board

    // Auto Mode
    if (controlMode == MODE_AUTO)
    {
      // MB Board
      if (boardType == 2)
      {
        // Only 
        if (outNum >= 10)
        {
          mbOutBoard = 1;
          mbOutNum = outNum - 10;
          mbOutVal = outVal;

          if (mbOutVal == OUT_ON)
            outO1XState[mbOutNum] = STATE_O1X_ON;
          else
            outO1XState[mbOutNum] = STATE_O1X_OFF;
        }
      }
    }
    // Test Mode
    else if (controlMode == MODE_TEST)
    {
      // Board
      if (boardType == 1) // Own
      {
        if ((outNum == 0) && (outVal == OUT_ON))
          ioOutA = OUT_ON;
        else if ((outNum == 0) && (outVal == OUT_OFF))
          ioOutA = OUT_OFF;
        else if ((outNum == 1) && (outVal == OUT_ON))
          ioOutB = OUT_ON;
        else if ((outNum == 1) && (outVal == OUT_OFF))
          ioOutB = OUT_OFF;    
        else if ((outNum == 2) && (outVal == OUT_ON))
          ioOutC = OUT_ON;
        else if ((outNum == 2) && (outVal == OUT_OFF))
          ioOutC = OUT_OFF;    
      }
      else if (boardType == 2) // MB
      {
        if (outNum >= 10)
        {
          mbOutBoard = 1;
          outNum = outNum - 10;
        }
        else
          mbOutBoard = 0;
          
        mbOutNum = outNum;
        mbOutVal = outVal;
  
        // Solo en modo Test
        if (controlMode == MODE_TEST)
        {
          if (mbState == MB_STANDBY)
            mbState = MB_WRITEOUT;
        }
      }
    } // (controlMode == MODE_TEST)
  }

  else if (rtopicStr.equals(TOPIC_GENON))
  {
    if(rpayloadStr.equals("1"))
    {
      InStartState = PULSACION_OK;
      remAct = 1;
    }
  }
  else if (rtopicStr.equals(TOPIC_GENOFF))
  {
    if(rpayloadStr.equals("1"))
      InEndState = PULSACION_OK;
  }
  /*
  else if (rtopicStr.equals(TOPIC_LUZCTR))
  {
    if(rpayloadStr.equals("1"))
    {}
  }
  else if (rtopicStr.equals(TOPIC_LUZSTOP))
  {
    if(rpayloadStr.equals("1"))
    {}
  }
  */
  // Watchdog
  else if (rtopicStr.equals(TOPIC_WATCHDOG))
  {
    if(rpayloadStr.equals("1"))
    {
      #if (_USE_WDE_ == 1)
      wdeForceReset = 1;
      #endif
    }
  }

  // Mode
  else if (rtopicStr.equals(TOPIC_MODE_AUTO))
  {
    if(rpayloadStr.equals("1"))
    {
      controlMode = MODE_AUTO;
    }
  }
  else if (rtopicStr.equals(TOPIC_MODE_TEST))
  {
    if(rpayloadStr.equals("1"))
    {
      controlMode = MODE_TEST;
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
  char    spayload[255];
  String  str;
  int     str_len;

  str = "{\n";
  
  /////////////
  // Control //
  /////////////
  if (itopic == 0)
  {
    
    str = str + "\"tOn\":\"";
    str = str + String(timeDay) + "d " + String(timeHour) + " : " + String(timeMin) + " : " + String(timeSec);
    str = str + "\",\n";
    /*
    str = str + "\"ram\":";
    str = str + String(freeRam);
    str = str + ",\n";
    */
    str = str + "\"ip\":\"";
    str = str + String(ipAddress.toString());
    str = str + "\",\n";
    
    str = str + "\"al\":\"0x";
    str = str + String(alarm[0]) + String(alarm[1]) + String(alarm[2]) + String(alarm[3]);
    str = str + String(alarm[4]) + String(alarm[5]) + String(alarm[6]) + String(alarm[7]);
    str = str + "\",\n";
  
    str = str + "\"md\":";
    str = str + String(controlMode);
    str = str + ",\n";
  
    if (OutGen == OUT_OFF)
      str = str + "\"gSt\":0";
    else
      str = str + "\"gSt\":1";
    str = str + ",\n";
  
    if (OutBomba == OUT_OFF)
      str = str + "\"bSt\":0";
    else
      str = str + "\"bSt\":1";
    str = str + ",\n";

    str = str + "\"gD\":";
    str = str + String(DisplayIndicador);
    str = str + ",\n";
        
    str = str + "\"gOn\":\"";
    str = str + String(genMinOn);
    str = str + "m\",\n";
    
    str = str + "\"gOff\":\"";
    str = str + String(genTimeDay) + "d " + String(genTimeHour) + " : " + String(genTimeMin) + " : " + String(genTimeSec);
    str = str + "\",\n";

    str = str + "\"gR\":";
    str = str + String(remAct);
    str = str + ",\n";
	    
    str = str + "\"adc\":";
    str = str + String(AdcVal);
    str = str + ",\n";

  }
  ///////////////////
  // Extra Control //
  ///////////////////
  else if (itopic == 1)
  {
    str = str + "\"i1\":";
    str = str + String(mbIns[0][0]);
    str = str + ",\n";
 
    str = str + "\"i2\":";
    str = str + String(mbIns[1][0]);
    str = str + ",\n";

    str = str + "\"i3\":";
    str = str + String(mbIns[2][0]);
    str = str + ",\n";

    str = str + "\"i4\":";
    str = str + String(mbIns[3][0]);
    str = str + ",\n";
 
    str = str + "\"i5\":";
    str = str + String(mbIns[4][0]);
    str = str + ",\n";
 
    str = str + "\"i6\":";
    str = str + String(mbIns[5][0]);
    str = str + ",\n";
 
    str = str + "\"i7\":";
    str = str + String(mbIns[6][0]);
    str = str + ",\n";

    str = str + "\"i8\":";
    str = str + String(mbIns[7][0]);
    str = str + ",\n";
    
    str = str + "\"i11\":";
    str = str + String(mbIns[0][1]);
    str = str + ",\n";
 
    str = str + "\"i12\":";
    str = str + String(mbIns[1][1]);
    str = str + ",\n";

    str = str + "\"i13\":";
    str = str + String(mbIns[2][1]);
    str = str + ",\n";

    str = str + "\"i14\":";
    str = str + String(mbIns[3][1]);
    str = str + ",\n";
 
    str = str + "\"i15\":";
    str = str + String(mbIns[4][1]);
    str = str + ",\n";
 
    str = str + "\"i16\":";
    str = str + String(mbIns[5][1]);
    str = str + ",\n";
 
    str = str + "\"i17\":";
    str = str + String(mbIns[6][1]);
    str = str + ",\n";

    str = str + "\"i18\":";
    str = str + String(mbIns[7][1]);
    str = str + ",\n";
  }
  //////////
  // Test //
  //////////
  else if (itopic == 2)
  {
    /////////
    // IOs //
    /////////
    str = str + "\"bO\":\"";
    str = str + String(ioOutA) + String(ioOutB) + String(ioOutC);
    str = str + "\",\n";
  
    str = str + "\"mbO1\":\"";
    str = str + String(mbOuts[0][0]) + String(mbOuts[1][0]) + String(mbOuts[2][0]) + String(mbOuts[3][0]);
    str = str + String(mbOuts[4][0]) + String(mbOuts[5][0]) + String(mbOuts[6][0]) + String(mbOuts[7][0]);
    str = str + "\",\n";
  
    str = str + "\"mbO2\":\"";
    str = str + String(mbOuts[0][1]) + String(mbOuts[1][1]) + String(mbOuts[2][1]) + String(mbOuts[3][1]);
    str = str + String(mbOuts[4][1]) + String(mbOuts[5][1]) + String(mbOuts[6][1]) + String(mbOuts[7][1]);
    str = str + "\",\n";
    
    str = str + "\"bI\":\"";
    str = str + String(ioInA) + String(ioInB) + String(ioInC) + String(ioInD) + String(ioInE);
    str = str + "\",\n";
    
    str = str + "\"mbI1\":\"";
    str = str + String(mbIns[0][0]) + String(mbIns[1][0]) + String(mbIns[2][0]) + String(mbIns[3][0]);
    str = str + String(mbIns[4][0]) + String(mbIns[5][0]) + String(mbIns[6][0]) + String(mbIns[7][0]);
    str = str + "\",\n";
  
    str = str + "\"mbI2\":\"";
    str = str + String(mbIns[0][1]) + String(mbIns[1][1]) + String(mbIns[2][1]) + String(mbIns[3][1]);
    str = str + String(mbIns[4][1]) + String(mbIns[5][1]) + String(mbIns[6][1]) + String(mbIns[7][1]);
    str = str + "\",\n";

    // AdcIn
    str = str + "\"adci\":";
    str = str + String(AdcIn);
    str = str + ",\n";
  }

  str_len = str.length();
  str = str + "\"len\":";
  str = str + String(str_len + 12);
  str = str + "\n";

  str = str + "}";

  str_len = str.length() + 1;
  str.toCharArray(spayload, str_len);

  if (itopic == 1)
    str = TOPIC_SINS;
  else if (itopic == 2)
    str = TOPIC_TEST;
  else
    str = TOPIC_SCTR;
  
  str_len = str.length() + 1;
  str.toCharArray(stopic, str_len);

  //if(mqttPublish(TOPIC_STATE, (char*)spayload))
  if(mqttPublish((char*)stopic, (char*)spayload))
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
  mqttPayload = 0;
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
      
        //if (mqttClient.connect(mqttClientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD))
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
        
        if (mqttSubscribe(TOPIC_OON)       &&
            mqttSubscribe(TOPIC_OOFF)      &&

            mqttSubscribe(TOPIC_MODE_AUTO) &&
            mqttSubscribe(TOPIC_MODE_TEST) &&
            
            mqttSubscribe(TOPIC_GENON)     &&
            mqttSubscribe(TOPIC_GENOFF)    &&
            //mqttSubscribe(TOPIC_LUZCTR)  &&
            //mqttSubscribe(TOPIC_LUZSTOP) &&
            
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
		    _MQTTSend(mqttPayload);

		    mqttPayload++;	
		    if (mqttPayload > 2)
		      mqttPayload = 0;

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
