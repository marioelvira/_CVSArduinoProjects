
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
    if (TimeControlSec != 0)
      TimeControlSec--;
    
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

      _GenTimeLoop();
      //genMinOn++;
    }
    
    timeTick = millis();

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
    
    Serial.print("Indicador LCD: ");
    Serial.print(DisplayIndicador);
    Serial.print(" -> ");
    Serial.print(InD); Serial.print("-"); Serial.print(InC); Serial.print("-"); Serial.print(InB); Serial.print("-"); Serial.print(InA);
    Serial.println(" ");
    if (InGenOn == IO_OFF)
      Serial.print("Gen In: OFF");
    else
      Serial.print("Gen In: ON");
    Serial.println(" ");
    Serial.println("---------------");
    
    Serial.print("Control Status: ");
    Serial.println(ControlState);  
    Serial.println("---------------");

    Serial.print("Gen Status: ");
    Serial.print(genState); Serial.print(" "); Serial.print(genMinOn); Serial.println("m ");
    Serial.print(genTimeDay); Serial.print("d "); Serial.print(genTimeHour); Serial.print(" : "); Serial.print(genTimeMin); Serial.print(" : "); Serial.print(genTimeSec);
    Serial.println(" ");
    Serial.println("---------------");
 
    Serial.print("Luz Off Status: ");
    Serial.println(LuzState);  
    Serial.println("---------------");

    Serial.print("Wi-Fi Status: ");
    Serial.println(wifiStatus);  
    Serial.println("---------------");
        
    if (OutGenPuls == OUT_ON)
     Serial.println("Gen Puls: ON");
    else
     Serial.println("Gen Puls: OFF");

    if (OutStopPuls == OUT_ON)
     Serial.println("Gen Stop: ON");
    else
     Serial.println("Gen Stop: OFF");

    if (OutLuzOff == OUT_ON)
     Serial.println("Luz OFF: ON");
    else
     Serial.println("Luz OFF: OFF");

    _ADCLoop();
    Serial.print("Vbatt In Dig: ");
    Serial.println(VbattInADC);
    Serial.print("Vbatt In: ");
    Serial.println(VbattIn);    

    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
