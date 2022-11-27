#include "main.h"

#if (_USE_WDE_ == 1)

///////////////////////
// WDE state machine //
///////////////////////
void _WDESetup()
{
  wdeForceReset = 0;
  ESP.wdtEnable(WTE_TIMEOUT);
}

///////////////////////
// WDE state machine //
///////////////////////
void _WDELoop()
{
  ESP.wdtFeed();
  if (wdeForceReset == 1)
    while(1);
}

#endif
