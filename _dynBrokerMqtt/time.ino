
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
}

////////////////////////
// Time state machine //
////////////////////////
void _TimeLoop(void)
{
  if (millis() - timeTick >= 1000)
  {   
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

    #if (_STATUS_SERIAL_DEBUG_ == 1)
        
    Serial.println("<><><><><><><>");
    Serial.print("Tiempo Encendio: ");
    Serial.print(timeDay); Serial.print("d "); Serial.print(timeHour); Serial.print(" : "); Serial.print(timeMin); Serial.print(" : "); Serial.print(timeSec);
    Serial.println(" ");
    
    _IOLoop();
    
    /*
    Serial.print("Vbatt In Dig: ");
    Serial.println(VbattInADC);
    Serial.print("Vbatt In: ");
    Serial.println(VbattIn);    
    */
    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
