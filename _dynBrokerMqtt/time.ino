
/////////////////
// Time set up //
/////////////////
void _TimeSetup(void)
{
  timeTick = millis();
  timeSec = 0;
  timeMin = 0;
  timeHour = 0;
  timeDay = 0;
  
  // RAM Setup
  _RAMSetup();
}

////////////////////////
// Time state machine //
////////////////////////
void _TimeLoop(void)
{
  if (millis() - timeTick >= 1000)
  {   
    timeSec++;
    if (timeSec >= 60)
    {
      timeSec = 0;
      timeMin++;
      if (timeMin >= 60)
      {
        timeMin = 0;
        timeHour++;
        if (timeHour >= 24)
        {
          timeHour = 0;
          timeDay++;
        }
      }
    }
    
    timeTick = millis();

    _FreeRAM();
  
    #if (_USE_WDE_ == 1)
    _WDELoop();
    #endif

    #if (_STATUS_SERIAL_DEBUG_ == 1)
        
    Serial.println("<><><><><><><>");
    Serial.print("Tiempo Encendio: ");
    Serial.print(timeDay); Serial.print("d "); Serial.print(timeHour); Serial.print(" : "); Serial.print(timeMin); Serial.print(" : "); Serial.print(timeSec);
    Serial.println(" ");
    
    Serial.print("Free RAM: ");
    Serial.println(freeRam);

    Serial.print("WiFi Status: ");
    Serial.println(wifiStatus);

    Serial.print("Broker State: ");
    Serial.println(brokerStatus);

    Serial.print("Num Clientes: ");
    Serial.println(brokerClients);

    Serial.print("Public IP: ");
    Serial.println(new_ip);

    Serial.print("Dns IP: ");
    Serial.println(ip_sent);
  
    //_IOLoop();
    
    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
