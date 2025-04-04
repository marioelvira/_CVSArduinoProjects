
//////////////////
// Wi-Fi set up //
//////////////////
void _WifiSetup(void)
{
  // Wi-Fi status
  wifiStatus = WIFI_START_ACCESSPOINT;
}

/////////////////////////
// Wi-Fi state machine //
/////////////////////////
void _WifiLoop()
{
  switch (wifiStatus)
  {
    case WIFI_START_ACCESSPOINT:

      #if (_WIFI_SERIAL_DEBUG_ == 1)
      Serial.println("Access point mode start ");
      Serial.print("SSID: ");
      Serial.println(ssidAp);
      Serial.print("PASSWORD: ");
      Serial.println(passwordAp);
      #endif
    
      WiFi.mode(WIFI_AP);
      WiFi.softAP(ssidAp, passwordAp);
  
      wifiIP = WiFi.softAPIP();
      
      #if (_WIFI_SERIAL_DEBUG_ == 1)
      Serial.print("AP IP address: ");
      Serial.println(wifiIP);
      #endif

      _HTTPStart();

       wifiAPTick = millis();
        
      wifiStatus = WIFI_ON_ACCESSPOINT;
      break;

    case WIFI_ON_ACCESSPOINT:
      // Station mode...
      if (wifiMode == STATION_MODE)
      {       
        if (millis() - wifiAPTick >= WIFI_ACCESSPOINT_TIMEOUT)
        {
          _HTTPStop();

          wifiStatus = WIFI_START_STATION;
        }
      }
      // Access point mode...
      else
      {
        wifiAPTick = millis();
      }
      break;

    case WIFI_START_STATION:
    
      WiFi.begin(ssid, password);
      WiFi.macAddress(mac);
     
      WiFi.disconnect();          // Prevent connecting to wifi based on previous configuration
      WiFi.hostname(deviceName);  // DHCP Hostname (useful for finding device for static lease)
    
      if (ipMode == FIXIP_MODE)
        WiFi.config(ipAddress, netMask, gateWay);

      WiFi.begin(ssid, password);
      WiFi.mode(WIFI_STA);        // WiFi mode station (connect to wifi router only)

      #if (_WIFI_SERIAL_DEBUG_ == 1)
      Serial.println("Station Mode start ");
      Serial.print("SSID: ");
      Serial.println(ssid);
      Serial.print("PASSWORD: ");
      Serial.println(password);
      #endif

      wifiStatus = WIFI_STATION_CONNECTING;
      break;
      
    case WIFI_STATION_CONNECTING:
      // If no connected...
      if (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
    
        #if (_WIFI_SERIAL_DEBUG_ == 1)
        Serial.print(".");
        #endif
      }
      // If connected...
      else
      {
        ipAddress = WiFi.localIP();
        gateWay   = WiFi.gatewayIP();
        netMask   = WiFi.subnetMask();
                
        #if (_WIFI_SERIAL_DEBUG_ == 1)
        Serial.println(" ");
        Serial.println("*******************************************************");
        Serial.println("*******************************************************");
        Serial.println("*******************************************************");
        Serial.print("Connected to ");
        Serial.println(ssid);
        if (ipMode == FIXIP_MODE)
          Serial.println("Fix IP Mode");
        else
          Serial.println("DHCP Mode");
        Serial.print("IP address: ");
        Serial.println(ipAddress);
        Serial.print("Mask: ");
        Serial.println(netMask);
        Serial.print("Gateway: ");
        Serial.println(gateWay);
        Serial.print("MAC: ");
        Serial.print(mac[5],HEX);
        Serial.print(":");
        Serial.print(mac[4],HEX);
        Serial.print(":");
        Serial.print(mac[3],HEX);
        Serial.print(":");
        Serial.print(mac[2],HEX);
        Serial.print(":");
        Serial.print(mac[1],HEX);
        Serial.print(":");
        Serial.println(mac[0],HEX);
        #endif

        _HTTPStart();
        
        #if (_USE_NTP_ == 1)
        _mNTPStart();
        #endif
      
        #if (_USE_MBTCP_ == 1)
        _mMBTCPStart();
        #endif

        wifiStatus = WIFI_STATION_CONNECTED;
      }
      break;

    case WIFI_STATION_CONNECTED:
      // If no connected...
      if (WiFi.status() != WL_CONNECTED)
      {
        _HTTPStop();

        #if (_USE_NTP_ == 1)
        _mNTPStop();
        #endif
        
        #if (_USE_MBTCP_ == 1)
        _mMBTCPStop();
        #endif

        wifiStatus = WIFI_START_STATION;
      }

      break;
  }
}

///////////////
// Wi-Fi Led //
///////////////
void _WifiLedLoop()
{
  switch (wifiStatus)
  {
    case WIFI_START_ACCESSPOINT:
      wifiLEDTick = millis();
      outLed = OUT_ON;
      break;

    case WIFI_ON_ACCESSPOINT:
      if (millis() - wifiLEDTick >= WIFI_BLINK_ACCESSPOINT)
      {
        if (outLed == OUT_ON)
          outLed = OUT_OFF;
        else
          outLed = OUT_ON;

        wifiLEDTick = millis();

        //#if (_WIFI_SERIAL_DEBUG_ == 1)
        //if (wifiMode == STATION_MODE)
        //  Serial.print(">");
        //else
        //  Serial.print(".");
        //#endif
      } 
      break;

    case WIFI_START_STATION:
    case WIFI_ON_STATION:
    case WIFI_STATION_CONNECTING:
      if (millis() - wifiLEDTick >= WIFI_BLINK_CONNECTING)
      {
        if (outLed == IO_OFF)
          outLed = IO_ON;
        else
          outLed = IO_OFF;

        wifiLEDTick = millis();
      } 
      break;

    case WIFI_STATION_CONNECTED:
      
      #if (_USE_MQTT_ == 1)
      _MQTTLedLoop();
      #else
      if (millis() - wifiLEDTick >= WIFI_BLINK_STATION)
      {
        //#if (_WIFI_SERIAL_DEBUG_ == 1)
        //Serial.print("-");
        //#endif
        
        wifiLEDTick = millis();
      }      
      outLed = IO_ON;
      #endif

      break;
  }
}
