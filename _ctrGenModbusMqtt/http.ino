void _HTTPSetup(void)
{
  httpStatus = HTTP_STOP;
}

void _HTTPStart(void)
{
  httpStatus = HTTP_INIT;
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
  html = html + "<h1>" + PROJECT + " #Estado<span>ESP8266 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";

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
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"11\" onclick=\"sendOUT(60)\">";
  html = html + "  <input type=\"button\" value=\"12\" onclick=\"sendOUT(61)\">";
  html = html + "  <input type=\"button\" value=\"13\" onclick=\"sendOUT(62)\">";
  html = html + "  <input type=\"button\" value=\"14\" onclick=\"sendOUT(63)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"15\" onclick=\"sendOUT(64)\">";
  html = html + "  <input type=\"button\" value=\"16\" onclick=\"sendOUT(65)\">";
  html = html + "  <input type=\"button\" value=\"17\" onclick=\"sendOUT(66)\">";
  html = html + "  <input type=\"button\" value=\"18\" onclick=\"sendOUT(67)\">";  
  html = html + "</p>";
  
  html = html + "<div class=\"section\"><span>6</span>Configuraci&oacuten</div>";
  html = html + "<p>";
  html = html + "  <a href=\"settings.htm\"><input type=\"button\" value=\"Red\"></a>";
  html = html + "  <a href=\"timeSettings.htm\"><input type=\"button\" value=\"Logic IOs\"></a>";
  html = html + "  <a href=\"ctrSettings.htm\"><input type=\"button\" value=\"Control\"></a>";
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

// Time Settings
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
  html = html + "<h1>" + PROJECT + " #Config<span>ESP8266 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
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
  html = html + "<label>ADC Config <input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCf) + "\" name=\"rADCf\"/></label>";
  html = html + "<label>ADC Alarm (/10)<input type=\"text\"  maxlength=\"16\" value=\"" + String((int)cfgADCal) + "\" name=\"rADCal\"/></label>";
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
  String rADCal      = httpServer.arg("rADCal");
  
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
      (rADCf.length() == 0)       ||
      (rADCal.length() == 0))
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
    cfgADCm  = rADCm.toInt();
    cfgADCb  = rADCb.toInt();
    cfgADCp  = rADCp.toInt();
    cfgADCs  = rADCs.toInt();
    cfgADCf  = rADCf.toInt();
    cfgADCal = rADCal.toInt();
    
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
    EEPROM.write(EEPROM_ADD_ADC_S,  (byte)cfgADCs);
    EEPROM.write(EEPROM_ADD_ADC_F,  (byte)cfgADCf);
    EEPROM.write(EEPROM_ADD_ADC_AL, (byte)cfgADCal);

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
  html = html + "<h1>" + PROJECT + " #Config<span>ESP8266 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
  
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

// Control Settings
void _serveCtrSETTINGS()
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
  html = html + "<h1>" + PROJECT + " #Config<span>ESP8266 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
  html = html + "<form method='get' action='setCtrSettings'>";

  // Temporizaciones
  html = html + "<div class=\"section\"><span>1</span>Temporizaciones</div>";
  html = html + "<div class=\"inner-wrap\">";
  
  html = html + "<label>Tiempo Buzzer (segundos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeBuzzerOn) + "\" name=\"timeBZ\"/></label>";
  html = html + "<label>Tiempo Start (segundos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeOutStart) + "\" name=\"timeStart\"/></label>";
  html = html + "<label>Tiempo Stop (segundos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeOutStop) + "\" name=\"timeStop\"/></label>";
  html = html + "<label>Tiempo Gen Alarma (segundos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeGenAl) + "\" name=\"timeGenAl\"/></label>";
  
  html = html + "</div>";
  html = html + "<div class=\"section\"><span>2</span>Temps Generador</div>";
  html = html + "<div class=\"inner-wrap\">";
  
  html = html + "<label>Tiempo P1 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeGenerador1P) + "\" name=\"time1\"/></label>";
  html = html + "<label>Tiempo P2 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeGenerador2P) + "\" name=\"time2\"/></label>";
  html = html + "<label>Tiempo P3 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeGenerador3P) + "\" name=\"time3\"/></label>";
  html = html + "<label>Tiempo P4 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeGenerador4P) + "\" name=\"time4\"/></label>";
  html = html + "<label>Tiempo P5 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeGenerador5P) + "\" name=\"time5\"/></label>";
  html = html + "<label>Tiempo P6 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeGenerador6P) + "\" name=\"time6\"/></label>";
  html = html + "<label>Tiempo P7 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeGenerador7P) + "\" name=\"time7\"/></label>";
  html = html + "<label>Tiempo P8 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeGenerador8P) + "\" name=\"time8\"/></label>";
  html = html + "<label>Tiempo P9 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeGenerador9P) + "\" name=\"time9\"/></label>";

  html = html + "</div>";
  html = html + "<div class=\"section\"><span>3</span>Temps OUTs</div>";
  html = html + "<div class=\"inner-wrap\">";
  
  html = html + "<label>Tiempo O11 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeO1X[0]) + "\" name=\"timeO11\"/></label>";
  html = html + "<label>Tiempo O12 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeO1X[1]) + "\" name=\"timeO12\"/></label>";
  html = html + "<label>Tiempo O13 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeO1X[2]) + "\" name=\"timeO13\"/></label>";
  html = html + "<label>Tiempo O14 (minutos)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeO1X[3]) + "\" name=\"timeO14\"/></label>";
  html = html + "<label>Tiempo O15 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeO1X[4]) + "\" name=\"timeO15\"/></label>";
  html = html + "<label>Tiempo O16 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeO1X[5]) + "\" name=\"timeO16\"/></label>";
  html = html + "<label>Tiempo O17 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeO1X[6]) + "\" name=\"timeO17\"/></label>";
  html = html + "<label>Tiempo O18 (horas)<input type=\"text\"  maxlength=\"16\" value=\"" + String(cfgTimeO1X[7]) + "\" name=\"timeO18\"/></label>";

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

void _setCtrSETTINGS()
{
  int eeprom_value_hi, eeprom_value_lo;
    
  String html = "";
  
  String rtimeBZ = httpServer.arg("timeBZ");
  String rtimeStart = httpServer.arg("timeStart");
  String rtimeStop = httpServer.arg("timeStop");
  String rtimeGenAl = httpServer.arg("timeGenAl");
    
  String rtime1 = httpServer.arg("time1");
  String rtime2 = httpServer.arg("time2");
  String rtime3 = httpServer.arg("time3");
  String rtime4 = httpServer.arg("time4");
  String rtime5 = httpServer.arg("time5");
  String rtime6 = httpServer.arg("time6");
  String rtime7 = httpServer.arg("time7");
  String rtime8 = httpServer.arg("time8");
  String rtime9 = httpServer.arg("time9");
  
  String rtimeO11 = httpServer.arg("timeO11");
  String rtimeO12 = httpServer.arg("timeO12");
  String rtimeO13 = httpServer.arg("timeO13");
  String rtimeO14 = httpServer.arg("timeO14");
  String rtimeO15 = httpServer.arg("timeO15");
  String rtimeO16 = httpServer.arg("timeO16");
  String rtimeO17 = httpServer.arg("timeO17");
  String rtimeO18 = httpServer.arg("timeO18");
  
  int error = 0;

  if ((rtimeBZ.length() == 0)    ||
      (rtimeStart.length() == 0) ||
      (rtimeStop.length() == 0)  ||
      (rtimeGenAl.length() == 0) ||
	  
      (rtime1.length() == 0)  ||
      (rtime2.length() == 0)  ||
      (rtime3.length() == 0)  ||
      (rtime4.length() == 0)  ||
      (rtime5.length() == 0)  ||
      (rtime6.length() == 0)  ||
      (rtime7.length() == 0)  ||
      (rtime8.length() == 0)  ||
      (rtime9.length() == 0)  ||

	    (rtimeO11.length() == 0)  ||
      (rtimeO12.length() == 0)  ||
      (rtimeO13.length() == 0)  ||
      (rtimeO14.length() == 0)  ||
      (rtimeO15.length() == 0)  ||
      (rtimeO16.length() == 0)  ||
      (rtimeO17.length() == 0)  ||
      (rtimeO18.length() == 0))
  {
    error = 1;  // falta un campo...
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Error... parametro vacío.");
    #endif
  }

  // Si no hay error...
  if (error == 0)
  {
    cfgTimeBuzzerOn = rtimeBZ.toInt();
    cfgTimeOutStart = rtimeStart.toInt();
    cfgTimeOutStop = rtimeStop.toInt();
    cfgTimeGenAl = rtimeGenAl.toInt();

    cfgTimeGenerador1P = rtime1.toInt();
    cfgTimeGenerador2P = rtime2.toInt();
    cfgTimeGenerador3P = rtime3.toInt();
    cfgTimeGenerador4P = rtime4.toInt();
    cfgTimeGenerador5P = rtime5.toInt();
    cfgTimeGenerador6P = rtime6.toInt();
    cfgTimeGenerador7P = rtime7.toInt();
    cfgTimeGenerador8P = rtime8.toInt();
    cfgTimeGenerador9P = rtime9.toInt();
    
    cfgTimeO1X[0] = rtimeO11.toInt();
	  cfgTimeO1X[1] = rtimeO12.toInt();
    cfgTimeO1X[2] = rtimeO13.toInt();
	  cfgTimeO1X[3] = rtimeO14.toInt();
	  cfgTimeO1X[4] = rtimeO15.toInt();
	  cfgTimeO1X[5] = rtimeO16.toInt();
	  cfgTimeO1X[6] = rtimeO17.toInt();
	  cfgTimeO1X[7] = rtimeO18.toInt();

    #if (_HTTP_SERIAL_DEBUG_ == 1)  
    Serial.print("Time 1P: ");  Serial.print (cfgTimeGenerador1P);  Serial.println(" min");
    Serial.print("Time 2P: ");  Serial.print (cfgTimeGenerador2P);  Serial.println(" min");
    Serial.print("Time 3P: ");  Serial.print (cfgTimeGenerador3P);  Serial.println(" min");
    Serial.print("Time 4P: ");  Serial.print (cfgTimeGenerador4P);  Serial.println(" min");
    Serial.print("Time 5P: ");  Serial.print (cfgTimeGenerador5P);  Serial.println(" min");
    Serial.print("Time 6P: ");  Serial.print (cfgTimeGenerador6P);  Serial.println(" hour");
    Serial.print("Time 7P: ");  Serial.print (cfgTimeGenerador7P);  Serial.println(" hour");
    Serial.print("Time 8P: ");  Serial.print (cfgTimeGenerador8P);  Serial.println(" hour");
    Serial.print("Time 9P: ");  Serial.print (cfgTimeGenerador9P);  Serial.println(" hour");

    Serial.print("Time Buzzer: ");  Serial.print (cfgTimeBuzzerOn);  Serial.println(" secs");
    Serial.print("Time Start: ");   Serial.print (cfgTimeOutStart);  Serial.println(" secs");
    Serial.print("Time Stop: ");    Serial.print (cfgTimeOutStop);   Serial.println(" secs");
    Serial.print("Time Gen Al: ");  Serial.print (cfgTimeGenAl);     Serial.println(" secs");
  
	  Serial.print("Time O11: ");  Serial.print (cfgTimeO1X[0]);  Serial.println(" min");
	  Serial.print("Time O12: ");  Serial.print (cfgTimeO1X[1]);  Serial.println(" min");
	  Serial.print("Time O13: ");  Serial.print (cfgTimeO1X[2]);  Serial.println(" min");
	  Serial.print("Time O14: ");  Serial.print (cfgTimeO1X[3]);  Serial.println(" min");
	  Serial.print("Time O15: ");  Serial.print (cfgTimeO1X[4]);  Serial.println(" hour");
	  Serial.print("Time O16: ");  Serial.print (cfgTimeO1X[5]);  Serial.println(" hour");
	  Serial.print("Time O17: ");  Serial.print (cfgTimeO1X[6]);  Serial.println(" hour");
	  Serial.print("Time O18: ");  Serial.print (cfgTimeO1X[7]);  Serial.println(" hour");
    
    #endif   

    // Data 
    EEPROM.write(EEPROM_ADD_1P_TIMER_GEN, cfgTimeGenerador1P);
    EEPROM.write(EEPROM_ADD_2P_TIMER_GEN, cfgTimeGenerador2P);
    EEPROM.write(EEPROM_ADD_3P_TIMER_GEN, cfgTimeGenerador3P);
    EEPROM.write(EEPROM_ADD_4P_TIMER_GEN, cfgTimeGenerador4P);
    EEPROM.write(EEPROM_ADD_5P_TIMER_GEN, cfgTimeGenerador5P);
    EEPROM.write(EEPROM_ADD_6P_TIMER_GEN, cfgTimeGenerador6P);
    EEPROM.write(EEPROM_ADD_7P_TIMER_GEN, cfgTimeGenerador7P);
    EEPROM.write(EEPROM_ADD_8P_TIMER_GEN, cfgTimeGenerador8P);
    EEPROM.write(EEPROM_ADD_9P_TIMER_GEN, cfgTimeGenerador9P);

    EEPROM.write(EEPROM_ADD_BUZZER_ON, cfgTimeBuzzerOn);
    EEPROM.write(EEPROM_ADD_TSTART,    cfgTimeOutStart);
    EEPROM.write(EEPROM_ADD_TSTOP,     cfgTimeOutStop);
    EEPROM.write(EEPROM_ADD_GEN_AL,    cfgTimeGenAl);
        
	  EEPROM.write(EEPROM_ADD_O11_TIMER,   cfgTimeO1X[0]);
	  EEPROM.write(EEPROM_ADD_O12_TIMER,   cfgTimeO1X[1]);
	  EEPROM.write(EEPROM_ADD_O13_TIMER,   cfgTimeO1X[2]);
	  EEPROM.write(EEPROM_ADD_O14_TIMER,   cfgTimeO1X[3]);
	  EEPROM.write(EEPROM_ADD_O15_TIMER,   cfgTimeO1X[4]);
	  EEPROM.write(EEPROM_ADD_O16_TIMER,   cfgTimeO1X[5]);
	  EEPROM.write(EEPROM_ADD_O17_TIMER,   cfgTimeO1X[6]);
	  EEPROM.write(EEPROM_ADD_O18_TIMER,   cfgTimeO1X[7]);

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
  html = html + "<h1>" + PROJECT + " #Config<span>ESP8266 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
  
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
void _serveSETTINGS()
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
  html = html + "<h1>" + PROJECT + " #Red Config<span>ESP8266 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
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

  #if (_USE_MBTCP_ == 1)
  // Modbus TCP
  html = html + "<div class=\"section\"><span>4</span>Modbus TCP </div>";
  html = html + "<div class=\"inner-wrap\">";

  html = html + "<label>IP Address <input type=\"text\"  maxlength=\"16\" value=\"" + String(mbIpAddress.toString()) + "\" name=\"mbipaddress\"/></label>";
  html = html + "<label>Port <input type=\"text\" maxlength=\"16\" value=\"" + String(mbPort) + "\" name=\"mbport\"/></label>";

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

void _setSETTINGS()
{
  String rwmode = httpServer.arg("wifimode");
  String rssid = httpServer.arg("ssid");
  String rpass = httpServer.arg("pass");
  
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

  #if (_USE_MBTCP_ == 1)
  String rmbipaddress = httpServer.arg("mbipaddress");
  String rmbport = httpServer.arg("mbport");
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

  #if (_USE_MQTT_ == 1)
  // Check broker error
  if ((rbrokerurl.length() == 0)  ||
      (rbrokerport.length() == 0) ||
      (rbrokeruser.length() == 0) ||
      (rbrokerpswd.length() == 0))
    error = 1;
  #endif

  #if (_USE_MBTCP_ == 1)
  if ((rmbipaddress.length() == 0)  ||
      (rmbport.length() == 0))
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
     #endif

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
     
     #if (_USE_MBTCP_ == 1)
     // Modbus IP
     j = rmbipaddress.length();
     k = 0;
     m = 0;
     for (i = 0; i < j; i++)
     {
       schar = rmbipaddress[i];
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
     mbIpAddress = IPAddress(val[0], val[1], val[2], val[3]);
    
     EEPROM.write(EEPROM_ADD_MB_IP1, val[0]);
     EEPROM.write(EEPROM_ADD_MB_IP2, val[1]);
     EEPROM.write(EEPROM_ADD_MB_IP3, val[2]);
     EEPROM.write(EEPROM_ADD_MB_IP4, val[3]);

     // Modbus Port
     mbPort = rmbport.toInt();
     eeprom_value_lo = mbPort & 0x00FF;
     EEPROM.write(EEPROM_ADD_MB_PORT, eeprom_value_lo);
     eeprom_value_hi = (mbPort & 0xFF00)>>8;
     EEPROM.write(EEPROM_ADD_MB_PORT + 1, eeprom_value_hi);
     #endif

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

     #if (_USE_MQTT_ == 1)
     // Broker configuration
     Serial.print("---->Broker Url: ");
     Serial.println(rbrokerurl);
     Serial.print("---->Broker Port: ");
     Serial.println(rbrokerport);     
     #endif

     #if (_USE_MBTCP_ == 1)
     Serial.print("---->Modbus TCP IP: ");
     Serial.println(mbIpAddress);
     Serial.print("---->Modbus TCP Port: ");
     Serial.println(mbPort);
     #endif

     #endif // (_HTTP_SERIAL_DEBUG_ == 1)
     
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
  html = html + "<h1>" + PROJECT + " #Config<span>ESP8266 tech</span><span align=\"right\"> Ver: " + compdate + " " + comptime + "</span></h1>";
  
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

  html = "<table style=\"width:100%\">";

  html = html + "<tr>";
  html = html + "<td>Modo</td>";
  if (controlMode == MODE_AUTO)
   html = html + "<td><font style=\"color:blue\">Autom&aacutetico</font></td>";
  else
   html = html + "<td><font style=\"color:red\">Test</font></td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Control " + String(ControlState) + "</td>";
  if (ControlState == STATE_START)
    html = html + "<td><font style=\"color:blue\">Arrancando...</font></td>";
  else if (ControlState == STATE_GEN_ON)
    html = html + "<td><font style=\"color:green\">Bomba: ON - Gen: ON</font></td>";
  else if (ControlState == STATE_GEN_ZUMB)
    html = html + "<td><font style=\"color:red\">Buzzer aviso...</font></td>";
  else if (ControlState == STATE_GEN_OFF)
    html = html + "<td><font style=\"color:red\">Bomba: ON - Gen: OFF</font></td>";
  else
    html = html + "<td><font style=\"color:grey\">Bomba: OFF - Gen: OFF</font></td>";

  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Tiempo OFF</td>";
  html = html + "<td>" + String(genTimeDay) + "d " + genTimeOnString + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>LCD </td>";
  html = html + "<td>" + String(DisplayIndicador) + " -> " + String(OutD) + "-" + String(OutC) + "-" + String(OutB) + "-" + String(OutA) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Sec cdown</td>";
  html = html + "<td>" + String(TimeControlSec) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Mins ON</td>";
  html = html + "<td>" + String(genMinOn) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Alarmas </td>";
  html = html + "<td>" + String(alarm[0]) + String(alarm[1]) + String(alarm[2]) + String(alarm[3]) + String(alarm[4]) + String(alarm[5]) + String(alarm[6]) + String(alarm[7]) + "</td>";
  html = html + "</tr>";
  html = html + "<tr>";
  html = html + "<td>  </td>";
  html = html + "<td>" + String(alarm[8]) + String(alarm[9]) + String(alarm[10]) + String(alarm[11]) + String(alarm[12]) + String(alarm[13]) + String(alarm[14]) + String(alarm[15]) + "</td>";
  html = html + "</tr>";
  html = html + "<tr>";
  html = html + "<td> </td>";
  html = html + "<td>" + String(alarm[16]) + String(alarm[17]) + String(alarm[18]) + String(alarm[19]) + String(alarm[20]) + String(alarm[21]) + String(alarm[22]) + String(alarm[23]) + "</td>";
  html = html + "</tr>";
  
  #if (_USE_MB_ == 1)
  html = html + "<tr>";
  html = html + "<td>Modbus St</td>";
  html = html + "<td>" + String(mbState) + " " + String(mbNError) + " - " +  String(mbNReply) + " - " + String(mbNRetry) + "</td>";
  html = html + "</tr>";
  #endif // (_USE_MB_ == 1)
  
  html = html + "<tr>";
  html = html + "<td>-----------------</td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>Generador</td>";
  if (OutGen == OUT_ON)
   html = html + "<td><font style=\"color:green\">Activado</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">Desactivado</font></td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Bomba</td>";
  if (OutBomba == OUT_ON)
   html = html + "<td><font style=\"color:green\">Activado</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">Desactivado</font></td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Zumbador</td>";
  if (OutZumb == OUT_ON)
   html = html + "<td><font style=\"color:blue\">Activado</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">Desactivado</font></td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Display</td>";
  if (OutDisp == OUT_ON)
   html = html + "<td><font style=\"color:blue\">Activado</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">Desactivado</font></td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>RELE: Control Estado</td>";
  html = html + "<td>" + mbctrInState[1] + mbctrInState[0] + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>RELE: Salida Estado</td>";
  html = html + "<td>" + mbctrOutState[1] + mbctrOutState[0] + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>RELE: Contador</td>";
  html = html + "<td>" + String(mbctrOutTick) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Consumos Luz</td>";
  html = html + "<td>" + String(mbRMSval[0]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Consumos Enchufes</td>";
  html = html + "<td>" + String(mbRMSval[1]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>In DC2 </td>";
  html = html + "<td>" + String(mbDCval[0]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>In DC3 </td>";
  html = html + "<td>" + String(mbDCval[1]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>In DC4 Reserva</td>";
  html = html + "<td>" + String(mbDCval[2]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>In DC5 Bateria 24Vdc</td>";
  html = html + "<td>" + String(mbDCval[3]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>In DC6 Bateria Generador</td>";
  html = html + "<td>" + String(mbDCval[4]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>In DC7 Alimentacion</td>";
  html = html + "<td>" + String(mbDCval[5]) + "</td>";
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
  html = html + "<td>" + String(ioInA) + "-" + String(ioInB) + "-" + String(ioInC) + "-" + String(ioInD) + "</td>";
  html = html + "</tr>";
  
  #if (_USE_MB_ == 1)
  html = html + "<tr>";
  html = html + "<td>Modbus Ins</td>";
  html = html + "<td>" + String(mbIns[0][0]) + "-" + String(mbIns[1][0]) + "-" + String(mbIns[2][0]) + "-" + String(mbIns[3][0]) + "-" + String(mbIns[4][0]) + "-" + String(mbIns[5][0]) + "-" + String(mbIns[6][0]) + "-" + String(mbIns[7][0]) + "</td>";
  html = html + "<td>" + String(mbIns[0][1]) + "-" + String(mbIns[1][1]) + "-" + String(mbIns[2][1]) + "-" + String(mbIns[3][1]) + "-" + String(mbIns[4][1]) + "-" + String(mbIns[5][1]) + "-" + String(mbIns[6][1]) + "-" + String(mbIns[7][1]) + "</td>";
  html = html + "</tr>";
  #endif // (_USE_MB_ == 1)
 
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
  html = html + "<td>Boards Outs</td>";
  html = html + "<td>" + String(ioOutA) + "-" + String(ioOutB) + "-" + String(ioOutC) + "</td>";
  html = html + "</tr>";

  #if (_USE_MB_ == 1)
  
  html = html + "<tr>";
  html = html + "<td>Modbus Outs</td>";
  html = html + "<td>" + String(mbOuts[0][0]) + "-" + String(mbOuts[1][0]) + "-" + String(mbOuts[2][0]) + "-" + String(mbOuts[3][0]) + "-" + String(mbOuts[4][0]) + "-" + String(mbOuts[5][0]) + "-" + String(mbOuts[6][0]) + "-" + String(mbOuts[7][0]) + "</td>";
  html = html + "<td>" + String(mbOuts[0][1]) + "-" + String(mbOuts[1][1]) + "-" + String(mbOuts[2][1]) + "-" + String(mbOuts[3][1]) + "-" + String(mbOuts[4][1]) + "-" + String(mbOuts[5][1]) + "-" + String(mbOuts[6][1]) + "-" + String(mbOuts[7][1]) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Modbus ROuts</td>";
  html = html + "<td>" + String(mbROuts[0][0]) + "-" + String(mbROuts[1][0]) + "-" + String(mbROuts[2][0]) + "-" + String(mbROuts[3][0]) + "-" + String(mbROuts[4][0]) + "-" + String(mbROuts[5][0]) + "-" + String(mbROuts[6][0]) + "-" + String(mbROuts[7][0]) + "</td>";
  html = html + "<td>" + String(mbROuts[0][1]) + "-" + String(mbROuts[1][1]) + "-" + String(mbROuts[2][1]) + "-" + String(mbROuts[3][1]) + "-" + String(mbROuts[4][1]) + "-" + String(mbROuts[5][1]) + "-" + String(mbROuts[6][1]) + "-" + String(mbROuts[7][1]) + "</td>";
  html = html + "</tr>";
  
  #endif // (_USE_MB_ == 1)
  
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

  // Solo en modo Test
  if (controlMode == MODE_TEST)
  {   
    // Out A
    if(out_number == "10")
    {
      if (ioOutA == OUT_ON)
      {
        ioOutA = OUT_OFF;
        html = "Out A OFF";
      }
      else
      {
        ioOutA = OUT_ON;
        html = "Out A ON";
      }
    }
    // Out B
    else if(out_number == "11")
    {
      if (ioOutB == OUT_ON)
      {
        ioOutB = OUT_OFF;
        html = "Out B OFF";
      }
      else
      {
        ioOutB = OUT_ON;
        html = "Out B ON";
      }
    }
    // Out C
    else if(out_number == "12")
    {
      if (ioOutC == OUT_ON)
      {
        ioOutC = OUT_OFF;
        html = "Out C OFF";
      }
      else
      {
        ioOutC = OUT_ON;
        html = "Out C ON";
      }
    }

    #if (_USE_MB_ == 1)
    
    // Outs
    if ((out_number == "50") || (out_number == "51") || (out_number == "52") || (out_number == "53") ||
        (out_number == "54") || (out_number == "55") || (out_number == "56") || (out_number == "57"))
    {
      mbOutBoard = 0;
      
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
      
      if (mbOuts[mbOutNum][mbOutBoard] == OUT_OFF)
        mbOutVal = OUT_ON;
      else
        mbOutVal = OUT_OFF;
  
      if (mbState == MB_STANDBY)
        mbState = MB_WRITEOUT;
      
      html = "Outs";
    }
  
    // Outs
    if ((out_number == "60") || (out_number == "61") || (out_number == "62") || (out_number == "63") ||
        (out_number == "64") || (out_number == "65") || (out_number == "66") || (out_number == "67"))
    {
      mbOutBoard = 1;
      
      if (out_number == "60")
        mbOutNum = 0; // O1
      else if (out_number == "61")
        mbOutNum = 1; // O2
      else if (out_number == "62")
        mbOutNum = 2; // O3
      else if (out_number == "63")
        mbOutNum = 3; // O4
      else if (out_number == "64")
        mbOutNum = 4; // O5
      else if (out_number == "65")
        mbOutNum = 5; // O6
      else if (out_number == "66")
        mbOutNum = 6; // O7     
      else
        mbOutNum = 7; // O8
      
      if (mbOuts[mbOutNum][mbOutBoard] == OUT_OFF)
        mbOutVal = OUT_ON;
      else
        mbOutVal = OUT_OFF;
  
      if (mbState == MB_STANDBY)
        mbState = MB_WRITEOUT;
      
      html = "Outs";
    }

    #endif // (_USE_MB_ == 1)
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
  
  html = html + "<tr>";
  html = html + "<td>Fecha NTP</td>";
  html = html + "<td>" + mntpTimeString + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Solar</td>";
  html = html + "<td>" + solarString + "</td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>Free RAM</td>";
  html = html + "<td>" + String(freeRam) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Wi-Fi </td>";
  html = html + "<td>" + String(wifiStatus) + "</td>";
  html = html + "</tr>";

  #if (_USE_MQTT_ == 1)
  html = html + "<tr>";
  html = html + "<td>MQTT </td>";
  html = html + "<td>" + String(mqttStatus) + "</td>";
  html = html + "</tr>";
  #endif

  html = html + "<tr>";
  html = html + "<td>Alarma </td>";
  html = html + "<td>" + String(alState) + " " + String(alNotify) + "-" + String(AL_NOTIFY_CONT) + "</td>";
  html = html + "</tr>";

  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

///////////////
// Http loop //
///////////////
void _HTTPLoop()
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
      httpServer.on("/ctrSettings.htm",   _serveCtrSETTINGS);

      // acctions
      httpServer.on("/readCTR",          _readCTR);
      httpServer.on("/setOUTS",          _setOUTS);      
      httpServer.on("/readOUTS",         _readOUTS);
      httpServer.on("/readINS",          _readINS);
      httpServer.on("/readSTATUS",        _readSTATUS);
      httpServer.on("/networSettings",   _setSETTINGS);
      httpServer.on("/setTimeSettings",  _setTimeSETTINGS);
      httpServer.on("/setCtrSettings",   _setCtrSETTINGS);

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
