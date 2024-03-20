
///////////////
// IO set up //
///////////////
void _IOSetup()
{ 
  // No bigger than OUT_NUMBER
  OutPin[0] = PIN_OUT0;
  OutPin[1] = PIN_OUT1;
  OutPin[2] = PIN_OUT2;
  OutPin[3] = PIN_OUT3;

  rgbPin[0] = PIN_RGB_R;
  rgbPin[1] = PIN_RGB_G;
  rgbPin[2] = PIN_RGB_B;

  // No bigger than IN_NUMBER
  InPin[0] = PIN_IN0;
  InPin[1] = PIN_IN1;
  InPin[2] = PIN_IN2;
  InPin[3] = PIN_IN3;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop()
{
}
