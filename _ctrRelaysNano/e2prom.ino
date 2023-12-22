
void _ConfigSetup(void)
{
  #if (_READ_EEPROM_ == 1)
  _ReadEEPROM();
  delay(1000);
  #endif

  // Config setup
  #if (_ERASE_EEPROM_ == 1)
    _ResetEEPROM();
    delay(1000);
  #endif

  // Read config from EEPROM
  _readCONFIG();

  #if (_READ_EEPROM_ == 1)
  delay(1000);
  _ReadEEPROM();
  #endif
}

void _readCONFIG (void)
{
  int ok;
  int eeprom_value_hi, eeprom_value_lo;
  
  //EEPROM.begin(512);  // ESPXX
    
  ok = EEPROM.read(EEPROM_ADD_OK);
  
  // Si NO esta grabada la configuracion...
  if (ok != EEPROM_VAL_OK)
  {
    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.println("Config NOK");
    #endif
  
    EEPROM.write(EEPROM_ADD_OK, EEPROM_VAL_OK);

    // Data Data
    EEPROM.write(EEPROM_ADD_MODBUS_ID,  EEPROM_VAL_MODBUS_ID);
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  EEPROM_VAL_LOGIC_INS);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, EEPROM_VAL_LOGIC_OUTS);

    // ADC 0
    eeprom_value_lo = EEPROM_VAL_C0ADC_EMON_R & 0x00FF;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_R_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C0ADC_EMON_R & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_R_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C0ADC_EMON_S & 0x00FF;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_S_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C0ADC_EMON_S & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_S_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C0ADC_EMON_O & 0x00FF;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_O_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C0ADC_EMON_O & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_O_HI, eeprom_value_hi);

    eeprom_value_lo = EEPROM_VAL_C0ADC_EMON_L & 0x00FF;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_L_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C0ADC_EMON_L & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_L_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C0ADC_EMON_SEC & 0x00FF;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_SEC_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C0ADC_EMON_SEC & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_SEC_HI, eeprom_value_hi);

    // ADC 1
    eeprom_value_lo = EEPROM_VAL_C1ADC_EMON_R & 0x00FF;
    EEPROM.write(EEPROM_ADD_C1ADC_EMON_R_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C1ADC_EMON_R & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C1ADC_EMON_R_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C1ADC_EMON_S & 0x00FF;
    EEPROM.write(EEPROM_ADD_C1ADC_EMON_S_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C1ADC_EMON_S & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C1ADC_EMON_S_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C1ADC_EMON_O & 0x00FF;
    EEPROM.write(EEPROM_ADD_C1ADC_EMON_O_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C1ADC_EMON_O & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C1ADC_EMON_O_HI, eeprom_value_hi);

    eeprom_value_lo = EEPROM_VAL_C1ADC_EMON_L & 0x00FF;
    EEPROM.write(EEPROM_ADD_C1ADC_EMON_L_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C1ADC_EMON_L & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C1ADC_EMON_L_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C1ADC_EMON_SEC & 0x00FF;
    EEPROM.write(EEPROM_ADD_C1ADC_EMON_SEC_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C1ADC_EMON_SEC & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C1ADC_EMON_SEC_HI, eeprom_value_hi);

    // ADC 2
    eeprom_value_lo = EEPROM_VAL_V0ADC_VDC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_V0ADC_VDC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V0ADC_VDC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V0ADC_VDC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_V0ADC_VDC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_V0ADC_VDC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V0ADC_VDC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V0ADC_VDC_B_HI, eeprom_value_hi);

    // ADC 3
    eeprom_value_lo = EEPROM_VAL_V1ADC_VDC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_V1ADC_VDC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V1ADC_VDC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V1ADC_VDC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_V1ADC_VDC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_V1ADC_VDC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V1ADC_VDC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V1ADC_VDC_B_HI, eeprom_value_hi);

    //EEPROM.commit();    // ESPXX Store data to EEPROM
  }
  else
  {
    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.println("Config OK");
    #endif
  }

  _eeprom2ramCONFIG();
}

void _ram2eepromCONFIG (void)
{
  int eeprom_value_hi, eeprom_value_lo;

  // Data Data
  EEPROM.write(EEPROM_ADD_MODBUS_ID,  (byte)cfgMbId);
  EEPROM.write(EEPROM_ADD_LOGIC_INS,  (byte)cfgLogicIns);
  EEPROM.write(EEPROM_ADD_LOGIC_OUTS, (byte)cfgLogicOuts);

  // ADC 0
  eeprom_value_lo = cfgC0ADCEmonR & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_R_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgC0ADCEmonR & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_R_HI, eeprom_value_hi);
  eeprom_value_lo = cfgC0ADCEmonS & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_S_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgC0ADCEmonS & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_S_HI, eeprom_value_hi);
  eeprom_value_lo = cfgC0ADCEmonO & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_O_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgC0ADCEmonO & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_O_HI, eeprom_value_hi);

  eeprom_value_lo = cfgC0ADCEmonL & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_L_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgC0ADCEmonL & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_L_HI, eeprom_value_hi);
  eeprom_value_lo = cfgC0ADCEmonSec & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_SEC_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgC0ADCEmonSec & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_SEC_HI, eeprom_value_hi);

  // ADC 1
  eeprom_value_lo = cfgC1ADCEmonR & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_R_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgC1ADCEmonR & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_R_HI, eeprom_value_hi);
  eeprom_value_lo = cfgC1ADCEmonS & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_S_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgC1ADCEmonS & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_S_HI, eeprom_value_hi);
  eeprom_value_lo = cfgC1ADCEmonO & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_O_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgC1ADCEmonO & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_O_HI, eeprom_value_hi);

  eeprom_value_lo = cfgC1ADCEmonL & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_L_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgC1ADCEmonL & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_L_HI, eeprom_value_hi);
  eeprom_value_lo = cfgC1ADCEmonSec & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_SEC_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgC1ADCEmonSec & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_SEC_HI, eeprom_value_hi);

  // ADC 2
  eeprom_value_lo = cfgV0ADCm & 0x00FF;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgV0ADCm & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgV0ADCb & 0x00FF;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgV0ADCb & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_B_HI, eeprom_value_hi);

  // ADC 3
  eeprom_value_lo = cfgV1ADCm & 0x00FF;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgV1ADCm & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgV1ADCb & 0x00FF;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgV1ADCb & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_B_HI, eeprom_value_hi);
}


void _eeprom2ramCONFIG (void)
{
  int eeprom_value_hi, eeprom_value_lo;

  cfgMbId           = (int)EEPROM.read(EEPROM_ADD_MODBUS_ID);
  cfgLogicIns       = (int)EEPROM.read(EEPROM_ADD_LOGIC_INS);
  cfgLogicOuts      = (int)EEPROM.read(EEPROM_ADD_LOGIC_OUTS); 
  
  // ADC 0
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_R_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_R_LO);
  cfgC0ADCEmonR       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_S_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_S_LO);
  cfgC0ADCEmonS       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_O_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_O_LO);
  cfgC0ADCEmonO       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_L_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_L_LO);
  cfgC0ADCEmonL       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_SEC_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_SEC_LO);
  cfgC0ADCEmonSec     = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 1
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_R_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_R_LO);
  cfgC1ADCEmonR       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_S_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_S_LO);
  cfgC1ADCEmonS       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_O_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_O_LO);
  cfgC1ADCEmonO       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_L_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_L_LO);
  cfgC1ADCEmonL       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_SEC_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_SEC_LO);
  cfgC1ADCEmonSec     = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 2
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_M_LO);
  cfgV0ADCm         = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_B_LO);
  cfgV0ADCb         = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 3
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_M_LO);
  cfgV1ADCm         = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_B_LO);
  cfgV1ADCb         = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Modbus ID: ");  Serial.println (cfgMbId);
  Serial.print("Logic Ins: ");  Serial.println (cfgLogicIns);
  Serial.print("Logic Outs: "); Serial.println (cfgLogicOuts);

  Serial.print("C0 Irms Ratio");   Serial.print(": "); Serial.print (cfgC0ADCEmonR);  Serial.println(" ");
  Serial.print("C0 Irms Samples"); Serial.print(": "); Serial.print (cfgC0ADCEmonS);  Serial.println(" ");
  Serial.print("C0 Irms Samples"); Serial.print(": "); Serial.print (cfgC0ADCEmonO);  Serial.println(" mA");
  Serial.print("C0 Irms Limit");   Serial.print(": "); Serial.print (cfgC0ADCEmonL);  Serial.println(" ");
  Serial.print("C0 Irms Hys Sec"); Serial.print(": "); Serial.print (cfgC0ADCEmonLS); Serial.println(" sec");

  Serial.print("C1 Irms Ratio");   Serial.print(": "); Serial.print (cfgC1ADCEmonR);  Serial.println(" ");
  Serial.print("C1 Irms Samples"); Serial.print(": "); Serial.print (cfgC1ADCEmonS);  Serial.println(" ");
  Serial.print("C1 Irms Samples"); Serial.print(": "); Serial.print (cfgC1ADCEmonO);  Serial.println(" mA");
  Serial.print("C1 Irms Limit");   Serial.print(": "); Serial.print (cfgC1ADCEmonL);  Serial.println(" ");
  Serial.print("C1 Irms Hys Sec"); Serial.print(": "); Serial.print (cfgC1ADCEmonLS); Serial.println(" sec");

  Serial.print("V0 Vdc recta m");  Serial.print(": "); Serial.print (cfgV0ADCm);  Serial.println(" ");
  Serial.print("V0 Vdc recta b");  Serial.print(": "); Serial.print (cfgv0ADCb);  Serial.println(" (/1000)");
  
  Serial.print("V1 Vdc recta m");  Serial.print(": "); Serial.print (cfgV1ADCm);  Serial.println(" ");
  Serial.print("V1 Vdc recta b");  Serial.print(": "); Serial.print (cfgv1ADCb);  Serial.println(" (/1000)");
  #endif
}

void _ResetEEPROM() {

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.println("Erasing E2PROM 512 size... ");
  #endif

  // write a 0 to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0xFF);
  }
  
  //EEPROM.commit();    // ESPXX Store data to EEPROM
}

void _ReadEEPROM() {

  int j = 0;

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.println("Reading E2PROM 512 size... ");
  #endif

  //EEPROM.begin(512);
   
  for (int i = 0; i < 512; i++) {

    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    j = EEPROM.read(i);
    if (j < 16)
      Serial.print("0");
    Serial.print(j, HEX);
    #endif
  }

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.println(" ");
  Serial.println("End ...");
  #endif  
}
