#include "main.h"

#if (_USE_WDE_ == 1)

///////////////////////
// WDE state machine //
///////////////////////
void _WDESetup()
{
  wdeForceReset = 0;
  //XXX.wdtEnable(WTE_TIMEOUT);
}

///////////////////////
// WDE state machine //
///////////////////////
void _WDELoop()
{
  // TODO XXX.wdtFeed();
  if (wdeForceReset == 1)
    while(1);
}

#endif
