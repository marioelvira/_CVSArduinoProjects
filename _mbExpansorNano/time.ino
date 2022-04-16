
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
    //if (TimeControlSec != 0)
    //   TimeControlSec--;
    
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

    _ADCsLoop();
    _INTISRsLoop();

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
    
    int i;
    
    Serial.println("<><><><><><><>");
    Serial.print("Tiempo Encendio: ");
    Serial.print(timeHour); Serial.print(" : "); Serial.print(timeMin); Serial.print(" : "); Serial.print(timeSec);
    Serial.println(" ");

    #if (_USE_FREERAM_ == 1)
    Serial.print("Free RAM: ");
    Serial.println(freeRam);
    #endif
    /*
    Serial.print("Cuenta Atras (Segundos): ");
    Serial.print(TimeControlSec);
    Serial.println(" ");

    Serial.print("Cuenta Ticks (ms): ");
    Serial.print(millis() - ControlTick);
    Serial.println(" ");
    
    Serial.print("Control Status "); Serial.println(ControlState);
    //if (ControlState == STATE_START)
    //  Serial.println("  Arrancando...");
    //else if (ControlState == STATE_XXXX)
    //  Serial.println("  State XXXXX");
    //else
    //  Serial.println("  Rest");
    */
    Serial.println("---------------");

    //Serial.print("intNumberD2: ");  Serial.println(inPulseD2);
    Serial.print("intNumberD3: ");    Serial.println(inPulseD3);
    Serial.print("RPM in D3: ");      Serial.println(RpmCounter);
        
    Serial.println("---------------");

    // ADC
    for (i = 0; i< ADC_NUMBER; i++)
    {
      Serial.print("ADC ");
      Serial.println(i);
      Serial.print("Dig: ");
      Serial.println(AdcDig[i]);
    }

    // OUTs
    for (i = 0; i< OUT_NUMBER; i++)
    {
      Serial.print("OUT ");
      Serial.println(i);
      Serial.print("Dig: ");
      Serial.println(OutDig[i]);
    }

    // INs
    for (i = 0; i< IN_NUMBER; i++)
    {
      Serial.print("IN ");
      Serial.println(i);
      Serial.print("Dig: ");
      Serial.println(InDig[i]);
    }
    
    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
