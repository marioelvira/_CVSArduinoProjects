#include "main.h"

#if (_USE_HTTP_ == 1)
void _HTTPSetup(void)
{
  httpStatus = HTTP_STOP;
}

void _HTTPStart(void)
{
  httpStatus = HTTP_START;
}

void _HTTPStop(void)
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
  html = html + "<h1>" + PROJECT + " #Estado<span>" + TECHNOLOGY + "</span><span align=\"right\"> " + compdate + " " + comptime + "</span></h1>";

  html = html + "<div class=\"section\"><span>1</span>Sistema</div>";
  html = html + "<p class=\"sansserif\" id=\"STATUSSid\">...</p>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Reset\" onclick=\"sendOUT(1)\">";
  html = html + "  <input type=\"button\" value=\"Restore\" onclick=\"sendOUT(2)\">";
  html = html + "</p>";

  html = html + "<div class=\"section\"><span>2</span>Control</div>";
  html = html + "<p class=\"sansserif\" id=\"CTRid\">...</p>";
  
  html = html + "<div class=\"section\"><span>3</span>Entradas</div>";
  html = html + "<p class=\"sansserif\" id=\"INSid\">...</p>";
  
  html = html + "<div class=\"section\"><span>4</span>Salidas</div>";
  html = html + "<p class=\"sansserif\" id=\"OUTSid\">...</p>";

  html = html + "<div class=\"section\"><span>5</span>Test</div>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Cambiar Modo\" onclick=\"sendOUT(0)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"0\" onclick=\"sendOUT(10)\">";
  html = html + "  <input type=\"button\" value=\"1\" onclick=\"sendOUT(11)\">";
  html = html + "</p>";

  html = html + "<div class=\"section\"><span>6</span>Configuraci&oacuten</div>";
  html = html + "<p>";
  html = html + "  <a href=\"network.htm\"><input type=\"button\" value=\"Red\"></a>";
  html = html + "  <a href=\"settings.htm\"><input type=\"button\" value=\"Parametros\"></a>";
  html = html + "</p>"; 
  html = html + "</div>";

  html = html + "<script>";
  
  html = html + "function sendOUT(out) {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.open(\"GET\", \"setOUTS?OUTNumber=\"+out, true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
  html = html + "setInterval(function() {";
  html = html + "  getCTR();";
  html = html + "  getOUTS();";
  html = html + "  getINS();";
  html = html + "  getSTATUS();";
  html = html + "}, 1000);";
  
  html = html + "function getCTR() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"CTRid\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readCTR\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
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
  
  html = html + "function getSTATUS() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"STATUSSid\").innerHTML = this.responseText;";
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

// Settings
void _serveSETTINGS()
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
  html = html + "<h1>" + PROJECT + " #Config<span>" + TECHNOLOGY + "</span><span align=\"right\"> " + compdate + " " + comptime + "</span></h1>";

  html = html + "<form method='get' action='settingsSet'>";

  html = html + "<div class=\"section\"><span>1</span>Control</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Tension Principal (Voltios)<input type=\"text\"  maxlength=\"16\" value=\""  + String(cfgResPrimVout)     + "\" name=\"cfgResPrimVout\"/></label>";
  html = html + "<label> Tension Inyectior (Voltios)<input type=\"text\"  maxlength=\"16\" value=\""  + String(cfgResInyeVout)     + "\" name=\"cfgResInyeVout\"/></label>";
  html = html + "<label> Temp Arranque Inyectior (ºC)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgResPrimInyeTemp) + "\" name=\"cfgResPrimInyeTemp\"/></label>";
  html = html + "<label> Temp Consigna Principal (ºC)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgResPrimConsTemp) + "\" name=\"cfgResPrimConsTemp\"/></label>";
  html = html + "<label> Temp Hist Principal (ºC)<input type=\"text\"  maxlength=\"16\" value=\""     + String(cfgResPrimHystTemp) + "\" name=\"cfgResPrimHystTemp\"/></label>";
  html = html + "<label> Temp Consigna Inyectior (ºC)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgResInyeConsTemp) + "\" name=\"cfgResInyeConsTemp\"/></label>";
  html = html + "<label> Temp Hist Inyectior (ºC)<input type=\"text\"  maxlength=\"16\" value=\""     + String(cfgResInyeHystTemp) + "\" name=\"cfgResInyeHystTemp\"/></label>";
  html = html + "<label> Temp Consigna Agua (ºC)<input type=\"text\"  maxlength=\"16\" value=\""      + String(cfgAguaConsTemp)    + "\" name=\"cfgAguaConsTemp\"/></label>";
  html = html + "<label> Temp Hist Agua (ºC)<input type=\"text\"  maxlength=\"16\" value=\""          + String(cfgAguaHystTemp)    + "\" name=\"cfgAguaHystTemp\"/></label>";
  html = html + "</div>";

  html = html + "<div class=\"section\"><span>2</span>Alarmas</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Alarma Principal (Minutos)<input type=\"text\"  maxlength=\"3\" value=\""  + String(cfgResPrimAlarMin)    + "\" name=\"cfgResPrimAlarMin\"/></label>";
  html = html + "<label> Alarma Inyectior (Minutos)<input type=\"text\"  maxlength=\"3\" value=\""  + String(cfgResInyeAlarMin)    + "\" name=\"cfgResInyeAlarMin\"/></label>";
  html = html + "<label> Alarma Agua (Minutos)<input type=\"text\"  maxlength=\"3\" value=\""       + String(cfgAguaAlarMin)       + "\" name=\"cfgAguaAlarMin\"/></label>";
  html = html + "</div>";

  html = html + "<div class=\"section\"><span>3</span>Logica</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Entradas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicIns) + "\" name=\"cfgLogicIns\"/></label>";
  html = html + "<label> Salidas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicOuts) + "\" name=\"cfgLogicOuts\"/></label>";
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

void _setSETTINGS()
{
  int eeprom_value_hi, eeprom_value_lo;
    
  String html = "";
  
  String scfgResPrimVout     = httpServer.arg("cfgResPrimVout");
  String scfgResInyeVout     = httpServer.arg("cfgResInyeVout");
  String scfgResPrimInyeTemp = httpServer.arg("cfgResPrimInyeTemp");
  String scfgResPrimConsTemp = httpServer.arg("cfgResPrimConsTemp");
  String scfgResPrimHystTemp = httpServer.arg("cfgResPrimHystTemp");
  String scfgResInyeHystTemp = httpServer.arg("cfgResInyeHystTemp");
  String scfgAguaConsTemp    = httpServer.arg("cfgAguaConsTemp");
  String scfgAguaHystTemp    = httpServer.arg("cfgAguaHystTemp");

  String scfgResPrimAlarMin  = httpServer.arg("cfgResPrimAlarMin");
  String scfgResInyeAlarMin  = httpServer.arg("cfgResInyeAlarMin");
  String scfgAguaAlarMin     = httpServer.arg("cfgAguaAlarMin");

  String scfgLogicIns        = httpServer.arg("cfgLogicIns");
  String scfgLogicOuts       = httpServer.arg("cfgLogicOuts");

  //String rdebugVal = httpServer.arg("tdebugVal");
  
  int error = 0;

  if ((scfgResPrimVout.length() == 0)     ||
      (scfgResInyeVout.length() == 0)     ||
      (scfgResPrimInyeTemp.length() == 0) ||
      (scfgResPrimConsTemp.length() == 0) ||
      (scfgResPrimHystTemp.length() == 0) ||
      (scfgResInyeHystTemp.length() == 0) ||
      (scfgAguaConsTemp.length() == 0)    ||
      (scfgAguaHystTemp.length() == 0)    ||

      (scfgResPrimAlarMin.length() == 0)  ||
      (scfgResInyeAlarMin.length() == 0)  ||
      (scfgAguaAlarMin.length() == 0)     ||

      (scfgLogicIns.length() == 0)        ||
      (scfgLogicOuts.length() == 0))

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
    cfgResPrimVout     = scfgResPrimVout.toInt();
    cfgResInyeVout     = scfgResInyeVout.toInt();
    cfgResPrimInyeTemp = scfgResPrimInyeTemp.toInt();
    cfgResPrimConsTemp = scfgResPrimConsTemp.toInt();
    cfgResPrimHystTemp = scfgResPrimHystTemp.toInt();
    cfgResInyeHystTemp = scfgResInyeHystTemp.toInt();
    cfgAguaConsTemp    = scfgAguaConsTemp.toInt();
    cfgAguaHystTemp    = scfgAguaHystTemp.toInt();

    cfgResPrimAlarMin  = scfgResPrimAlarMin.toInt();
    cfgResInyeAlarMin  = scfgResInyeAlarMin.toInt();
    cfgAguaAlarMin     = scfgAguaAlarMin.toInt();

    cfgLogicIns  = scfgLogicIns.toInt();
    cfgLogicOuts = scfgLogicOuts.toInt();

    //DebugVal = rdebugVal.toInt();
    
    _ram2eepromCONFIG();
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
  html = html + "<h1>" + PROJECT + " #Config<span>" + TECHNOLOGY + "</span><span align=\"right\"> " + compdate + " " + comptime + "</span></h1>";
  
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
void _serveNETWORK()
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
  html = html + "<h1>" + PROJECT + " #Red<span>" + TECHNOLOGY + "</span><span align=\"right\"> " + compdate + " " + comptime + "</span></h1>";
  //html = html + "<form method=\"post\">";
  html = html + "<form method='get' action='networkSet'>";

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

  #if (_USE_MQTT_ == 1)
  // Broker
  html = html + "<div class=\"section\"><span>3</span>Broker </div>";
  html = html + "<div class=\"inner-wrap\">";

  html = html + "<label>Url <input type=\"text\" maxlength=\"30\" value=\"" + String(brokerUrl) + "\" name=\"brokerurl\"/></label>";
  html = html + "<label>Port <input type=\"text\" maxlength=\"16\" value=\"" + String(brokerPort) + "\" name=\"brokerport\"/></label>";
  html = html + "<label>User <input type=\"text\" maxlength=\"30\" value=\"" + String(brokerUser) + "\" name=\"brokeruser\"/></label>";
  html = html + "<label>Pswd <input type=\"text\" maxlength=\"30\" value=\"" + String(brokerPswd) + "\" name=\"brokerpswd\"/></label>";

  html = html + "</div>";
  // End
  #endif

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

void _setNETWORK()
{
  String ripmode = httpServer.arg("ipmode");
  String ripaddress = httpServer.arg("ipaddress");
  String rmask = httpServer.arg("mask");
  String rgate = httpServer.arg("gateway");
  
  #if (_USE_MQTT_ == 1)
  String rbrokerurl = httpServer.arg("brokerurl");
  String rbrokerport = httpServer.arg("brokerport");
  String rbrokeruser = httpServer.arg("brokeruser");
  String rbrokerpswd = httpServer.arg("brokerpswd");
  #endif
 
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

  #if (_USE_MQTT_ == 1)
  // Check broker error
  if ((rbrokerurl.length() == 0)  ||
      (rbrokerport.length() == 0) ||
      (rbrokeruser.length() == 0) ||
      (rbrokerpswd.length() == 0))
    error = 1;
  #endif

  // If no error on data...
  if (error == 0)
  {
    #if (_USE_MQTT_ == 1)
    // Broker Url
    for (i = 0; i < MQTT_URL_MAX; i++)
      EEPROM.write(EEPROM_ADD_BROKER + i, 0);
    j = rbrokerurl.length();
    for (i = 0; i < j; i++)
      EEPROM.write(EEPROM_ADD_BROKER + i, rbrokerurl[i]);
    // Broker Port   
    brokerPort = rbrokerport.toInt();
    eeprom_value_lo = brokerPort & 0x00FF;
    EEPROM.write(EEPROM_ADD_BROKER_PORT, eeprom_value_lo);
    eeprom_value_hi = (brokerPort & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_BROKER_PORT + 1, eeprom_value_hi);
    // Broker User
    for (i = 0; i < MQTT_USER_MAX; i++)
      EEPROM.write(EEPROM_ADD_MQTT_USER + i, 0);
    j = rbrokeruser.length();
    for (i = 0; i < j; i++)
      EEPROM.write(EEPROM_ADD_MQTT_USER + i, rbrokeruser[i]);
    // Broker Password
    for (i = 0; i < MQTT_PSWD_MAX; i++)
      EEPROM.write(EEPROM_ADD_MQTT_PSWD + i, 0);
    j = rbrokerpswd.length();
    for (i = 0; i < j; i++)
      EEPROM.write(EEPROM_ADD_MQTT_PSWD + i, rbrokerpswd[i]);

    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.print("---->Broker Url: ");
    Serial.println(rbrokerurl);
    Serial.print("---->Broker Port: ");
    Serial.println(rbrokerport);     
    #endif

    #endif // _USE_MQTT_
     
    /////////////
    // IP Mpde //
    /////////////
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

    // OK
    i = 200;

    #if (_HTTP_SERIAL_DEBUG_ == 1)
    // IP configuration
    Serial.print("---->Local IP: ");
    Serial.println(localip);
    Serial.print("---->Local mask: ");
    Serial.println(localmask);
    Serial.print("---->Local gateway: ");
    Serial.println(localgate);
    #endif // (_HTTP_SERIAL_DEBUG_ == 1)

    EEPROM.commit();

    #if (_READ_EEPROM_ == 1)
    _ReadEEPROM();
    delay(1000);
    #endif
    
    // Read config from EEPROM
    _readCONFIG();
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
  html = html + "<h1>" + PROJECT + " #Config<span>" + TECHNOLOGY + "</span><span align=\"right\"> " + compdate + " " + comptime + "</span></h1>";
  
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
void _readCTR()
{
  String html = "";
  int aux;

  html = "<table style=\"width:100%\">";

  html = html + "<tr>";
  html = html + "<td>Modo</td>";
  if (ctrMode == MODE_AUTO)
   html = html + "<td><font style=\"color:blue\">Autom&aacutetico</font></td>";
  else
   html = html + "<td><font style=\"color:red\">Test</font></td>";
  html = html + "</tr>";

  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

void _readINS()
{ 
  String html = "";

  html = "<table style=\"width:100%\">";

  html = html + "<tr>";
  html = html + "<td>Boards Ins</td>";
  html = html + "<td>" + String(InDig[0]) + "-" + String(InDig[1]) + "</td>";
  html = html + "</tr>";
  
  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

void _readOUTS()
{
  String html = "";

  html = "<table style=\"width:100%\">";
  
  html = html + "<tr>";
  html = html + "<td>Boards Outs</td>";
  html = html + "<td>" + String(OutDig[0]) + "-" + String(OutDig[1]) + "</td>";
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
    if (ctrMode == MODE_TEST)
    {
      ctrMode = MODE_AUTO;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Modo Auto");
      #endif
      html = "Modo Auto";
    }
    else
    {
      ctrMode = MODE_TEST;
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

  // Solo en modo Test
  if (ctrMode == MODE_TEST)
  {   
    // Out 0
    if(out_number == "10")
    {
      if (OutDig[0] == OUT_ON)
      {
        OutDig[0] = OUT_OFF;
        html = "Out 0 OFF";
      }
      else
      {
        OutDig[0] = OUT_ON;
        html = "Out 0 ON";
      }
    }
    // Out 1
    else if(out_number == "11")
    {
      if (OutDig[1] == OUT_ON)
      {
        OutDig[1] = OUT_OFF;
        html = "Out 1 OFF";
      }
      else
      {
        OutDig[1] = OUT_ON;
        html = "Out 1 ON";
      }
    }
  }
  else
    html = "NO Outs";
  
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
  
  #if (_USE_NTP_ == 1)
  html = html + "<tr>";
  html = html + "<td>Fecha NTP</td>";
  html = html + "<td>" + mntpTimeString + "</td>";
  html = html + "</tr>";
  #endif
  
  #if (_USE_MQTT_ == 1)
  html = html + "<tr>";
  html = html + "<td>MQTT </td>";
  html = html + "<td>" + String(mqttStatus) + "</td>";
  html = html + "</tr>";
  #endif

  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

void _pageNotFound() {
  httpServer.send(404, "text/plain", "404: No found");
}

///////////////
// Http loop //
///////////////
void _HTTPLoop()
{
  switch (httpStatus)
  {
    case HTTP_START:

      // css Style
      httpServer.on("/style.css",   _serveCSS);

      // html pages
      httpServer.on("/",             _serveMAIN);
      httpServer.on("/index.htm",    _serveMAIN);
      httpServer.on("/network.htm",  _serveNETWORK);
      httpServer.on("/settings.htm", _serveSETTINGS);

      // config
      httpServer.on("/networkSet",   _setNETWORK);
      httpServer.on("/settingsSet",  _setSETTINGS);

      // acctions
      httpServer.on("/readCTR",      _readCTR);
      httpServer.on("/setOUTS",      _setOUTS);      
      httpServer.on("/readOUTS",     _readOUTS);
      httpServer.on("/readINS",      _readINS);
      httpServer.on("/readSTATUS",   _readSTATUS);

      // Error
      httpServer.onNotFound(_pageNotFound);

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

    case HTTP_STOP:
      break;
  }
}

#endif
