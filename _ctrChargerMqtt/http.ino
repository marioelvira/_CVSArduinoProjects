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
  html = html + "<title>CHARGER MQTT+ Estado</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>CHARGER MQTT+ #Estado<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";

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
  html = html + "  <input type=\"button\" value=\"Batt A\" onclick=\"sendOUT(10)\">";
  html = html + "  <input type=\"button\" value=\"Batt B\" onclick=\"sendOUT(11)\">";
  html = html + "  <input type=\"button\" value=\"Batt C\" onclick=\"sendOUT(12)\">";
  html = html + "</p>";
  html = html + "<div class=\"section\">Watchdog</div>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Reset\" onclick=\"sendOUT(1)\">";
  html = html + "</p>";
  html = html + "<div class=\"section\">Configuraci&oacuten</div>";
  html = html + "<p>";
  html = html + "  <a href=\"settings.htm\"><input type=\"button\" value=\"Red\"></a>";
  html = html + "  <a href=\"timeSettings.htm\"><input type=\"button\" value=\"Config\"></a>";
  //html = html + "  <input type=\"button\" value=\"Reset Timers\" onclick=\"sendOUT(20)\">";
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
  html = html + "<title>CHARGER MQTT+ #Configuraci&oacuten</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>CHARGER MQTT+ #Configuraci&oacuten<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  html = html + "<form method='get' action='setTimeSettings'>";

  html = html + "<div class=\"section\">Batt Charge</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label>Batt Transicion (ds)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgBattTds) + "\" name=\"battTsecs\"/></label>";
  html = html + "<label>Batt A (V)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgBattAvolts) + "\" name=\"battAvolts\"/></label>";
  html = html + "<label>Batt A (*15m)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgBattAmins) + "\" name=\"battAmins\"/></label>";
  html = html + "<label>Batt B (V)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgBattBvolts) + "\" name=\"battBvolts\"/></label>";
  html = html + "<label>Batt B (*15m)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgBattBmins) + "\" name=\"battBmins\"/></label>";
  html = html + "<label>Batt C (V)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgBattCvolts) + "\" name=\"battCvolts\"/></label>";
  html = html + "<label>Batt C (*15m)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgBattCmins) + "\" name=\"battCmins\"/></label>";
  html = html + "</div>";

  html = html + "<div class=\"section\">Logica</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Salidas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicIns) + "\" name=\"cfgIns\"/></label>";
  html = html + "<label> Entradas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicOuts) + "\" name=\"cfgOuts\"/></label>";
  html = html + "</div>";

  html = html + "<div class=\"section\"><span>3</span>vBat ADC: y = mx +/- b</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label>ADC recta:m <input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCm) + "\" name=\"rADCm\"/></label>";
  html = html + "<label>ADC recta:b (/1000) <input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCb) + "\" name=\"rADCb\"/></label>";
  html = html + "<label>ADC recta:prscal <input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCp) + "\" name=\"rADCp\"/></label>";
  html = html + "<label>ADC signo (+/-  1/0)<input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCs) + "\" name=\"rADCs\"/></label>";
  html = html + "<label>ADC filtro (si/no 1/0)<input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCf) + "\" name=\"rADCf\"/></label>";
  html = html + "</div>";
  /*
  html = html + "<div class=\"section\">Debug</div>";
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

  String rbattTsecs  = httpServer.arg("battTsecs");
  String rbattAvolts = httpServer.arg("battAvolts");
  String rbattAmins  = httpServer.arg("battAmins");
  String rbattBvolts = httpServer.arg("battBvolts");
  String rbattBmins  = httpServer.arg("battBmins");
  String rbattCvolts = httpServer.arg("battCvolts");
  String rbattCmins  = httpServer.arg("battCmins");
  
  String cfgIns    = httpServer.arg("cfgIns");
  String cfgOuts   = httpServer.arg("cfgOuts");
  
  String rADCm     = httpServer.arg("rADCm");
  String rADCb     = httpServer.arg("rADCb");
  String rADCp     = httpServer.arg("rADCp");
  String rADCs     = httpServer.arg("rADCs");
  String rADCf     = httpServer.arg("rADCf");
  
  //String rdebugVal = httpServer.arg("tdebugVal");
  
  int error = 0;

  if ((rbattTsecs.length() == 0)  ||
      (rbattAvolts.length() == 0) ||
      (rbattAmins.length() == 0)  ||
      (rbattBvolts.length() == 0) ||
      (rbattBmins.length() == 0)  ||
      (rbattCvolts.length() == 0) ||
      (rbattCmins.length() == 0)  ||
      (cfgIns.length() == 0)      ||
      (cfgOuts.length() == 0)     ||
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
    cfgBattTds = rbattTsecs.toInt();
    cfgBattAvolts = rbattAvolts.toInt();
    cfgBattAmins = rbattAmins.toInt();
    cfgBattBvolts = rbattBvolts.toInt();
    cfgBattBmins = rbattBmins.toInt();
    cfgBattCvolts = rbattCvolts.toInt();
    cfgBattCmins = rbattCmins.toInt();
    
    cfgLogicIns = cfgIns.toInt();
    cfgLogicOuts = cfgOuts.toInt();

    cfgADCm = rADCm.toInt();
    cfgADCb = rADCb.toInt();
    cfgADCp = rADCp.toInt();
    cfgADCs = rADCs.toInt();
    cfgADCf = rADCf.toInt();
    
    //DebugVal = rdebugVal.toInt();
    
    #if (_HTTP_SERIAL_DEBUG_ == 1)  
    Serial.print("Batt salto: ");     Serial.print (cfgBattTds);         Serial.println(" ds");
    Serial.print("Batt A charge: ");  Serial.print (cfgBattAvolts);      Serial.println(" Volts");
    Serial.print("Batt A charge: ");  Serial.print (cfgBattAmins);       Serial.println(" *15 min");
    Serial.print("Batt B charge: ");  Serial.print (cfgBattBvolts);      Serial.println(" Volts");
    Serial.print("Batt B charge: ");  Serial.print (cfgBattBmins);       Serial.println(" *15 min");
    Serial.print("Batt C charge: ");  Serial.print (cfgBattCvolts);      Serial.println(" Volts");
    Serial.print("Batt C charge: ");  Serial.print (cfgBattCmins);       Serial.println(" *15 min");
  
    Serial.print("Logic Ins: ");     Serial.println(cfgLogicIns);
    Serial.print("Logic Outs: ");    Serial.println(cfgLogicOuts);
  
    Serial.print("ADC m: ");         Serial.print (cfgADCm);            Serial.println(" ");
    Serial.print("ADC b: ");         Serial.print (cfgADCb);            Serial.println(" /1000");
    Serial.print("ADC p: ");         Serial.print (cfgADCp);            Serial.println(" ");
    Serial.print("ADC s: ");         Serial.print (cfgADCs);            Serial.println(" +/-  1/0");
    Serial.print("ADC f: ");         Serial.print (cfgADCf);            Serial.println(" si/no 1/0");
    #endif   

    // Data
    EEPROM.write(EEPROM_ADD_BATTA_VOLTS,  (byte)cfgBattAvolts);
    EEPROM.write(EEPROM_ADD_BATTA_MIN,    (byte)cfgBattAmins);
    EEPROM.write(EEPROM_ADD_BATTB_VOLTS,  (byte)cfgBattBvolts);
    EEPROM.write(EEPROM_ADD_BATTB_MIN,    (byte)cfgBattBmins);
    EEPROM.write(EEPROM_ADD_BATTC_VOLTS,  (byte)cfgBattCvolts);
    EEPROM.write(EEPROM_ADD_BATTC_MIN,    (byte)cfgBattCmins);
    
    EEPROM.write(EEPROM_ADD_LOGIC_INS,    (byte)cfgLogicIns);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS,   (byte)cfgLogicOuts);

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
  html = html + "<title>CHARGER MQTT+ #Configuraci&oacuten</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>CHARGER MQTT+ #Configuraci&oacuten<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  
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
  html = html + "<title>Network Settings</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>CHARGER MQTT+ #Network settings<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  //html = html + "<form method=\"post\">";
  html = html + "<form method='get' action='networSettings'>";

  // Wi-Fi
  html = html + "<div class=\"section\"><span>1</span>Wi-Fi Settings</div>";
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
  html = html + "<div class=\"section\"><span>2</span>IP Settings</div>";
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

  // If no error on data...
  if (error == 0)
  {
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
  html = html + "<title>CHARGER MQTT+ #Configuraci&oacuten</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>CHARGER MQTT+ #Configuraci&oacuten<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  
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
  html = html + "<td>Ins</td>";
  html = html + "<td>" + String(InD) + "-" + String(InC) + "-" + String(InB) + "-" + String(InA) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Vbatt In (Dig)</td>";
  html = html + "<td>" + String(VbattInADC) + "</td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>Vbatt In (V)</td>";
  html = html + "<td>" + String(VbattIn) + "</td>";
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
  html = html + "<td>Control Timeout (s) </td>";
  html = html + "<td>" + String((millis() - ControlTick)/1000) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Wi-Fi State </td>";
  html = html + "<td>" + String(wifiStatus) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>-----------------</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>OutBattA</td>";
  if (OutBattA == OUT_ON)
   html = html + "<td><font style=\"color:green\">Activado</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">Desactivado</font></td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>OutBattB</td>";
  if (OutBattB == OUT_ON)
   html = html + "<td><font style=\"color:green\">Activado</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">Desactivado</font></td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>OutBattC</td>";
  if (OutBattC == OUT_ON)
   html = html + "<td><font style=\"color:green\">Activado</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">Desactivado</font></td>";
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

  // OutBattA
  if(out_number == "10")
  {
    if (OutBattA == OUT_ON)
    {
      OutBattA = OUT_OFF;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("OutBattA OFF");
      #endif
      html = "OutBattA OFF";
    }
    else
    {
      OutBattA = OUT_ON;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("OutBattA ON");
      #endif
      html = "OutBattA ON";
    }
  }
  
  // OutBattB
  if(out_number == "11")
  {
    if (OutBattB == OUT_ON)
    {
      OutBattB = OUT_OFF;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("OutBattB OFF");
      #endif
      html = "OutBattB OFF";
    }
    else
    {
      OutBattB = OUT_ON;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("OutBattB ON");
      #endif
      html = "OutBattB ON";
    }
  }

  // OutBattC
  if(out_number == "12")
  {
    if (OutBattC == OUT_ON)
    {
      OutBattC = OUT_OFF;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("OutBattC OFF");
      #endif
      html = "OutBattC OFF";
    }
    else
    {
      OutBattC = OUT_ON;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("OutBattC ON");
      #endif
      html = "OutBattC ON";
    }
  }

  /*
  // Reset Timers
  if(out_number == "20")
  {
    _ResetEEPROM();
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Reset Timers");
    #endif
    html = "Reset Timers";
  }
  */
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
      httpServer.on("/style.css",        _serveCSS);

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
