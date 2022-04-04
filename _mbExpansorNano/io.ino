
///////////////
// IO set up //
///////////////
void _IOSetup()
{  
  InStartVal_ant = InStartVal;
  InStartCounter = 0;

  InEndVal_ant = InEndVal;
  InEndCounter = 0;
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

  // In end...
  if (InEndVal_ant == InEndVal)
    InEndCounter++; // Incrementamos el contador.
  else
  {
    // Si detectamos un flanco ...
    if (InEndVal_ant == FLANCO)
    {
      if (InEndCounter > PULSACION_OK)
      {
        InEndState = PULSACION_OK;
      }

      #if (_PULS_SERIAL_DEBUG_ == 1)
      if (InEndState == PULSACION_OK)
        Serial.println(">> End -> Pulsacion OK");
      else
        Serial.println(">> End -> Error Pulsacion");
      #endif
    }

    InEndCounter = 0;
  }

  // Almacenamos el valor anterior...
  InStartVal_ant  = InStartVal;
  InEndVal_ant  = InEndVal;
}

void _IOPulsLoop(void) {

  // Si se pulsa el incrementador...
  if (InStartState == PULSACION_OK)
  {
    // Control here
        
    #if (_PULS_SERIAL_DEBUG_ == 1)
    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> Start -> Incrementa");
    #endif
  }

  // Si se pulsa la parada...
  if (InEndState == PULSACION_OK)
  {
    // Control here
    
    #if (_PULS_SERIAL_DEBUG_ == 1)
    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> End -> Paro Gen");
    #endif
  }

  InStartState = NO_PULSACION;
  InEndState   = NO_PULSACION;
}
