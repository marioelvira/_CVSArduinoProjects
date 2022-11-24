#include "joystick.h"

////////////////////
// JOYSTICK setup //
////////////////////
void _JOYSTICKSetup()
{
  joystickState = JOYSTICK_STANDBY;
}

////////////////////////////
// JOYSTICK state machine //
////////////////////////////
void _JOYSTICKLoop(void)
{
  switch (joystickState)
  {
    case JOYSTICK_STANDBY:
      joystickTick = millis();

      // Check
      if (boardP3P3 > JOYSTICK_LIM_UP)
        joystickState = JOYSTICK_ST_UP;
      else if (boardP3P3 < JOYSTICK_LIM_DOWN)
        joystickState = JOYSTICK_ST_DOWN;
      else if (boardP3P2 == IO_ON)
        joystickState = JOYSTICK_ST_PUSH;
        
      break;
      
    case JOYSTICK_ST_UP:
    case JOYSTICK_ST_DOWN:
    case JOYSTICK_ST_PUSH:
    
      if (millis() - joystickTick < JOYSTICK_BLINK_TICK)
        break;

      // Check
      if (boardP3P3 > JOYSTICK_LIM_UP)
        joystickState = JOYSTICK_ST_UP;
      else if (boardP3P3 < JOYSTICK_LIM_DOWN)
        joystickState = JOYSTICK_ST_DOWN;
      else if (boardP3P2 == IO_ON)
        joystickState = JOYSTICK_ST_PUSH;
      else
        joystickState = JOYSTICK_STANDBY;

      break;
  }
}
