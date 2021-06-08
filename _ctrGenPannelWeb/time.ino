
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

    Serial.print("Tiempo Encendio: ");
    Serial.print(timeHour); Serial.print(" : "); Serial.print(timeMin); Serial.print(" : "); Serial.print(timeSec);
    Serial.println(" ");
 
    Serial.print("Cuenta Atras (Segundos): ");
    Serial.print(TimeControlSec);
    Serial.println(" ");

    Serial.print("Indicador LCD: ");
    Serial.print(DisplayIndicador);
    Serial.print(" -> ");
    Serial.print(OutD6); Serial.print("-"); Serial.print(OutD5); Serial.print("-"); Serial.print(OutD4); Serial.print("-"); Serial.print(OutD3);
    Serial.println(" ");
     
    if (PulsadorDigInStatus == IO_ON)
     Serial.println("Pulsador: ON");
    else
     Serial.println("Pulsador: OFF");

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

    Serial.println(">>>>>>>>>");
    Serial.println(" ");

    #endif
  }
}
