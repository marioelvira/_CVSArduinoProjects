#include "main.h"

#if (_USE_FREERAM_ == 1)

////////////////
// RAM set up //
////////////////
void _RAMSetup(void)
{
  freeRam = ESP.getFreeHeap();
}

//////////////
// Free RAM //
//////////////
void _FreeRAM(void)
{
  if(ESP.getFreeHeap() != freeRam)
    freeRam = ESP.getFreeHeap();
}

#endif
