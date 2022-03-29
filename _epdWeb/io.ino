
//////////////
// IO setup //
//////////////
void _IOSetup()
{  
  InStartVal_ant = InStartVal;
  InStartCounter = 0;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop()
{ 
  // In Start...
  if (InStartVal_ant == InStartVal)
    InStartCounter++;
  else
  {
    // Si detectamos un flanco ...
    if (InStartVal_ant == FLANCO)
    {
      if (InStartCounter > PULSACION_OK)
        InStartState = PULSACION_OK;

      #if (_PULS_SERIAL_DEBUG_ == 1)
      if (InStartState == PULSACION_OK)
        Serial.println(">>>>>>>>>>>>>>>>>>> Start -> Pulsacion OK");
      else
        Serial.println(">>>>>>>>>>>>>>>>>>> Start -> Error Pulsacion");
      #endif
    }

    InStartCounter = 0;
  }

  // Almacenamos el valor anterior...
  InStartVal_ant  = InStartVal;
}
