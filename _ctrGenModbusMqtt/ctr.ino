
////////////////
// Ctr set up //
////////////////
void _CtrSetup(void)
{
  ControlState = STATE_STANDBY;
  ControlTick = millis();
  
  TimeControlSec = 0;
  DisplayIndicador = 0;
  remAct = 0;

  _GenTimeReset();
  genMinOn = 0;

  // Control
  OutBomba = OUT_OFF;
  OutGen = OUT_OFF;

  // Outs Time Setup
  ctrOTimeSetup();
}

// Outs Time Setup
void ctrOTimeSetup(void)
{
  int i;
   
  for (i = 0; i < NUM_O1X_MAX; i++)
  {
    outO1XState[i] = STATE_O1X_STANDBY;
    outO1XSec[i] = 0;
  }
}

///////////////////////
// Ctr state machine //
///////////////////////
void _CtrLoop(void)
{
  if (ControlState == STATE_STANDBY)
  {}  //genMinOn = 0;
  else
    _GenTimeReset();
      
  switch (ControlState)
  {
    case STATE_STANDBY:    
      // Control
      OutBomba = OUT_OFF;
      OutGen = OUT_OFF;

      // Indicadores
      OutZumb = OUT_OFF;
      OutDisp = OUT_OFF;

      // Alarm reset
      alarm[AL_ERROR_GEN] = 0;
    
      TimeControlSec = 0;
      ControlTick = millis();

      break;

    case STATE_START:
      // Control
      OutBomba = OUT_OFF;
      OutGen = OUT_OFF;
      
      genMinOn = 0;
      
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

      // Alarm
      if (TimeControlSec > cfgTimeGenAl)
      { 
        if (InGen == IO_OFF)
          alarm[AL_ERROR_GEN] = 1;
        else
          alarm[AL_ERROR_GEN] = 0;
      }

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
      {
        // Remote
        remAct = 0;
        ControlState = STATE_STANDBY;
      }
      
      break;

  }

  // loops
  ctrIOsLoop();
  ctrInsLoop();
  ctrPulsLoop();
  ctrLcdLoop();
  ctrOTimeLoop();
}

// IOs used in ctr
void ctrIOsLoop(void)
{
  // Ins
  InStartVal= ioInA;
  InEndVal  = ioInB;
  InGen = ioInC;

  // Outs
  ioOutA = OutGen;
  ioOutB = OutBomba;
  ioOutC = OutZumb;
  
  if (OutA != mbOuts[0][0])
  {  
    mbOutVal = OutA;
    mbOutBoard = 0;
    mbOutNum = 0; // O1
    
    if (mbState == MB_STANDBY)
      mbState = MB_WRITEOUT;
  }
  else if (OutB != mbOuts[1][0])
  {
    mbOutVal = OutB;
    mbOutBoard = 0;
    mbOutNum = 1; // O2
    
    if (mbState == MB_STANDBY)
      mbState = MB_WRITEOUT;
    
  }
  else if (OutC != mbOuts[2][0])
  {
    mbOutVal = OutC;
    mbOutBoard = 0;
    mbOutNum = 2; // O3
    
    if (mbState == MB_STANDBY)
      mbState = MB_WRITEOUT;    
  }
  else if (OutD != mbOuts[3][0])
  {
    mbOutVal = OutD;
    mbOutBoard = 0;
    mbOutNum = 3; // O2
    
    if (mbState == MB_STANDBY)
      mbState = MB_WRITEOUT;
  }
  else if (OutDisp != mbOuts[4][0])
  {
    mbOutVal = OutDisp;
    mbOutBoard = 0;
    mbOutNum = 4; // O3
    
    if (mbState == MB_STANDBY)
      mbState = MB_WRITEOUT;
  }
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

    // Si estamos en paaro
    if (ControlState == STATE_STANDBY)
      ControlState = STATE_START;
    // Mantenemos el arranque 
    else if (ControlState != STATE_START)
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

// Outs Time
void ctrOTimeLoop(void)
{
  int i, minHour;

  for (i = 0; i < NUM_O1X_MAX ; i++)
  {
	  if (i < 4) minHour = X_60;
	  else minHour = X_3600;
	
	  switch (outO1XState[i])
	  {
      case STATE_O1X_STANDBY:
        break;
 
	    case STATE_O1X_ON:
        mbOutBoard = 1;
        mbOutNum = i;
        mbOutVal = OUT_ON;

        if (mbState == MB_STANDBY)
        {
          mbState = MB_WRITEOUT;
          outO1XState[i] = STATE_O1X_TOUT_ON;
          outO1XSec[i] = timeTickSec;
        }
        break;
      
      case STATE_O1X_TOUT_ON:
		    if (timeTickSec - outO1XSec[i] >= (cfgTimeO1X[i]*minHour))
		      outO1XState[i] = STATE_O1X_OFF;

		    break;

      case STATE_O1X_OFF:
        mbOutBoard = 1;
        mbOutNum = i;
        mbOutVal = OUT_OFF;

        if (mbState == MB_STANDBY)
        {
          mbState = MB_WRITEOUT;
          outO1XState[i] = STATE_O1X_STANDBY;
        }
        break;
	  }
  }
}
