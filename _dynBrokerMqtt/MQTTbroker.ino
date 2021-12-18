
///////////////////
// Broker set up //
///////////////////
void _BrokerSetup(void)
{
  brokerStatus = BROKER_INIT;
  freeRam = ESP.getFreeHeap();
}

///////////////////////////
// Broker  state machine //
///////////////////////////
void _BrokerLoop(void)
{

  switch (brokerStatus)
  {
    case BROKER_INIT:
      if (broker.init(mqttPort))
      {
        #if (_BROKER_SERIAL_DEBUG_ == 1)
        Serial.println("++++++++++++++++ Broker Init OK +++++++++++++++");
        #endif
        brokerStatus = BROKER_LOOP;
      }
      break;

    case BROKER_LOOP:
      broker.update();
      break;
  }
}

//////////////
// Free RAM //
//////////////
void _FreeRAM(void)
{
  if(ESP.getFreeHeap() != freeRam)
  {
    freeRam = ESP.getFreeHeap();
    
    #if (_FREERAM_SERIAL_DEBUG_ == 1)
    Serial.print("RAM:");
    Serial.println(freeRam);
    #endif
  }
}
