
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

  ioTick = millis();
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop()
{
  if (millis() - ioTick >= IO_LOOP_TICK)
  {
    inPuls = InDig[0];
    
    if (inPuls_ant == inPuls)
      inPulsCounter++;
    else
    {
      // Si detectamos un flanco ...
      if (inPuls_ant == FLANCO)
      {
        if (inPulsCounter > LONG_PULS)
          inPulsState = LONG_PULS;
        else if (inPulsCounter > SHORT_PULS)
          inPulsState = SHORT_PULS;
      }
  
      inPulsCounter = 0;
    }

    _ctrPuls();

    inPulsState  = NO_PULS;
    inPuls_ant  = inPuls;
  }

  ioTick = millis();
}
