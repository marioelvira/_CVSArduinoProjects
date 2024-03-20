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
  html = html + "<h1>" + PROJECT + " #Estado<span>ESP tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";

  html = html + "<div class=\"section\"><span>1</span>Sistema</div>";
  html = html + "<p class=\"sansserif\" id=\"TEMPSid\">...</p>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Reset\" onclick=\"sendOUT(1)\">";
  html = html + "  <input type=\"button\" value=\"Restore\" onclick=\"sendOUT(2)\">";
  html = html + "</p>";
 
  html = html + "<div class=\"section\"><span>3</span>Entradas</div>";
  html = html + "<p class=\"sansserif\" id=\"INSid\">...</p>";
  
  html = html + "<div class=\"section\"><span>4</span>Salidas</div>";
  html = html + "<p class=\"sansserif\" id=\"OUTSid\">...</p>";
  
  html = html + "<div class=\"section\"><span>5</span>ADCs</div>";
  html = html + "<p class=\"sansserif\" id=\"ADCSid\">...</p>";

  html = html + "<div class=\"section\"><span>6</span>Control</div>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Cambiar Modo\" onclick=\"sendOUT(0)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"0\" onclick=\"sendOUT(10)\">";
  html = html + "  <input type=\"button\" value=\"1\" onclick=\"sendOUT(11)\">";
  html = html + "  <input type=\"button\" value=\"2\" onclick=\"sendOUT(12)\">";
  html = html + "  <input type=\"button\" value=\"3\" onclick=\"sendOUT(13)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"0\" onclick=\"sendOUT(20)\">";
  html = html + "  <input type=\"button\" value=\"1\" onclick=\"sendOUT(21)\">";
  html = html + "  <input type=\"button\" value=\"2\" onclick=\"sendOUT(22)\">";
  html = html + "</p>";
  
  html = html + "<div class=\"section\"><span>7</span>Configuraci&oacuten</div>";
  html = html + "<p>";
  html = html + "  <a href=\"netSettings.htm\"><input type=\"button\" value=\"Red\"></a>";
  html = html + "  <a href=\"cfgSettings.htm\"><input type=\"button\" value=\"Config\"></a>";
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
  html = html + "  getADCS();";
  html = html + "  getSTATUS();";
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

  html = html + "function getADCS() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"ADCSid\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readADCS\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";

  html = html + "function getSTATUS() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"TEMPSid\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readSTATUS\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
  html = html + "</script>";

  html = html + "</form>";
  html = html + "</div>";
  
  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

// Cfg Settings
void _serveCfgSETTINGS()
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
  html = html + "<h1>" + PROJECT + " #Config<span>ESP tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
  html = html + "<form method='get' action='setCfgSettings'>";

  html = html + "<div class=\"section\"><span>1</span>Logica</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Entradas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicIns) + "\" name=\"cfgIns\"/></label>";
  html = html + "<label> Salidas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicOuts) + "\" name=\"cfgOuts\"/></label>";
  html = html + "<label> Tiempo Salidas <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimefOuts) + "\" name=\"cfgTfOuts\"/></label>";
  html = html + "</div>";

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

void _setCfgSETTINGS()
{
  int eeprom_value_hi, eeprom_value_lo;
    
  String html = "";
  
  String rcfgIns          = httpServer.arg("cfgIns");
  String rcfgOuts         = httpServer.arg("cfgOuts");
  String rcfgTimefOuts    = httpServer.arg("cfgTfOuts");
  
  int error = 0;

  if ((rcfgIns.length() == 0)     ||
      (rcfgOuts.length() == 0)    ||
      (rcfgTimefOuts.length() == 0))
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
    cfgTimefOuts = rcfgTimefOuts.toInt();
        
    //DebugVal = rdebugVal.toInt();
    
    #if (_HTTP_SERIAL_DEBUG_ == 1)  
    Serial.print("cfgLogic Ins: ");  Serial.println(cfgLogicIns);
    Serial.print("cfgLogic Outs: "); Serial.println(cfgLogicOuts);  
    Serial.print("Time for Outs: "); Serial.println(cfgTimefOuts);
    #endif   

    // Data 
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  (byte)cfgLogicIns);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, (byte)cfgLogicOuts);

    eeprom_value_lo = cfgTimefOuts & 0x00FF;
    EEPROM.write(EEPROM_ADD_TIMEF_OUTS_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgTimefOuts & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_TIMEF_OUTS_HI, eeprom_value_hi);

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
  html = html + "<h1>" + PROJECT + " #Config<span>ESP tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
  
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

// Network Settings
void _serveNetSETTINGS()
{
  String html = "";
  
  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>" + PROJECT + " Red Config</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #Red Config<span>ESP tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
  //html = html + "<form method=\"post\">";
  html = html + "<form method='get' action='setNetSettings'>";

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

void _setNetSETTINGS()
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
  html = html + "<title>" + PROJECT + " Config</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #Config<span>ESP tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
  
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
  html = html + "<td>Board Ins</td>";
  html = html + "<td>" + String(InDig[0]) + "-" + String(InDig[1]) + "-" + String(InDig[2]) + "-" + String(InDig[3]) + "</td>";
  html = html + "</tr>";
  
  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

void _readADCS()
{ 
  String html = "";

  html = "<table style=\"width:100%\">";

  html = html + "<tr>";
  html = html + "<td>A0</td>";
  html = html + "<td>" + String(AdcDig[0]) + "</td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>A1</td>";
  html = html + "<td>" + String(AdcDig[1]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>A2</td>";
  html = html + "<td>" + String(AdcDig[2]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>A3</td>";
  html = html + "<td>" + String(AdcDig[3]) + "</td>";
  html = html + "</tr>";

  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

void _readOUTS()
{
  String html = "";

  html = "<table style=\"width:100%\">";
  
  html = html + "<tr>";
  html = html + "<td>Board Outs</td>";
  html = html + "<td>" + String(OutDig[0]) + "-" + String(OutDig[1]) + "-" + String(OutDig[2]) + "-" + String(OutDig[3]) + "</td>";
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

  // Out 0
  if ((out_number == "10") ||
      (out_number == "11") ||
      (out_number == "12") ||
      (out_number == "13"))
  {
    int out;

    if (out_number == "10")
      out = 0;
    else if (out_number == "11")
      out = 1;
    else if (out_number == "12")
      out = 2;
    else
      out = 3;

    if (OutDig[out] == OUT_ON)
    {
      OutDig[out] = OUT_OFF;
      html = "Out OFF";
    }
    else
    {
      OutDig[out] = OUT_ON;
      html = "Out ON";
    }
  }
  else
    html = "NO Outs";

  // Out 0
  if ((out_number == "20") ||
      (out_number == "21") ||
      (out_number == "22"))
  {
    int out;

    if (out_number == "20")
      out = 0;
    else if (out_number == "21")
      out = 1;
    else
      out = 2;

    if (rgbDig[out] == OUT_ON)
    {
      rgbDig[out] = OUT_OFF;
      html = "RGB OFF";
    }
    else
    {
      rgbDig[out] = OUT_ON;
      html = "RGB ON";
    }
  }
  else
    html = "NO RGB";

  httpServer.send(200, "text/plane", html);
}

void _readSTATUS()
{ 
  String html = "";

  html = "<table style=\"width:100%\">";
  
  html = html + "<tr>";
  html = html + "<td>Tiempo Encendio</td>";
  html = html + "<td>" + String(timeDay) + "d " + timeOnString + "</td>";
  html = html + "</tr>";
  
  #if (_USE_FREERAM_ == 1)
  html = html + "<tr>";
  html = html + "<td>Free RAM</td>";
  html = html + "<td>" + String(freeRam) + "</td>";
  html = html + "</tr>";
  #endif

  html = html + "<tr>";
  html = html + "<td>Wi-Fi </td>";
  html = html + "<td>" + String(wifiStatus) + "</td>";
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
      httpServer.on("/netSettings.htm",   _serveNetSETTINGS);
      httpServer.on("/cfgSettings.htm",   _serveCfgSETTINGS);

      // acctions
      httpServer.on("/setOUTS",          _setOUTS);      
      httpServer.on("/readOUTS",         _readOUTS);
      httpServer.on("/readINS",          _readINS);
      httpServer.on("/readADCS",         _readADCS);
      httpServer.on("/readSTATUS",       _readSTATUS);
      httpServer.on("/setNetSettings",   _setNetSETTINGS);
      httpServer.on("/setCfgSettings",   _setCfgSETTINGS);

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
