#include "main.h"
#include "http.h"

#include "mTime.h"

#if (_USE_HTTP_ == 1)
// Libraries
#include <ETH.h>
#include <WebServer.h>
#if (_USE_ETHERNET_ == 1)
#include "mEthernet.h"
#endif

///////////////
// Variables //
///////////////
WebServer httpServer(HTTP_PORT);
int httpStatus;

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

  html = html + "<div class=\"section\"><span>1</span>Control</div>";
  html = html + "<p class=\"sansserif\" id=\"CTRid\">...</p>";
  
  html = html + "<div class=\"section\"><span>2</span>Modo</div>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Cambiar\" onclick=\"sendOUT(10)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"RL1\" onclick=\"sendOUT(6)\">";
  html = html + "  <input type=\"button\" value=\"RL2\" onclick=\"sendOUT(7)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"O1\" onclick=\"sendOUT(1)\">";
  html = html + "  <input type=\"button\" value=\"O2\" onclick=\"sendOUT(2)\">";
  html = html + "  <input type=\"button\" value=\"O3\" onclick=\"sendOUT(3)\">";
  html = html + "  <input type=\"button\" value=\"O4\" onclick=\"sendOUT(4)\">";
  html = html + "  <input type=\"button\" value=\"O5\" onclick=\"sendOUT(5)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"TR3\" onclick=\"sendOUT(33)\">";
  html = html + "  <input type=\"button\" value=\"TR2\" onclick=\"sendOUT(32)\">";
  html = html + "  <input type=\"button\" value=\"TR1\" onclick=\"sendOUT(31)\">";
  html = html + "</p>";

  html = html + "<div class=\"section\"><span>3</span>Estado</div>";
  html = html + "<p class=\"sansserif\" id=\"INSid\">...</p>";
  html = html + "<p class=\"sansserif\" id=\"OUTSid\">...</p>";

  html = html + "<div class=\"section\"><span>4</span>Sistema</div>";
  html = html + "<p class=\"sansserif\" id=\"STATUSSid\">...</p>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Reset\" onclick=\"sendOUT(11)\">";
  html = html + "  <input type=\"button\" value=\"Restore\" onclick=\"sendOUT(12)\">";
  html = html + "</p>";

  html = html + "<div class=\"section\"><span>5</span>Configuraci&oacuten</div>";
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

  html = html + "<div class=\"section\"><span>1.1</span>Temperaturas de Control</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Arranque Inyectior (ºC)<input type=\"text\"  maxlength=\"16\" value=\""  + String(cfgResPrimInyeTemp) + "\" name=\"cfgResPrimInyeTemp\"/></label>";
  html = html + "<label> Consigna Principal (ºC)<input type=\"text\"  maxlength=\"16\" value=\""  + String(cfgResPrimConsTemp) + "\" name=\"cfgResPrimConsTemp\"/></label>";
  html = html + "<label> Histereis Principal (ºC)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgResPrimHystTemp) + "\" name=\"cfgResPrimHystTemp\"/></label>";
  html = html + "<label> Consigna Inyectior (ºC)<input type=\"text\"  maxlength=\"16\" value=\""  + String(cfgResInyeConsTemp) + "\" name=\"cfgResInyeConsTemp\"/></label>";
  html = html + "<label> Histereis Inyectior (ºC)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgResInyeHystTemp) + "\" name=\"cfgResInyeHystTemp\"/></label>";
  html = html + "<label> Consigna Agua (ºC)<input type=\"text\"  maxlength=\"16\" value=\""       + String(cfgAguaConsTemp)    + "\" name=\"cfgAguaConsTemp\"/></label>";
  html = html + "<label> Histereis Agua (ºC)<input type=\"text\"  maxlength=\"16\" value=\""      + String(cfgAguaHystTemp)    + "\" name=\"cfgAguaHystTemp\"/></label>";
  html = html + "</div>";

  #if (_USE_MBRTU_ == 1)
  html = html + "<div class=\"section\"><span>1.2</span>Sondas Temperatura</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> 0->No usado, 1-> Temp. Principal, 2-> Temp. Inyector, 3-> Temp. Agua</label>";
  html = html + "<label> Temp 1 Uso <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTempUse[0]) + "\" name=\"cfgTempUse0\"/></label>";
  html = html + "<label> Temp 2 Uso <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTempUse[1]) + "\" name=\"cfgTempUse1\"/></label>";
  html = html + "<label> Temp 3 Uso <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTempUse[2]) + "\" name=\"cfgTempUse2\"/></label>";
  html = html + "<label> Temp 4 Uso <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTempUse[3]) + "\" name=\"cfgTempUse3\"/></label>";
  html = html + "</div>";
  #endif

  #if (_USE_TRIAC_ == 1)
  html = html + "<div class=\"section\"><span>2.1</span>Triac tension salida (Vac)</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Triac 1 <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTriacVout[0]) + "\" name=\"cfgTriacVout0\"/></label>";
  html = html + "<label> Triac 2 <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTriacVout[1]) + "\" name=\"cfgTriacVout1\"/></label>";
  html = html + "<label> Triac 3 <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTriacVout[2]) + "\" name=\"cfgTriacVout2\"/></label>";
  html = html + "</div>";

  html = html + "<div class=\"section\"><span>2.2</span>Triac Uso</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> 0->No usado, 1-> Res. Principal, 2-> Res. Inyector</label>";
  html = html + "<label> Triac 1 <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTriacUse[0]) + "\" name=\"cfgTriacUse0\"/></label>";
  html = html + "<label> Triac 2 <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTriacUse[1]) + "\" name=\"cfgTriacUse1\"/></label>";
  html = html + "<label> Triac 3 <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTriacUse[2]) + "\" name=\"cfgTriacUse2\"/></label>";
  html = html + "</div>";
  #endif

  html = html + "<div class=\"section\"><span>3.1</span>Alarmas</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Alarma Principal (Minutos)<input type=\"text\"  maxlength=\"3\" value=\""  + String(cfgResPrimAlarMin)    + "\" name=\"cfgResPrimAlarMin\"/></label>";
  html = html + "<label> Alarma Inyectior (Minutos)<input type=\"text\"  maxlength=\"3\" value=\""  + String(cfgResInyeAlarMin)    + "\" name=\"cfgResInyeAlarMin\"/></label>";
  html = html + "<label> Alarma Agua (Minutos)<input type=\"text\"  maxlength=\"3\" value=\""       + String(cfgAguaAlarMin)       + "\" name=\"cfgAguaAlarMin\"/></label>";
  html = html + "</div>";

  html = html + "<div class=\"section\"><span>X</span>Otros</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Entradas Reposo <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicIns) + "\" name=\"cfgLogicIns\"/></label>";
  html = html + "<label> Salidas Reposo <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgLogicOuts) + "\" name=\"cfgLogicOuts\"/></label>";
  html = html + "<label> Modbus ID Temp <input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgMB1Add) + "\" name=\"cfgMB1Add\"/></label>";
  html = html + "</div>";

  #if (_USE_PWM_ == 1)
  html = html + "<div class=\"section\"><span>X</span>PWM</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<label> Ciclo <input type=\"text\"  maxlength=\"16\" value=\"" + String(pwmDutyCycle) + "\" name=\"pwmDutyCycle\"/></label>";
  html = html + "</div>";
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

void _setSETTINGS()
{
  int eeprom_value_hi, eeprom_value_lo;
  int response = 200;
    
  String html = "";
  
  String scfgResPrimInyeTemp = httpServer.arg("cfgResPrimInyeTemp");
  String scfgResPrimConsTemp = httpServer.arg("cfgResPrimConsTemp");
  String scfgResPrimHystTemp = httpServer.arg("cfgResPrimHystTemp");
  String scfgResInyeHystTemp = httpServer.arg("cfgResInyeHystTemp");
  String scfgAguaConsTemp    = httpServer.arg("cfgAguaConsTemp");
  String scfgAguaHystTemp    = httpServer.arg("cfgAguaHystTemp");

  String scfgResPrimAlarMin  = httpServer.arg("cfgResPrimAlarMin");
  String scfgResInyeAlarMin  = httpServer.arg("cfgResInyeAlarMin");
  String scfgAguaAlarMin     = httpServer.arg("cfgAguaAlarMin");

  #if (_USE_TRIAC_ == 1)
  String scfgTriacVout0     = httpServer.arg("cfgTriacVout0");
  String scfgTriacVout1     = httpServer.arg("cfgTriacVout1");
  String scfgTriacVout2     = httpServer.arg("cfgTriacVout2");

  String scfgTriacUse0      = httpServer.arg("cfgTriacUse0");
  String scfgTriacUse1      = httpServer.arg("cfgTriacUse1");
  String scfgTriacUse2      = httpServer.arg("cfgTriacUse2");
  #endif

  #if (_USE_MBRTU_ == 1)
  String scfgTempUse0       = httpServer.arg("cfgTempUse0");
  String scfgTempUse1       = httpServer.arg("cfgTempUse1");
  String scfgTempUse2       = httpServer.arg("cfgTempUse2");
  String scfgTempUse3       = httpServer.arg("cfgTempUse3");
  #endif

  #if (_USE_PWM_ == 1)
  String spwmDutyCycle       = httpServer.arg("pwmDutyCycle");
  #endif

  String scfgLogicIns        = httpServer.arg("cfgLogicIns");
  String scfgLogicOuts       = httpServer.arg("cfgLogicOuts");
  String scfgMB1Add          = httpServer.arg("cfgMB1Add");
  
  //String rdebugVal = httpServer.arg("tdebugVal");
  
  if ((scfgResPrimInyeTemp.length() == 0) ||
      (scfgResPrimConsTemp.length() == 0) ||
      (scfgResPrimHystTemp.length() == 0) ||
      (scfgResInyeHystTemp.length() == 0) ||
      (scfgAguaConsTemp.length() == 0)    ||
      (scfgAguaHystTemp.length() == 0)    ||

      (scfgResPrimAlarMin.length() == 0)  ||
      (scfgResInyeAlarMin.length() == 0)  ||
      (scfgAguaAlarMin.length() == 0)     ||

      #if (_USE_TRIAC_ == 1)
      (scfgTriacVout0.length() == 0)      ||
      (scfgTriacVout1.length() == 0)      ||
      (scfgTriacVout2.length() == 0)      ||

      (scfgTriacUse0.length() == 0)       ||
      (scfgTriacUse1.length() == 0)       ||
      (scfgTriacUse2.length() == 0)       ||
      #endif

      #if (_USE_MBRTU_ == 1)
      (scfgTempUse0.length() == 0)        ||
      (scfgTempUse1.length() == 0)        ||
      (scfgTempUse2.length() == 0)        ||
      (scfgTempUse3.length() == 0)        ||
      #endif

      #if (_USE_PWM_ == 1)
      (spwmDutyCycle.length() == 0)       ||
      #endif

      (scfgLogicIns.length() == 0)        ||
      (scfgLogicOuts.length() == 0)       ||
      (scfgMB1Add.length() == 0))

      //(rdebugVal.length() == 0))
  {
    response = 400;  // Error...
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Error... parametro vacío.");
    #endif
  }

  // Si no hay error...
  if (response == 200)
  {    
    cfgLogicIns  = scfgLogicIns.toInt();
    cfgLogicOuts = scfgLogicOuts.toInt();
    cfgMB1Add    = scfgMB1Add.length();

    cfgResPrimInyeTemp = scfgResPrimInyeTemp.toInt();
    cfgResPrimConsTemp = scfgResPrimConsTemp.toInt();
    cfgResPrimHystTemp = scfgResPrimHystTemp.toInt();
    cfgResInyeHystTemp = scfgResInyeHystTemp.toInt();
    cfgAguaConsTemp    = scfgAguaConsTemp.toInt();
    cfgAguaHystTemp    = scfgAguaHystTemp.toInt();

    cfgResPrimAlarMin  = scfgResPrimAlarMin.toInt();
    cfgResInyeAlarMin  = scfgResInyeAlarMin.toInt();
    cfgAguaAlarMin     = scfgAguaAlarMin.toInt();

    #if (_USE_TRIAC_ == 1)
    cfgTriacVout[0]  = scfgTriacVout0.toInt();
    cfgTriacVout[1]  = scfgTriacVout1.toInt();
    cfgTriacVout[2]  = scfgTriacVout2.toInt();

    cfgTriacUse[0]  = scfgTriacUse0.toInt();
    cfgTriacUse[1]  = scfgTriacUse1.toInt();
    cfgTriacUse[2]  = scfgTriacUse2.toInt();
    #endif

    #if (_USE_MBRTU_ == 1)
    cfgTempUse[0]  = scfgTempUse0.toInt();
    cfgTempUse[1]  = scfgTempUse1.toInt();
    cfgTempUse[2]  = scfgTempUse2.toInt();
    cfgTempUse[3]  = scfgTempUse3.toInt();
    #endif

    #if (_USE_PWM_ == 1)
    pwmDutyCycle = spwmDutyCycle.toInt();
    #endif
    
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
  
  if (response == 200)
    html += "<p class=\"sansserif\">Configuraci&oacuten guardada correctamente.</p>";
  else
    html += "<p class=\"sansserif\">Error el guardar la configuraci&oacuten. Revise los datos introducidos.</p>";

  html = html + "<div class=\"button-section\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Volver\"></a>";
  html = html + "</div>";

  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (response, "text/html", html);
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
  html = html + "<div class=\"section\"><span>1</span>IP</div>";
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
  html = html + "<div class=\"section\"><span>2</span>Broker </div>";
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
  int eeprom_value_hi, eeprom_value_lo;

  String html = "";
  int response = 200;
  int i, j, k, m;
  char schar;
  char sbuf[4];
  byte val[4];

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

  IPAddress localip;
  IPAddress localmask;
  IPAddress localgate;

  #if (_USE_MQTT_ == 1)
  // Check broker error
  if ((rbrokerurl.length() == 0)  ||
      (rbrokerport.length() == 0) ||
      (rbrokeruser.length() == 0) ||
      (rbrokerpswd.length() == 0))
    response = 400;
  #endif

  // If no error...
  if (response == 200)
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
    response = 400;
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
  
  if (response == 200)
    html += "<p class=\"sansserif\">Configuraci&oacuten guardada correctamente.</p>";
  else
    html += "<p class=\"sansserif\">Error el guardar la configuraci&oacuten. Revise los datos introducidos.</p>";

  html = html + "<div class=\"button-section\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Volver\"></a>";
  html = html + "</div>";

  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (response, "text/html", html);
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
  html = html + "<td style=\"width:60%\">Modo</td>";
  if (ctrMode == MODE_AUTO)
   html = html + "<td style=\"width:40%\"><font style=\"color:blue\">Autom&aacutetico</font></td>";
  else
   html = html + "<td style=\"width:40%\"><font style=\"color:red\">Test</font></td>";
  html = html + "</tr>";

  #if (_USE_ALARM_ == 1)
  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Alarmas</td>";
  html = html + "<td style=\"width:40%\">" + String(alarmOn[7]) + "-" + String(alarmOn[6]) + "-" + String(alarmOn[5]) + "-" + String(alarmOn[4]) + "-" + String(alarmOn[3]) + "-" + String(alarmOn[2]) + "-" + String(alarmOn[1]) + "-" + String(alarmOn[0]) + "</td>";
  html = html + "</tr>";
  #endif

  #if (_USE_TRIAC_ == 1)
  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Periodo de Red</td>";
  html = html + "<td style=\"width:40%\">" + triacZCPeriod + " ms</td>";
  html = html + "</tr>";
  #endif

  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

void _readINS()
{ 
  String html = "";

  html = "<table style=\"width:100%\">";

  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Entradas</td>";
  html = html + "<td style=\"width:40%\">" + String(InDig[0]) + "-" + String(InDig[1]) + "-" + String(InDig[2]) + "-" + String(InDig[3]) + "</td>";
  html = html + "</tr>";
  
  #if (_USE_MBRTU_ == 1)
  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Temperatura 1</td>";
  html = html + "<td style=\"width:40%\">" + String(mbTemp[0]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Temperatura 2</td>";
  html = html + "<td style=\"width:40%\">" + String(mbTemp[1]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Temperatura 3</td>";
  html = html + "<td style=\"width:40%\">" + String(mbTemp[2]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Temperatura 4</td>";
  html = html + "<td style=\"width:40%\">" + String(mbTemp[3]) + "</td>";
  html = html + "</tr>";
  #endif

  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

void _readOUTS()
{
  String html = "";

  html = "<table style=\"width:100%\">";
  
  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Reles</td>";
  html = html + "<td style=\"width:40%\">" + String(OutDig[5]) + "-" + String(OutDig[6]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Salidas</td>";
  html = html + "<td style=\"width:40%\">" + String(OutDig[0]) + "-" + String(OutDig[1]) + "-" + String(OutDig[2]) + "-" + String(OutDig[3]) + "-" + String(OutDig[4]) + "</td>";
  html = html + "</tr>";

  #if (_USE_TRIAC_ == 1)
  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Triacs</td>";
  html = html + "<td style=\"width:40%\">" + String(TriacCtr[2]) + "-" + String(TriacCtr[1]) + "-" + String(TriacCtr[0]) + "</td>";
  html = html + "</tr>";
  #endif

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
  if(out_number == "10")
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
  if(out_number == "11")
  {
    #if (_USE_WDE_ == 1)
    wdeForceReset = 1;
    #endif
      
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Watchdog reset");
    #endif
  }

  // Restore
  if(out_number == "12")
  {
    _ResetEEPROM();
    html = "Restore";
  }

  // Solo en modo Test
  if (ctrMode == MODE_TEST)
  {   
    // Out 1
    if(out_number == "1")
    {
      if (OutDig[0] == OUT_ON)
      {
        OutDig[0] = OUT_OFF;
        html = "O1 OFF";
      }
      else
      {
        OutDig[0] = OUT_ON;
        html = "O1 ON";
      }
    }
    // Out 2
    else if(out_number == "2")
    {
      if (OutDig[1] == OUT_ON)
      {
        OutDig[1] = OUT_OFF;
        html = "O2 OFF";
      }
      else
      {
        OutDig[1] = OUT_ON;
        html = "O2 ON";
      }
    }
    // Out 3
    else if(out_number == "3")
    {
      if (OutDig[2] == OUT_ON)
      {
        OutDig[2] = OUT_OFF;
        html = "O3 OFF";
      }
      else
      {
        OutDig[2] = OUT_ON;
        html = "O3 ON";
      }
    }
    // Out 4
    else if(out_number == "4")
    {
      if (OutDig[3] == OUT_ON)
      {
        OutDig[3] = OUT_OFF;
        html = "O4 OFF";
      }
      else
      {
        OutDig[3] = OUT_ON;
        html = "O4 ON";
      }
    }
    // Out 5
    else if(out_number == "5")
    {
      if (OutDig[4] == OUT_ON)
      {
        OutDig[4] = OUT_OFF;
        html = "O5 OFF";
      }
      else
      {
        OutDig[4] = OUT_ON;
        html = "O5 ON";
      }
    }
    // Out 6 - RL1
    else if(out_number == "6")
    {
      if (OutDig[5] == OUT_ON)
      {
        OutDig[5] = OUT_OFF;
        html = "O6 RL1 OFF";
      }
      else
      {
        OutDig[5] = OUT_ON;
        html = "O6 RL1 ON";
      }
    }
    // Out 7 - RL2
    else if(out_number == "7")
    {
      if (OutDig[6] == OUT_ON)
      {
        OutDig[6] = OUT_OFF;
        html = "O7 RL2 OFF";
      }
      else
      {
        OutDig[6] = OUT_ON;
        html = "O7 RL2 ON";
      }
    }
    #if (_USE_TRIAC_ == 1)
    // Triac 1
    else if(out_number == "31")
    {
      if (TriacCtr[0] == OUT_ON)
      {
        TriacCtr[0] = OUT_OFF;
        html = "Triac 1 OFF";
      }
      else
      {
        TriacCtr[0] = OUT_ON;
        html = "Triac 1 ON";
      }
    }
    // Triac 2
    else if(out_number == "32")
    {
      if (TriacCtr[1] == OUT_ON)
      {
        TriacCtr[1] = OUT_OFF;
        html = "Triac 2 OFF";
      }
      else
      {
        TriacCtr[1] = OUT_ON;
        html = "Triac 2 ON";
      }
    }
    // Triac 3
    else if(out_number == "33")
    {
      if (TriacCtr[2] == OUT_ON)
      {
        TriacCtr[2] = OUT_OFF;
        html = "Triac 3 OFF";
      }
      else
      {
        TriacCtr[2] = OUT_ON;
        html = "Triac 3 ON";
      }
    }
    #endif
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
  html = html + "<td style=\"width:60%\">Tiempo Encendio</td>";
  html = html + "<td style=\"width:40%\">" + String(timeDay) + "d " + timeOnString + "</td>";
  html = html + "</tr>";
  
  #if (_USE_NTP_ == 1)
  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Fecha NTP</td>";
  html = html + "<td style=\"width:40%\">" + mntpTimeString + "</td>";
  html = html + "</tr>";
  #endif
  
  #if (_USE_MQTT_ == 1)
  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">MQTT </td>";
  html = html + "<td style=\"width:40%\">" + String(mqttStatus) + "</td>";
  html = html + "</tr>";
  #endif

  #if (_USE_MBRTU_ == 1)
  html = html + "<tr>";
  html = html + "<td style=\"width:60%\">Modbus RTU</td>";
  html = html + "<td style=\"width:40%\">" + String(mbState) + "-" + String(mbNError) + "-" + String(mbNReply) + "-" + String(mbNRetry) + "</td>";
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
