
/////////////////
// Time set up //
/////////////////
void _TimeSetup(void)
{
  timeTick = millis();
  timeSec = 0;
  timeMin = 0;
  timeHour = 0;
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

#if (_STATUS_SERIAL_DEBUG_ == 1)
    
    Serial.println("<><><><><><><>");
    Serial.print("Tiempo Encendio: ");
    Serial.print(timeHour); Serial.print(" : "); Serial.print(timeMin); Serial.print(" : "); Serial.print(timeSec);
    Serial.println(" ");
    /*
    Serial.print("Cuenta Atras (Segundos): ");
    Serial.print(TimeControlSec);
    Serial.println(" ");

    Serial.print("Cuenta Ticks (ms): ");
    Serial.print(millis() - ControlTick);
    Serial.println(" ");
    */
    Serial.print("Indicador LCD: ");
    Serial.print(DisplayIndicador);
    Serial.print(" -> ");
    Serial.print(InD); Serial.print("-"); Serial.print(InC); Serial.print("-"); Serial.print(InB); Serial.print("-"); Serial.print(InA);
    Serial.println(" ");
    Serial.println("---------------");

    /*
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
    */
    
    if (OutRemotePuls == OUT_ON)
     Serial.println("Remote Puls: ON");
    else
     Serial.println("Remote Puls: OFF");

    Serial.print("Vbatt: ");
    Serial.println(VbattInValue);

    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
