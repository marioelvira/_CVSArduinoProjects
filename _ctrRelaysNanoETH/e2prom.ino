
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
  #if (_USE_MQTT_ == 1)
  int i, j;
  #endif
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

    #if (_USE_ETHERNET_ == 1)
    // IP Mode
    EEPROM.write(EEPROM_ADD_IP_MODE, EEPROM_VAL_IP_MODE);
    EEPROM.write(EEPROM_ADD_IP1,     EEPROM_VAL_IP1);
    EEPROM.write(EEPROM_ADD_IP2,     EEPROM_VAL_IP2);
    EEPROM.write(EEPROM_ADD_IP3,     EEPROM_VAL_IP3);
    EEPROM.write(EEPROM_ADD_IP4,     EEPROM_VAL_IP4);
    EEPROM.write(EEPROM_ADD_MASK1,   EEPROM_VAL_MASK1);
    EEPROM.write(EEPROM_ADD_MASK2,   EEPROM_VAL_MASK2);
    EEPROM.write(EEPROM_ADD_MASK3,   EEPROM_VAL_MASK3);
    EEPROM.write(EEPROM_ADD_MASK4,   EEPROM_VAL_MASK4);
    EEPROM.write(EEPROM_ADD_GATE1,   EEPROM_VAL_GATE1);
    EEPROM.write(EEPROM_ADD_GATE2,   EEPROM_VAL_GATE2);
    EEPROM.write(EEPROM_ADD_GATE3,   EEPROM_VAL_GATE3);
    EEPROM.write(EEPROM_ADD_GATE4,   EEPROM_VAL_GATE4);

    #endif // _USE_ETHERNET_

    #if (_USE_MQTT_ == 1)
    // Broker Url
    for (i = 0; i < MQTT_URL_MAX; i++)
      EEPROM.write(EEPROM_ADD_BROKER + i, 0);
    j = strlen(brokerUrlSt);
    for (i = 0; i < j; i++)
      EEPROM.write(EEPROM_ADD_BROKER + i, brokerUrlSt[i]);
    // Broker port
    eeprom_value_lo = MQTT_BROKER_PORT & 0x00FF;
    EEPROM.write(EEPROM_ADD_BROKER_PORT, eeprom_value_lo);
    eeprom_value_hi = (MQTT_BROKER_PORT & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_BROKER_PORT + 1, eeprom_value_hi);
    // Broker User
    for (i = 0; i < MQTT_USER_MAX; i++)
      EEPROM.write(EEPROM_ADD_MQTT_USER + i, 0);
    j = strlen(brokerUserSt);
    for (i = 0; i < j; i++)
      EEPROM.write(EEPROM_ADD_MQTT_USER + i, brokerUserSt[i]);
    // Broker Pswd
    for (i = 0; i < MQTT_PSWD_MAX; i++)
      EEPROM.write(EEPROM_ADD_MQTT_PSWD + i, 0);
    j = strlen(brokerPswdSt);
    for (i = 0; i < j; i++)
      EEPROM.write(EEPROM_ADD_MQTT_PSWD + i, brokerPswdSt[i]);
    #endif // _USE_MQTT_

    // Logic
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  EEPROM_VAL_LOGIC_INS);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, EEPROM_VAL_LOGIC_OUTS);

    // ADC 0
    EEPROM.write(EEPROM_ADD_C0ADC_TYPE, EEPROM_VAL_C0ADC_TYPE);
    
    eeprom_value_lo = EEPROM_VAL_C0ADC_EMON_R & 0x00FF;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_R_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C0ADC_EMON_R & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C0ADC_EMON_R_HI, eeprom_value_hi);
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
    EEPROM.write(EEPROM_ADD_C2ADC_TYPE, EEPROM_VAL_C2ADC_TYPE);

    eeprom_value_lo = EEPROM_VAL_C2ADC_EMON_R & 0x00FF;
    EEPROM.write(EEPROM_ADD_C2ADC_EMON_R_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C2ADC_EMON_R & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C2ADC_EMON_R_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C2ADC_IDC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_C2ADC_IDC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C2ADC_IDC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C2ADC_IDC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C2ADC_IDC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_C2ADC_IDC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C2ADC_IDC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C2ADC_IDC_B_HI, eeprom_value_hi);

    eeprom_value_lo = EEPROM_VAL_C2ADC_EMON_L & 0x00FF;
    EEPROM.write(EEPROM_ADD_C2ADC_EMON_L_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C2ADC_EMON_L & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C2ADC_EMON_L_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C2ADC_EMON_SEC & 0x00FF;
    EEPROM.write(EEPROM_ADD_C2ADC_EMON_SEC_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C2ADC_EMON_SEC & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C2ADC_EMON_SEC_HI, eeprom_value_hi);

    // ADC 3
    EEPROM.write(EEPROM_ADD_C3ADC_TYPE, EEPROM_VAL_C3ADC_TYPE);

    eeprom_value_lo = EEPROM_VAL_C3ADC_EMON_R & 0x00FF;
    EEPROM.write(EEPROM_ADD_C3ADC_EMON_R_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C3ADC_EMON_R & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C3ADC_EMON_R_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C3ADC_IDC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_C3ADC_IDC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C3ADC_IDC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C3ADC_IDC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C3ADC_IDC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_C3ADC_IDC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C3ADC_IDC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C3ADC_IDC_B_HI, eeprom_value_hi);

    eeprom_value_lo = EEPROM_VAL_C3ADC_EMON_L & 0x00FF;
    EEPROM.write(EEPROM_ADD_C3ADC_EMON_L_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C3ADC_EMON_L & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C3ADC_EMON_L_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_C3ADC_EMON_SEC & 0x00FF;
    EEPROM.write(EEPROM_ADD_C3ADC_EMON_SEC_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_C3ADC_EMON_SEC & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_C3ADC_EMON_SEC_HI, eeprom_value_hi);

    // ADC 4
    eeprom_value_lo = EEPROM_VAL_V0ADC_VDC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_V0ADC_VDC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V0ADC_VDC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V0ADC_VDC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_V0ADC_VDC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_V0ADC_VDC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V0ADC_VDC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V0ADC_VDC_B_HI, eeprom_value_hi);

    // ADC 5
    eeprom_value_lo = EEPROM_VAL_V1ADC_VDC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_V1ADC_VDC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V1ADC_VDC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V1ADC_VDC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_V1ADC_VDC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_V1ADC_VDC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V1ADC_VDC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V1ADC_VDC_B_HI, eeprom_value_hi);

    // ADC 6
    eeprom_value_lo = EEPROM_VAL_V2ADC_VDC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_V2ADC_VDC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V2ADC_VDC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V2ADC_VDC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_V2ADC_VDC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_V2ADC_VDC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V2ADC_VDC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V2ADC_VDC_B_HI, eeprom_value_hi);

    // ADC 7
    eeprom_value_lo = EEPROM_VAL_V3ADC_VDC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_V3ADC_VDC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V3ADC_VDC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V3ADC_VDC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_V3ADC_VDC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_V3ADC_VDC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_V3ADC_VDC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_V3ADC_VDC_B_HI, eeprom_value_hi);

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
  #if (_USE_MQTT_ == 1)
  int i, j;
  #endif
  int eeprom_value_hi, eeprom_value_lo;

  #if (_USE_ETHERNET_ == 1)
  // IP Mode
  EEPROM.write(EEPROM_ADD_IP_MODE, (byte)ipMode);
  EEPROM.write(EEPROM_ADD_IP1,     (byte)ipAddress[0]);
  EEPROM.write(EEPROM_ADD_IP2,     (byte)ipAddress[1]);
  EEPROM.write(EEPROM_ADD_IP3,     (byte)ipAddress[2]);
  EEPROM.write(EEPROM_ADD_IP4,     (byte)ipAddress[3]);
  EEPROM.write(EEPROM_ADD_MASK1,   (byte)netMask[0]);
  EEPROM.write(EEPROM_ADD_MASK2,   (byte)netMask[1]);
  EEPROM.write(EEPROM_ADD_MASK3,   (byte)netMask[2]);
  EEPROM.write(EEPROM_ADD_MASK4,   (byte)netMask[3]);
  EEPROM.write(EEPROM_ADD_GATE1,   (byte)gateWay[0]);
  EEPROM.write(EEPROM_ADD_GATE2,   (byte)gateWay[1]);
  EEPROM.write(EEPROM_ADD_GATE3,   (byte)gateWay[2]);
  EEPROM.write(EEPROM_ADD_GATE4,   (byte)gateWay[3]);
  #endif

  #if (_USE_MQTT_ == 1)
  // Broker Url
   for (i = 0; i < MQTT_URL_MAX; i++)
    EEPROM.write(EEPROM_ADD_BROKER + i, 0);
  j = strlen(brokerUrl);
  for (i = 0; i < j; i++)
    EEPROM.write(EEPROM_ADD_BROKER + i, brokerUrl[i]);
  // Broker port
  eeprom_value_lo = brokerPort & 0x00FF;
  EEPROM.write(EEPROM_ADD_BROKER_PORT, eeprom_value_lo);
  eeprom_value_hi = (brokerPort & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_BROKER_PORT + 1, eeprom_value_hi);
  // Broker User
  for (i = 0; i < MQTT_USER_MAX; i++)
    EEPROM.write(EEPROM_ADD_MQTT_USER + i, 0);
  j = strlen(brokerUser);
  for (i = 0; i < j; i++)
    EEPROM.write(EEPROM_ADD_MQTT_USER + i, brokerUser[i]);
  // Broker Pswd
  for (i = 0; i < MQTT_PSWD_MAX; i++)
    EEPROM.write(EEPROM_ADD_MQTT_PSWD + i, 0);
  j = strlen(brokerPswd);
  for (i = 0; i < j; i++)
    EEPROM.write(EEPROM_ADD_MQTT_PSWD + i, brokerPswd[i]);
  #endif

  // Data Data
  EEPROM.write(EEPROM_ADD_LOGIC_INS,  (byte)cfgLogicIns);
  EEPROM.write(EEPROM_ADD_LOGIC_OUTS, (byte)cfgLogicOuts);

   // ADC 0
  EEPROM.write(EEPROM_ADD_C0ADC_TYPE,  (byte)cfgIType[0]);

  eeprom_value_lo = cfgIACr[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_R_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIACr[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_R_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIDCm[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_IDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIDCm[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_IDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIDCb[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_IDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIDCb[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_IDC_B_HI, eeprom_value_hi);

  eeprom_value_lo = cfgIlim[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_L_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIlim[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_L_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIsec[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_SEC_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIsec[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C0ADC_EMON_SEC_HI, eeprom_value_hi);

  // ADC 1
  EEPROM.write(EEPROM_ADD_C1ADC_TYPE,  (byte)cfgIType[1]);

  eeprom_value_lo = cfgIACr[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_R_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIACr[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_R_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIDCm[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_IDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIDCm[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_IDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIDCb[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_IDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIDCb[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_IDC_B_HI, eeprom_value_hi);

  eeprom_value_lo = cfgIlim[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_L_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIlim[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_L_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIsec[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_SEC_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIsec[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C1ADC_EMON_SEC_HI, eeprom_value_hi);

  // ADC 2
  EEPROM.write(EEPROM_ADD_C2ADC_TYPE,  (byte)cfgIType[2]);

  eeprom_value_lo = cfgIACr[2] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C2ADC_EMON_R_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIACr[2] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C2ADC_EMON_R_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIDCm[2] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C2ADC_IDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIDCm[2] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C2ADC_IDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIDCb[2] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C2ADC_IDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIDCb[2] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C2ADC_IDC_B_HI, eeprom_value_hi);

  eeprom_value_lo = cfgIlim[2] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C2ADC_EMON_L_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIlim[2] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C2ADC_EMON_L_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIsec[2] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C2ADC_EMON_SEC_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIsec[2] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C2ADC_EMON_SEC_HI, eeprom_value_hi);

  // ADC 3
  EEPROM.write(EEPROM_ADD_C3ADC_TYPE,  (byte)cfgIType[3]);

  eeprom_value_lo = cfgIACr[3] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C3ADC_EMON_R_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIACr[3] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C3ADC_EMON_R_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIDCm[3] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C3ADC_IDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIDCm[3] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C3ADC_IDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIDCb[3] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C3ADC_IDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIDCb[3] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C3ADC_IDC_B_HI, eeprom_value_hi);

  eeprom_value_lo = cfgIlim[3] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C3ADC_EMON_L_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIlim[3] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C3ADC_EMON_L_HI, eeprom_value_hi);
  eeprom_value_lo = cfgIsec[3] & 0x00FF;
  EEPROM.write(EEPROM_ADD_C3ADC_EMON_SEC_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgIsec[3] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_C3ADC_EMON_SEC_HI, eeprom_value_hi);

  // ADC 4
  eeprom_value_lo = cfgVDCm[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVDCm[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgVDCb[0] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVDCb[0] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V0ADC_VDC_B_HI, eeprom_value_hi);

  // ADC 5
  eeprom_value_lo = cfgVDCm[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVDCm[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgVDCb[1] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVDCb[1] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V1ADC_VDC_B_HI, eeprom_value_hi);

  // ADC 6
  eeprom_value_lo = cfgVDCm[2] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V2ADC_VDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVDCm[2] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V2ADC_VDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgVDCb[2] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V2ADC_VDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVDCb[2] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V2ADC_VDC_B_HI, eeprom_value_hi);

  // ADC 7
  eeprom_value_lo = cfgVDCm[3] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V3ADC_VDC_M_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVDCm[3] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V3ADC_VDC_M_HI, eeprom_value_hi);
  eeprom_value_lo = cfgVDCb[3] & 0x00FF;
  EEPROM.write(EEPROM_ADD_V3ADC_VDC_B_LO, eeprom_value_lo);
  eeprom_value_hi = (cfgVDCb[3] & 0xFF00)>>8;
  EEPROM.write(EEPROM_ADD_V3ADC_VDC_B_HI, eeprom_value_hi);
}

void _eeprom2ramCONFIG (void)
{
  #if (_USE_MQTT_ == 1)
  int i, j;
  #endif
  int eeprom_value_hi, eeprom_value_lo;

  #if (_USE_ETHERNET_ == 1)
  // IP Mode
  ipMode = EEPROM.read(EEPROM_ADD_IP_MODE);
  
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  if (ipMode == FIXIP_MODE)
    Serial.println("IP Mode: FIX IP");
  else
    Serial.println("IP Mode: DHCP");
  #endif
  
  if (ipMode == FIXIP_MODE)
  {
    // Ip Address
    ipAddress[0] = EEPROM.read(EEPROM_ADD_IP1);
    ipAddress[1] = EEPROM.read(EEPROM_ADD_IP2);
    ipAddress[2] = EEPROM.read(EEPROM_ADD_IP3);
    ipAddress[3] = EEPROM.read(EEPROM_ADD_IP4);
    
    // Mask
    netMask[0] = EEPROM.read(EEPROM_ADD_MASK1);
    netMask[1] = EEPROM.read(EEPROM_ADD_MASK2);
    netMask[2] = EEPROM.read(EEPROM_ADD_MASK3);
    netMask[3] = EEPROM.read(EEPROM_ADD_MASK4);

    // Gateway
    gateWay[0] = EEPROM.read(EEPROM_ADD_GATE1);
    gateWay[1] = EEPROM.read(EEPROM_ADD_GATE2);
    gateWay[2] = EEPROM.read(EEPROM_ADD_GATE3);
    gateWay[3] = EEPROM.read(EEPROM_ADD_GATE4);
  }

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("IP: ");
  Serial.print(ipAddress[0]); Serial.print(".");Serial.print(ipAddress[1]); Serial.print(".");Serial.print(ipAddress[2]); Serial.print(".");Serial.print(ipAddress[3]);
  Serial.print(" Mask: ");
  Serial.print(netMask[0]); Serial.print(".");Serial.print(netMask[1]); Serial.print(".");Serial.print(netMask[2]); Serial.print(".");Serial.print(netMask[3]);
  Serial.print(" Gateway: ");
  Serial.print(gateWay[0]); Serial.print(".");Serial.print(gateWay[1]); Serial.print(".");Serial.print(gateWay[2]); Serial.print(".");Serial.print(gateWay[3]);
  Serial.println();
  #endif

  #endif // _USE_ETHERNET_

  #if (_USE_MQTT_ == 1)
  // Broker Url
  for (i = 0; i < MQTT_URL_MAX; i++)
    brokerUrl[i] = char(EEPROM.read(EEPROM_ADD_BROKER + i));
  // Broker Port
  eeprom_value_hi = EEPROM.read(EEPROM_ADD_BROKER_PORT + 1);
  eeprom_value_lo = EEPROM.read(EEPROM_ADD_BROKER_PORT);   
  brokerPort = ((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  // Broker User
  for (i = 0; i < MQTT_USER_MAX; i++)
    brokerUser[i] = char(EEPROM.read(EEPROM_ADD_MQTT_USER + i));
  // Broker Pswd
  for (i = 0; i < MQTT_PSWD_MAX; i++)
    brokerPswd[i] = char(EEPROM.read(EEPROM_ADD_MQTT_PSWD + i));  

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Broker URL: ");
  Serial.println(brokerUrl);
  Serial.print("Broker Port: ");
  Serial.println(brokerPort);
  Serial.print("Broker User: ");
  Serial.println(brokerUser);
  Serial.print("Broker Password: ");
  Serial.println(brokerPswd);  
  #endif 

  #endif // _USE_MQTT_

  cfgLogicIns       = (int)EEPROM.read(EEPROM_ADD_LOGIC_INS);
  cfgLogicOuts      = (int)EEPROM.read(EEPROM_ADD_LOGIC_OUTS); 

  // ADC 0
  cfgIType[0]       = (int)EEPROM.read(EEPROM_ADD_C0ADC_TYPE);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_R_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_R_LO);
  cfgIACr[0]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_IDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_IDC_M_LO);
  cfgIDCm[0]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_IDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_IDC_B_LO);
  cfgIDCb[0]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_L_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_L_LO);
  cfgIlim[0]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_SEC_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C0ADC_EMON_SEC_LO);
  cfgIsec[0]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 1
  cfgIType[1]       = (int)EEPROM.read(EEPROM_ADD_C1ADC_TYPE);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_R_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_R_LO);
  cfgIACr[1]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_IDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_IDC_M_LO);
  cfgIDCm[1]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_IDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_IDC_B_LO);
  cfgIDCb[1]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_L_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_L_LO);
  cfgIlim[1]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_SEC_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C1ADC_EMON_SEC_LO);
  cfgIsec[1]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 2
  cfgIType[2]       = (int)EEPROM.read(EEPROM_ADD_C2ADC_TYPE);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C2ADC_EMON_R_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C2ADC_EMON_R_LO);
  cfgIACr[2]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C2ADC_IDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C2ADC_IDC_M_LO);
  cfgIDCm[2]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C2ADC_IDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C2ADC_IDC_B_LO);
  cfgIDCb[2]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C2ADC_EMON_L_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C2ADC_EMON_L_LO);
  cfgIlim[2]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C2ADC_EMON_SEC_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C2ADC_EMON_SEC_LO);
  cfgIsec[2]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 3
  cfgIType[3]       = (int)EEPROM.read(EEPROM_ADD_C3ADC_TYPE);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C3ADC_EMON_R_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C3ADC_EMON_R_LO);
  cfgIACr[3]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C3ADC_IDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C3ADC_IDC_M_LO);
  cfgIDCm[3]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C3ADC_IDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C3ADC_IDC_B_LO);
  cfgIDCb[3]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C3ADC_EMON_L_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C3ADC_EMON_L_LO);
  cfgIlim[3]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_C3ADC_EMON_SEC_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_C3ADC_EMON_SEC_LO);
  cfgIsec[3]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 4
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_M_LO);
  cfgVDCm[0]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V0ADC_VDC_B_LO);
  cfgVDCb[0]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 5
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_M_LO);
  cfgVDCm[1]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V1ADC_VDC_B_LO);
  cfgVDCb[1]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 6
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V2ADC_VDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V2ADC_VDC_M_LO);
  cfgVDCm[2]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V2ADC_VDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V2ADC_VDC_B_LO);
  cfgVDCb[2]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  // ADC 7
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V3ADC_VDC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V3ADC_VDC_M_LO);
  cfgVDCm[3]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_V3ADC_VDC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_V3ADC_VDC_B_LO);
  cfgVDCb[3]        = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Logic Ins: ");  Serial.println (cfgLogicIns);
  Serial.print("Logic Outs: "); Serial.println (cfgLogicOuts);

  // I
  Serial.print("C0 I Type");       Serial.print(": "); Serial.print (cfgIType[0]);  Serial.println(" ");
  Serial.print("C0 Irms Ratio");   Serial.print(": "); Serial.print (cfgIACr[0]);  Serial.println(" ");
  Serial.print("C0 Idc recta m");  Serial.print(": "); Serial.print (cfgIDCm[0]);  Serial.println(" ");
  Serial.print("C0 Idc recta b");  Serial.print(": "); Serial.print (cfgIDCb[0]);  Serial.println(" (/1000)");
  Serial.print("C0 I Limit");      Serial.print(": "); Serial.print (cfgIlim[0]);  Serial.println(" ");
  Serial.print("C0 I Hys Sec");    Serial.print(": "); Serial.print (cfgIsec[0]); Serial.println(" sec");

  Serial.print("C1 I Type");       Serial.print(": "); Serial.print (cfgIType[1]);  Serial.println(" ");
  Serial.print("C1 Irms Ratio");   Serial.print(": "); Serial.print (cfgIACr[1]);  Serial.println(" ");
  Serial.print("C1 Idc recta m");  Serial.print(": "); Serial.print (cfgIDCm[1]);  Serial.println(" ");
  Serial.print("C1 Idc recta b");  Serial.print(": "); Serial.print (cfgIDCb[1]);  Serial.println(" (/1000)");
  Serial.print("C1 I Limit");      Serial.print(": "); Serial.print (cfgIlim[1]);  Serial.println(" ");
  Serial.print("C1 I Hys Sec");    Serial.print(": "); Serial.print (cfgIsec[1]); Serial.println(" sec");

  Serial.print("C2 I Type");       Serial.print(": "); Serial.print (cfgIType[2]);  Serial.println(" ");
  Serial.print("C2 Irms Ratio");   Serial.print(": "); Serial.print (cfgIACr[2]);  Serial.println(" ");
  Serial.print("C2 Idc recta m");  Serial.print(": "); Serial.print (cfgIDCm[2]);  Serial.println(" ");
  Serial.print("C2 Idc recta b");  Serial.print(": "); Serial.print (cfgIDCb[2]);  Serial.println(" (/1000)");
  Serial.print("C2 I Limit");      Serial.print(": "); Serial.print (cfgIlim[2]);  Serial.println(" ");
  Serial.print("C2 I Hys Sec");    Serial.print(": "); Serial.print (cfgIsec[2]); Serial.println(" sec");

  Serial.print("C3 I Type");       Serial.print(": "); Serial.print (cfgIType[3]);  Serial.println(" ");
  Serial.print("C3 Irms Ratio");   Serial.print(": "); Serial.print (cfgIACr[3]);  Serial.println(" ");
  Serial.print("C3 Idc recta m");  Serial.print(": "); Serial.print (cfgIDCm[3]);  Serial.println(" ");
  Serial.print("C3 Idc recta b");  Serial.print(": "); Serial.print (cfgIDCb[3]);  Serial.println(" (/1000)");
  Serial.print("C3 I Limit");      Serial.print(": "); Serial.print (cfgIlim[3]);  Serial.println(" ");
  Serial.print("C3 I Hys Sec");    Serial.print(": "); Serial.print (cfgIsec[3]); Serial.println(" sec");

  // V
  Serial.print("V0 Vdc recta m");  Serial.print(": "); Serial.print (cfgVDCm[0]);  Serial.println(" ");
  Serial.print("V0 Vdc recta b");  Serial.print(": "); Serial.print (cfgVDCb[0]);  Serial.println(" (/1000)");
  
  Serial.print("V1 Vdc recta m");  Serial.print(": "); Serial.print (cfgVDCm[1]);  Serial.println(" ");
  Serial.print("V1 Vdc recta b");  Serial.print(": "); Serial.print (cfgVDCb[1]);  Serial.println(" (/1000)");

  Serial.print("V2 Vdc recta m");  Serial.print(": "); Serial.print (cfgVDCm[2]);  Serial.println(" ");
  Serial.print("V2 Vdc recta b");  Serial.print(": "); Serial.print (cfgVDCb[2]);  Serial.println(" (/1000)");
  
  Serial.print("V3 Vdc recta m");  Serial.print(": "); Serial.print (cfgVDCm[3]);  Serial.println(" ");
  Serial.print("V3 Vdc recta b");  Serial.print(": "); Serial.print (cfgVDCb[3]);  Serial.println(" (/1000)");
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
