
///////////////
// IO set up //
///////////////
void _IOSetup()
{ 
  // No bigger than OUT_NUMBER
  OutPin[0] = PIN_OUTB;
  OutPin[1] = PIN_OUTC;
  OutPin[2] = PIN_OUTD;
  OutPin[3] = PIN_OUTE;
  OutPin[4] = PIN_OUTF;
  
  OutPin[5] = PIN_OUTA;
  
  // No bigger than IN_NUMBER
  InPin[0] = PIN_IN0;
  InPin[1] = PIN_IN1;
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
