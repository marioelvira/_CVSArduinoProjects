
/////////////////
// Time set up //
/////////////////
void _TimeSetup(void)
{
  timeTick = millis();
  timeSec = 0;
  timeMin = 0;
  timeHour = 0;
  timeDay = 0;

  // RAM setup
  _RAMSetup();
}

////////////////////////
// Time state machine //
////////////////////////
void _TimeLoop(void)
{
  if (millis() - timeTick >= 1000)
  {
    //if (TimeControlSec != 0)
    //  TimeControlSec--;

    timeSec++;
    if (timeSec >= 60)
    {
      timeSec = 0;
      timeMin++;
      if (timeMin >= 60)
      {
        timeMin = 0;
        timeHour++;
        if (timeHour >= 24)
        {
          timeHour = 0;
          timeDay++;
        }
      }

    }
    
    timeTick = millis();

    _NTCLoop();
    _FreeRAM();
    #if (_USE_WDE_ == 1)
    _WDELoop();
    #endif
    
    #if (_STATUS_SERIAL_DEBUG_ == 1)
    
    Serial.println("<><><><><><><>");
    Serial.print("Tiempo Encendio: ");
    Serial.print(timeDay); Serial.print("d "); Serial.print(timeHour); Serial.print(" : "); Serial.print(timeMin); Serial.print(" : "); Serial.print(timeSec);
    Serial.println(" ");

    Serial.print("Free RAM: ");
    Serial.println(freeRam);
    
    Serial.print("Control Status: ");
    Serial.println(ControlState);  

    Serial.print("Window Status: ");
    Serial.println(windowState);

    Serial.print("Wi-Fi Status: ");
    Serial.println(wifiStatus);  
    Serial.println("---------------");

    if (OutOpen == OUT_ON)
     Serial.println("OutOpen: ON");
    else
     Serial.println("OutOpen: OFF");

    if (OutClose == OUT_ON)
     Serial.println("OutClose: ON");
    else
     Serial.println("OutClose: OFF");

    if (OutFan == OUT_ON)
     Serial.println("FAN: ON");
    else
     Serial.println("FAN: OFF");

    if (OutPump == OUT_ON)
     Serial.println("PUMP: ON");
    else
     Serial.println("PUMP: OFF");

    if (OutIrri == OUT_ON)
     Serial.println("IRRI: ON");
    else
     Serial.println("IRRI: OFF");

    if (OutAux1 == OUT_ON)
     Serial.println("AUX1: ON");
    else
     Serial.println("AUX1: OFF");

    if (OutAux2 == OUT_ON)
     Serial.println("AUX2: ON");
    else
     Serial.println("AUX2: OFF");
     
    Serial.print("NTC In Dig: ");
    Serial.println(NtcInADC);
    Serial.print("NTC In: ");
    Serial.println(NtcIn);
    Serial.print("NTC R: ");
    Serial.println(NtcR); 

    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
