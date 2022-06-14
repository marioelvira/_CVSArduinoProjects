
///////////////
// NTC setup //
///////////////
void _NTCSetup()
{
  NtcInADC = 0;
  NtcIn = 25;

  for (int i = 0; i < NTC_ARRAY_SIZE; i++)
    NtcInArray[i] = 0;

  NtcInPointer = 0;
}

//////////////////////
// IO state machine //
//////////////////////
void _NTCLoop()
{
  float V, /*R,*/ logR, R_th, kelvin;

  if (cfgADCf == 1)
  {
    int   ntcAcc = 0;
    
    NtcInArray[NtcInPointer] = analogRead(PIN_NTC_IN);
    NtcInPointer++;
    if (NtcInPointer >= NTC_ARRAY_SIZE)
      NtcInPointer = 0;
  
    // Calculamos la media del Array...
    for (int i = 0; i < NTC_ARRAY_SIZE; i++)
      ntcAcc = ntcAcc + NtcInArray[i];
    
    NtcInADC = ntcAcc/NTC_ARRAY_SIZE;
  }
  else
    NtcInADC = analogRead(PIN_NTC_IN);

  /////////////////////
  // NTC calculation //
  /////////////////////
  V = ((float)NtcInADC / 1024) * Vcc;
  NtcR = (Rc * V) / (Vcc - V);

  logR  = log(NtcR);
  // Aprox Steinhart-Hart
  R_th = 1.0 / (A + B*logR + C*logR*logR*logR);
  kelvin = R_th - V*V/(K * NtcR)*1000;
  NtcIn = kelvin - 273.15;
}
