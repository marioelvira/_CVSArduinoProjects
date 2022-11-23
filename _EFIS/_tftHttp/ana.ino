#include "ana.h"

void _analogOnString (void)
{
  if (boardAN0 < 10)
    sAnalog = "000" + String(boardAN0);
  else if (boardAN0 < 100)
    sAnalog = "00" + String(boardAN0);
  else if (boardAN0 < 1000)
    sAnalog = "0" + String(boardAN0);      
  else 
    sAnalog = String(boardAN0);
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
    boardAN0 = analogRead(PIN_ANA0);
    
    ANTick = millis();
  }
}
