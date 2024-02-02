
///////////////
// IO set up //
///////////////
void _IOSetup()
{ 
  // No bigger than OUT_NUMBER
  OutPin[0] = PIN_OUTA;
  OutPin[1] = PIN_OUTB;
  OutPin[2] = PIN_OUTC;
  OutPin[3] = PIN_OUTD;
  
  // No bigger than IN_NUMBER
  InPin[0] = PIN_IN0;
  InPin[1] = PIN_IN1;
  InPin[2] = PIN_IN2;
  InPin[3] = PIN_IN3;
}

//////////////////////
// IO state machine //
//////////////////////
/*
void _IOLoop()
{
  if (millis() - ioTick >= IO_LOOP_TICK)
  {

    ioTick = millis();
  }
}
*/
