
//////////////////////
// IO state machine //
//////////////////////
void _IOSetup()
{  
  InStartVal_ant = InStartVal;
  InStartCounter = 0;

  InEndVal_ant = InEndVal;
  InEndCounter = 0;

  DisplayIndicador = 1;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop()
{
  int startInState;
  int endInState;
  
  // Leemos las entradas digitales...
  startInState = InStartVal;
  endInState = InStartVal;

  // In Start..
  if (InStartVal_ant == startInState)
    InStartCounter++; // Incrementamos el contador.
  else
  {
    // Si detectamos un flanco ...
    if (InStartVal_ant == FLANCO)
    {
      if (InStartCounter > PULSACION_OK)
      {
        InStartState = PULSACION_OK;
      }

      #if (_PULS_SERIAL_DEBUG_ == 1)
      if (InStartState == PULSACION_OK)
        Serial.println(">> Start -> Pulsacion OK");
      else
        Serial.println(">> Start -> Error Pulsacion");
      #endif
    }

    InStartCounter = 0;
  }

  // In end...
  if (InEndVal_ant == endInState)
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

  // Aplicamos el filto software en Modo ...
  if (InStartCounter > AUTOMAN_FILTRO)
    InStartVal = startInState;

  if (InEndCounter > AUTOMAN_FILTRO)
    InEndVal = endInState;

  // Almacenamos el valor anterior...
  InStartVal_ant  = startInState;
  InEndVal_ant  = endInState;
  
}

void _IOPulsLoop(void) {

  // Si se pulsa el pulsador...
  if (InStartState != NO_PULSACION)
  {
    #if (_PULS_SERIAL_DEBUG_ == 1)
    Serial.println(">> Pulsador -> Incrementa");
    #endif

    ControlState = STATE_GEN_ON;  // reseteamos el estado...

    if (DisplayIndicador == 9)
      TimeControlSec = TimeGenerador9P*X_3600; // TIMER_GEN_7H_00M_SEC;
      
    else if (DisplayIndicador == 8)
      TimeControlSec = TimeGenerador9P*X_3600; //TIMER_GEN_7H_00M_SEC;
      
    else if (DisplayIndicador == 7)
      TimeControlSec = TimeGenerador8P*X_3600; //TIMER_GEN_5H_00M_SEC;
      
    else if (DisplayIndicador == 6)
      TimeControlSec = TimeGenerador7P*X_3600; //TIMER_GEN_4H_00M_SEC;
      
    else if (DisplayIndicador == 5)
      TimeControlSec = TimeGenerador6P*X_3600; //TIMER_GEN_3H_00M_SEC;
      
    else if (DisplayIndicador == 4)
      TimeControlSec = TimeGenerador5P*X_60; //TIMER_GEN_2H_00M_SEC;
      
    else if (DisplayIndicador == 3)
      TimeControlSec = TimeGenerador4P*X_60; //TIMER_GEN_1H_30M_SEC;
      
    else if (DisplayIndicador == 2)
      TimeControlSec = TimeGenerador3P*X_60; //TIMER_GEN_1H_00M_SEC;
      
    else if (DisplayIndicador == 1)
      TimeControlSec = TimeGenerador2P*X_60; //TIMER_GEN_0H_30M_SEC;
      
    else
      TimeControlSec = TimeGenerador1P*X_60; //TIMER_GEN_0H_15M_SEC;
  }

  // Reset de Pulsaciones...
  InStartState   = NO_PULSACION;
}

void _IOLcdLoop(void) {

  if (TimeControlSec > TimeGenerador8P*X_3600) // TIMER_GEN_5H_00M_SEC)
  {
    DisplayIndicador = 9;//TIMER_GEN_7H_00M_SEC; // 7h -> 9
    OutA = OUT_ON;
    OutB = OUT_OFF;
    OutC = OUT_OFF;
    OutD = OUT_ON;  
  }
  else if (TimeControlSec > TimeGenerador7P*X_3600) // TIMER_GEN_4H_00M_SEC)
  {
    DisplayIndicador = 8; //TIMER_GEN_5H_00M_SEC; // 5h -> 8
    OutA = OUT_OFF;
    OutB = OUT_OFF;
    OutC = OUT_OFF;
    OutD = OUT_ON;  
  }
  else if (TimeControlSec > TimeGenerador6P*X_3600) //TIMER_GEN_3H_00M_SEC)
  {
    DisplayIndicador = 7; //TIMER_GEN_4H_00M_SEC; // 4h -> 7
    OutA = OUT_ON;
    OutB = OUT_ON;
    OutC = OUT_ON;
    OutD = OUT_OFF;   
  }
  else if (TimeControlSec > TimeGenerador5P*X_60) //TIMER_GEN_2H_00M_SEC)
  {
    DisplayIndicador = 6; //TIMER_GEN_3H_00M_SEC; // 3h -> 6
    OutA = OUT_OFF;
    OutB = OUT_ON;
    OutC = OUT_ON;
    OutD = OUT_OFF;   
  }
  else if (TimeControlSec > TimeGenerador4P*X_60) //TIMER_GEN_1H_30M_SEC)
  {
    DisplayIndicador = 5; //TIMER_GEN_2H_00M_SEC; // 2h -> 5
    OutA = OUT_ON;
    OutB = OUT_OFF;
    OutC = OUT_ON;
    OutD = OUT_OFF;     
  }
  else if (TimeControlSec > TimeGenerador3P*X_60) //TIMER_GEN_1H_00M_SEC)
  {
    DisplayIndicador = 4; //TIMER_GEN_1H_30M_SEC; // 1h30m -> 4
    OutA = OUT_OFF;
    OutB = OUT_OFF;
    OutC = OUT_ON;
    OutD = OUT_OFF;   
  }
  else if (TimeControlSec > TimeGenerador2P*X_60) //TIMER_GEN_0H_30M_SEC)
  {
    DisplayIndicador = 3; //TIMER_GEN_1H_00M_SEC; // 1h -> 3
    OutA = OUT_ON;
    OutB = OUT_ON;
    OutC = OUT_OFF;
    OutD = OUT_OFF;  
  }
  else if (TimeControlSec > TimeGenerador1P*X_60) // TIMER_GEN_0H_15M_SEC)
  {
    DisplayIndicador = 2; //TIMER_GEN_0H_30M_SEC; // 30m -> 2
    OutA = OUT_OFF;
    OutB = OUT_ON;
    OutC = OUT_OFF;
    OutD = OUT_OFF;    
  }
  else if (TimeControlSec > TimeBuzzerOn) //TIMER_GEN_END_SEC
  {
    DisplayIndicador = 1; //TIMER_GEN_0H_15M_SEC; // 15m -> 1
    OutA = OUT_ON;
    OutB = OUT_OFF;
    OutC = OUT_OFF;
    OutD = OUT_OFF;  
  }
  else
  {
    DisplayIndicador = 0; //TIMER_GEN_END_SEC; // 15s -> 0
    OutA = OUT_OFF;
    OutB = OUT_OFF;
    OutC = OUT_OFF;
    OutD = OUT_OFF;  
  }
}
