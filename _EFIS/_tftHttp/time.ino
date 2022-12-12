#include "main.h"

void _timeOnString(void)
{
    if (timeHour < 10)
      timeOnString = "0" + String(timeHour);
    else
      timeOnString = String(timeHour);

    timeOnString = timeOnString + ":";

    if (timeMin < 10)
      timeOnString = timeOnString + "0" + String(timeMin);
    else
      timeOnString = timeOnString + String(timeMin);

    timeOnString = timeOnString + ":";

    if (timeSec < 10)
      timeOnString = timeOnString + "0" + String(timeSec);
    else
      timeOnString = timeOnString + String(timeSec);
}

/////////////////
// Time set up //
/////////////////
void _TimeSetup(void)
{
  timeTick = millis();
  timeSec = 0;
  timeMin = 0;
  timeHour = 0;

  _timeOnString();

  #if (_USE_RAM_ == 1)
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
    _timeOnString();
        
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

    #if (_USE_RAM_ == 1)
    _FreeRAM();
    #endif

    _LEDTest();

    #if (_USE_WDE_ == 1)
    _WDELoop();
    #endif
    
    #if (_STATUS_SERIAL_DEBUG_ == 1)
    
    Serial.println("<><><><><><><>");
    Serial.print("Time On: ");
    Serial.println(timeOnString);

    #if (_USE_RAM_ == 1)
    Serial.print("Free RAM: ");
    Serial.println(freeRam);
    #endif

    //Serial.printf("OUT(%d): %d\n", PIN_CN12, boardCN1P2); 
    Serial.printf("IN(%d): %d\n",  PIN_P3P2, boardP3P2);
    Serial.printf("ANA(%d): %d\n", PIN_P3P3, boardP3P3);
    
    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
