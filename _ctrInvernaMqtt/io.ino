
//////////////
// IO setup //
//////////////
void _IOSetup()
{  
  InOpen_ant = InOpen;
  InOpenCounter = 0;

  InClose_ant = InClose;
  InCloseCounter = 0;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop()
{ 
  // In Start...
  if (InOpen_ant == InOpen)
    InOpenCounter++;
  else
  {
    // Si detectamos un flanco ...
    if (InOpen_ant == FLANCO)
    {
      if (InOpenCounter > PULSACION_OK)
        InOpenState = PULSACION_OK;

      #if (_PULS_SERIAL_DEBUG_ == 1)
      if (InOpenState == PULSACION_OK)
        Serial.println("Open -> Pulsacion OK");
      else
        Serial.println("Open -> Error Pulsacion");
      #endif
    }

    InOpenCounter = 0;
  }

  // In end...
  if (InClose_ant == InClose)
    InCloseCounter++; // Incrementamos el contador.
  else
  {
    // Si detectamos un flanco ...
    if (InClose_ant == FLANCO)
    {
      if (InCloseCounter > PULSACION_OK)
      {
        InCloseState = PULSACION_OK;
      }

      #if (_PULS_SERIAL_DEBUG_ == 1)
      if (InCloseState == PULSACION_OK)
        Serial.println("Close -> Pulsacion OK");
      else
        Serial.println("Close -> Error Pulsacion");
      #endif
    }

    InCloseCounter = 0;
  }

  // Almacenamos el valor anterior...
  InOpen_ant  = InOpen;
  InClose_ant = InClose;
}
