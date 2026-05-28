#include "main.h"
#include "ctr.h"

///////////////
// Variables //
///////////////
int ctrMode;
String ctrStateString;

int ctrState;
int ctrInState;
int ctrOutState;

int ctrTempPrin = 0;
int ctrTemp = 0;

void _ctrStateString(void)
{
}

////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ctrMode = MODE_AUTO;
  ctrState = IN_THERMO_OFF;
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  /*
  switch (ctrState)
  {
    case IN_THERMO_OFF:
      break;

    case IN_THERMO_ON:
      break;
  }
  */
  /*
  #if (_USE_ALARM_ == 1)
  // TODO
  if (alarm[AL_ERROR0] == 1)
  {
    // Incremenetar timer
  }
  else
  {
    //Resetear timer
  }
  #endif
  */
}
