
/////////////////
// Time set up //
/////////////////
void _TimeSetup(void)
{
  timeTick = millis();
  timeSec = 0;
  timeMin = 0;
  timeHour = 0;

  #if (_USE_FREERAM_ == 1)
  // RAM setup
  _RAMSetup();
  #endif
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
      }
    }
    
    timeTick = millis();

    _RMPLoop();

    #if (_USE_FREERAM_ == 1)
    _FreeRAM();
    #endif

    #if (_USE_WDE_ == 1)
    _WDELoop();
    #endif

    if (boardLed == OUT_OFF)
      boardLed = OUT_ON;
    else
      boardLed = OUT_OFF;

    #if (_STATUS_SERIAL_DEBUG_ == 1)
    
    Serial.println("<><><><><><><>");
    Serial.print("Tiempo Encendio: ");
    Serial.print(timeHour); Serial.print(" : "); Serial.print(timeMin); Serial.print(" : "); Serial.print(timeSec);
    Serial.println(" ");

    #if (_USE_FREERAM_ == 1)
    Serial.print("Free RAM: ");
    Serial.println(freeRam);
    #endif
 
    Serial.print("Cuenta Atras (Segundos): ");
    Serial.print(TimeControlSec);
    Serial.println(" ");

    Serial.print("Cuenta Ticks (ms): ");
    Serial.print(millis() - ControlTick);
    Serial.println(" ");

    Serial.print("Indicador LCD: ");
    Serial.print(DisplayIndicador);
    Serial.print(" -> ");
    Serial.print(OutD); Serial.print("-"); Serial.print(OutC); Serial.print("-"); Serial.print(OutB); Serial.print("-"); Serial.print(OutA);
    Serial.println(" ");
    Serial.println("---------------");
    
    Serial.print("Control Status "); Serial.println(ControlState);
    if (ControlState == STATE_START)
      Serial.println("  Arrancando...");
    else if (ControlState == STATE_GEN_ON)
      Serial.println("  Bomba: ON - Gen: ON");
    else if (ControlState == STATE_GEN_ZUMB)
      Serial.println("  Buzzer aviso...");
    else if (ControlState == STATE_GEN_OFF)
      Serial.println("  Bomba: ON - Gen: OFF");
    else
      Serial.println("  Bomba: OFF - Gen: OFF");

    Serial.println("---------------");

    if (InStartVal == IO_ON)
     Serial.println("Marcha: ON");
    else
     Serial.println("Marcha: OFF");

    if (InEndVal == IO_ON)
     Serial.println("Paro: ON");
    else
     Serial.println("Paro: OFF");

    Serial.println("---------------");

    //Serial.print("intNumberD2: ");  Serial.println(inPulseD2);
    Serial.print("intNumberD3: ");    Serial.println(inPulseD3);
    Serial.print("RPM in D3: ");      Serial.println(RpmCounter);
        
    Serial.println("---------------");

    if (OutGen == OUT_ON)
     Serial.println("Generador: ON");
    else
     Serial.println("Generador: OFF");
    
    if (OutZumb == OUT_ON)
     Serial.println("Zumbador: ON");
    else
     Serial.println("Zumbador: OFF");

    if (OutDisp == OUT_ON)
     Serial.println("Display: ON");
    else
     Serial.println("Display: OFF");

    _ADCLoop();
    Serial.print("Vbatt In Dig: ");
    Serial.println(VbattInADC);
    //Serial.print("Vbatt In: ");
    //Serial.println(VbattIn); 

    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}