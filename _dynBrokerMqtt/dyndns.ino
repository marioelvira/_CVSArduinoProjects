
/////////////////
// Dyndns set up //
/////////////////
void _DyndnsSetup(void)
{
  dyndnsTick = millis();

  ddns_u = DYNDS_USER;
  ddns_p = DYNDS_PASSWORD;
  ddns_d = DYNDS_URL;
}

////////////////////////
// Dyndns state machine //
////////////////////////
void _DyndnsLoop(void)
{
  //String payload;
  String auth;
  int httpCode = 0;
  
  if (millis() - dyndnsTick >= (DYNDNS_TIMEOUT))
  {
    dyndnsTick = millis();

    ifconfigHttp.begin(ifconfigClient, "http://ifconfig.me/ip");
    httpCode = ifconfigHttp.GET();

    #if (_DYNDNS_SERIAL_DEBUG_ == 1)
    Serial.print(">>>> DYN DNS Public IP httpCode: ");
    Serial.println(httpCode);
    #endif
    
    if (httpCode == HTTP_CODE_OK)
      new_ip = ifconfigHttp.getString();

    ifconfigHttp.end();
    
    if (httpCode = HTTP_CODE_OK)
    {
      #if (_DYNDNS_SERIAL_DEBUG_ == 1)
      Serial.print(">>>> DYN DNS Public IP address: ");
      Serial.println(new_ip);
      #endif
      
      httpCode = 0;
      update_url = "http://" + ddns_u + ":" + ddns_p + "@dynupdate.no-ip.com/nic/update?hostname=" + ddns_d + "&myip=" + new_ip + "";
      
      if (old_ip != new_ip)
      { 
        #if (_DYNDNS_SERIAL_DEBUG_ == 1)
        Serial.println(">>>> DYN DNS url");
        Serial.println(update_url);
        #endif

        ip_sent = 0;

        dyndnsHttp.begin(dyndnsClient, update_url);
        dyndnsHttp.setUserAgent("CVSesma ESP8266-LolinV3/ESP8266HTTPClient sdpelicanos@example.com");
        auth = base64::encode(ddns_u + ":" + ddns_p);
        dyndnsHttp.addHeader("Authorization", "Basic " + auth);
        //dyndnsHttp.addHeader("Pragma", "no-cache");
        //dyndnsHttp.addHeader("Cache-Control", "no-cache");
        //dyndnsHttp.addHeader("Acept", "text/html");
        
        httpCode = dyndnsHttp.GET();
        
        #if (_DYNDNS_SERIAL_DEBUG_ == 1)
        Serial.print(">>>> DYN DNS Public IP reported httpCode: ");
        Serial.println(httpCode);
        //payload = dyndnsHttp.getString();
        //Serial.println(payload.substring(0, 200));
        #endif
        
        if (httpCode == HTTP_CODE_OK)
        {
          #if (_DYNDNS_SERIAL_DEBUG_ == 1)
          Serial.print(">>>> DYN DNS New IP reported OK ");
          #endif
          old_ip = new_ip;
          ip_sent = 1;
        }
        else
        {
          #if (_DYNDNS_SERIAL_DEBUG_ == 1)
          Serial.print(">>>> DYN DNS New IP reported ERROR ");
          #endif
          ip_sent = 0;
        }
        
        dyndnsHttp.end();
      }
      else
      {
        #if (_DYNDNS_SERIAL_DEBUG_ == 1)
        Serial.print(">>>> DYN DNS NO new IP to report ");
        #endif 
      }
    }
  }
}
