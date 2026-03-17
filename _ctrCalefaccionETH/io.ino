
///////////////
// IO set up //
///////////////
void _IOSetup()
{ 
  // No bigger than OUT_NUMBER
  OutPin[0] = PIN_OUT1;
  OutPin[1] = PIN_OUT2;
  OutPin[2] = PIN_OUT3;
  OutPin[3] = PIN_OUT4;
  OutPin[4] = PIN_OUT5;
  OutPin[5] = PIN_OUT6;
    
  // No bigger than IN_NUMBER
  InPin[0] = PIN_IN1;
  InPin[1] = PIN_IN2;
  InPin[2] = PIN_IN3;
  InPin[3] = PIN_IN4;

  // No bigger than TRIAC_NUMBER
  /*
  TriacPin[0] = PIN_TRIAC1;
  TriacPin[1] = PIN_TRIAC2;
  TriacPin[2] = PIN_TRIAC3;
  */
}

