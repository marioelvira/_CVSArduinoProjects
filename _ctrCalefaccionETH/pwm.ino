#include "main.h"

#if (_USE_PWM_ == 1)

///////////////
// PWM set up //
///////////////
void _PWMSetup()
{ 
  ledcAttach(pwmPin, pwmFreq, pwmResolution); 
}

///////////////////////
// PWM state machine //
///////////////////////
void _PWMLoop()
{
  /*
  pwmDutyCycle++;
  if (pwmDutyCycle > 255)
    pwmDutyCycle = 0;
  */
  ledcWrite(pwmPin, pwmDutyCycle);
}

#endif // (_USE_PWM_ == 1)