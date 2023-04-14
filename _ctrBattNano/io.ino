
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
    // In[0]
    InPuls = InDig[0];
    
    if (InPuls_ant == InPuls)
      InPulsCounter++;
    else
    {
      // Si detectamos un flanco ...
      if (InPuls_ant == FLANCO)
      {
        if (InPulsCounter > LONG_PULS)
          InPulsState = LONG_PULS;
        else if (InPulsCounter > SHORT_PULS)
          InPulsState = SHORT_PULS;
      }
  
      InPulsCounter = 0;
    }
  
    // Puls Control
    _IOPulsCtr();
  
    // Almacenamos el valor anterior...
    InPuls_ant  = InPuls;
  }

  ioTick = millis();
}

void _IOPulsCtr(void) {

  if (InPulsState == LONG_PULS)
  {
  }
  else if (InPulsState == SHORT_PULS)
  {
  }

  InPulsState  = NO_PULS;
}
