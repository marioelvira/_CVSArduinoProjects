#include "main.h"
#include "pwm.h"

#if (_USE_PWM_ == 1)

///////////////
// Variables //
///////////////
const int pwmPin = PIN_PWM0; 
int pwmState;

int pwmFreq = 50;              // Frecuencia (Hz)
const int pwmResolution = 14;  // Resolución de 8 bits (valores de 0 a 255)

int pwmDutyCycle = 6000;       // 50%

///////////////
// PWM set up //
///////////////
void _PWMSetup()
{ 
  pwmState = PWM_START;
}

///////////////////////
// PWM state machine //
///////////////////////
void _PWMLoop()
{
  switch (pwmState)
  {
    case PWM_START:
      #if (_PWM_SERIAL_DEBUG_ == 1)
      Serial.print("--> PWM strat: ");
      Serial.print(pwmFreq);       Serial.print(" ");
      Serial.print(pwmResolution); Serial.println(" ");
      #endif

      ledcAttach(pwmPin, pwmFreq, pwmResolution); 
      pwmState = PWM_CONFIG;
      break;

    case PWM_CONFIG:
      #if (_PWM_SERIAL_DEBUG_ == 1)
      Serial.print("--> PWM duty: ");
      Serial.print(pwmDutyCycle); Serial.println(" ");
      #endif

      ledcWrite(pwmPin, pwmDutyCycle);
      pwmState = PWM_STANDBY;
      break;

    case PWM_STANDBY:      
      break;
  }
}

#endif // (_USE_PWM_ == 1)