///////////////////
// Broker set up //
///////////////////
void _BrokerSetup(void)
{
  brokerStatus = BROKER_INIT;
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
        Serial.println(" ");
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

////////////////
// Broker Led //
////////////////
void _BrokerLedLoop()
{
  switch (brokerStatus)
  {
    case BROKER_INIT:
      if (millis() - wifiLEDTick >= BROKER_BLINK_STARTING)
      {
        if (outLed == OUT_ON)
          outLed = OUT_OFF;
        else
          outLed = OUT_ON;

        wifiLEDTick = millis();
      } 
      break;

    case BROKER_LOOP: 
      outLed = IO_ON;
      break;
  }
}
