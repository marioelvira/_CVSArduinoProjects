
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
  int ok, i;
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

    // Data
    EEPROM.write(EEPROM_ADD_MODBUS_ID,   EEPROM_VAL_MODBUS_ID);
	
    eeprom_value_lo = EEPROM_VAL_ADC0_M & 0x00FF;
	  EEPROM.write(EEPROM_ADD_ADC0_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC0_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC0_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC0_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC0_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC0_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC0_B_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC0_P & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC0_P_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC0_P & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC0_P_HI, eeprom_value_hi);
    EEPROM.write(EEPROM_ADD_ADC0_S,  EEPROM_VAL_ADC0_S);
    EEPROM.write(EEPROM_ADD_ADC0_F,  EEPROM_VAL_ADC0_F);

	  eeprom_value_lo = EEPROM_VAL_ADC1_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC1_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC1_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC1_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC1_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC1_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC1_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC1_B_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC1_P & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC1_P_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC1_P & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC1_P_HI, eeprom_value_hi);   
    EEPROM.write(EEPROM_ADD_ADC1_S,  EEPROM_VAL_ADC1_S);
    EEPROM.write(EEPROM_ADD_ADC1_F,  EEPROM_VAL_ADC1_F);
    	
	  eeprom_value_lo = EEPROM_VAL_ADC2_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC2_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC2_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC2_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC2_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC2_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC2_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC2_B_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC2_P & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC2_P_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC2_P & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC2_P_HI, eeprom_value_hi);   
    EEPROM.write(EEPROM_ADD_ADC2_S,  EEPROM_VAL_ADC2_S);
    EEPROM.write(EEPROM_ADD_ADC2_F,  EEPROM_VAL_ADC2_F);
	
	  eeprom_value_lo = EEPROM_VAL_ADC3_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC3_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC3_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC3_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC3_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC3_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC3_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC3_B_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC3_P & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC3_P_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC3_P & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC3_P_HI, eeprom_value_hi);   
    EEPROM.write(EEPROM_ADD_ADC3_S,  EEPROM_VAL_ADC3_S);
    EEPROM.write(EEPROM_ADD_ADC3_F,  EEPROM_VAL_ADC3_F);

    EEPROM.write(EEPROM_ADD_RPM,   EEPROM_VAL_RPM);
    EEPROM.write(EEPROM_ADD_PRESS, EEPROM_VAL_PRESS);

    //EEPROM.commit();    // ESPXX Store data to EEPROM
  }
  else
  {
    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.println("Config OK");
    #endif
  }

  cfgMbId = (int)EEPROM.read(EEPROM_ADD_MODBUS_ID);
  
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC0_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC0_M_LO);   
  cfgADCm[0]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC0_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC0_B_LO);   
  cfgADCb[0]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC0_P_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC0_P_LO);
  cfgADCp[0]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF); 
  cfgADCs[0]        = (int)EEPROM.read(EEPROM_ADD_ADC0_S);
  cfgADCf[0]        = (int)EEPROM.read(EEPROM_ADD_ADC0_F);
   
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC1_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC1_M_LO);   
  cfgADCm[1]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC1_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC1_B_LO);   
  cfgADCb[1]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC1_P_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC1_P_LO);   
  cfgADCp[1]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF); 
  cfgADCs[1]        = (int)EEPROM.read(EEPROM_ADD_ADC1_S);
  cfgADCf[1]        = (int)EEPROM.read(EEPROM_ADD_ADC1_F);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC2_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC2_M_LO);   
  cfgADCm[2]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC2_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC2_B_LO);   
  cfgADCb[2]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC2_P_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC2_P_LO);   
  cfgADCp[2]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF); 
  cfgADCs[2]        = (int)EEPROM.read(EEPROM_ADD_ADC2_S);
  cfgADCf[2]        = (int)EEPROM.read(EEPROM_ADD_ADC2_F);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC3_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC3_M_LO);   
  cfgADCm[3]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC3_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC3_B_LO);   
  cfgADCb[3]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC3_P_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC3_P_LO);   
  cfgADCp[3]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF); 
  cfgADCs[3]        = (int)EEPROM.read(EEPROM_ADD_ADC3_S);
  cfgADCf[3]        = (int)EEPROM.read(EEPROM_ADD_ADC3_F);
    
  cfgRpm   = (int)EEPROM.read(EEPROM_ADD_RPM);
  cfgPres  = (int)EEPROM.read(EEPROM_ADD_PRESS);

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Modbus ID: ");  Serial.println (cfgMbId);
  for (i = 0; i < ADC_NUMBER; i++)
  {
    Serial.print("ADC"); Serial.print(i);
    Serial.print(" m"); Serial.print(cfgADCm[i]);
    Serial.print(" b"); Serial.print(cfgADCb[i]);
    Serial.print(" p"); Serial.print(cfgADCp[i]);
    Serial.print(" s"); Serial.print(cfgADCs[i]);
    Serial.print(" f"); Serial.print(cfgADCf[i]);
    Serial.println(" ");
  }
  
  Serial.print("RMP: ");    Serial.println (cfgRpm);
  Serial.print("PRESS: ");  Serial.println (cfgPres);
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
