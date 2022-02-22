
//////////////////////
// IO state machine //
//////////////////////
//void _IOSetup(){}

void _ADCSetup()
{
  VbattInADC = 0;

  for (int i = 0; i < VBATT_ARRAY_SIZE; i++)
    VbattInArray[i] = 0;

  VbattInPointer = 0;
}

//////////////////////
// IO state machine //
//////////////////////
//void _IOLoop(){}

void _ADCLoop()
{
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
    VbattInADC = analogRead(PIN_VBATT_IN);

  if (cfgADCs == 0)
    VbattIn = (float)VbattInADC*((float)cfgADCm)/(float)cfgADCp - (float)cfgADCb;
  else
    VbattIn = (float)VbattInADC*((float)cfgADCm)/(float)cfgADCp + (float)cfgADCb;
}
