
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

void _IOPulsLoop(void) {

  // Si se pulsa Open...
  if (InOpenState == PULSACION_OK)
  {
    #if (_PULS_SERIAL_DEBUG_ == 1)
    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> Puls Open");
    #endif
    
    // Solo si NO estamos abriendo...
    if (windowState != STATE_WOPENING)
    {
      #if (_PULS_SERIAL_DEBUG_ == 1)
      Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> Opening");
      #endif
      windowState = STATE_WOPENING;
    }
  }

  // Si se pulsa Close...
  if (InCloseState == PULSACION_OK)
  {
    #if (_PULS_SERIAL_DEBUG_ == 1)
    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> Puls Close");
    #endif
    
    // Solo si NO estamos cerrando...
    if (windowState != STATE_WCLOSING)
    {
      #if (_PULS_SERIAL_DEBUG_ == 1)
      Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> Closing");
      #endif
      windowState = STATE_WCLOSING;
    }
  }

  InOpenState  = NO_PULSACION;
  InCloseState = NO_PULSACION;
}
