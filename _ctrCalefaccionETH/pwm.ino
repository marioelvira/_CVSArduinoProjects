#include "main.h"
#include "pwm.h"

#if (_USE_PWM_ == 1)

///////////////
// Variables //
///////////////
const int pwmPin = PIN_PWM0; 

const int pwmFreq = 50; // Frecuencia (Hz)
const int pwmResolution = 14;  // Resolución de 8 bits (valores de 0 a 255)

int pwmDutyCycle = 5000;       // 50%

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