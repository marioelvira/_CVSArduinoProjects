
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
  
    EEPROM.write(EEPROM_ADD_OK,      EEPROM_VAL_OK);

    // Data Data
    EEPROM.write(EEPROM_ADD_MODBUS_ID,  EEPROM_VAL_MODBUS_ID);
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  EEPROM_VAL_LOGIC_INS);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, EEPROM_VAL_LOGIC_OUTS);

    for (i = 0; i < ADC_NUMBER; i++)
    {
      eeprom_value_lo = EEPROM_VAL_ADC_M & 0x00FF;
      EEPROM.write(EEPROM_ADD_ADC_M_LO + i*EEPROM_ADC_SIZE, eeprom_value_lo);
      eeprom_value_hi = (EEPROM_VAL_ADC_M & 0xFF00)>>8;
      EEPROM.write(EEPROM_ADD_ADC_M_HI + i*EEPROM_ADC_SIZE, eeprom_value_hi);
      
      eeprom_value_lo = EEPROM_VAL_ADC_B & 0x00FF;
      EEPROM.write(EEPROM_ADD_ADC_B_LO + i*EEPROM_ADC_SIZE, eeprom_value_lo);
      eeprom_value_hi = (EEPROM_VAL_ADC_B & 0xFF00)>>8;
      EEPROM.write(EEPROM_ADD_ADC_B_HI + i*EEPROM_ADC_SIZE, eeprom_value_hi);
 
      EEPROM.write(EEPROM_ADD_ADC_S + i*EEPROM_ADC_SIZE,  EEPROM_VAL_ADC_S);

      eeprom_value_lo = EEPROM_VAL_ADC_T & 0x00FF;
      EEPROM.write(EEPROM_ADD_ADC_T_LO + i*EEPROM_ADC_SIZE, eeprom_value_lo);
      eeprom_value_hi = (EEPROM_VAL_ADC_T & 0xFF00)>>8;
      EEPROM.write(EEPROM_ADD_ADC_T_HI + i*EEPROM_ADC_SIZE, eeprom_value_hi);
      
    }
    
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
  
  for (i = 0; i < ADC_NUMBER; i++)
  {
    eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_M_HI + i*EEPROM_ADC_SIZE);
    eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_M_LO + i*EEPROM_ADC_SIZE);
    cfgADCm[i]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
    
    eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_B_HI + i*EEPROM_ADC_SIZE);
    eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_B_LO + i*EEPROM_ADC_SIZE);   
    cfgADCb[i]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
        
    cfgADCs[i]        = (int)EEPROM.read(EEPROM_ADD_ADC_S + i*EEPROM_ADC_SIZE);

    eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_T_HI + i*EEPROM_ADC_SIZE);
    eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_T_LO + i*EEPROM_ADC_SIZE);   
    cfgADCt[i]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  }

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Modbus ID: ");   Serial.println (cfgMbId);
  Serial.print("Logic Ins: ");   Serial.println (cfgLogicIns);
  Serial.print("Logic Outs: ");  Serial.println (cfgLogicOuts);

  for (i = 0; i < ADC_NUMBER; i++)
  {
    Serial.print("ADC m");    Serial.print (i); Serial.print(": "); Serial.print (cfgADCm[i]); Serial.println(" ");
    Serial.print("ADC b");    Serial.print (i); Serial.print(": "); Serial.print (cfgADCb[i]); Serial.println(" (/1000)");
    Serial.print("ADC p");    Serial.print (i); Serial.print(": "); Serial.print (cfgADCp[i]); Serial.println(" ");
    Serial.print("ADC s");    Serial.print (i); Serial.print(": "); Serial.print (cfgADCs[i]); Serial.println(" +/-  1/0");
    Serial.print("ADC trig"); Serial.print (i); Serial.print(": "); Serial.print (cfgADCb[i]); Serial.println(" (/1000)");
  }
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
