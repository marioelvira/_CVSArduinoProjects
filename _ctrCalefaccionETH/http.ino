#include "main.h"

#if (_USE_HTTP_ == 1)

/*
void _setTimeSETTINGS()
{
  int eeprom_value_hi, eeprom_value_lo;
    
  String html = "";

  String rscaleMIN = httpServer.arg("scaleMIN");
  String rtimeFAN  = httpServer.arg("timeFAN");
  String rtimePUMP = httpServer.arg("timePUMP");
  String rtimeIRRI = httpServer.arg("timeIRRI");
  
  String cfgIns    = httpServer.arg("cfgIns");
  String cfgOuts   = httpServer.arg("cfgOuts");
  
  String rADCf     = httpServer.arg("rADCf");

  String rTempHi       = httpServer.arg("tempHi");
  String rTempLo       = httpServer.arg("tempLo");
  String rTimeOpenMin  = httpServer.arg("timeOpenMin");
  String rTimeCloseMin = httpServer.arg("timeCloseMin");
  String rTimeCicloMin = httpServer.arg("timeCicloMin");
  
  String rFanTempHi    = httpServer.arg("fanTempHi");
  String rFanTempLo    = httpServer.arg("fanTempLo");

  //String rdebugVal = httpServer.arg("tdebugVal");
  
  int error = 0;

  if ((rscaleMIN.length() == 0) ||
      (rtimeFAN.length() == 0)  ||
      (rtimePUMP.length() == 0) ||
      (rtimeIRRI.length() == 0) ||
      
      (cfgIns.length() == 0)    ||
      (cfgOuts.length() == 0)   ||
      
      (rADCf.length() == 0)     ||

      (rTempHi.length() == 0)       ||
      (rTempLo.length() == 0)       ||
      (rTimeOpenMin.length() == 0)  ||
      (rTimeCloseMin.length() == 0) ||
      (rTimeCicloMin.length() == 0) ||
      
      (rFanTempHi.length() == 0)    ||
      (rFanTempLo.length() == 0))
  {
    error = 1;  // falta un campo...
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Error... parametro vacío.");
    #endif
  }

  // Si no hay error...
  if (error == 0)
  {
    cfgScaleMin = rscaleMIN.toInt();
    cfgFanTick  = rtimeFAN.toInt();
    cfgPumpTick = rtimePUMP.toInt();
    cfgIrriTick = rtimeIRRI.toInt();
    
    cfgLogicIns = cfgIns.toInt();
    cfgLogicOuts = cfgOuts.toInt();
    
    cfgADCf = rADCf.toInt();
    
    cfgTempHi = rTempHi.toInt();
    cfgTempLo = rTempLo.toInt();
    cfgTimeOpenMin = rTimeOpenMin.toInt();
    cfgTimeCloseMin = rTimeCloseMin.toInt();
    cfgTimeCicloMin = rTimeCicloMin.toInt();

    cfgFanTempHi = rFanTempHi.toInt();
    cfgFanTempLo = rFanTempLo.toInt();

    //DebugVal = rdebugVal.toInt();
    
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.print("Min Scale: ");     Serial.print (cfgScaleMin);        Serial.println(" min");
    Serial.print("Fan: ");           Serial.print (cfgFanTick);         Serial.println(" * min");
    Serial.print("Pump: ");          Serial.print (cfgPumpTick);        Serial.println(" * min");
    Serial.print("Irri: ");          Serial.print (cfgIrriTick);        Serial.println(" * min");
    
    Serial.print("cfgLogic Ins: ");  Serial.println(cfgLogicIns);
    Serial.print("cfgLogic Outs: "); Serial.println(cfgLogicOuts);

    // NTC Adc
    Serial.print("ADC f: ");         Serial.print (cfgADCf);            Serial.println(" si/no 1/0");

    // Control
    Serial.print("cfgTempHi: ");       Serial.print (cfgTempHi);        Serial.println(" ºC");
    Serial.print("cfgTempLo: ");       Serial.print (cfgTempLo);        Serial.println(" ºC");
    Serial.print("cfgTimeOpenMin: ");  Serial.print (cfgTimeOpenMin);   Serial.println(" min");
    Serial.print("cfgTimeCloseMin: "); Serial.print (cfgTimeCloseMin);  Serial.println(" min");
    Serial.print("cfgTimeCicloMin: "); Serial.print (cfgTimeCicloMin);  Serial.println(" min");

    Serial.print("cfgFanTempHi: ");    Serial.print (cfgFanTempHi);     Serial.println(" ºC");
    Serial.print("cfgFanTempLo: ");    Serial.print (cfgFanTempLo);     Serial.println(" ºC");

    //Serial.print("Debug: ");       Serial.print (DebugVal);           Serial.println(" ---");
    #endif   

    // Data
    EEPROM.write(EEPROM_ADD_SCALE_XM,  (byte)cfgScaleMin);
    EEPROM.write(EEPROM_ADD_FAN_XM,    (byte)cfgFanTick);
    EEPROM.write(EEPROM_ADD_PUMP_XM,   (byte)cfgPumpTick);
    EEPROM.write(EEPROM_ADD_IRRI_XM,   (byte)cfgIrriTick);
    
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  (byte)cfgLogicIns);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, (byte)cfgLogicOuts);
    
    EEPROM.write(EEPROM_ADD_ADC_F,      (byte)cfgADCf);

    EEPROM.write(EEPROM_ADD_TEMP_HI,    (byte)cfgTempHi);
    EEPROM.write(EEPROM_ADD_TEMP_LO,    (byte)cfgTempLo);
    EEPROM.write(EEPROM_ADD_OPEN_MIN,   (byte)cfgTimeOpenMin);
    EEPROM.write(EEPROM_ADD_CLOSE_MIN,  (byte)cfgTimeCloseMin);
    EEPROM.write(EEPROM_ADD_CICLO_MIN,  (byte)cfgTimeCicloMin);
   
    EEPROM.write(EEPROM_ADD_FAN_TEMP_HI,  (byte)cfgFanTempHi);
    EEPROM.write(EEPROM_ADD_FAN_TEMP_LO,  (byte)cfgFanTempLo);

    //EEPROM.write(EEPROM_ADD_DEBUG,      (byte)DebugVal);

    EEPROM.commit();    //Store data to EEPROM
  }

  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>INV MQTT+ #Configuraci&oacuten</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>INV MQTT+ #Configuraci&oacuten<span>Nano Every tech</span><span align=\"right\"> " + FW_Version + "</span></h1>";
  
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
*/

/*
void _serveFavicon()
{
  const static byte tblFavicon[] PROGMEM = {0x00, 0x01, ...};

  httpClient.println(F("HTTP/1.1 200 OK"));
  httpClient.println(F("Content-Type: image/x-icon"));
  httpClient.println();

  for (uint16_t i = 0; i < sizeof(tblFavicon); i++)
  {
    byte p = pgm_read_byte_near(tblFavicon + i);
    httpClient.print(p);
  }
}
*/

void _serveERROR()
{
  httpClient.println(F("HTTP/1.1 404 ERROR"));
  httpClient.println(F("Content-Type: text/html"));
  httpClient.println();
  httpClient.print(F("<html>"));
  httpClient.print(F("<head>"));
  httpClient.print(F("<title>Error 404</title>"));
  httpClient.print(F("</head>"));
  httpClient.print(F("<body>"));
  httpClient.print(F("<p>Error 404</p>"));
  httpClient.print(F("</body>"));
  httpClient.print(F("</html>"));
}

void _serveCSS()
{
  httpClient.println(F("HTTP/1.1 200 OK"));
  httpClient.println(F("Content-Type: text/css"));
  httpClient.println();

  httpClient.println(cssSTYLE);
}

void _serveMAIN()
{
  String html;

  httpClient.println(F("HTTP/1.1 200 OK"));
  httpClient.println(F("Content-Type: text/html"));
  httpClient.println();

  httpClient.print(F("<!DOCTYPE HTML><html>"));
  httpClient.print("<title>" + String(PROJECT) + " Estado</title>");

  httpClient.print(F("<head>"));
  httpClient.print(F("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>"));
  httpClient.print(F("<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />"));
  httpClient.print(F("</head>"));

  httpClient.print(F("<body>"));
  httpClient.print(F("<div class=\"myform\">"));
  html = "<h1>" + String(PROJECT) + " #Estado<span>" + String(TECHNOLOGY) + "</span><span align=\"right\"> " + String(compdate) + " " + String(comptime) + "</span></h1>";
  httpClient.print(html);

  httpClient.print(F("<div class=\"section\">Estados</div>"));
  httpClient.print(F("<p class=\"sansserif\" id=\"STATUSid\">...</p>"));

  httpClient.print(F("<div class=\"section\">Control</div>"));
  httpClient.print(F("<p>"));
  httpClient.print(F("  <input type=\"button\" value=\"Cambiar Modo\" onclick=\"sendOUT(0)\">"));
  httpClient.print(F("</p>"));

  httpClient.print(F("<div class=\"section\">Watchdog</div>"));
  httpClient.print(F("<p>"));
  httpClient.print(F("  <input type=\"button\" value=\"Reset\" onclick=\"sendOUT(1)\">"));
  httpClient.print(F("</p>"));

  httpClient.print(F("<div class=\"section\">Configuraci&oacuten</div>"));
  httpClient.print(F("<p>"));
  httpClient.print(F("  <a href=\"nwset.htm\"><input type=\"button\" value=\"Red\"></a>"));
  httpClient.print(F("  <a href=\"cfg.htm\"><input type=\"button\" value=\"Config\"></a>"));
  httpClient.print(F("  <input type=\"button\" value=\"Restauracion\" onclick=\"sendOUT(20)\">"));
  httpClient.print(F("</p>"));

  httpClient.print(F("</div>"));

  httpClient.print(F("<script>"));
  
  httpClient.print(F("function sendOUT(out) {"));
  httpClient.print(F("  var xhttp = new XMLHttpRequest();"));
  httpClient.print(F("  xhttp.open(\"GET\", \"setOUTS?OUTNumber=\"+out, true);"));
  httpClient.print(F("  xhttp.send();"));
  httpClient.print(F("}"));
  
  httpClient.print(F("setInterval(function() {"));
  httpClient.print(F("  getSTATUS();"));
  httpClient.print(F("}, 1000);"));

  httpClient.print(F("function getSTATUS() {"));
  httpClient.print(F("  var xhttp = new XMLHttpRequest();"));
  httpClient.print(F("  xhttp.onreadystatechange = function() {"));
  httpClient.print(F("    if (this.readyState == 4 && this.status == 200) {"));
  httpClient.print(F("      document.getElementById(\"STATUSid\").innerHTML = this.responseText;"));
  httpClient.print(F("   }"));
  httpClient.print(F("  };"));
  httpClient.print(F("  xhttp.open(\"GET\", \"readSTATUS\", true);"));
  httpClient.print(F("  xhttp.send();"));
  httpClient.print(F("}"));

  httpClient.print(F("</script>"));
  
  httpClient.print(F("</form>"));
  httpClient.print(F("</div>"));
  
  httpClient.print(F("</body> "));
  httpClient.print(F("</html>"));
}

void _serveNetwork()
{
  String html;

  httpClient.println(F("HTTP/1.1 200 OK"));
  httpClient.println(F("Content-Type: text/html"));
  httpClient.println();

  httpClient.print(F("<!DOCTYPE HTML><html>"));
  httpClient.print("<title>" + String(PROJECT) + " Red Config</title>");
  
  httpClient.print(F("<head>"));
  httpClient.print(F("<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />"));
  httpClient.print(F("</head>"));

  httpClient.print(F("<body>"));
  httpClient.print(F("<div class=\"myform\">"));
  html = "<h1>" + String(PROJECT) + " #Red Config<span>" + String(TECHNOLOGY) + "</span><span align=\"right\"> " + String(compdate) + " " + String(comptime) + "</span></h1>";
  httpClient.print(html);
  httpClient.print(F("<form method='get' action='setNetwork'>"));

  // Red
  httpClient.print(F("<div class=\"section\"><span>1</span>IP Config</div>"));
  httpClient.print(F("<div class=\"inner-wrap\">"));

  if (ipMode == DHCP_MODE)
  {
    httpClient.print(F("<label><input type=\"radio\" name=\"ipmode\" value=\"dhcp\" checked> DHCP</label>"));
    httpClient.print(F("<label><input type=\"radio\" name=\"ipmode\" value=\"ipfx\"> Fix IP</label>"));
  }
  else
  {
    httpClient.print(F("<label><input type=\"radio\" name=\"ipmode\" value=\"dhcp\"> DHCP</label>"));
    httpClient.print(F("<label><input type=\"radio\" name=\"ipmode\" value=\"ipfx\" checked> Fix IP</label>"));
  }
  html = String(ipAddress[0]) + "." + String(ipAddress[1]) + "." + String(ipAddress[2]) + "." + String(ipAddress[3]); 
  httpClient.print(("<label>IP Address <input type=\"text\"  maxlength=\"16\" value=\"" + html + "\" name=\"ipaddress\"/></label>"));
  html = String(netMask[0]) + "." + String(netMask[1]) + "." + String(netMask[2]) + "." + String(netMask[3]); 
  httpClient.print(("<label>Mask <input type=\"text\" maxlength=\"16\" value=\"" + html + "\" name=\"mask\"/></label>"));
  html = String(gateWay[0]) + "." + String(gateWay[1]) + "." + String(gateWay[2]) + "." + String(gateWay[3]); 
  httpClient.print(("<label>Gateway <input type=\"text\" maxlength=\"16\" value=\"" + html + "\" name=\"gateway\"/></label>"));

  httpClient.print(F("</div>"));
  // End

  #if (_USE_MQTT_ == 1)
  // Broker
  httpClient.print(F("<div class=\"section\"><span>2</span>Broker </div>"));
  httpClient.print(F("<div class=\"inner-wrap\">"));

  httpClient.print("<label>URL <input type=\"text\" maxlength=\"30\" value=\"" + String(brokerUrl) + "\" name=\"brokerurl\"/></label>");
  httpClient.print("<label>Port <input type=\"text\" maxlength=\"16\" value=\"" + String(brokerPort) + "\" name=\"brokerport\"/></label>");

  httpClient.print(F("</div>"));
  // End
  #endif

  httpClient.print(F("<div class=\"button-section\">"));
  httpClient.print(F("  <input type=\"submit\" value=\"Guardar\">"));
  httpClient.print(F("  <a href=\"index.htm\"><input type=\"button\" value=\"Volver\"></a>"));
  httpClient.print(F("</div>"));
  
  httpClient.print(F("</div>"));
  httpClient.print(F("</div>"));
  httpClient.print(F("</form>"));
  httpClient.print(F("</div>"));

  httpClient.print(F("</body>"));
  httpClient.print(F("</html>"));
}

void _serveCfg()
{
  String html;

  httpClient.println(F("HTTP/1.1 200 OK"));
  httpClient.println(F("Content-Type: text/html"));
  httpClient.println();

  httpClient.print(F("<!DOCTYPE HTML><html>"));
  httpClient.print("<title>" + String(PROJECT) + " Config</title>");
  
  httpClient.print(F("<head>"));
  httpClient.print(F("<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />"));
  httpClient.print(F("</head>"));

  httpClient.print(F("<body>"));
  httpClient.print(F("<div class=\"myform\">"));
  html = "<h1>" + String(PROJECT) + " #Config<span>" + String(TECHNOLOGY) + "</span><span align=\"right\"> " + String(compdate) + " " + String(comptime) + "</span></h1>";
  httpClient.print(html);
  httpClient.print(F("<form method='get' action='setCfg'>"));

  httpClient.print(F("<div class=\"section\"><span>1</span>Control</div>"));
  httpClient.print(F("<div class=\"inner-wrap\">"));
  httpClient.print("<label> Tension Principal (Voltios)<input type=\"text\"  maxlength=\"16\" value=\""  + String(cfgResPrimVout)     + "\" name=\"cfgResPrimVout\"/></label>");
  httpClient.print("<label> Tension Inyectior (Voltios)<input type=\"text\"  maxlength=\"16\" value=\""  + String(cfgResInyeVout)     + "\" name=\"cfgResInyeVout\"/></label>");
  httpClient.print("<label> Temp Arranque Inyectior (ºC)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgResPrimInyeTemp) + "\" name=\"cfgResPrimInyeTemp\"/></label>");
  httpClient.print("<label> Temp Consigna Principal (ºC)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgResPrimConsTemp) + "\" name=\"cfgResPrimConsTemp\"/></label>");
  httpClient.print("<label> Temp Hist Principal (ºC)<input type=\"text\"  maxlength=\"16\" value=\""     + String(cfgResPrimHystTemp) + "\" name=\"cfgResPrimHystTemp\"/></label>");
  httpClient.print("<label> Temp Consigna Inyectior (ºC)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgResInyeConsTemp) + "\" name=\"cfgResInyeConsTemp\"/></label>");
  httpClient.print("<label> Temp Hist Inyectior (ºC)<input type=\"text\"  maxlength=\"16\" value=\""     + String(cfgResInyeHystTemp) + "\" name=\"cfgResInyeHystTemp\"/></label>");
  httpClient.print("<label> Temp Consigna Agua (ºC)<input type=\"text\"  maxlength=\"16\" value=\""      + String(cfgAguaConsTemp)    + "\" name=\"cfgAguaConsTemp\"/></label>");
  httpClient.print("<label> Temp Hist Agua (ºC)<input type=\"text\"  maxlength=\"16\" value=\""          + String(cfgAguaHystTemp)    + "\" name=\"cfgAguaHystTemp\"/></label>");
  httpClient.print(F("</div>"));

  httpClient.print(F("<div class=\"section\"><span>2</span>Alarmas</div>"));
  httpClient.print(F("<div class=\"inner-wrap\">"));
  httpClient.print("<label> Alarma Principal (Minutos)<input type=\"text\"  maxlength=\"3\" value=\""  + String(cfgResPrimAlarMin)    + "\" name=\"cfgResPrimAlarMin\"/></label>");
  httpClient.print("<label> Alarma Inyectior (Minutos)<input type=\"text\"  maxlength=\"3\" value=\""  + String(cfgResInyeAlarMin)    + "\" name=\"cfgResInyeAlarMin\"/></label>");
  httpClient.print("<label> Alarma Agua (Minutos)<input type=\"text\"  maxlength=\"3\" value=\""       + String(cfgAguaAlarMin)       + "\" name=\"cfgAguaAlarMin\"/></label>");
  httpClient.print(F("</div>"));

  httpClient.print(F("<div class=\"section\"><span>3</span>Logica</div>"));
  httpClient.print(F("<div class=\"inner-wrap\">"));
  httpClient.print("<label> Entradas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicIns) + "\" name=\"cfgLogicIns\"/></label>");
  httpClient.print("<label> Salidas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicOuts) + "\" name=\"cfgLogicOuts\"/></label>");
  httpClient.print(F("</div>"));

  httpClient.print(F("<div class=\"button-section\">"));
  httpClient.print(F("  <input type=\"submit\" value=\"Guardar\">"));
  httpClient.print(F("  <a href=\"index.htm\"><input type=\"button\" value=\"Volver\"></a>"));
  httpClient.print(F("</div>"));
  
  httpClient.print(F("</div>"));
  httpClient.print(F("</div>"));
  httpClient.print(F("</form>"));
  httpClient.print(F("</div>"));

  httpClient.print(F("</body>"));
  httpClient.print(F("</html>"));
}

String _httpArg(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if(data.charAt(i) == separator || i == maxIndex){
        found++;
        strIndex[0] = strIndex[1] + 1;
        strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void _setNetwork()
{
  bool error = 0;
  int i = 0, j, k, m;
  String subStr, paramStr;
  String ripmode, ripaddress, rmask, rgate;

  char schar;
  char sbuf[4];
  byte val[4];

  int eeprom_value_hi, eeprom_value_lo;

  IPAddress localip;
  IPAddress localmask;
  IPAddress localgate;
  
  // Get params  
  i = httpRxString.indexOf('?');
  if (i != -1)
  {
    subStr = httpRxString.substring(i + 1);
    i = subStr.indexOf(' ');
    if (i != -1)
      subStr = subStr.substring(0, i);
    else
      error = 1;
  }
  else
    error = 1;

  if (error == 0)
  {
    for (i = 0; i < HTTP_NUM_NETWORK_PARAMS; i++)
    {
      //Get param
      paramStr = _httpArg(subStr, '&', i);
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println (paramStr);
      #endif

      if (paramStr.indexOf("ipmode=") != -1)
        ripmode = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("ipaddress=") != -1)
        ripaddress = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("mask=") != -1)
        rmask = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("gateway=") != -1)
        rgate = _httpArg(paramStr, '=', 1);
    }
  }

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
  
  // Check broker error
  //if ((rbrokerurl.length() == 0) ||
  //    (rbrokerport.length() == 0))
  //  error |= 1;

  // If no error on data...
  if (error == 0)
  {
    /*
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
    */   
       
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

    #if (_HTTP_SERIAL_DEBUG_ == 1)
    
     // IP configuration
     Serial.print("---->Local IP: ");
     Serial.println(localip);
     Serial.print("---->Local mask: ");
     Serial.println(localmask);
     Serial.print("---->Local gateway: ");
     Serial.println(localgate);
     /*
     // Broker configuration
     Serial.print("---->Broker Url: ");
     Serial.println(rbrokerurl);
     Serial.print("---->Broker Port: ");
     Serial.println(rbrokerport);     
     */
     #endif
     
     //EEPROM.commit();

     #if (_READ_EEPROM_ == 1)
     _ReadEEPROM();
     delay(1000);
     #endif
    
     // Read config from EEPROM
     _readCONFIG();

    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Sending 200");
    #endif
  }
  else
  {
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Sending 404");
    #endif
  }

  httpClient.println(F("HTTP/1.1 200 OK"));
  httpClient.println(F("Content-Type: text/html"));
  httpClient.println();

  httpClient.print(F("<!DOCTYPE HTML><html>"));
  httpClient.print("<title>" + String(PROJECT) + " + Red Config</title>");
  
  httpClient.print(F("<head>"));
  httpClient.print(F("<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />"));
  httpClient.print(F("</head>"));

  if (error == 0)
    httpClient.print(F("<p class=\"sansserif\">Configuraci&oacuten guardada correctamente.</p>"));
  else
    httpClient.print(F("<p class=\"sansserif\">Error el guardar la configuraci&oacuten. Revise los datos introducidos.</p>"));

  httpClient.print(F("<div class=\"button-section\">"));
  httpClient.print(F("  <a href=\"index.htm\"><input type=\"button\" value=\"Volver\"></a>"));
  httpClient.print(F("</div>"));
  
  httpClient.print(F("</div>"));
  httpClient.print(F("</div>"));
  httpClient.print(F("</form>"));
  httpClient.print(F("</div>"));

  httpClient.print(F("</body>"));
  httpClient.print(F("</html>"));
}

void _setCfg()
{
  bool error = 0;
  /*
  int i = 0;
  String subStr, paramStr;

  String scfgLogicIns;
  String scfgLogicOuts;

  String scfgResPrimVout;
  String scfgResInyeVout;
  String scfgResPrimInyeTemp;
  String scfgResPrimConsTemp;
  String scfgResPrimHystTemp;
  String scfgResInyeConsTemp;
  String scfgResInyeHystTemp;
  String scfgAguaConsTemp;
  String scfgAguaHystTemp;

  String scfgResPrimAlarMin;
  String scfgResInyeAlarMin;
  String scfgAguaAlarMin;

 // Get params  
  i = httpRxString.indexOf('?');
  if (i != -1)
  {
    subStr = httpRxString.substring(i + 1);
    i = subStr.indexOf(' ');
    if (i != -1)
      subStr = subStr.substring(0, i);
    else
      error = 1;
  }
  else
    error = 1;

  if (error == 0)
  {
    for (i = 0; i < HTTP_NUM_CFG_PARAMS; i++)
    {
      //Get param
      paramStr = _httpArg(subStr, '&', i);
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println (paramStr);
      #endif

      if (paramStr.indexOf("cfgResInyeVout=") != -1)
        scfgLogicIns = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("cfgLogicOuts=") != -1)
        scfgLogicOuts = _httpArg(paramStr, '=', 1);

      else if (paramStr.indexOf("cfgResPrimVout=") != -1)
        scfgResPrimVout = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("cfgResInyeVout=") != -1)
        scfgResInyeVout = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("cfgResPrimInyeTemp=") != -1)
        scfgResPrimInyeTemp = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("cfgResPrimConsTemp=") != -1)
        scfgResPrimConsTemp = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("cfgResPrimHystTemp=") != -1)
        scfgResPrimHystTemp = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("cfgResInyeConsTemp=") != -1)
        scfgResInyeConsTemp = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("cfgResInyeHystTemp=") != -1)
        scfgResInyeHystTemp = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("cfgAguaConsTemp=") != -1)
        scfgAguaConsTemp = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("scfgAguaHystTemp=") != -1)
        scfgAguaHystTemp = _httpArg(paramStr, '=', 1);

      else if (paramStr.indexOf("cfgResPrimAlarMin=") != -1)
        scfgResPrimAlarMin = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("cfgResInyeAlarMin=") != -1)
        scfgResInyeAlarMin = _httpArg(paramStr, '=', 1);
      else if (paramStr.indexOf("cfgAguaAlarMin=") != -1)
        scfgAguaAlarMin = _httpArg(paramStr, '=', 1);
    }
  }

  // Must be 
  if ((scfgLogicIns.length() == 0)        ||
      (scfgLogicOuts.length() == 0)       ||

      (scfgResPrimVout.length() == 0)     ||
      (scfgResInyeVout.length() == 0)     ||
      (scfgResPrimInyeTemp.length() == 0) ||
      (scfgResPrimConsTemp.length() == 0) ||
      (scfgResPrimHystTemp.length() == 0) ||
      (scfgResInyeConsTemp.length() == 0) ||
      (scfgAguaConsTemp.length() == 0)    ||
      (scfgAguaHystTemp.length() == 0)    ||

      (scfgResPrimAlarMin.length() == 0)  ||
      (scfgResInyeAlarMin.length() == 0)  ||
      (scfgAguaAlarMin.length() == 0))
    error = 1;
  */

  httpClient.println(F("HTTP/1.1 200 OK"));
  httpClient.println(F("Content-Type: text/html"));
  httpClient.println();

  httpClient.print(F("<!DOCTYPE HTML><html>"));
  httpClient.print("<title>" + String(PROJECT) + " + Config</title>");
  
  httpClient.print(F("<head>"));
  httpClient.print(F("<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />"));
  httpClient.print(F("</head>"));

  if (error == 0)
    httpClient.print(F("<p class=\"sansserif\">Configuraci&oacuten guardada correctamente.</p>"));
  else
    httpClient.print(F("<p class=\"sansserif\">Error el guardar la configuraci&oacuten. Revise los datos introducidos.</p>"));

  httpClient.print(F("<div class=\"button-section\">"));
  httpClient.print(F("  <a href=\"index.htm\"><input type=\"button\" value=\"Volver\"></a>"));
  httpClient.print(F("</div>"));
  
  httpClient.print(F("</div>"));
  httpClient.print(F("</div>"));
  httpClient.print(F("</form>"));
  httpClient.print(F("</div>"));

  httpClient.print(F("</body>"));
  httpClient.print(F("</html>"));
}

/////////////
// Actions //
/////////////
void _setOUTS()
{
  String html;
  int outNumber = 0;

  httpClient.println(F("HTTP/1.1 200 OK"));
  httpClient.println(F("Content-Type: text/plane"));
  httpClient.println();
  
  // Cambiar Modo
  if (httpRxString.indexOf("OUTNumber=0 HTTP") != -1)
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
  if (httpRxString.indexOf("OUTNumber=1 HTTP") != -1)
  {
    #if (_USE_WDE_ == 1)
    wdeForceReset = 1;
    #endif
      
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Watchdog reset");
    #endif
  }
  /*
  // OutOpen
  if(out_number == "10")
  {
    if (OutOpen == OUT_ON)
    {
      OutOpen = OUT_OFF;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("OutOpen OFF");
      #endif
      html = "OutOpen OFF";
    }
    else
    {
      OutOpen = OUT_ON;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("OutOpen ON");
      #endif
      html = "OutOpen ON";
    }
  }
  */
  // Restore
  if (httpRxString.indexOf("OUTNumber=20 HTTP") != -1)
  {
    _ResetEEPROM();
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Restore");
    #endif
    html = "Restore";
  }

  httpClient.print(html);
}

void _serveSTATUS()
{
  String html;

  httpClient.println(F("HTTP/1.1 200 OK"));
  httpClient.println(F("Content-Type: text/plane"));
  httpClient.println();

  httpClient.print(F("<table style=\"width:100%\">"));

  httpClient.print(F("<tr>"));
  httpClient.print(F("<td>Tiempo ON </td>"));
  httpClient.print("<td>" + timeOnString + "</td>");
  httpClient.print(F("</tr>"));

  httpClient.print(F("<tr>"));
  httpClient.print(F("<td>Control Modo </td>"));
  if (ctrMode == MODE_AUTO)
   httpClient.print(F("<td><font style=\"color:green\">AUTO</font></td>"));
  else
   httpClient.print(F("<td><font style=\"color:grey\">TEST</font></td>"));
  httpClient.print(F("</tr>"));
  /*
  httpClient.print(F("<tr>"));
  httpClient.print(F("<td>MQTT Estado </td>"));
  httpClient.print("<td>" + String(mqttStatus) + "</td>");
  httpClient.print(F("</tr>"));

  httpClient.print(F("<tr>"));
  httpClient.print(F("<td>-----------------</td>"));
  httpClient.print(F("</tr>"));
 
  httpClient.print(F("<tr>"));
  httpClient.print(F("<td>Ventilador</td>"));
  if (OutFan == OUT_ON)
   httpClient.print(F("<td><font style=\"color:green\">ON</font></td>"));
  else
   httpClient.print(F("<td><font style=\"color:grey\">OFF</font></td>"));
  httpClient.print(F("</tr>"));
  */
  
  httpClient.print(F("</table>"));
}

void _HttpSetup(void)
{
  httpServerStatus = HTTP_SERVER_INIT;

  httpClientStatus = HTTP_CLIENT_INIT;
  httpClientConnected = false;

  http1stline = 0;
  httpRxString = "";
  httpRxTick = millis();
}

void _HttpLoop()
{ 
  switch (httpServerStatus)
  {
    case HTTP_SERVER_INIT:
      httpServer.begin(80);

      #if (_MBTCP_SERIAL_DEBUG_ == 1)
      Serial.println("Http server started");
      #endif
      httpServerStatus = HTTP_SERVER_ON;
      break;

    case HTTP_SERVER_ON:
      _httpClientLoop();
      break;
  }
}

void _httpClientLoop ()
{
  switch (httpClientStatus)
  {
    case HTTP_CLIENT_INIT:
      httpClient = httpServer.available();
      if (httpClient)
      {
        #if (_HTTP_SERIAL_DEBUG_ == 1)
        Serial.println(">>");
        Serial.print("http client connected: "); Serial.println(httpClient);
        #endif

        httpClientStatus = HTTP_CLIENT_CONNECTED;
        httpClientConnected = true;

        http1stline = 0;
        httpRxString = "";
        httpRxTick = millis();
      }
      break;

    case HTTP_CLIENT_CONNECTED:
      // Client connected....
      if (httpClient.connected())
      {
        if (httpClient.available())
        {
          #if (_HTTP_SERIAL_DEBUG_ == 1)
          Serial.println("http request start");
          #endif

          httpClientStatus = HTTP_CLIENT_ON_RX;
          
          http1stline = 0;
          httpRxString = "";
          httpRxTick = millis();
        }
        else
        {
          // Time out no RX...
          if (millis() - httpRxTick >= HTTP_CONNECTION_TIMEOUT)
          {
            #if (_HTTP_SERIAL_DEBUG_ == 1)
            Serial.print("httpClient.available() timeout");
            #endif

            httpClientStatus = HTTP_CLIENT_INIT;
            httpClient.stop();
            httpClientConnected = false;
          }
        }
      }
      // Client time out disconnected...
      else
      {
        if (millis() - httpRxTick >= HTTP_CONNECTION_TIMEOUT)
        {
          #if (_HTTP_SERIAL_DEBUG_ == 1)
          Serial.println("httpClient.connected() timeout");
          #endif

          httpClientStatus = HTTP_CLIENT_INIT;
          httpClient.stop();
          httpClientConnected = false;
        }
      }
      break;

    case HTTP_CLIENT_ON_RX:
      // Client connected...
      if (httpClient.connected())
      {
        if (httpClient.available())
        {
          char newChar = httpClient.read();
          
          if (newChar == '\n')
            http1stline = 1;

          if (http1stline == 0)
            httpRxString += newChar;
          
          httpRxTick = millis();
        }
        else
        {
          // RX Time out...
          if (millis() - httpRxTick >= HTTP_RX_TIMEOUT)
          {
             #if (_HTTP_SERIAL_DEBUG_ == 1)
             Serial.println ("http request rx");
             Serial.println(httpRxString);
             #endif

             httpClientStatus = HTTP_CLIENT_ON_ANALYSIS;
          }
        }
      }
      // Client disconnected...
      else
      {
        #if (_HTTP_SERIAL_DEBUG_ == 1)
        Serial.println("httpClient.connected() disconnected");
        #endif

        httpClientStatus = HTTP_CLIENT_INIT;
        httpClient.stop();
        httpClientConnected = false;
      }
      break;
    
    case HTTP_CLIENT_ON_ANALYSIS:
      // Client connected...
      if (httpClient.connected())
      {
        #if (_HTTP_SERIAL_DEBUG_ == 1)
        Serial.println("http analysis");
        #endif
        
        if (httpRxString.indexOf("GET /favicon") != -1)
          httpTxPage = 0; // 1;
        else if (httpRxString.indexOf("GET /style.css") != -1)
          httpTxPage = 3;
        else if (httpRxString.indexOf("GET /readSTATUS") != -1)
          httpTxPage = 4;
        else if (httpRxString.indexOf("GET /setOUTS") != -1)
          httpTxPage = 5;
        else if (httpRxString.indexOf("GET /nwset.htm") != -1)
          httpTxPage = 6;
        else if (httpRxString.indexOf("GET /setNetwork") != -1)
          httpTxPage = 7;
        else if (httpRxString.indexOf("GET /cfg.htm") != -1)
          httpTxPage = 8;
        else if (httpRxString.indexOf("GET /setCfg") != -1)
          httpTxPage = 9;
        else if ((httpRxString.indexOf("GET /index.htm") != -1) ||
                 (httpRxString.indexOf("GET / HTTP") != -1))
          httpTxPage = 2;
        else
        {
          httpTxPage = 0;
          #if (_HTTP_SERIAL_DEBUG_ == 1)
          Serial.println("http ERROR 404");
          #endif
        }

        httpClientStatus = HTTP_CLIENT_ON_TX;
      }
      // Client disconnected...
      else
      {
        #if (_HTTP_SERIAL_DEBUG_ == 1)
        Serial.println("httpClient.connected() disc in analysis");
        #endif

        httpClientStatus = HTTP_CLIENT_INIT;
        httpClient.stop();
        httpClientConnected = false;
      }
      break;

    case HTTP_CLIENT_ON_TX:

      httpClient.flush();

      switch (httpTxPage)
      {
        // Error
        case 0:
          _serveERROR();
          break;
        
        // favicon
        //case 1:
        //  _serveFavicon();
        //  break;
        
        // index
        case 2:
          _serveMAIN();
          break;

        //style.css
        case 3:
          _serveCSS();
          break;

        case 4:
          _serveSTATUS();
          break;

        case 5:
          _setOUTS();
          break;

        case 6:
          _serveNetwork();
          break;

        case 7:
          _setNetwork();
          break;

        case 8:
          _serveCfg();
          break;

        case 9:
          _setCfg();
          break;
      }
      
      httpClient.stop();
      httpClientStatus = HTTP_CLIENT_INIT;
      break;
  }
}

#endif // (_USE_HTTP_ == 1)