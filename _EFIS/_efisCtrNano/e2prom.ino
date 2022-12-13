
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
  //int eeprom_value_hi, eeprom_value_lo;
  
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
    EEPROM.write(EEPROM_ADD_ADCF0,       EEPROM_VAL_ADCF0);
    EEPROM.write(EEPROM_ADD_ADCF1,       EEPROM_VAL_ADCF1);
    EEPROM.write(EEPROM_ADD_ADCF2,       EEPROM_VAL_ADCF2);
    EEPROM.write(EEPROM_ADD_ADCF3,       EEPROM_VAL_ADCF3);

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
  cfgADCf[0] = (int)EEPROM.read(EEPROM_ADD_ADCF0);
  cfgADCf[1] = (int)EEPROM.read(EEPROM_ADD_ADCF1);
  cfgADCf[2] = (int)EEPROM.read(EEPROM_ADD_ADCF2);
  cfgADCf[3] = (int)EEPROM.read(EEPROM_ADD_ADCF3);
  
  cfgRpm   = (int)EEPROM.read(EEPROM_ADD_RPM);
  cfgPres  = (int)EEPROM.read(EEPROM_ADD_PRESS);

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Modbus ID: ");  Serial.print (cfgMbId);  Serial.println(" ");
  for (i = 0; i < ADC_NUMBER; i++)
  {
    Serial.print("Filter ADC: "); Serial.println(cfgADCf[i]);
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
