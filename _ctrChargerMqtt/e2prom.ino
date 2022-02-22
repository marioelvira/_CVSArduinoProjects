
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
  int i, j;
  byte val[4];

  int eeprom_value_hi, eeprom_value_lo;
  
  EEPROM.begin(512);
    
  i = EEPROM.read(EEPROM_ADD_OK);
  
  // Si NO esta grabada la configuracion...
  if (i != EEPROM_VAL_OK)
  {
    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.println("Config NOK");
    #endif
  
    EEPROM.write(EEPROM_ADD_OK,      EEPROM_VAL_OK);

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

    // Wi-Fi
    EEPROM.write(EEPROM_ADD_WIFI_MODE, EEPROM_VAL_WIFI_MODE);
  
    for (i = 0; i < WIFI_SSID_MAX; i++)
      EEPROM.write(EEPROM_ADD_WIFI_SSID + i, 0);

    #if (_WRITE_SSID_EEPROM_ == 1)
    j = strlen(ssidSt);
    for (i = 0; i < j; i++)
      EEPROM.write(EEPROM_ADD_WIFI_SSID + i, ssidSt[i]);
    #endif

    for (i = 0; i < WIFI_PSWD_MAX; i++)
      EEPROM.write(EEPROM_ADD_WIFI_PSWD + i, 0);

    #if (_WRITE_SSID_EEPROM_ == 1)
    j = strlen(passwordSt);
    for (i = 0; i < j; i++)
      EEPROM.write(EEPROM_ADD_WIFI_PSWD + i, passwordSt[i]);
    #endif

    // Other Data
    EEPROM.write(EEPROM_ADD_BATT_TSECS,  EEPROM_VAL_BATT_TSECS);
    EEPROM.write(EEPROM_ADD_BATTA_VOLTS, EEPROM_VAL_BATTA_VOLTS);
    EEPROM.write(EEPROM_ADD_BATTA_MIN,   EEPROM_VAL_BATTA_MIN);
    EEPROM.write(EEPROM_ADD_BATTB_VOLTS, EEPROM_VAL_BATTB_VOLTS);
    EEPROM.write(EEPROM_ADD_BATTB_MIN,   EEPROM_VAL_BATTB_MIN);
    EEPROM.write(EEPROM_ADD_BATTC_VOLTS, EEPROM_VAL_BATTC_VOLTS);
    EEPROM.write(EEPROM_ADD_BATTC_MIN,   EEPROM_VAL_BATTC_MIN);

    EEPROM.write(EEPROM_ADD_LOGIC_INS,  EEPROM_VAL_LOGIC_INS);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, EEPROM_VAL_LOGIC_OUTS);

    eeprom_value_lo = EEPROM_VAL_ADC_M & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_M_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_M & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_M_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC_B & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_B_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_B & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_B_HI, eeprom_value_hi);
    eeprom_value_lo = EEPROM_VAL_ADC_P & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC_P_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_ADC_P & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC_P_HI, eeprom_value_hi);   
    EEPROM.write(EEPROM_ADD_ADC_S,      EEPROM_VAL_ADC_S);
    EEPROM.write(EEPROM_ADD_ADC_F,      EEPROM_VAL_ADC_F);
    
    //EEPROM.write(EEPROM_ADD_DEBUG,    EEPROM_VAL_DEBUG);
    
    EEPROM.commit();    //Store data to EEPROM
  }
  else
  {
    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.println("Config OK");
    #endif
  }

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
    val[0] = EEPROM.read(EEPROM_ADD_IP1);
    val[1] = EEPROM.read(EEPROM_ADD_IP2);
    val[2] = EEPROM.read(EEPROM_ADD_IP3);
    val[3] = EEPROM.read(EEPROM_ADD_IP4);
    ipAddress = IPAddress(val[0], val[1], val[2], val[3]);
    
    // Mask
    val[0] = EEPROM.read(EEPROM_ADD_MASK1);
    val[1] = EEPROM.read(EEPROM_ADD_MASK2);
    val[2] = EEPROM.read(EEPROM_ADD_MASK3);
    val[3] = EEPROM.read(EEPROM_ADD_MASK4);
    netMask = IPAddress(val[0], val[1], val[2], val[3]);

    // Gateway
    val[0] = EEPROM.read(EEPROM_ADD_GATE1);
    val[1] = EEPROM.read(EEPROM_ADD_GATE2);
    val[2] = EEPROM.read(EEPROM_ADD_GATE3);
    val[3] = EEPROM.read(EEPROM_ADD_GATE4);
    gateWay = IPAddress(val[0], val[1], val[2], val[3]);
  }

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("IP: ");
  Serial.print(ipAddress);
  Serial.print(" Mask: ");
  Serial.print(netMask);
  Serial.print(" Gateway: ");
  Serial.println(gateWay);
  #endif
  
  // Wi-Fi Mode
  wifiMode = EEPROM.read(EEPROM_ADD_WIFI_MODE);

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  if (wifiMode == STATION_MODE)
    Serial.println("Wi-Fi Mode: Station");
  else
    Serial.println("Wi-Fi Mode: Access point");
  #endif

  if (wifiMode == STATION_MODE)
  {
    for (i = 0; i < WIFI_SSID_MAX; i++)
      ssid[i] = char(EEPROM.read(EEPROM_ADD_WIFI_SSID + i));

    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.print("SSID: ");
    Serial.println(ssid);
    #endif

    for (i = 0; i < WIFI_SSID_MAX; i++)
      password[i] = char(EEPROM.read(EEPROM_ADD_WIFI_PSWD + i));

    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.print("PASSWORD: ");
    Serial.println(password);
    #endif
  }

  // Other Data
  cfgBattTds        = (int)EEPROM.read(EEPROM_ADD_BATT_TSECS);

  cfgBattAvolts     = (int)EEPROM.read(EEPROM_ADD_BATTA_VOLTS);
  cfgBattAmins      = (int)EEPROM.read(EEPROM_ADD_BATTA_MIN);
  cfgBattBvolts     = (int)EEPROM.read(EEPROM_ADD_BATTB_VOLTS);
  cfgBattBmins      = (int)EEPROM.read(EEPROM_ADD_BATTB_MIN);
  cfgBattCvolts     = (int)EEPROM.read(EEPROM_ADD_BATTC_VOLTS);
  cfgBattCmins      = (int)EEPROM.read(EEPROM_ADD_BATTC_MIN);

  cfgLogicIns       = (int)EEPROM.read(EEPROM_ADD_LOGIC_INS);
  cfgLogicOuts      = (int)EEPROM.read(EEPROM_ADD_LOGIC_OUTS);

  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_M_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_M_LO);   
  cfgADCm           = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_B_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_B_LO);   
  cfgADCb           = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
  eeprom_value_hi   = (int)EEPROM.read(EEPROM_ADD_ADC_P_HI);
  eeprom_value_lo   = (int)EEPROM.read(EEPROM_ADD_ADC_P_LO);   
  cfgADCp           = (int)((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF); 
  cfgADCs           = (int)EEPROM.read(EEPROM_ADD_ADC_S);
  cfgADCf           = (int)EEPROM.read(EEPROM_ADD_ADC_F);
  
  //DebugVal        = (int)EEPROM.read(EEPROM_ADD_DEBUG);
  
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Batt salto: ");     Serial.print (cfgBattTds);         Serial.println(" ds");
  Serial.print("Batt A charge: ");  Serial.print (cfgBattAvolts);      Serial.println(" Volts");
  Serial.print("Batt A charge: ");  Serial.print (cfgBattAmins);       Serial.println(" *15 min");
  Serial.print("Batt B charge: ");  Serial.print (cfgBattBvolts);      Serial.println(" Volts");
  Serial.print("Batt B charge: ");  Serial.print (cfgBattBmins);       Serial.println(" *15 min");
  Serial.print("Batt C charge: ");  Serial.print (cfgBattCvolts);      Serial.println(" Volts");
  Serial.print("Batt C charge: ");  Serial.print (cfgBattCmins);       Serial.println(" *15 min");

  Serial.print("Logic Ins: ");     Serial.println(cfgLogicIns);
  Serial.print("Logic Outs: ");    Serial.println(cfgLogicOuts);

  Serial.print("ADC m: ");         Serial.print (cfgADCm);            Serial.println(" ");
  Serial.print("ADC b: ");         Serial.print (cfgADCb);            Serial.println(" ");
  Serial.print("ADC p: ");         Serial.print (cfgADCp);            Serial.println(" ");
  Serial.print("ADC s: ");         Serial.print (cfgADCs);            Serial.println(" +/-  1/0");
  Serial.print("ADC f: ");         Serial.print (cfgADCf);            Serial.println(" si/no 1/0");
  
  //Serial.print("Debug: ");       Serial.print (DebugVal);           Serial.println(" ---");
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
  
  EEPROM.commit();    //Store data to EEPROM
}

void _ReadEEPROM() {

  int j = 0;

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.println("Reading E2PROM 512 size... ");
  #endif

  EEPROM.begin(512);
   
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
