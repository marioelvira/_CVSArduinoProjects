
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
    eeprom_value_lo = EEPROM_VAL_NTIME_SECS & 0x00FF;
    EEPROM.write(EEPROM_ADD_NTIME_SECS_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_NTIME_SECS & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_NTIME_SECS_HI, eeprom_value_hi);

    // ADC 0
    eeprom_value_lo = EEPROM_VAL_ADC_EMON_R & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_EMON_R_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_EMON_R & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_EMON_R_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC_EMON_S & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_EMON_S_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_EMON_S & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_EMON_S_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC_EMON_O & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_EMON_O_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_EMON_O & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_EMON_O_HI, eeprom_value_hi);

    eeprom_value_lo = EEPROM_VAL_ADC_EMON_L & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_EMON_L_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_EMON_L & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_EMON_L_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC_EMON_SEC & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_EMON_SEC_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_EMON_SEC & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_EMON_SEC_HI, eeprom_value_hi);

    // ADC 1
    eeprom_value_lo = EEPROM_VAL_ADC_VDC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_VDC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_VDC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_VDC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC_VDC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_VDC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_VDC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_VDC_B_HI, eeprom_value_hi);

    eeprom_value_lo = EEPROM_VAL_ADC_VDC_L1 & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_VDC_L1_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_VDC_L1 & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_VDC_L1_HI, eeprom_value_hi);

    eeprom_value_lo = EEPROM_VAL_ADC_VDC_L2 & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_VDC_L2_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_VDC_L2 & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_VDC_L2_HI, eeprom_value_hi);

    eeprom_value_lo = EEPROM_VAL_ADC_VDC_SEC & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_VDC_SEC_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_VDC_SEC & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_VDC_SEC_HI, eeprom_value_hi);

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
  eeprom_value_lo = cfgNTimeSecs & 0x00FF;
  EEPROM.write(EEPROM_ADD_NTIME_SECS_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgNTimeSecs & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_NTIME_SECS_HI, eeprom_value_hi);

  // ADC 0
  eeprom_value_lo = cfgADCEmonR & 0x00FF;
  EEPROM.write(EEPROM_ADD_ADC_EMON_R_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgADCEmonR & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_ADC_EMON_R_HI, eeprom_value_hi);
  eeprom_value_lo = cfgADCEmonS & 0x00FF;
  EEPROM.write(EEPROM_ADD_ADC_EMON_S_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgADCEmonS & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_ADC_EMON_S_HI, eeprom_value_hi);
  eeprom_value_lo = cfgADCEmonO & 0x00FF;
  EEPROM.write(EEPROM_ADD_ADC_EMON_O_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgADCEmonO & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_ADC_EMON_O_HI, eeprom_value_hi);

  eeprom_value_lo = cfgADCEmonL & 0x00FF;
  EEPROM.write(EEPROM_ADD_ADC_EMON_L_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgADCEmonL & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_ADC_EMON_L_HI, eeprom_value_hi);
  eeprom_value_lo = cfgADCEmonSec & 0x00FF;
  EEPROM.write(EEPROM_ADD_ADC_EMON_SEC_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgADCEmonSec & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_ADC_EMON_SEC_HI, eeprom_value_hi);

  // ADC 1
  eeprom_value_lo = cfgADCm & 0x00FF;
  EEPROM.write(EEPROM_ADD_ADC_VDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgADCm & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_ADC_VDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgADCb & 0x00FF;
  EEPROM.write(EEPROM_ADD_ADC_VDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgADCb & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_ADC_VDC_B_HI, eeprom_value_hi);

  eeprom_value_lo = cfgADCVdcL1 & 0x00FF;
  EEPROM.write(EEPROM_ADD_ADC_VDC_L1_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgADCVdcL1 & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_ADC_VDC_L1_HI, eeprom_value_hi);
  eeprom_value_lo = cfgADCVdcL2 & 0x00FF;
  EEPROM.write(EEPROM_ADD_ADC_VDC_L2_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgADCVdcL2 & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_ADC_VDC_L2_HI, eeprom_value_hi);

  eeprom_value_lo = cfgADCVdcSec & 0x00FF;
  EEPROM.write(EEPROM_ADD_ADC_VDC_SEC_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgADCVdcSec & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_ADC_VDC_SEC_HI, eeprom_value_hi);
}


void _eeprom2ramCONFIG (void)
{
  int eeprom_value_hi, eeprom_value_lo;

  cfgMbId           = (int)EEPROM.read(EEPROM_ADD_MODBUS_ID);
  cfgLogicIns       = (int)EEPROM.read(EEPROM_ADD_LOGIC_INS);
  cfgLogicOuts      = (int)EEPROM.read(EEPROM_ADD_LOGIC_OUTS); 
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_NTIME_SECS_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_NTIME_SECS_LO);
  cfgNTimeSecs      = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  
  // ADC 0
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_EMON_R_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_EMON_R_LO);
  cfgADCEmonR       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_EMON_S_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_EMON_S_LO);
  cfgADCEmonS       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_EMON_O_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_EMON_O_LO);
  cfgADCEmonO       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_EMON_L_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_EMON_L_LO);
  cfgADCEmonL       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_EMON_SEC_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_EMON_SEC_LO);
  cfgADCEmonSec     = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 1
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_VDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_VDC_M_LO);
  cfgADCm           = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_VDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_VDC_B_LO);
  cfgADCb           = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_VDC_L1_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_VDC_L1_LO);
  cfgADCVdcL1       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);  
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_VDC_L2_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_VDC_L2_LO);
  cfgADCVdcL2       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_VDC_SEC_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_VDC_SEC_LO);
  cfgADCVdcSec      = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Modbus ID: ");  Serial.println (cfgMbId);
  Serial.print("Logic Ins: ");  Serial.println (cfgLogicIns);
  Serial.print("Logic Outs: "); Serial.println (cfgLogicOuts);
  Serial.print("NTime Secs: "); Serial.println (cfgNTimeSecs);

  Serial.print("Irms Ratio");   Serial.print(": "); Serial.print (cfgADCEmonR);  Serial.println(" ");
  Serial.print("Irms Samples"); Serial.print(": "); Serial.print (cfgADCEmonS);  Serial.println(" ");
  Serial.print("Irms Samples"); Serial.print(": "); Serial.print (cfgADCEmonO);  Serial.println(" mA");
  Serial.print("Irms Limit");   Serial.print(": "); Serial.print (cfgADCEmonL);  Serial.println(" ");
  Serial.print("Irms Hys Sec"); Serial.print(": "); Serial.print (cfgADCEmonLS); Serial.println(" sec");

  Serial.print("Vdc recta m");  Serial.print(": "); Serial.print (cfgADCm);  Serial.println(" ");
  Serial.print("Vdc recta b");  Serial.print(": "); Serial.print (cfgADCb);  Serial.println(" (/1000)");
  Serial.print("Vdc Limit1");   Serial.print(": "); Serial.print (cfgADCVdcL1); Serial.println(" x10");
  Serial.print("Vdc Limit2");   Serial.print(": "); Serial.print (cfgADCVdcL2);  Serial.println(" x10");
  Serial.print("Irms Hys Sec"); Serial.print(": "); Serial.print (cfgADCVdcSec); Serial.println(" sec");
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
