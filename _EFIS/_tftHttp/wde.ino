#include "main.h"

#if (_USE_WDE_ == 1)

///////////////////////
// WDE state machine //
///////////////////////
void _WDESetup()
{
  wdeForceReset = 0;

  //ESP.wdtEnable(WTE_TIMEOUT);
  esp_task_wdt_init(WDT_TIMEOUT, true);
  //esp_task_wdt_add(NULL);
}

///////////////////////
// WDE state machine //
///////////////////////
void _WDELoop()
{
  //ESP.wdtFeed();
  esp_task_wdt_reset();
  
  if (wdeForceReset == 1)
    while(1);
}

#endif
