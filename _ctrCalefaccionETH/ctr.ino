#include "main.h"
#include "ctr.h"

///////////////
// Variables //
///////////////
String ctrStateString;
int ctrMode;
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
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
}
