
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
    EEPROM.write(EEPROM_ADD_C0ADC_TYPE, EEPROM_VAL_C0ADC_TYPE);

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

    eeprom_value_lo = EEPROM_VAL_C0ADC_IDC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_C0ADC_IDC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C0ADC_IDC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C0ADC_IDC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C0ADC_IDC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_C0ADC_IDC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C0ADC_IDC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C0ADC_IDC_B_HI, eeprom_value_hi);

    eeprom_value_lo = EEPROM_VAL_C0ADC_EMON_L & 0x00FF;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_L_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C0ADC_EMON_L & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_L_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C0ADC_EMON_SEC & 0x00FF;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_SEC_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C0ADC_EMON_SEC & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_SEC_HI, eeprom_value_hi);

    // ADC 1
    EEPROM.write(EEPROM_ADD_C1ADC_TYPE, EEPROM_VAL_C1ADC_TYPE);
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

    eeprom_value_lo = EEPROM_VAL_C1ADC_IDC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_C1ADC_IDC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C1ADC_IDC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C1ADC_IDC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C1ADC_IDC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_C1ADC_IDC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C1ADC_IDC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C1ADC_IDC_B_HI, eeprom_value_hi);

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
  EEPROM.write(EEPROM_ADD_C0ADC_TYPE,  (byte)cfgEmonType[0]);

  eeprom_value_lo = cfgEmonR[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_R_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonR[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_R_HI, eeprom_value_hi);
  eeprom_value_lo = cfgEmonS[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_S_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonS[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_S_HI, eeprom_value_hi);
  eeprom_value_lo = cfgEmonO[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_O_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonO[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_O_HI, eeprom_value_hi);

  eeprom_value_lo = cfgEmonIDCm[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_IDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonIDCm[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_IDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgEmonIDCb[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_IDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonIDCb[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_IDC_B_HI, eeprom_value_hi);

  eeprom_value_lo = cfgEmonL[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_L_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonL[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_L_HI, eeprom_value_hi);
  eeprom_value_lo = cfgEmonSec[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_SEC_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonSec[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_SEC_HI, eeprom_value_hi);

  // ADC 1
  EEPROM.write(EEPROM_ADD_C1ADC_TYPE,  (byte)cfgEmonType[1]);

  eeprom_value_lo = cfgEmonR[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_R_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonR[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_R_HI, eeprom_value_hi);
  eeprom_value_lo = cfgEmonS[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_S_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonS[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_S_HI, eeprom_value_hi);
  eeprom_value_lo = cfgEmonO[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_O_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonO[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_O_HI, eeprom_value_hi);

  eeprom_value_lo = cfgEmonIDCm[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_IDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonIDCm[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_IDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgEmonIDCb[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_IDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonIDCb[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_IDC_B_HI, eeprom_value_hi);

  eeprom_value_lo = cfgEmonL[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_L_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonL[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_L_HI, eeprom_value_hi);
  eeprom_value_lo = cfgEmonSec[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_SEC_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgEmonSec[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_SEC_HI, eeprom_value_hi);

  // ADC 2
  eeprom_value_lo = cfgVADCm[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVADCm[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgVADCb[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVADCb[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_B_HI, eeprom_value_hi);

  // ADC 3
  eeprom_value_lo = cfgVADCm[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVADCm[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgVADCb[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVADCb[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_B_HI, eeprom_value_hi);
}


void _eeprom2ramCONFIG (void)
{
  int eeprom_value_hi, eeprom_value_lo;

  cfgMbId           = (int)EEPROM.read(EEPROM_ADD_MODBUS_ID);
  cfgLogicIns       = (int)EEPROM.read(EEPROM_ADD_LOGIC_INS);
  cfgLogicOuts      = (int)EEPROM.read(EEPROM_ADD_LOGIC_OUTS); 
  
  // ADC 0
  cfgEmonType[0]    = (int)EEPROM.read(EEPROM_ADD_C0ADC_TYPE);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_R_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_R_LO);
  cfgEmonR[0]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_S_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_S_LO);
  cfgEmonS[0]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_O_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_O_LO);
  cfgEmonO[0]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_IDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_IDC_M_LO);
  cfgEmonIDCm[0]    = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_IDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_IDC_B_LO);
  cfgEmonIDCb[0]    = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_L_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_L_LO);
  cfgEmonL[0]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_SEC_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_SEC_LO);
  cfgEmonSec[0]     = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 1
  cfgEmonType[1]    = (int)EEPROM.read(EEPROM_ADD_C1ADC_TYPE);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_R_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_R_LO);
  cfgEmonR[1]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_S_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_S_LO);
  cfgEmonS[1]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_O_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_O_LO);
  cfgEmonO[1]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_IDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_IDC_M_LO);
  cfgEmonIDCm[1]    = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_IDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_IDC_B_LO);
  cfgEmonIDCb[1]    = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_L_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_L_LO);
  cfgEmonL[1]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_SEC_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_SEC_LO);
  cfgEmonSec[1]     = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 2
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_M_LO);
  cfgVADCm[0]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_B_LO);
  cfgVADCb[0]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 3
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_M_LO);
  cfgVADCm[1]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_B_LO);
  cfgVADCb[1]       = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Modbus ID: ");  Serial.println (cfgMbId);
  Serial.print("Logic Ins: ");  Serial.println (cfgLogicIns);
  Serial.print("Logic Outs: "); Serial.println (cfgLogicOuts);

  Serial.print("C0 I Type");   Serial.print(": "); Serial.print (cfgEmonType[0]);  Serial.println(" ");

  Serial.print("C0 Irms Ratio");   Serial.print(": "); Serial.print (cfgEmonR[0]);  Serial.println(" ");
  Serial.print("C0 Irms Samples"); Serial.print(": "); Serial.print (cfgEmonS[0]);  Serial.println(" ");
  Serial.print("C0 Irms Samples"); Serial.print(": "); Serial.print (cfgEmonO[0]);  Serial.println(" mA");

  Serial.print("C0 Vdc recta m");  Serial.print(": "); Serial.print (cfgEmonVDCm[0]);  Serial.println(" ");
  Serial.print("C0 Vdc recta b");  Serial.print(": "); Serial.print (cfgEmonVDCb[0]);  Serial.println(" (/1000)");

  Serial.print("C0 Irms Limit");   Serial.print(": "); Serial.print (cfgEmonL[0]);  Serial.println(" ");
  Serial.print("C0 Irms Hys Sec"); Serial.print(": "); Serial.print (cfgEmonLSec[0]); Serial.println(" sec");

  Serial.print("C1 I Type");   Serial.print(": "); Serial.print (cfgEmonType[1]);  Serial.println(" ");

  Serial.print("C1 Irms Ratio");   Serial.print(": "); Serial.print (cfgEmonR[1]);  Serial.println(" ");
  Serial.print("C1 Irms Samples"); Serial.print(": "); Serial.print (cfgEmonS[1]);  Serial.println(" ");
  Serial.print("C1 Irms Samples"); Serial.print(": "); Serial.print (cfgEmonO[1]);  Serial.println(" mA");
  
  Serial.print("C1 Vdc recta m");  Serial.print(": "); Serial.print (cfgEmonVDCm[1]);  Serial.println(" ");
  Serial.print("C1 Vdc recta b");  Serial.print(": "); Serial.print (cfgEmonVDCb[1]);  Serial.println(" (/1000)");

  Serial.print("C1 Irms Limit");   Serial.print(": "); Serial.print (cfgEmonL[1]);  Serial.println(" ");
  Serial.print("C1 Irms Hys Sec"); Serial.print(": "); Serial.print (cfgEmonLSec[1]); Serial.println(" sec");

  Serial.print("V0 Vdc recta m");  Serial.print(": "); Serial.print (cfgVADCm[0]);  Serial.println(" ");
  Serial.print("V0 Vdc recta b");  Serial.print(": "); Serial.print (cfgvADCb[0]);  Serial.println(" (/1000)");
  
  Serial.print("V1 Vdc recta m");  Serial.print(": "); Serial.print (cfgVADCm[1]);  Serial.println(" ");
  Serial.print("V1 Vdc recta b");  Serial.print(": "); Serial.print (cfgvADCb[1]);  Serial.println(" (/1000)");
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
