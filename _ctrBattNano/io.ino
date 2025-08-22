
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

  OutPin[9] = PIN_OUT2;

  // No bigger than IN_NUMBER
  InPin[0] = PIN_IN0;
  InPin[1] = PIN_IN1;
  InPin[2] = PIN_IN2;

  ioTick = millis();

  inPulsState = IN_PULS_STANDBY;
  inPulsType = IN_PULS_STANDBY;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop()
{
  if (millis() - ioTick >= IO_LOOP_TICK)
  {
    inPuls = InDig[0];

    switch (inPulsState)
    {
      case IN_PULS_STANDBY:
        // Hay flanco?
        if ((inPuls_ant == IN_DOWN) && (inPuls == IN_UP))
        {
          inPulsState = IN_PULS_FLANCO;
          inPulsCounter = 0;
        }
        break;

      case IN_PULS_FLANCO:
        if (inPuls_ant == inPuls)
        {
          inPulsCounter++;

          if (inPulsCounter > TOOLONG_PULS)
          {
            inPulsType = TOOLONG_PULS;
            inPulsState = IN_PULS_CTR;
            #if (_PULS_SERIAL_DEBUG_ == 1)
            Serial.println("-----------> TOO LONG PULSE");
            #endif
          }
        }
        else
        {
          if (inPulsCounter >= LONG_PULS)
          {
            inPulsType = LONG_PULS;
            #if (_PULS_SERIAL_DEBUG_ == 1)
            Serial.println("-----------> LONG PULSE");
            #endif
          }
          else /*if (inPulsCounter >= SHORT_PULS)*/
          {
            inPulsType = SHORT_PULS;
            #if (_PULS_SERIAL_DEBUG_ == 1)
            Serial.println("-----------> SHORT PULSE");
            #endif
          }
          /*
          else
          {
            inPulsType = TOOSHORT_PULS;
            #if (_PULS_SERIAL_DEBUG_ == 1)
            Serial.println("-----------> TOOSHORT PULSE");
            #endif
          }
          */
          inPulsState = IN_PULS_CTR;
        }

        break;

      case IN_PULS_CTR:
        _ctrPuls();
        inPulsType  = NO_PULS;
        inPulsState = IN_PULS_STANDBY;
        break;
    }

    inPuls_ant  = inPuls;

    ioTick = millis();
  }
}
