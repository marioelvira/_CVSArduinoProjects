
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
    
    Serial.print("Ins: ");
    Serial.print(InD); Serial.print("-"); Serial.print(InC); Serial.print("-"); Serial.print(InB); Serial.print("-"); Serial.print(InA);
    Serial.println(" ");
    Serial.println("---------------");
    
    Serial.print("Control Status: ");
    Serial.println(ControlState);
    Serial.print("Control Tick: ");
    Serial.println((millis() - ControlTick)/1000);
    Serial.println("---------------");
 
    Serial.print("Wi-Fi Status: ");
    Serial.println(wifiStatus);
    Serial.println("---------------");

    if (OutBattA == OUT_ON)
     Serial.println("OutBattA: ON");
    else
     Serial.println("OutBattA: OFF");

    if (OutBattB == OUT_ON)
     Serial.println("OutBattB: ON");
    else
     Serial.println("OutBattB: OFF");
     
    if (OutBattC == OUT_ON)
     Serial.println("OutBattC: ON");
    else
     Serial.println("OutBattC: OFF");

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
