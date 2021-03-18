
//////////////////////
// IO state machine //
//////////////////////
void _IOSetup()
{  
  PulsadorDigInStatus_ant = PulsadorDigInStatus;
  PulsadorDigInCounter = 0;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop()
{
  int pulsadorInState;
  
  // Leemos las entradas digitales...
  pulsadorInState = PulsadorDigInStatus;

  //////////////////////
  // Entrada Pulsador //
  //////////////////////
  if (PulsadorDigInStatus_ant == pulsadorInState)
    PulsadorDigInCounter++; // Incrementamos el contador.
  else
  {
    // Si detectamos un flanco ...
    if (PulsadorDigInStatus_ant == FLANCO)
    {
      if (PulsadorDigInCounter > PULSACION_OK)
      {
        PulsadorPulsacion = PULSACION_OK;
      }

      #if (_PULS_SERIAL_DEBUG_ == 1)
      if (PulsadorPulsacion == PULSACION_OK)
        Serial.println(">> Pulsador -> Pulsacion OK");
      else
        Serial.println(">> Pulsador -> Error Pulsacion");
      #endif
    }

    PulsadorDigInCounter = 0;
  }

  // Aplicamos el filto software en Modo ...
  if (PulsadorDigInCounter > AUTOMAN_FILTRO)
    PulsadorDigInStatus = pulsadorInState;

  // Almacenamos el valor anterior...
  PulsadorDigInStatus_ant  = pulsadorInState;
}

void _IOPulsLoop(void) {

  // Si se pulsa el pulsador...
  if (PulsadorPulsacion != NO_PULSACION)
  {

    ControlState = STATE_GEN_ON;  // reseteamos el estado...

    if (DisplayIndicador == 9)
      TimeControlSec = TimeGenerador9P*3600; // TIMER_GEN_7H_00M_SEC;
      
    else if (DisplayIndicador == 8)
      TimeControlSec = TimeGenerador9P*3600; //TIMER_GEN_7H_00M_SEC;
      
    else if (DisplayIndicador == 7)
      TimeControlSec = TimeGenerador8P*3600; //TIMER_GEN_5H_00M_SEC;
      
    else if (DisplayIndicador == 6)
      TimeControlSec = TimeGenerador7P*3600; //TIMER_GEN_4H_00M_SEC;
      
    else if (DisplayIndicador == 5)
      TimeControlSec = TimeGenerador6P*3600; //TIMER_GEN_3H_00M_SEC;
      
    else if (DisplayIndicador == 4)
      TimeControlSec = TimeGenerador5P*60; //TIMER_GEN_2H_00M_SEC;
      
    else if (DisplayIndicador == 3)
      TimeControlSec = TimeGenerador4P*60; //TIMER_GEN_1H_30M_SEC;
      
    else if (DisplayIndicador == 2)
      TimeControlSec = TimeGenerador3P*60; //TIMER_GEN_1H_00M_SEC;
      
    else if (DisplayIndicador == 1)
      TimeControlSec = TimeGenerador2P*60; //TIMER_GEN_0H_30M_SEC;
      
    else
      TimeControlSec = TimeGenerador1P*60; //TIMER_GEN_0H_15M_SEC;
  }

  // Reset de Pulsaciones...
  PulsadorPulsacion   = NO_PULSACION;
}

void _IOLcdLoop(void) {

  if (TimeControlSec > TimeGenerador8P*3600) // TIMER_GEN_5H_00M_SEC)
  {
    DisplayIndicador = 9;//TIMER_GEN_7H_00M_SEC; // 7h -> 9
    OutD3 = OUT_ON;
    OutD4 = OUT_OFF;
    OutD5 = OUT_OFF;
    OutD6 = OUT_ON;  
  }
  else if (TimeControlSec > TimeGenerador7P*3600) // TIMER_GEN_4H_00M_SEC)
  {
    DisplayIndicador = 8; //TIMER_GEN_5H_00M_SEC; // 5h -> 8
    OutD3 = OUT_OFF;
    OutD4 = OUT_OFF;
    OutD5 = OUT_OFF;
    OutD6 = OUT_ON;  
  }
  else if (TimeControlSec > TimeGenerador6P*3600) //TIMER_GEN_3H_00M_SEC)
  {
    DisplayIndicador = 7; //TIMER_GEN_4H_00M_SEC; // 4h -> 7
    OutD3 = OUT_ON;
    OutD4 = OUT_ON;
    OutD5 = OUT_ON;
    OutD6 = OUT_OFF;   
  }
  else if (TimeControlSec > TimeGenerador5P*60) //TIMER_GEN_2H_00M_SEC)
  {
    DisplayIndicador = 6; //TIMER_GEN_3H_00M_SEC; // 3h -> 6
    OutD3 = OUT_OFF;
    OutD4 = OUT_ON;
    OutD5 = OUT_ON;
    OutD6 = OUT_OFF;   
  }
  else if (TimeControlSec > TimeGenerador4P*60) //TIMER_GEN_1H_30M_SEC)
  {
    DisplayIndicador = 5; //TIMER_GEN_2H_00M_SEC; // 2h -> 5
    OutD3 = OUT_ON;
    OutD4 = OUT_OFF;
    OutD5 = OUT_ON;
    OutD6 = OUT_OFF;     
  }
  else if (TimeControlSec > TimeGenerador3P*60) //TIMER_GEN_1H_00M_SEC)
  {
    DisplayIndicador = 4; //TIMER_GEN_1H_30M_SEC; // 1h30m -> 4
    OutD3 = OUT_OFF;
    OutD4 = OUT_OFF;
    OutD5 = OUT_ON;
    OutD6 = OUT_OFF;   
  }
  else if (TimeControlSec > TimeGenerador2P*60) //TIMER_GEN_0H_30M_SEC)
  {
    DisplayIndicador = 3; //TIMER_GEN_1H_00M_SEC; // 1h -> 3
    OutD3 = OUT_ON;
    OutD4 = OUT_ON;
    OutD5 = OUT_OFF;
    OutD6 = OUT_OFF;  
  }
  else if (TimeControlSec > TimeGenerador1P*60) // TIMER_GEN_0H_15M_SEC)
  {
    DisplayIndicador = 2; //TIMER_GEN_0H_30M_SEC; // 30m -> 2
    OutD3 = OUT_OFF;
    OutD4 = OUT_ON;
    OutD5 = OUT_OFF;
    OutD6 = OUT_OFF;    
  }
  else if (TimeControlSec > TimeBuzzerOn) //TIMER_GEN_END_SEC
  {
    DisplayIndicador = 1; //TIMER_GEN_0H_15M_SEC; // 15m -> 1
    OutD3 = OUT_ON;
    OutD4 = OUT_OFF;
    OutD5 = OUT_OFF;
    OutD6 = OUT_OFF;  
  }
  else
  {
    DisplayIndicador = 0; //TIMER_GEN_END_SEC; // 15s -> 0
    OutD3 = OUT_OFF;
    OutD4 = OUT_OFF;
    OutD5 = OUT_OFF;
    OutD6 = OUT_OFF;  
  }
}
