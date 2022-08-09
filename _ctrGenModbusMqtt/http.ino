void _HttpSetup(void)
{
  // Http status
  httpStatus = HTTP_INIT;
}

void _HttpEnd(void)
{
  httpServer.stop();
}

///////////
// Pages //
///////////

void _serveCSS()
{
  httpServer.send (200, "text/css", cssSTYLE);
}

void _serveMAIN()
{
  String html = "";
  
  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>" + PROJECT + " Estado</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #Estado<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";

  html = html + "<div class=\"section\">Temporizaciones</div>";
  html = html + "<p class=\"sansserif\" id=\"TEMPSid\">...</p>";
  html = html + "<div class=\"section\">Entradas</div>";
  html = html + "<p class=\"sansserif\" id=\"INSid\">...</p>";
  html = html + "<div class=\"section\">Estados / Salidas</div>";
  html = html + "<p class=\"sansserif\" id=\"OUTSid\">...</p>";
  html = html + "<div class=\"section\">Control</div>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Cambiar Modo\" onclick=\"sendOUT(0)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"A\" onclick=\"sendOUT(10)\">";
  html = html + "  <input type=\"button\" value=\"B\" onclick=\"sendOUT(11)\">";
  html = html + "  <input type=\"button\" value=\"C\" onclick=\"sendOUT(12)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"1\" onclick=\"sendOUT(50)\">";
  html = html + "  <input type=\"button\" value=\"2\" onclick=\"sendOUT(51)\">";
  html = html + "  <input type=\"button\" value=\"3\" onclick=\"sendOUT(52)\">";
  html = html + "  <input type=\"button\" value=\"4\" onclick=\"sendOUT(53)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"5\" onclick=\"sendOUT(54)\">";
  html = html + "  <input type=\"button\" value=\"6\" onclick=\"sendOUT(55)\">";
  html = html + "  <input type=\"button\" value=\"7\" onclick=\"sendOUT(56)\">";
  html = html + "  <input type=\"button\" value=\"8\" onclick=\"sendOUT(57)\">";  
  html = html + "</p>";
  html = html + "<div class=\"section\">Watchdog</div>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Reset\" onclick=\"sendOUT(1)\">";
  html = html + "</p>";
  html = html + "<div class=\"section\">Configuraci&oacuten</div>";
  html = html + "<p>";
  html = html + "  <a href=\"settings.htm\"><input type=\"button\" value=\"Red\"></a>";
  html = html + "  <a href=\"timeSettings.htm\"><input type=\"button\" value=\"Config\"></a>";
  html = html + "  <input type=\"button\" value=\"Restore\" onclick=\"sendOUT(2)\">";
  html = html + "</p>";
  html = html + "</div>";

  html = html + "<script>";
  
  html = html + "function sendOUT(out) {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.open(\"GET\", \"setOUTS?OUTNumber=\"+out, true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
  html = html + "setInterval(function() {";
  html = html + "  getOUTS();";
  html = html + "  getINS();";
  html = html + "  getTEMPS();";
  html = html + "}, 1000);";
  
  html = html + "function getOUTS() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"OUTSid\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readOUTS\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
  html = html + "function getINS() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"INSid\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readINS\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";

  html = html + "function getTEMPS() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"TEMPSid\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readTEMPS\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
  html = html + "</script>";

  html = html + "</form>";
  html = html + "</div>";
  
  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

void _serveTimeSETTINGS()
{
  String html = "";
  
  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>" + PROJECT + " Config</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #Config<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  html = html + "<form method='get' action='setTimeSettings'>";

  html = html + "<div class=\"section\"><span>1</span>Logica</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Entradas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicIns) + "\" name=\"cfgIns\"/></label>";
  html = html + "<label> Salidas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicOuts) + "\" name=\"cfgOuts\"/></label>";
  html = html + "</div>";

  html = html + "<div class=\"section\"><span>2</span>Adc: y = mx +/- b</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label>ADC recta:m (/10)<input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCm) + "\" name=\"rADCm\"/></label>";
  html = html + "<label>ADC recta:b (/1000)<input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCb) + "\" name=\"rADCb\"/></label>";
  html = html + "<label>ADC recta:prscal <input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCp) + "\" name=\"rADCp\"/></label>";
  html = html + "<label>ADC signo (+/-  1/0)<input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCs) + "\" name=\"rADCs\"/></label>";
  html = html + "<label>ADC filtro (si/no 1/0)<input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCf) + "\" name=\"rADCf\"/></label>";
  html = html + "</div>";
  
  html = html + "<div class=\"section\"><span>3</span>Modbus</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label>Address 1<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgMB1Add) + "\" name=\"cfgMb1add\"/></label>";
  html = html + "<label>Address 2<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgMB2Add) + "\" name=\"cfgMb2add\"/></label>";
  html = html + "</div>";
  /*
  html = html + "<div class=\"section\"><span>*</span>Debug</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label>Debug (0)<input type=\"text\"  maxlength=\"16\" value=\"" + String(DebugVal) + "\" name=\"tdebugVal\"/></label>";
  html = html + "</div>";
  */
  html = html + "<div class=\"button-section\">";
  html = html + "  <input type=\"submit\" value=\"Guardar\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Volver\"></a>";
  html = html + "</div>";
  
  html = html + "</div>";
  html = html + "</div>";
  html = html + "</form>";
  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

void _setTimeSETTINGS()
{
  int eeprom_value_hi, eeprom_value_lo;
    
  String html = "";
  
  String rcfgIns     = httpServer.arg("cfgIns");
  String rcfgOuts    = httpServer.arg("cfgOuts");
  String rcfgMb1add  = httpServer.arg("cfgMb1add");
  String rcfgMb2add  = httpServer.arg("cfgMb2add");
  String rADCm       = httpServer.arg("rADCm");
  String rADCb       = httpServer.arg("rADCb");
  String rADCp       = httpServer.arg("rADCp");
  String rADCs       = httpServer.arg("rADCs");
  String rADCf       = httpServer.arg("rADCf");
  
  //String rdebugVal = httpServer.arg("tdebugVal");
  
  int error = 0;

  if ((rcfgIns.length() == 0)     ||
      (rcfgOuts.length() == 0)    ||
      (rcfgMb1add.length() == 0)  ||
      (rcfgMb2add.length() == 0)  ||
      (rADCm.length() == 0)       ||
      (rADCb.length() == 0)       ||
      (rADCp.length() == 0)       ||
      (rADCs.length() == 0)       ||
      (rADCf.length() == 0))
      //(rdebugVal.length() == 0))
  {
    error = 1;  // falta un campo...
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Error... parametro vacío.");
    #endif
  }

  // Si no hay error...
  if (error == 0)
  {
    cfgLogicIns  = rcfgIns.toInt();
    cfgLogicOuts = rcfgOuts.toInt();
    cfgMB1Add    = rcfgMb1add.toInt();
    cfgMB2Add    = rcfgMb2add.toInt();
    cfgADCm = rADCm.toInt();
    cfgADCb = rADCb.toInt();
    cfgADCp = rADCp.toInt();
    cfgADCs = rADCs.toInt();
    cfgADCf = rADCf.toInt();
    
    //DebugVal = rdebugVal.toInt();
    
    #if (_HTTP_SERIAL_DEBUG_ == 1)  
    Serial.print("cfgLogic Ins: ");  Serial.println(cfgLogicIns);
    Serial.print("cfgLogic Outs: "); Serial.println(cfgLogicOuts);
    Serial.print("Modbus Add1: ");   Serial.println(cfgMB1Add);
    Serial.print("Modbus Add2: ");   Serial.println(cfgMB2Add);

    Serial.print("ADC m: ");         Serial.print (cfgADCm);            Serial.println(" ");
    Serial.print("ADC b: ");         Serial.print (cfgADCb);            Serial.println(" (/1000)");
    Serial.print("ADC p: ");         Serial.print (cfgADCp);            Serial.println(" ");
    Serial.print("ADC s: ");         Serial.print (cfgADCs);            Serial.println(" +/-  1/0");
    Serial.print("ADC f: ");         Serial.print (cfgADCf);            Serial.println(" si/no 1/0");
  
    //Serial.print("Debug: ");       Serial.print (DebugVal);           Serial.println(" ---");
    #endif   

    // Data 
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  (byte)cfgLogicIns);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, (byte)cfgLogicOuts);
    EEPROM.write(EEPROM_ADD_MBADD1,     (byte)cfgMB1Add);
    EEPROM.write(EEPROM_ADD_MBADD2,     (byte)cfgMB2Add);

    eeprom_value_lo = cfgADCm & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgADCm & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_M_HI, eeprom_value_hi);
    eeprom_value_lo = cfgADCb & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgADCb & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_B_HI, eeprom_value_hi);
    eeprom_value_lo = cfgADCp & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_P_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgADCp & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_P_HI, eeprom_value_hi);
    EEPROM.write(EEPROM_ADD_ADC_S,        (byte)cfgADCs);
    EEPROM.write(EEPROM_ADD_ADC_F,        (byte)cfgADCf);
    
    //EEPROM.write(EEPROM_ADD_DEBUG,      (byte)DebugVal);

    EEPROM.commit();    //Store data to EEPROM
  }

  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>" + PROJECT + " Config</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #Config<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  
  if (error == 0)
    html += "<p class=\"sansserif\">Configuraci&oacuten guardada correctamente.</p>";
  else
    html += "<p class=\"sansserif\">Error el guardar la configuraci&oacuten. Revise los datos introducidos.</p>";

  html = html + "<div class=\"button-section\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Volver\"></a>";
  html = html + "</div>";

  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

void _serveSETTINGS()
{
  //int mobile = 0;
  String html = "";

  int n = WiFi.scanNetworks();
  
  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>" + PROJECT + " Red Config</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #Red Config<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  //html = html + "<form method=\"post\">";
  html = html + "<form method='get' action='networSettings'>";

  // Wi-Fi
  html = html + "<div class=\"section\"><span>1</span>Wi-Fi</div>";
  html = html + "<div class=\"inner-wrap\">";

  if (wifiMode == STATION_MODE)
  {
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"ap\"> Access Point</label>";
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"st\" checked> Station</label>";
  }
  else
  {
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"ap\" checked> Access Point</label>";
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"st\"> Station</label>";
  }
  
  //html = html + "<label>SSID">
  //html = html + "<select id='wifi' name='wifi'>";
  //html = html + " <option value=\"\" selected>Selet</option>";
  //for (int i = 0; i < n; ++i)
  //  html = html + " <option value=\"" + (String)(WiFi.SSID(i)) + "\">" + (String)(WiFi.SSID(i)) + "</option>";    
  //html = html + "</select></label>";

  html = html + "<label>SSID <input type=\"text\" maxlength=\"30\" value=\"" + String(ssid) + "\" name=\"ssid\"/></label>";
  html = html + "<label>Password <input type=\"text\" maxlength=\"30\" value=\"" + String(password) + "\" name=\"pass\"/></label>";

  html = html + "</div>";
  // End

  // Red
  html = html + "<div class=\"section\"><span>2</span>IP</div>";
  html = html + "<div class=\"inner-wrap\">";

  if (ipMode == DHCP_MODE)
  {
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"dhcp\" checked> DHCP</label>";
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"ipfx\"> Fix IP</label>";
  }
  else
  {
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"dhcp\"> DHCP</label>";
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"ipfx\" checked> Fix IP</label>";
  }

  html = html + "<label>IP Address <input type=\"text\"  maxlength=\"16\" value=\"" + String(ipAddress.toString()) + "\" name=\"ipaddress\"/></label>";
  html = html + "<label>Mask <input type=\"text\" maxlength=\"16\" value=\"" + String(netMask.toString()) + "\" name=\"mask\"/></label>";
  html = html + "<label>Gateway <input type=\"text\" maxlength=\"16\" value=\"" + String(gateWay.toString()) + "\" name=\"gateway\"/></label>";

  html = html + "</div>";
  // End

  // Broker
  html = html + "<div class=\"section\"><span>3</span>Broker </div>";
  html = html + "<div class=\"inner-wrap\">";

  html = html + "<label>URL <input type=\"text\" maxlength=\"30\" value=\"" + String(brokerUrl) + "\" name=\"brokerurl\"/></label>";
  html = html + "<label>Port <input type=\"text\" maxlength=\"16\" value=\"" + String(brokerPort) + "\" name=\"brokerport\"/></label>";

  html = html + "</div>";
  // End
                        
  html = html + "<div class=\"button-section\">";
  html = html + "  <input type=\"submit\" value=\"Guardar\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Volver\"></a>";
  html = html + "</div>";
  
  html = html + "</div>";
  html = html + "</div>";
  html = html + "</form>";
  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);  
}

void _setSETTINGS()
{
  String rwmode = httpServer.arg("wifimode");
  String rssid = httpServer.arg("ssid");
  String rpass = httpServer.arg("pass");
  
  String ripmode = httpServer.arg("ipmode");
  String ripaddress = httpServer.arg("ipaddress");
  String rmask = httpServer.arg("mask");
  String rgate = httpServer.arg("gateway");
  
  String rbrokerurl = httpServer.arg("brokerurl");
  String rbrokerport = httpServer.arg("brokerport");
    
  String html = "";
  int i, j, k, m;
  int error = 0;
  char schar;
  char sbuf[4];
  byte val[4];

  int eeprom_value_hi, eeprom_value_lo;

  IPAddress localip;
  IPAddress localmask;
  IPAddress localgate;

  // Wi-Fi and IP configuration
  if (rwmode.length() > 0)
  {
    // Wi-Fi on Station mode
    if (rwmode == "st")
    {
      // must have a value
      if (rssid.length() == 0)
        error = 1;

      if (ripmode.length() == 0)
        error = 1;

      // must have a value
      if (ripmode == "ipfx")
      {
        // Must be 
        if ((ripaddress.length() == 0) ||
            (rmask.length() == 0)      ||
            (rgate.length() == 0))
          error = 1;
      }
      // DHCP mode
      //else {}
      
    }
    // Wi-Fi Access Point mode
    //else {}
    
  }
  else
    error = 1;

  // Check broker error
  if ((rbrokerurl.length() == 0) ||
      (rbrokerport.length() == 0))
    error |= 1;

  // If no error on data...
  if (error == 0)
  {
     ////////////
     // Broker //
     ////////////
     for (i = 0; i < BROKER_MAX; i++)
       EEPROM.write(EEPROM_ADD_BROKER + i, 0);
     j = rbrokerurl.length();
     for (i = 0; i < j; i++)
       EEPROM.write(EEPROM_ADD_BROKER + i, rbrokerurl[i]);
      
     brokerPort = rbrokerport.toInt();
     eeprom_value_lo = brokerPort & 0x00FF;
     EEPROM.write(EEPROM_ADD_BROKER_PORT, eeprom_value_lo);
     eeprom_value_hi = (brokerPort & 0xFF00)>>8;
     EEPROM.write(EEPROM_ADD_BROKER_PORT + 1, eeprom_value_hi);
          
     /////////////////////////
     // Wi-Fi configuration //
     /////////////////////////
     #if (_HTTP_SERIAL_DEBUG_ == 1)
     Serial.println("Wi-Fi 2 eeprom:");
     #endif
     
     // AP mode
     if (rwmode == "ap")
       EEPROM.write(EEPROM_ADD_WIFI_MODE, ACCESSPOINT_MODE);
     else
     {
       // Station mode
       EEPROM.write(EEPROM_ADD_WIFI_MODE, STATION_MODE);
  
       // ssid
       for (i = 0; i < WIFI_SSID_MAX; i++)
         EEPROM.write(EEPROM_ADD_WIFI_SSID + i, 0);
       j = rssid.length();
       for (i = 0; i < j; i++)
         EEPROM.write(EEPROM_ADD_WIFI_SSID + i, rssid[i]);
       // password
       for (i = 0; i < WIFI_PSWD_MAX; i++)
         EEPROM.write(EEPROM_ADD_WIFI_PSWD + i, 0);
       j = rpass.length();
       for (i = 0; i < j; i++)
         EEPROM.write(EEPROM_ADD_WIFI_PSWD + i, rpass[i]);
       
       /////////////
       // IP Mpde //
       /////////////
       #if (_HTTP_SERIAL_DEBUG_ == 1)
       Serial.println("IP 2 eeprom:");
       #endif
       // mode
       if (ripmode == "dhcp")
         EEPROM.write(EEPROM_ADD_IP_MODE, DHCP_MODE);
       else
       {
         EEPROM.write(EEPROM_ADD_IP_MODE, FIXIP_MODE);
  
         // IP
         j = ripaddress.length();
         k = 0;
         m = 0;
         for (i = 0; i < j; i++)
         {
           schar = ripaddress[i];
           if (schar == '.')
           {        
             sbuf[k] = 0;  // end of buffer
             val[m] = (byte)(atoi(sbuf)); // change to int
             k = 0;
             m++;
           }
           else
           {
             sbuf[k] = schar;
             k++;
           }
         }
         // last IP value
         sbuf[k] = 0;  // end of buffer
         val[m] = (byte)(atoi(sbuf)); // change to int
         localip = IPAddress(val[0], val[1], val[2], val[3]);
    
         EEPROM.write(EEPROM_ADD_IP1, val[0]);
         EEPROM.write(EEPROM_ADD_IP2, val[1]);
         EEPROM.write(EEPROM_ADD_IP3, val[2]);
         EEPROM.write(EEPROM_ADD_IP4, val[3]);
         
         // Mask
         j = rmask.length();
         k = 0;
         m = 0;
         for (i = 0; i < j; i++)
         {
           schar = rmask[i];
           if (schar == '.')
           {
             sbuf[k] = 0;  // end of buffer
             val[m] = (byte)(atoi(sbuf)); // change to int
             k = 0;
             m++;
           }
           else
           {
             sbuf[k] = schar;
             k++;
           }
         }
         // last IP value
         sbuf[k] = 0;  // end of buffer
         val[m] = (byte)(atoi(sbuf)); // change to int
         localmask = IPAddress(val[0], val[1], val[2], val[3]);
    
         EEPROM.write(EEPROM_ADD_MASK1, val[0]);
         EEPROM.write(EEPROM_ADD_MASK2, val[1]);
         EEPROM.write(EEPROM_ADD_MASK3, val[2]);
         EEPROM.write(EEPROM_ADD_MASK4, val[3]);
    
         // Gateway
         j = rgate.length();
         k = 0;
         m = 0;
         for (i = 0; i < j; i++)
         {
           schar = rgate[i];
           if (schar == '.')
           {
             sbuf[k] = 0;  // end of buffer
             val[m] = (byte)(atoi(sbuf)); // change to int
             k = 0;
             m++;
           }
           else
           {
             sbuf[k] = schar;
             k++;
           }
         }
         // last IP value
         sbuf[k] = 0;  // end of buffer
         val[m] = (byte)(atoi(sbuf)); // change to int
         localgate = IPAddress(val[0], val[1], val[2], val[3]);
    
         EEPROM.write(EEPROM_ADD_GATE1, val[0]);
         EEPROM.write(EEPROM_ADD_GATE2, val[1]);
         EEPROM.write(EEPROM_ADD_GATE3, val[2]);
         EEPROM.write(EEPROM_ADD_GATE4, val[3]);
       }
     }
     
     #if (_HTTP_SERIAL_DEBUG_ == 1)
     // Wi-Fi configuration
     Serial.print("---->Wi-Fi mode: ");
     Serial.println(rwmode);
     Serial.print("---->Wi-Fi SSID: ");
     Serial.println(rssid);
     Serial.print("---->Wi-Fi Password: ");
     Serial.println(rpass);
     Serial.println("");

     // IP configuration
     Serial.print("---->Local IP: ");
     Serial.println(localip);
     Serial.print("---->Local mask: ");
     Serial.println(localmask);
     Serial.print("---->Local gateway: ");
     Serial.println(localgate);

     // Broker configuration
     Serial.print("---->Broker Url: ");
     Serial.println(rbrokerurl);
     Serial.print("---->Broker Port: ");
     Serial.println(rbrokerport);     
     #endif
     
     EEPROM.commit();

     #if (_READ_EEPROM_ == 1)
     _ReadEEPROM();
     delay(1000);
     #endif
    
     // Read config from EEPROM
     _readCONFIG();

     // OK
     i = 200;
   }
   else
   {
     #if (_HTTP_SERIAL_DEBUG_ == 1)
     Serial.println("Sending 404");
     #endif

     // Error
     i = 404;
  }

  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>" + PROJECT + " Config</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #Config<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  
  if (error == 0)
    html += "<p class=\"sansserif\">Configuraci&oacuten guardada correctamente.</p>";
  else
    html += "<p class=\"sansserif\">Error el guardar la configuraci&oacuten. Revise los datos introducidos.</p>";

  html = html + "<div class=\"button-section\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Volver\"></a>";
  html = html + "</div>";

  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

/////////////
// Actions //
/////////////
void _readINS()
{ 
  String html = "";

  html = "<table style=\"width:100%\">";

  html = html + "<tr>";
  html = html + "<td>Modo</td>";
  if (controlMode == MODE_AUTO)
   html = html + "<td><font style=\"color:blue\">Autom&aacutetico</font></td>";
  else
   html = html + "<td><font style=\"color:red\">Control Manual</font></td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Boards Ins</td>";
  html = html + "<td>" + String(InA) + "-" + String(InB) + "-" + String(InC) + "-" + String(InD) + "-" + String(InE) + "</td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>Modbus Ins</td>";
  html = html + "<td>" + String(mbIns[0]) + "-" + String(mbIns[1]) + "-" + String(mbIns[2]) + "-" + String(mbIns[3]) + "-" + String(mbIns[4]) + "-" + String(mbIns[5]) + "-" + String(mbIns[6]) + "-" + String(mbIns[7]) + "</td>";
  html = html + "</tr>";
 
  html = html + "<tr>";
  html = html + "<td>Adc Dig</td>";
  html = html + "<td>" + String(AdcIn) + "</td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>Adc Val</td>";
  html = html + "<td>" + String(AdcVal) + "</td>";
  html = html + "</tr>";
  
  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

void _readOUTS()
{
  String html = "";

  html = "<table style=\"width:100%\">";

  html = html + "<tr>";
  html = html + "<td>Control State </td>";
  html = html + "<td>" + String(ControlState) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Wi-Fi State </td>";
  html = html + "<td>" + String(wifiStatus) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>MQTT State </td>";
  html = html + "<td>" + String(mqttStatus) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>-----------------</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Boards Outs</td>";
  html = html + "<td>" + String(OutA) + "-" + String(OutB) + "-" + String(OutC) + "</td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>Modbus Outs</td>";
  html = html + "<td>" + String(mbOuts[0]) + "-" + String(mbOuts[1]) + "-" + String(mbOuts[2]) + "-" + String(mbOuts[3]) + "-" + String(mbOuts[4]) + "-" + String(mbOuts[5]) + "-" + String(mbOuts[6]) + "-" + String(mbOuts[7]) + "</td>";
  html = html + "</tr>";
   
  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

void _setOUTS()
{
  String out_number = httpServer.arg("OUTNumber");
  String html = "";
 
  #if (_HTTP_SERIAL_DEBUG_ == 1)
  Serial.print("Change stats out: ");
  Serial.println(out_number);
  #endif

  // Cambiar Modo
  if(out_number == "0")
  {
    if (controlMode == MODE_TEST)
    {
      controlMode = MODE_AUTO;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Modo Auto");
      #endif
      html = "Modo Auto";
    }
    else
    {
      controlMode = MODE_TEST;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Modo Test");
      #endif
      html = "Mode Test";
    }
  }

  // Reset
  if(out_number == "1")
  {
    #if (_USE_WDE_ == 1)
    wdeForceReset = 1;
    #endif
      
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Watchdog reset");
    #endif
  }

  // Restore
  if(out_number == "2")
  {
    _ResetEEPROM();
    html = "Restore";
  }

  // Out A
  if(out_number == "10")
  {
    if (OutA == OUT_ON)
    {
      OutA = OUT_OFF;
      html = "Out A OFF";
    }
    else
    {
      OutA = OUT_ON;
      html = "Out A ON";
    }
  }
  // Out B
  else if(out_number == "11")
  {
    if (OutB == OUT_ON)
    {
      OutB = OUT_OFF;
      html = "Out B OFF";
    }
    else
    {
      OutB = OUT_ON;
      html = "Out B ON";
    }
  }
  // Out C
  else if(out_number == "12")
  {
    if (OutC == OUT_ON)
    {
      OutC = OUT_OFF;
      html = "Out C OFF";
    }
    else
    {
      OutC = OUT_ON;
      html = "Out C ON";
    }
  }

  // Outs
  if ((out_number == "50") || (out_number == "51") || (out_number == "52") || (out_number == "53") ||
      (out_number == "54") || (out_number == "55") || (out_number == "56") || (out_number == "57"))
  {
    if (out_number == "50")
      mbOutNum = 0; // O1
    else if (out_number == "51")
      mbOutNum = 1; // O2
    else if (out_number == "52")
      mbOutNum = 2; // O3
    else if (out_number == "53")
      mbOutNum = 3; // O4
    else if (out_number == "54")
      mbOutNum = 4; // O5
    else if (out_number == "55")
      mbOutNum = 5; // O6
    else if (out_number == "56")
      mbOutNum = 6; // O7     
    else
      mbOutNum = 7; // O8
    
    if (mbOuts[mbOutNum] == OUT_OFF)
      mbOutVal = OUT_ON;
    else
      mbOutVal = OUT_OFF;

    if (mbState == MB_STANDBY)
      mbState = MB_WRITEOUT;
    
    html = "Outs";
  }
  
  httpServer.send(200, "text/plane", html);
}

void _readTEMPS()
{ 
  String html = "";

  html = "<table style=\"width:100%\">";
  
  html = html + "<tr>";
  html = html + "<td>Tiempo Encendio</td>";
  html = html + "<td>" + String(timeDay) + "d " + String(timeHour) + " : " + String(timeMin) + " : " + String(timeSec) + "</td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>Free RAM</td>";
  html = html + "<td>" + String(freeRam) + "</td>";
  html = html + "</tr>";

  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

////////////////////////
// Http state machine //
////////////////////////
void _HttpLoop()
{
  switch (httpStatus)
  {
    case HTTP_INIT:

      // css Style
      httpServer.on("/style.css",         _serveCSS);

      // html pages
      httpServer.on("/",                  _serveMAIN);
      httpServer.on("/index.htm",         _serveMAIN);
      httpServer.on("/settings.htm",      _serveSETTINGS);
      httpServer.on("/timeSettings.htm",  _serveTimeSETTINGS);

      // acctions
      httpServer.on("/setOUTS",          _setOUTS);
      httpServer.on("/readOUTS",         _readOUTS);
      httpServer.on("/readINS",          _readINS);
      httpServer.on("/readTEMPS",        _readTEMPS);
      httpServer.on("/networSettings",   _setSETTINGS);
      httpServer.on("/setTimeSettings",  _setTimeSETTINGS);

      httpServer.begin();

      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.print("HTTP server started on ");
      Serial.print(HTTP_PORT);
      Serial.println(" port");      
      #endif
      httpStatus = HTTP_ONSERVE;
      break;
    
    case HTTP_ONSERVE:
      httpServer.handleClient();
      break;
  }
}
