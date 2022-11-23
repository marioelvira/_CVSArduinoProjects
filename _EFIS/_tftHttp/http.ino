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
  html = html + "<title>" + PROJECT + " #Project</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #State<span>ESP32 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";

  html = html + "<div class=\"section\">Timers</div>";
  html = html + "<p class=\"sansserif\" id=\"TEMPSid\">...</p>";
  html = html + "<div class=\"section\">INs</div>";
  html = html + "<p class=\"sansserif\" id=\"INSid\">...</p>";
  //html = html + "<div class=\"section\">OUTs</div>";
  //html = html + "<p class=\"sansserif\" id=\"OUTSid\">...</p>";
  html = html + "<div class=\"section\">Control</div>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Change Mode\" onclick=\"sendOUT(0)\">";
  //html = html + "</p><p>";
  //html = html + "  <input type=\"button\" value=\"OUT01\" onclick=\"sendOUT(11)\">";
  //html = html + "  <input type=\"button\" value=\"OUT02\" onclick=\"sendOUT(12)\">";
  html = html + "</p>";
  html = html + "<div class=\"section\">Watchdog</div>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Reset\" onclick=\"sendOUT(1)\">";
  html = html + "</p>";
  html = html + "<div class=\"section\">Configuraci&oacuten</div>";
  html = html + "<p>";
  //html = html + "  <a href=\"settings.htm\"><input type=\"button\" value=\"Wi-Fi\"></a>";
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
  //html = html + "  getOUTS();";
  html = html + "  getINS();";
  html = html + "  getTEMPS();";
  html = html + "}, 1000);";
  /*
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
  */
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
  html = html + "<title>" + PROJECT + " #Project</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #Config<span>ESP32 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
  html = html + "<form method='get' action='setTimeSettings'>";

  // Temporizaciones 
  html = html + "<div class=\"section\"><span>2</span>Temps Generador</div>";
  html = html + "<div class=\"inner-wrap\">";
  
  html = html + "<label>Tiempo P1 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(TimeGenerador1P) + "\" name=\"time1\"/></label>";
  html = html + "<label>Tiempo P2 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(TimeGenerador2P) + "\" name=\"time2\"/></label>";
  html = html + "<label>Tiempo P3 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(TimeGenerador3P) + "\" name=\"time3\"/></label>";
  html = html + "<label>Tiempo P4 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(TimeGenerador4P) + "\" name=\"time4\"/></label>";
  html = html + "<label>Tiempo P5 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(TimeGenerador5P) + "\" name=\"time5\"/></label>";
  html = html + "<label>Tiempo P6 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(TimeGenerador6P) + "\" name=\"time6\"/></label>";
  html = html + "<label>Tiempo P7 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(TimeGenerador7P) + "\" name=\"time7\"/></label>";
  html = html + "<label>Tiempo P8 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(TimeGenerador8P) + "\" name=\"time8\"/></label>";
  html = html + "<label>Tiempo P9 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(TimeGenerador9P) + "\" name=\"time9\"/></label>";
  
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

void _setTimeSETTINGS()
{
  String html = "";
  
  String rtime1 = httpServer.arg("time1");
  String rtime2 = httpServer.arg("time2");
  String rtime3 = httpServer.arg("time3");
  String rtime4 = httpServer.arg("time4");
  String rtime5 = httpServer.arg("time5");
  String rtime6 = httpServer.arg("time6");
  String rtime7 = httpServer.arg("time7");
  String rtime8 = httpServer.arg("time8");
  String rtime9 = httpServer.arg("time9");

  int error = 0;

  if ((rtime1.length() == 0)  ||
      (rtime2.length() == 0)  ||
      (rtime3.length() == 0)  ||
      (rtime4.length() == 0)  ||
      (rtime5.length() == 0)  ||
      (rtime6.length() == 0)  ||
      (rtime7.length() == 0)  ||
      (rtime8.length() == 0)  ||
      (rtime9.length() == 0))
  {
    error = 1;  // falta un campo...
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Error... parametro vacío.");
    #endif
  }

  // Si no hay error...
  if (error == 0)
  {   
    TimeGenerador1P = rtime1.toInt();
    TimeGenerador2P = rtime2.toInt();
    TimeGenerador3P = rtime3.toInt();
    TimeGenerador4P = rtime4.toInt();
    TimeGenerador5P = rtime5.toInt();
    TimeGenerador6P = rtime6.toInt();
    TimeGenerador7P = rtime7.toInt();
    TimeGenerador8P = rtime8.toInt();
    TimeGenerador9P = rtime9.toInt();
    
    #if (_HTTP_SERIAL_DEBUG_ == 1)  
    
    Serial.print("Time 1P: ");  Serial.print (TimeGenerador1P);  Serial.println(" min");
    Serial.print("Time 2P: ");  Serial.print (TimeGenerador2P);  Serial.println(" min");
    Serial.print("Time 3P: ");  Serial.print (TimeGenerador3P);  Serial.println(" min");
    Serial.print("Time 4P: ");  Serial.print (TimeGenerador4P);  Serial.println(" min");
    Serial.print("Time 5P: ");  Serial.print (TimeGenerador5P);  Serial.println(" min");
    Serial.print("Time 6P: ");  Serial.print (TimeGenerador6P);  Serial.println(" hour");
    Serial.print("Time 7P: ");  Serial.print (TimeGenerador7P);  Serial.println(" hour");
    Serial.print("Time 8P: ");  Serial.print (TimeGenerador8P);  Serial.println(" hour");
    Serial.print("Time 9P: ");  Serial.print (TimeGenerador9P);  Serial.println(" hour");

    #endif   
    
    EEPROM.write(EEPROM_ADD_1P_TIMER_GEN,   TimeGenerador1P);
    EEPROM.write(EEPROM_ADD_2P_TIMER_GEN,   TimeGenerador2P);
    EEPROM.write(EEPROM_ADD_3P_TIMER_GEN,   TimeGenerador3P);
    EEPROM.write(EEPROM_ADD_4P_TIMER_GEN,   TimeGenerador4P);
    EEPROM.write(EEPROM_ADD_5P_TIMER_GEN,   TimeGenerador5P);
    EEPROM.write(EEPROM_ADD_6P_TIMER_GEN,   TimeGenerador6P);
    EEPROM.write(EEPROM_ADD_7P_TIMER_GEN,   TimeGenerador7P);
    EEPROM.write(EEPROM_ADD_8P_TIMER_GEN,   TimeGenerador8P);
    EEPROM.write(EEPROM_ADD_9P_TIMER_GEN,   TimeGenerador9P);

    EEPROM.commit();    //Store data to EEPROM
  }

  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>" + PROJECT + " #Project</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #Config<span>ESP32 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
  
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
  html = html + "<title>" + PROJECT + " #Project</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #Network Config<span>ESP32 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
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
  html = html + "<title>" + PROJECT + " #Project</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>" + PROJECT + " #Network Config<span>ESP32 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
  
  if (i == 200)
    html += "<p>Settings OK: Saved</p>";
  else
    html += "<p>Settings Error: Not Saved</p>";

  html = html + "<div class=\"button-section\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Back\"></a>";
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

  _analogOnString();
    
  html = "<table style=\"width:100%\">";

  html = html + "<tr>";
  html = html + "<td>Analog</td>";
  html = html + "<td><font>" + sAnalog + "</font></td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>In IO1</td>";
  if (boardIO1 == IO_ON)
   html = html + "<td><font style=\"color:green\">ON</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">OFF</font></td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>In IO2</td>";
  if (boardIO2 == IO_ON)
   html = html + "<td><font style=\"color:green\">ON</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">OFF</font></td>";
  html = html + "</tr>";
  
  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}
/*
void _readOUTS()
{
  String html = "";

  html = "<table style=\"width:100%\">";
  
  html = html + "<tr>";
  html = html + "<td>In IO1</td>";
  if (boardIO1 == OUT_ON)
   html = html + "<td><font style=\"color:green\">ON</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">OFF</font></td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>In IO2</td>";
  if (boardIO2 == OUT_ON)
   html = html + "<td><font style=\"color:green\">ON</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">OFF</font></td>";
  html = html + "</tr>";
  
  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}
*/
void _setOUTS()
{
  String out_number = httpServer.arg("OUTNumber");
  String html = "";
 
  #if (_HTTP_SERIAL_DEBUG_ == 1)
  Serial.print("Change stats out: ");
  Serial.println(out_number);
  #endif

  // Change Mode
  if(out_number == "0")
  {
    if (ctrMode == MODE_TEST)
    {
      ctrMode = MODE_AUTO;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Mode Auto");
      #endif
      html = "Mode Auto";
    }
    else
    {
      ctrMode = MODE_TEST;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Mode Test");
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

  // Reset EEPROM
  if(out_number == "20")
  {
    _ResetEEPROM();
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Reset EEPROM");
    #endif
    html = "Reset EEPROM";
  }
  
  httpServer.send(200, "text/plane", html);
}

void _readTEMPS()
{ 
  String html = "";

  html = "<table style=\"width:100%\">";
  
  html = html + "<tr>";
  html = html + "<td>Time ON</td>";
  html = html + "<td>" + timeOnString + "</td>";
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
      //httpServer.on("/readOUTS",       _readOUTS);
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
