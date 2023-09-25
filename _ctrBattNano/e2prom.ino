
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
  
    EEPROM.write(EEPROM_ADD_OK,      EEPROM_VAL_OK);

    // Data Data
    EEPROM.write(EEPROM_ADD_MODBUS_ID,  EEPROM_VAL_MODBUS_ID);
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  EEPROM_VAL_LOGIC_INS);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, EEPROM_VAL_LOGIC_OUTS);

    // ADC 0
    eeprom_value_lo = EEPROM_VAL_ADC0_EMON_R & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC0_EMON_R_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC0_EMON_R & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC0_EMON_R_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC0_EMON_S & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC0_EMON_S_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC0_EMON_S & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC0_EMON_S_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC0_EMON_O & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC0_EMON_O_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC0_EMON_O & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC0_EMON_O_HI, eeprom_value_hi);

    EEPROM.write(EEPROM_ADD_ADC0_EMON_TS, EEPROM_VAL_ADC0_EMON_TS);
    eeprom_value_lo = EEPROM_VAL_ADC0_EMON_T & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC0_EMON_T_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC0_EMON_T & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC0_EMON_T_HI, eeprom_value_hi);

    // ADC 1
    eeprom_value_lo = EEPROM_VAL_ADC1_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC1_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC1_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC1_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC1_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC1_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC1_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC1_B_HI, eeprom_value_hi);
    EEPROM.write(EEPROM_ADD_ADC1_S,  EEPROM_VAL_ADC1_S);

    EEPROM.write(EEPROM_ADD_ADC1_TS,  EEPROM_VAL_ADC1_TS);
    eeprom_value_lo = EEPROM_VAL_ADC1_T & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC1_T_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC1_T & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC1_T_HI, eeprom_value_hi);

    //EEPROM.commit();    // ESPXX Store data to EEPROM
  }
  else
  {
    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.println("Config OK");
    #endif
  }

  cfgMbId      = (int)EEPROM.read(EEPROM_ADD_MODBUS_ID);
  cfgLogicIns  = (int)EEPROM.read(EEPROM_ADD_LOGIC_INS);
  cfgLogicOuts = (int)EEPROM.read(EEPROM_ADD_LOGIC_OUTS);
  
  // ADC 0
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC0_EMON_R_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC0_EMON_R_LO);
  cfgADC0EmonR      = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC0_EMON_S_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC0_EMON_S_LO);
  cfgADC0EmonS      = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC0_EMON_O_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC0_EMON_O_LO);
  cfgADC0EmonO      = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  cfgADC0Emonts     = (int)EEPROM.read(EEPROM_ADD_ADC0_EMON_TS);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC0_EMON_T_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC0_EMON_T_LO);
  cfgADC0Emont      = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 1
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC1_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC1_M_LO);
  cfgADC1m          = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC1_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC1_B_LO);
  cfgADC1b          = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  cfgADC1s          = (int)EEPROM.read(EEPROM_ADD_ADC1_S);

  cfgADC1ts         = (int)EEPROM.read(EEPROM_ADD_ADC1_TS);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC1_T_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC1_T_LO);
  cfgADC1t          = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);


  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Modbus ID: ");   Serial.println (cfgMbId);
  Serial.print("Logic Ins: ");   Serial.println (cfgLogicIns);
  Serial.print("Logic Outs: ");  Serial.println (cfgLogicOuts);

  Serial.print("ADC0 Ration");  Serial.print(": "); Serial.print (cfgADC0EmonR);  Serial.println(" ");
  Serial.print("ADC0 Samples"); Serial.print(": "); Serial.print (cfgADC0EmonS);  Serial.println(" ");
  Serial.print("ADC0 Samples"); Serial.print(": "); Serial.print (cfgADC0Emon0);  Serial.println(" mA");
  Serial.print("ADC0 trig s");  Serial.print(": "); Serial.print (cfgADC0Emonts); Serial.println(" u/d - 1/0");
  Serial.print("ADC0 trig");    Serial.print(": "); Serial.print (cfgADC0Emont);  Serial.println(" ");

  Serial.print("ADC1 m");       Serial.print(": "); Serial.print (cfgADC1m);  Serial.println(" ");
  Serial.print("ADC1 b");       Serial.print(": "); Serial.print (cfgADC1b);  Serial.println(" (/1000)");
  Serial.print("ADC1 s");       Serial.print(": "); Serial.print (cfgADC1s);  Serial.println(" +/- 1/0");
  Serial.print("ADC1 trig s");  Serial.print(": "); Serial.print (cfgADC1ts); Serial.println(" u/d - 1/0");
0  Serial.print("ADC1 trig");   Serial.print(": "); Serial.print (cfgADC1t);  Serial.println(" ");
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
