
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

void _ADCSetup()
{
  VbattInADC = 0;
  /*
  for (int i = 0; i < VBATT_ARRAY_SIZE; i++)
    VbattInArray[i] = 0;

  VbattInPointer = 0;
  */
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

void _ADCLoop()
{
  /*
  if (cfgADCf == 1)
  {
    int   vbattAcc = 0;
    
    VbattInArray[VbattInPointer] = analogRead(PIN_VBATT_IN);
    VbattInPointer++;
    if (VbattInPointer >= VBATT_ARRAY_SIZE)
      VbattInPointer = 0;
  
    // Calculamos la media del Array...
    for (int i = 0; i < VBATT_ARRAY_SIZE; i++)
      vbattAcc = vbattAcc + VbattInArray[i];
    
    VbattInADC = vbattAcc/VBATT_ARRAY_SIZE;
  }
  else
  */
    VbattInADC = analogRead(PIN_VBATT_IN);
  /*
  if (cfgADCs == 0)
    VbattIn = (float)VbattInADC*((float)cfgADCm)/(float)cfgADCp - (float)cfgADCb/1000;
  else
    VbattIn = (float)VbattInADC*((float)cfgADCm)/(float)cfgADCp + (float)cfgADCb/1000;
  */
}

void _IOPulsLoop(void) {

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
      TimeControlSec = TimeGenerador9P*X_3600;
      
    else if (DisplayIndicador == 8)
      TimeControlSec = TimeGenerador9P*X_3600;
      
    else if (DisplayIndicador == 7)
      TimeControlSec = TimeGenerador8P*X_3600;
      
    else if (DisplayIndicador == 6)
      TimeControlSec = TimeGenerador7P*X_3600;
      
    else if (DisplayIndicador == 5)
      TimeControlSec = TimeGenerador6P*X_3600;
      
    else if (DisplayIndicador == 4)
      TimeControlSec = TimeGenerador5P*X_60;
      
    else if (DisplayIndicador == 3)
      TimeControlSec = TimeGenerador4P*X_60;
      
    else if (DisplayIndicador == 2)
      TimeControlSec = TimeGenerador3P*X_60;
      
    else if (DisplayIndicador == 1)
      TimeControlSec = TimeGenerador2P*X_60;
      
    else
      TimeControlSec = TimeGenerador1P*X_60;
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

void _IOLcdLoop(void) {

  if (TimeControlSec > TimeGenerador8P*X_3600)
  {
    DisplayIndicador = 9;
    OutA = OUT_ON;
    OutB = OUT_OFF;
    OutC = OUT_OFF;
    OutD = OUT_ON;  
  }
  else if (TimeControlSec > TimeGenerador7P*X_3600)
  {
    DisplayIndicador = 8;
    OutA = OUT_OFF;
    OutB = OUT_OFF;
    OutC = OUT_OFF;
    OutD = OUT_ON;  
  }
  else if (TimeControlSec > TimeGenerador6P*X_3600)
  {
    DisplayIndicador = 7;
    OutA = OUT_ON;
    OutB = OUT_ON;
    OutC = OUT_ON;
    OutD = OUT_OFF;   
  }
  else if (TimeControlSec > TimeGenerador5P*X_60)
  {
    DisplayIndicador = 6;
    OutA = OUT_OFF;
    OutB = OUT_ON;
    OutC = OUT_ON;
    OutD = OUT_OFF;   
  }
  else if (TimeControlSec > TimeGenerador4P*X_60)
  {
    DisplayIndicador = 5;
    OutA = OUT_ON;
    OutB = OUT_OFF;
    OutC = OUT_ON;
    OutD = OUT_OFF;     
  }
  else if (TimeControlSec > TimeGenerador3P*X_60)
  {
    DisplayIndicador = 4;
    OutA = OUT_OFF;
    OutB = OUT_OFF;
    OutC = OUT_ON;
    OutD = OUT_OFF;   
  }
  else if (TimeControlSec > TimeGenerador2P*X_60)
  {
    DisplayIndicador = 3;
    OutA = OUT_ON;
    OutB = OUT_ON;
    OutC = OUT_OFF;
    OutD = OUT_OFF;  
  }
  else if (TimeControlSec > TimeGenerador1P*X_60)
  {
    DisplayIndicador = 2;
    OutA = OUT_OFF;
    OutB = OUT_ON;
    OutC = OUT_OFF;
    OutD = OUT_OFF;    
  }
  else if (TimeControlSec > TimeBuzzerOn)
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
