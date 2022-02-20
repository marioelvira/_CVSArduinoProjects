////////////////
// RAM set up //
////////////////
void _RAMSetup(void)
{
  freeRam = ESP.getFreeHeap();
}

//////////////
// Free RAM //
//////////////
void _FreeRAM(void)
{
  if(ESP.getFreeHeap() != freeRam)
  {
    freeRam = ESP.getFreeHeap();
    
    #if (_FREERAM_SERIAL_DEBUG_ == 1)
    Serial.print("RAM:");
    Serial.println(freeRam);
    #endif
  }
}
