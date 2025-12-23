#include "main.h"

#if (_USE_HTTP_ == 1)

/*
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
  //String html = "";

  html = "HTTP/1.1 200 OK";
  html = html + "Content-Type: text/html";
  html = html + "<!DOCTYPE HTML><html>";

  html = html + "<title>INV MQTT+ Estado</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  //html = html + "<h1>INV MQTT+ #Estado<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  html = html + "<h1>INV MQTT+ #Estado<span>ESP8266 tech</span><span align=\"right\"> Ver: TODO</span></h1>";

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
  html = html + "  <input type=\"button\" value=\"Abrir\" onclick=\"sendOUT(10)\">";
  html = html + "  <input type=\"button\" value=\"Cerrar\" onclick=\"sendOUT(11)\">";
  html = html + "  <input type=\"button\" value=\"Ventilador\" onclick=\"sendOUT(12)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"Bomba\" onclick=\"sendOUT(13)\">";
  html = html + "  <input type=\"button\" value=\"Irrigacion\" onclick=\"sendOUT(14)\">";
  html = html + "</p>";
  html = html + "<div class=\"section\">Watchdog</div>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Reset\" onclick=\"sendOUT(1)\">";
  html = html + "</p>";
  html = html + "<div class=\"section\">Configuraci&oacuten</div>";
  html = html + "<p>";
  html = html + "  <a href=\"settings.htm\"><input type=\"button\" value=\"Red\"></a>";
  html = html + "  <a href=\"timeSettings.htm\"><input type=\"button\" value=\"Config\"></a>";
  html = html + "  <input type=\"button\" value=\"Restauracion\" onclick=\"sendOUT(20)\">";
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

  //httpServer.send (200, "text/html", html);
}

void _serveTimeSETTINGS()
{
  String html = "";
  
  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>INV MQTT+ #Configuraci&oacuten</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>INV MQTT+ #Configuraci&oacuten<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  html = html + "<form method='get' action='setTimeSettings'>";

  html = html + "<div class=\"section\"><span>1</span>Tiempos</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label>Scale (min)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgScaleMin) + "\" name=\"scaleMIN\"/></label>";
  html = html + "<label>Fan Out (*m)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgFanTick) + "\" name=\"timeFAN\"/></label>";
  html = html + "<label>Pump Out (*m)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgPumpTick) + "\" name=\"timePUMP\"/></label>";
  html = html + "<label>Irri Out (*m)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgIrriTick) + "\" name=\"timeIRRI\"/></label>";
  html = html + "</div>";

  html = html + "<div class=\"section\"><span>2</span>Logica</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Entradas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicIns) + "\" name=\"cfgIns\"/></label>";
  html = html + "<label> Salidas ON <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicOuts) + "\" name=\"cfgOuts\"/></label>";
  html = html + "</div>";

  html = html + "<div class=\"section\"><span>3</span>NTC</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label>NTC filtro (si/no 1/0)<input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCf) + "\" name=\"rADCf\"/></label>";
  html = html + "</div>";

  html = html + "<div class=\"section\"><span>4</span>Ventana Control</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label>Temp Alta (ºC)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTempHi) + "\" name=\"tempHi\"/></label>";
  html = html + "<label>Temp Baja (ºC)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTempLo) + "\" name=\"tempLo\"/></label>";
  html = html + "<label>Apertura (min)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeOpenMin) + "\" name=\"timeOpenMin\"/></label>";
  html = html + "<label>Cierre (min)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeCloseMin) + "\" name=\"timeCloseMin\"/></label>";
  html = html + "<label>Ciclo (min)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeCicloMin) + "\" name=\"timeCicloMin\"/></label>";
  html = html + "</div>";

  html = html + "<div class=\"section\"><span>5</span>Ventilador Control</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label>Vent Temp Alta (ºC) - 0 deshabilitado<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgFanTempHi) + "\" name=\"fanTempHi\"/></label>";
  html = html + "<label>Vent Temp Baja (ºC) - 0 deshabilitado<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgFanTempLo) + "\" name=\"fanTempLo\"/></label>";
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
  html = html + "<h1>INV MQTT+ #Configuraci&oacuten<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  
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
  //html = html + "<meta name='apple-mobile-web-app-capable' content='yes' />";
  //html = html + "<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>INV MQTT+ #Network settings<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
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
  html = html + "<title>INV MQTT+ #Configuraci&oacuten</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>INV MQTT+ #Configuraci&oacuten<span>ESP8266 tech</span><span align=\"right\"> Ver: " + FW_Version + "</span></h1>";
  
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

  // INs
  html = html + "<tr>";
  html = html + "<td>Puls Abrir</td>";
  if (InOpen == IO_OFF)
    html = html + "<td><font style=\"color:grey\">OFF</font></td>";
  else
    html = html + "<td><font style=\"color:green\">ON</font></td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Puls Cerrar</td>";
  if (InClose == IO_OFF)
    html = html + "<td><font style=\"color:grey\">OFF</font></td>";
  else
    html = html + "<td><font style=\"color:green\">ON</font></td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Ventana Cerrada</td>";
  if (InWClose == IOW_OFF)
    html = html + "<td><font style=\"color:grey\">OFF</font></td>";
  else
    html = html + "<td><font style=\"color:green\">ON</font></td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Ventana Abierta</td>";
  if (InWOpen == IOW_OFF)
    html = html + "<td><font style=\"color:grey\">OFF</font></td>";
  else
    html = html + "<td><font style=\"color:green\">ON</font></td>";
  html = html + "</tr>";

  // NTC ADC
  html = html + "<tr>";
  html = html + "<td>Ntc In (Dig)</td>";
  html = html + "<td>" + String(NtcInADC) + "</td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>Ntc In (ºC)</td>";
  html = html + "<td>" + String(NtcIn) + "</td>";
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
 
  // OutClose
  if(out_number == "11")
  {
    if (OutClose == OUT_ON)
    {
      OutClose = OUT_OFF;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Close OFF");
      #endif
      html = "Close OFF";
    }
    else
    {
      OutClose = OUT_ON;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Close ON");
      #endif
      html = "Close ON";
    }
  }

  // OutFan
  if(out_number == "12")
  {
    if (OutFan == OUT_ON)
    {
      OutFan = OUT_OFF;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Fan OFF");
      #endif
      html = "Fan OFF";
    }
    else
    {
      OutFan = OUT_ON;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Fan ON");
      #endif
      html = "Fan ON";
    }
  }

  // OutPump
  if(out_number == "13")
  {
    if (OutPump == OUT_ON)
    {
      OutPump = OUT_OFF;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Pump OFF");
      #endif
      html = "Pump OFF";
    }
    else
    {
      OutPump = OUT_ON;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Pump ON");
      #endif
      html = "Pump ON";
    }
  }

  // OutIrri
  if(out_number == "14")
  {
    if (OutIrri == OUT_ON)
    {
      OutIrri = OUT_OFF;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Irri OFF");
      #endif
      html = "Irri OFF";
    }
    else
    {
      OutIrri = OUT_ON;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Irri ON");
      #endif
      html = "Irri ON";
    }
  }
  
  // Restore
  if(out_number == "20")
  {
    _ResetEEPROM();
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Restore");
    #endif
    html = "Restore";
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
*/


void _serveFavicon()
{
  const static byte tblFavicon[] PROGMEM = {0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x10, 0x10, 0x00, 0x01, 0x00, 0x04, 0x00, 0x28, 0x01, 
                                            0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 
                                            0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                            0x00, 0x00, 0x82, 0x7E, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                            0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                            0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                            0x00, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x01, 0x00, 0x01, 0x00, 0x10, 0x00, 0x10, 0x10, 
                                            0x01, 0x00, 0x01, 0x00, 0x10, 0x00, 0x11, 0x10, 0x01, 0x00, 0x01, 0x00, 0x11, 0x10, 0x10, 0x10, 
                                            0x01, 0x00, 0x01, 0x00, 0x10, 0x10, 0x10, 0x10, 0x11, 0x10, 0x11, 0x10, 0x11, 0x10, 0xFF, 0xFF, 
                                            0x00, 0x00, 0xF0, 0x1F, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0xFE, 0xFF, 
                                            0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0xFA, 0xBF, 0x00, 0x00, 0xFC, 0x7F, 
                                            0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x5B, 0xB7, 0x00, 0x00, 0x5B, 0xB7, 
                                            0x00, 0x00, 0x1B, 0xB1, 0x00, 0x00, 0x5B, 0xB5, 0x00, 0x00, 0x51, 0x11, 0x00, 0x00 
                                           };

  httpClient.println(F("HTTP/1.1 200 OK"));
  httpClient.println(F("Content-Type: image/x-icon"));
  httpClient.println();

  for (uint16_t i = 0; i < sizeof(tblFavicon); i++)
  {
    byte p = pgm_read_byte_near(tblFavicon + i);
    httpClient.print(p);
  }
}

void _serveERROR()
{ 
  httpClient.println(F("HTTP/1.1 404 ERROR"));
  httpClient.println(F("Content-Type: text/html"));
  httpClient.println();
  httpClient.print(F("<HTML>"));
  httpClient.print(F("<HEAD>"));
  httpClient.print(F("<TITLE>Error 404</TITLE>"));
  httpClient.print(F("</HEAD>"));
  httpClient.print(F("<BODY>"));
  httpClient.print(F("<p>Error 404</p>"));
  httpClient.print(F("</BODY>"));
  httpClient.print(F("</HTML>"));
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
  html = "<title>" + String(PROJECT) + " + Estado</title>";
  httpClient.print(html);

  httpClient.print(F("<head>"));
  httpClient.print(F("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>"));
  httpClient.print(F("<link rel=\"icon\" href=\"data:,\">"));
  httpClient.print(F("<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />"));
  httpClient.print(F("</head>"));

  httpClient.print(F("<body>"));
  httpClient.print(F("<div class=\"myform\">"));
  html = "<h1>" + String(PROJECT) + " #Config<span>ESP8266 tech</span><span align=\"right\"> Ver: " + String(compdate) + " " + String(comptime) + "</span></h1>";
  httpClient.print(html);
  httpClient.print(F("<div class=\"section\">Temporizaciones</div>"));
  httpClient.print(F("<p class=\"sansserif\" id=\"TEMPSid\">...</p>"));
  httpClient.print(F("<div class=\"section\">Entradas</div>"));
  httpClient.print(F("<p class=\"sansserif\" id=\"INSid\">...</p>"));
  httpClient.print(F("<div class=\"section\">Estados / Salidas</div>"));
  httpClient.print(F("<p class=\"sansserif\" id=\"OUTSid\">...</p>"));
  httpClient.print(F("<div class=\"section\">Control</div>"));
  httpClient.print(F("<p>"));
  httpClient.print(F("  <input type=\"button\" value=\"Cambiar Modo\" onclick=\"sendOUT(0)\">"));
  httpClient.print(F("</p><p>"));
  httpClient.print(F("  <input type=\"button\" value=\"Abrir\" onclick=\"sendOUT(10)\">"));
  httpClient.print(F("  <input type=\"button\" value=\"Cerrar\" onclick=\"sendOUT(11)\">"));
  httpClient.print(F("  <input type=\"button\" value=\"Ventilador\" onclick=\"sendOUT(12)\">"));
  httpClient.print(F("</p><p>"));
  httpClient.print(F("  <input type=\"button\" value=\"Bomba\" onclick=\"sendOUT(13)\">"));
  httpClient.print(F("  <input type=\"button\" value=\"Irrigacion\" onclick=\"sendOUT(14)\">"));
  httpClient.print(F("</p>"));
  httpClient.print(F("<div class=\"section\">Watchdog</div>"));
  httpClient.print(F("<p>"));
  httpClient.print(F("  <input type=\"button\" value=\"Reset\" onclick=\"sendOUT(1)\">"));
  httpClient.print(F("</p>"));
  httpClient.print(F("<div class=\"section\">Configuraci&oacuten</div>"));
  httpClient.print(F("<p>"));
  httpClient.print(F("  <a href=\"settings.htm\"><input type=\"button\" value=\"Red\"></a>"));
  httpClient.print(F("  <a href=\"timeSettings.htm\"><input type=\"button\" value=\"Config\"></a>"));
  httpClient.print(F("  <input type=\"button\" value=\"Restauracion\" onclick=\"sendOUT(20)\">"));
  httpClient.print(F("</p>"));
  httpClient.print(F("</div>"));

  httpClient.print(F("<script>"));
  
  httpClient.print(F("function sendOUT(out) {"));
  httpClient.print(F("  var xhttp = new XMLHttpRequest();"));
  httpClient.print(F("  xhttp.open(\"GET\", \"setOUTS?OUTNumber=\"+out, true);"));
  httpClient.print(F("  xhttp.send();"));
  httpClient.print(F("}"));
  /*
  httpClient.print(F("setInterval(function() {"));
  httpClient.print(F("  getOUTS();"));
  httpClient.print(F("  getINS();"));
  httpClient.print(F("  getTEMPS();"));
  httpClient.print(F("}, 1000);"));
  
  httpClient.print(F("function getOUTS() {"));
  httpClient.print(F("  var xhttp = new XMLHttpRequest();"));
  httpClient.print(F("  xhttp.onreadystatechange = function() {"));
  httpClient.print(F("    if (this.readyState == 4 && this.status == 200) {"));
  httpClient.print(F("      document.getElementById(\"OUTSid\").innerHTML = this.responseText;"));
  httpClient.print(F("   }"));
  httpClient.print(F("  };"));
  httpClient.print(F("  xhttp.open(\"GET\", \"readOUTS\", true);"));
  httpClient.print(F("  xhttp.send();"));
  httpClient.print(F("}"));
  /*
  httpClient.print(F("function getINS() {"));
  httpClient.print(F("  var xhttp = new XMLHttpRequest();"));
  httpClient.print(F("  xhttp.onreadystatechange = function() {"));
  httpClient.print(F("    if (this.readyState == 4 && this.status == 200) {"));
  httpClient.print(F("      document.getElementById(\"INSid\").innerHTML = this.responseText;"));
  httpClient.print(F("   }"));
  httpClient.print(F("  };"));
  httpClient.print(F("  xhttp.open(\"GET\", \"readINS\", true);"));
  httpClient.print(F("  xhttp.send();"));
  httpClient.print(F("}"));

  httpClient.print(F("function getTEMPS() {"));
  httpClient.print(F("  var xhttp = new XMLHttpRequest();"));
  httpClient.print(F("  xhttp.onreadystatechange = function() {"));
  httpClient.print(F("    if (this.readyState == 4 && this.status == 200) {"));
  httpClient.print(F("      document.getElementById(\"TEMPSid\").innerHTML = this.responseText;"));
  httpClient.print(F("   }"));
  httpClient.print(F("  };"));
  httpClient.print(F("  xhttp.open(\"GET\", \"readTEMPS\", true;"));
  httpClient.print(F("  xhttp.send();"));
  httpClient.print(F("}"));
  */
  httpClient.print(F("</script>"));
  
  httpClient.print(F("</form>"));
  httpClient.print(F("</div>"));
  
  httpClient.print(F("</body> "));
  httpClient.print(F("</html>"));
}

void _setOUTS()
{
  String html;
  int outNumber = 0;

  httpClient.println(F("HTTP/1.1 200 OK"));
  httpClient.println(F("Content-Type: text/plane"));
  httpClient.println();

  outNumber = (int)(atoi(httpRxArray[23]));
  
  #if (_HTTP_SERIAL_DEBUG_ == 1)
  Serial.print("Change status out: ");
  Serial.print(httpRxArray[23]);
  Serial.println(httpRxArray[24]);
  //Serial.println(outNumber);
  #endif

  // Cambiar Modo
  if(outNumber == 0)
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
  /*
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
   
  // Restore
  if(out_number == "20")
  {
    _ResetEEPROM();
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Restore");
    #endif
    html = "Restore";
  }
  */

  httpClient.print(html);
}

void _serveOUTS()
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
  httpClient.print(F("<td>MQTT Estado </td>"));
  httpClient.print("<td>" + String(mqttStatus) + "</td>");
  httpClient.print(F("</tr>"));

  /*
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
  httpRxIndex = 0;
  httpRxTick = millis();
}

void _HttpLoop()
{ 
  switch (httpServerStatus)
  {
    case HTTP_SERVER_INIT:
      httpServer.begin(80);

      #if (_MBTCP_SERIAL_DEBUG_ == 1)
      Serial.println("HTTP server started");
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
  //#if (_HTTP_SERIAL_DEBUG_ == 1)
  //Serial.print("HTTP State "); Serial.print(httpClientStatus); Serial.println(" ***");
  //#endif

  switch (httpClientStatus)
  {
    case HTTP_CLIENT_INIT:
      httpClient = httpServer.available();
      if (httpClient)
      {
        #if (_HTTP_SERIAL_DEBUG_ == 1)
        Serial.println(">>>>>>>>>>>>");
        Serial.print("http client connected: "); Serial.println(httpClient);
        #endif

        httpClientStatus = HTTP_CLIENT_CONNECTED;
        httpClientConnected = true;

        http1stline = 0;
        httpRxIndex = 0;
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
          Serial.println("http client start request");
          #endif

          httpClientStatus = HTTP_CLIENT_ON_RX;
          
          http1stline = 0;
          httpRxIndex = 0;
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

          if ((httpRxIndex < HTTP_RX_MAX_BTYE) && (http1stline == 0))
          {
            #if (_HTTP_SERIAL_DEBUG_ == 1)
            Serial.print (newChar);
            #endif

            httpRxArray[httpRxIndex] = newChar;
            httpRxIndex++;
          }

          httpRxTick = millis();
        }
        else
        {
          // RX Time out...
          if (millis() - httpRxTick >= HTTP_RX_TIMEOUT)
          {
             #if (_HTTP_SERIAL_DEBUG_ == 1)
             Serial.println ("");
             Serial.print ("http client request received of "); Serial.print (httpRxIndex); Serial.println (" bytes");
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
        Serial.println("http request analysis");
        #endif
        
        if (strncmp("GET /favicon", httpRxArray, 12) == 0)
        {
          httpTxPage = 1;
          #if (_HTTP_SERIAL_DEBUG_ == 1)
          Serial.println("favcion");
          #endif
        }
        else if (strncmp("GET /style.css", httpRxArray, 14) == 0)
        {
          httpTxPage = 3;
          #if (_HTTP_SERIAL_DEBUG_ == 1)
          Serial.println("style");
          #endif
        }
        else if (strncmp("GET /readOUTS", httpRxArray, 13) == 0)
        {
          httpTxPage = 4;
          #if (_HTTP_SERIAL_DEBUG_ == 1)
          Serial.println("readOUTS");
          #endif
        }
        else if (strncmp("GET /setOUTS", httpRxArray, 12) == 0)
        {
          httpTxPage = 5;
          #if (_HTTP_SERIAL_DEBUG_ == 1)
          Serial.println("setOUTS");
          #endif
        }        
        else if (strncmp("GET / HTTP/1.1", httpRxArray, 14) == 0)
        {
          httpTxPage = 2;
          #if (_HTTP_SERIAL_DEBUG_ == 1)
          Serial.println("index");
          #endif
        }
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
        Serial.println("httpClient.connected() disconnected in analysis.");
        #endif

        httpClientStatus = HTTP_CLIENT_INIT;
        httpClient.stop();
        httpClientConnected = false;
      }
      break;

    case HTTP_CLIENT_ON_TX:

      httpClient.flush();

      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("http response sent");
      #endif

      switch (httpTxPage)
      {
        // Error
        case 0:
          _serveERROR();
          break;
        
        // favicon
        case 1:
          _serveFavicon();
          break;
        
        // index
        case 2:
          _serveMAIN();
          break;

        //style.css
        case 3:
          _serveCSS();
          break;

        case 4:
          _serveOUTS();
          break;

        case 5:
          _setOUTS();
          break;
      }
      
      httpClient.stop();
      httpClientStatus = HTTP_CLIENT_INIT;
      break;
  }
}

#endif // (_USE_HTTP_ == 1)