
////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ctrState = STATE_START;
  ctrTick = millis();

  // Variables
  engineRMP = 4000;
  carbPreasure = 3700;
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  // Test
  if (millis() - ctrTick >= CTR_TEST_TICK)
  {
    engineRMP += 23;
    if (engineRMP > 6400)
      engineRMP = 4000;

    carbPreasure -= 11;
    if (carbPreasure < 2700)
      carbPreasure = 3700; 
    
    ctrTick = millis();
  }
}
