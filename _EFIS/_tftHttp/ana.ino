#include "ana.h"

void _analogOnString (void)
{
  if (boardP3P3 < 10)
    sAnalog = "000" + String(boardP3P3);
  else if (boardP3P3 < 100)
    sAnalog = "00" + String(boardP3P3);
  else if (boardP3P3 < 1000)
    sAnalog = "0" + String(boardP3P3);      
  else 
    sAnalog = String(boardP3P3);
}

//////////////
// ANA setup //
//////////////
void _ANASetup()
{
  ANTick = millis();
}

//////////////////////
// ANA state machine //
//////////////////////
void _ANALoop(void)
{
  if (millis() - ANTick >= ANA_UPDATE_TICK)
  {
    boardP3P3 = analogRead(PIN_P3P3);
    
    ANTick = millis();
  }
}
