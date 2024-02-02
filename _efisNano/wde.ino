#include "main.h"

#if (_USE_WDE_ == 1)

#include <avr/wdt.h>

///////////////
// WDE setup //
///////////////
void _WDESetup()
{
  wdeForceReset = 0;
  wdt_disable();
  wdt_enable(WDTO_4S);
}

///////////////////////
// WDE state machine //
///////////////////////
void _WDELoop()
{
  wdt_reset();
  if (wdeForceReset == 1)
    while(1);
}

#endif
