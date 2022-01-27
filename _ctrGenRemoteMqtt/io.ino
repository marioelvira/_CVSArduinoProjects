
//////////////////////
// IO state machine //
//////////////////////
void _IOSetup()
{  
  DisplayIndicador = 1;

  VbattInADC = 0;

  for (int i = 0; i < VBATT_ARRAY_SIZE; i++)
    VbattInArray[i] = 0;

  VbattInPointer = 0;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop()
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
  VbattIn = (float)VbattInADC*((float)cfgADCm/10000) - (float)cfgADCb/10;
}

void _IOLcdLoop(void) {

  // DisplayIndicador
  if ((InD == OUT_OFF) && (InC == OUT_OFF) && (InB == OUT_OFF) && (InA == OUT_OFF)) 
    DisplayIndicador = 0;
  else if ((InD == OUT_OFF) && (InC == OUT_OFF) && (InB == OUT_OFF) && (InA == OUT_ON)) 
    DisplayIndicador = 1;
  else if ((InD == OUT_OFF) && (InC == OUT_OFF) && (InB == OUT_ON) && (InA == OUT_OFF)) 
    DisplayIndicador = 2;
  else if ((InD == OUT_OFF) && (InC == OUT_OFF) && (InB == OUT_ON) && (InA == OUT_ON)) 
    DisplayIndicador = 3;
  else if ((InD == OUT_OFF) && (InC == OUT_ON) && (InB == OUT_OFF) && (InA == OUT_OFF)) 
    DisplayIndicador = 4;
  else if ((InD == OUT_OFF) && (InC == OUT_ON) && (InB == OUT_OFF) && (InA == OUT_ON)) 
    DisplayIndicador = 5;
  else if ((InD == OUT_OFF) && (InC == OUT_ON) && (InB == OUT_ON) && (InA == OUT_OFF)) 
    DisplayIndicador = 6;    
  else if ((InD == OUT_OFF) && (InC == OUT_ON) && (InB == OUT_ON) && (InA == OUT_ON)) 
    DisplayIndicador = 7;
  else if ((InD == OUT_ON) && (InC == OUT_OFF) && (InB == OUT_OFF) && (InA == OUT_OFF)) 
    DisplayIndicador = 8;
  else
    DisplayIndicador = 9;
}
