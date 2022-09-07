
////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ControlState = STATE_STANDBY;
  ControlTick = millis();
  
  TimeControlSec = 0;
  DisplayIndicador = 1;

  // Control
  OutBomba = OUT_OFF;
  OutGen = OUT_OFF;
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{

  switch (ControlState)
  {
    case STATE_STANDBY:    
      // Control
      OutBomba = OUT_OFF;
      OutGen = OUT_OFF;

      // Indicadores
      OutZumb = OUT_OFF;
      OutDisp = OUT_OFF;
    
      TimeControlSec = 0;
      ControlTick = millis();
      break;

    case STATE_START:
      // Control
      OutBomba = OUT_OFF;
      OutGen = OUT_OFF;
      
      // Indicadores
      OutDisp = OUT_ON;
      OutZumb = OUT_OFF;

      if (millis() - ControlTick >= (cfgTimeOutStart*1000))
        ControlState = STATE_GEN_ON;
      break;

    case STATE_GEN_ON:
      // Control
      OutBomba = OUT_ON;
      OutGen = OUT_ON;
      
      // Indicadores
      OutDisp = OUT_ON;
      OutZumb = OUT_OFF;
             
      if (TimeControlSec <= cfgTimeBuzzerOn)
        ControlState = STATE_GEN_ZUMB;

      ControlTick = millis();
      break;

    case STATE_GEN_ZUMB:
      // Control
      OutBomba = OUT_ON;
      OutGen = OUT_ON;

      // Indicadores
      if (millis() - ControlTick >= CTR_BUZZER_TICK)
      {
        if (OutZumb == OUT_ON)
          OutZumb = OUT_OFF;
        else
          OutZumb = OUT_ON;

        if (OutDisp == OUT_ON)
          OutDisp = OUT_OFF;
        else
          OutDisp = OUT_ON;

        ControlTick = millis();
      } 

      if (TimeControlSec <= 0)
        ControlState = STATE_GEN_OFF;

      break;
   
    case STATE_GEN_OFF:
      // Control     
      OutBomba = OUT_ON;
      OutGen = OUT_OFF;

      // Indicadores
      OutZumb = OUT_OFF;
      OutDisp = OUT_OFF;

      TimeControlSec = 0;

      if (millis() - ControlTick >= (cfgTimeOutStop*1000))
        ControlState = STATE_STANDBY;

      break;

  }

  // loops
  ctrIOsLoop();
  ctrInsLoop();
  ctrPulsLoop();
  ctrLcdLoop();
}

// IOs used in ctr
void ctrIOsLoop(void)
{
  // Ins
  InStartVal= mbIns[0][0];
  InEndVal  = mbIns[1][0]; 

  // Outs
  mbOuts[0][0] = OutGen;
  mbOuts[1][0] = OutBomba;
  mbOuts[2][0] = OutDisp;
  mbOuts[3][0] = OutZumb;
  mbOuts[4][0] = OutA;
  mbOuts[5][0] = OutB;
  mbOuts[6][0] = OutC;
  mbOuts[7][0] = OutD;
}

// Ins loop
void ctrInsLoop(void)
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

// Puls loop
void ctrPulsLoop(void)
{
  // Si se pulsa el incrementador...
  if (InStartState == PULSACION_OK)
  {
    #if (_PULS_SERIAL_DEBUG_ == 1)
    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> Start -> Incrementa");
    #endif

    // Mantenemos el arranque
    if (ControlState != STATE_START)
      ControlState = STATE_GEN_ON;

    if (DisplayIndicador == 9)
      TimeControlSec = cfgTimeGenerador9P*X_3600;
      
    else if (DisplayIndicador == 8)
      TimeControlSec = cfgTimeGenerador9P*X_3600;
      
    else if (DisplayIndicador == 7)
      TimeControlSec = cfgTimeGenerador8P*X_3600;
      
    else if (DisplayIndicador == 6)
      TimeControlSec = cfgTimeGenerador7P*X_3600;
      
    else if (DisplayIndicador == 5)
      TimeControlSec = cfgTimeGenerador6P*X_3600;
      
    else if (DisplayIndicador == 4)
      TimeControlSec = cfgTimeGenerador5P*X_60;
      
    else if (DisplayIndicador == 3)
      TimeControlSec = cfgTimeGenerador4P*X_60;
      
    else if (DisplayIndicador == 2)
      TimeControlSec = cfgTimeGenerador3P*X_60;
      
    else if (DisplayIndicador == 1)
      TimeControlSec = cfgTimeGenerador2P*X_60;
      
    else
      TimeControlSec = cfgTimeGenerador1P*X_60;
  }

  // Si se pulsa la parada...
  if (InEndState == PULSACION_OK)
  {
    ControlState = STATE_GEN_OFF;

    #if (_PULS_SERIAL_DEBUG_ == 1)
    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> End -> Paro Gen");
    #endif
  }

  InStartState = NO_PULSACION;
  InEndState   = NO_PULSACION;
}

// Lcd
void ctrLcdLoop(void) {

  if (TimeControlSec > cfgTimeGenerador8P*X_3600)
  {
    DisplayIndicador = 9;
    OutA = OUT_ON;
    OutB = OUT_OFF;
    OutC = OUT_OFF;
    OutD = OUT_ON;  
  }
  else if (TimeControlSec > cfgTimeGenerador7P*X_3600)
  {
    DisplayIndicador = 8;
    OutA = OUT_OFF;
    OutB = OUT_OFF;
    OutC = OUT_OFF;
    OutD = OUT_ON;  
  }
  else if (TimeControlSec > cfgTimeGenerador6P*X_3600)
  {
    DisplayIndicador = 7;
    OutA = OUT_ON;
    OutB = OUT_ON;
    OutC = OUT_ON;
    OutD = OUT_OFF;   
  }
  else if (TimeControlSec > cfgTimeGenerador5P*X_60)
  {
    DisplayIndicador = 6;
    OutA = OUT_OFF;
    OutB = OUT_ON;
    OutC = OUT_ON;
    OutD = OUT_OFF;   
  }
  else if (TimeControlSec > cfgTimeGenerador4P*X_60)
  {
    DisplayIndicador = 5;
    OutA = OUT_ON;
    OutB = OUT_OFF;
    OutC = OUT_ON;
    OutD = OUT_OFF;     
  }
  else if (TimeControlSec > cfgTimeGenerador3P*X_60)
  {
    DisplayIndicador = 4;
    OutA = OUT_OFF;
    OutB = OUT_OFF;
    OutC = OUT_ON;
    OutD = OUT_OFF;   
  }
  else if (TimeControlSec > cfgTimeGenerador2P*X_60)
  {
    DisplayIndicador = 3;
    OutA = OUT_ON;
    OutB = OUT_ON;
    OutC = OUT_OFF;
    OutD = OUT_OFF;  
  }
  else if (TimeControlSec > cfgTimeGenerador1P*X_60)
  {
    DisplayIndicador = 2;
    OutA = OUT_OFF;
    OutB = OUT_ON;
    OutC = OUT_OFF;
    OutD = OUT_OFF;    
  }
  else if (TimeControlSec > cfgTimeBuzzerOn)
  {
    DisplayIndicador = 1;
    OutA = OUT_ON;
    OutB = OUT_OFF;
    OutC = OUT_OFF;
    OutD = OUT_OFF;  
  }
  else
  {
    DisplayIndicador = 0;
    OutA = OUT_OFF;
    OutB = OUT_OFF;
    OutC = OUT_OFF;
    OutD = OUT_OFF;  
  }
}
