#include "main.h"
#include "mTime.h"

#if (_USE_ALARM_ == 1)
#include "alarm.h"
#endif

#if (_USE_MQTT_ == 1)
#include "MQTT.h"
#endif

#if (_USE_NTP_ == 1)
#include "mNTP.h"
#endif

#if (_USE_WDE_ == 1)
#include "wde.h"
#endif

#if (_USE_PWM_ == 1)
#include "pwm.h"
#endif

// Librerias
#include <WString.h>

///////////////
// Variables //
///////////////
String timeOnString;
unsigned long timeTick = 0;
unsigned long timeSecTick = 0;
int timeSec = 0;
int timeMin = 0;
int timeHour = 0;
int timeDay = 0;

void _timeOn2String(void)
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
  timeSecTick = 0;
  timeSec = 0;
  timeMin = 0;
  timeHour = 0;
  timeDay = 0;
  
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
    timeSecTick++;
    
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
    
    _timeOn2String();
    
    #if (_USE_MQTT_ == 1)
    _ctrStateString();
    #endif

    timeTick = millis();

    #if (_USE_ALARM_ == 1)
    _ALARMLoop();
    #endif

    #if (_USE_NTP_ == 1)
    _mNTPfakeSec();
    #endif

    #if (_USE_WDE_ == 1)
    _WDELoop();
    #endif

    #if (_USE_TRIAC_ == 1)
    _TRIACLoop();
    #endif

    #if (_USE_PWM_ == 1)
    _PWMLoop();
    #endif

    #if (_USE_LED_ == 1)
    if (boardLed == OUT_OFF)
      boardLed = OUT_ON;
    else
      boardLed = OUT_OFF;
    #endif

    #if (_STATUS_SERIAL_DEBUG_ == 1)
    
    int i;
    
    Serial.println("<><><><><><><>");
    Serial.print("Tiempo Encendio: ");
    Serial.print(timeDay); Serial.print("d "); Serial.print(timeOnString);
    Serial.println(" ");

    Serial.print("ethStatus: ");
    Serial.print(ethStatus);
    Serial.println(" ");

    Serial.println("<><><><><><><>");
    Serial.println(" ");

    #endif
  }
}
