
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
  OutPin[4] = PIN_OUTE;
  OutPin[5] = PIN_OUTF;
  OutPin[6] = PIN_OUTG;
  OutPin[7] = PIN_OUTDP;

  OutPin[8] = PIN_OUTRELE;

  // No bigger than IN_NUMBER
  InPin[0] = PIN_IN0;
  InPin[1] = PIN_IN1;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop()
{
}
