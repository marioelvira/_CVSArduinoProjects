
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

    // Broker
    for (i = 0; i < BROKER_MAX; i++)
      EEPROM.write(EEPROM_ADD_BROKER + i, 0);
    j = strlen(brokerSt);
    for (i = 0; i < j; i++)
      EEPROM.write(EEPROM_ADD_BROKER + i, brokerSt[i]);

    eeprom_value_lo = EEPROM_VAL_BROKER_PORT & 0x00FF;
    EEPROM.write(EEPROM_ADD_BROKER_PORT, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VAL_BROKER_PORT & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_BROKER_PORT + 1, eeprom_value_hi);

    // Other Data
    EEPROM.write(EEPROM_ADD_RPUSL_MSEC, EEPROM_VAL_RPUSL_MSEC);
    EEPROM.write(EEPROM_ADD_LUZOFF_15M, EEPROM_VAL_LUZOFF_15M);  
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  EEPROM_VAL_LOGIC_INS);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, EEPROM_VAL_LOGIC_OUTS);
    EEPROM.write(EEPROM_ADD_GENON_PIN,  EEPROM_VAL_GENON_PIN);
    EEPROM.write(EEPROM_ADD_ADC_M,      EEPROM_VAL_ADC_M);
    EEPROM.write(EEPROM_ADD_ADC_B,      EEPROM_VAL_ADC_B);
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

  // Broker
  for (i = 0; i < BROKER_MAX; i++)
    brokerUrl[i] = char(EEPROM.read(EEPROM_ADD_BROKER + i));
  
  eeprom_value_hi = EEPROM.read(EEPROM_ADD_BROKER_PORT + 1);
  eeprom_value_lo = EEPROM.read(EEPROM_ADD_BROKER_PORT);   
  brokerPort = ((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
 
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Broker URL: ");
  Serial.println(brokerUrl);
  Serial.print("Broker Port: ");
  Serial.println(brokerPort);
  #endif 

  // Other Data
  cfgRemotePulsTick = (int)EEPROM.read(EEPROM_ADD_RPUSL_MSEC);
  cfgLuzOutTick     = (int)EEPROM.read(EEPROM_ADD_LUZOFF_15M);
  cfgLogicIns       = (int)EEPROM.read(EEPROM_ADD_LOGIC_INS);
  cfgLogicOuts      = (int)EEPROM.read(EEPROM_ADD_LOGIC_OUTS);
  cfgGenOnPin       = (int)EEPROM.read(EEPROM_ADD_GENON_PIN);
  cfgADCm           = (int)EEPROM.read(EEPROM_ADD_ADC_M);
  cfgADCb           = (int)EEPROM.read(EEPROM_ADD_ADC_B);
  //DebugVal        = (int)EEPROM.read(EEPROM_ADD_DEBUG);
  
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Remote Pulse: ");  Serial.print (cfgRemotePulsTick);  Serial.println(" *100 ms");
  Serial.print("Luz Off: ");       Serial.print (cfgLuzOutTick);      Serial.println(" *15 min");
  Serial.print("Logic Ins: ");     Serial.println(cfgLogicIns);
  Serial.print("Logic Outs: ");    Serial.println(cfgLogicOuts);
  Serial.print("Gen On Pin: ");    Serial.println(cfgGenOnPin);
  Serial.print("ADC m: ");         Serial.print (cfgADCm);            Serial.println(" /10");
  Serial.print("ADC b: ");         Serial.print (cfgADCb);            Serial.println(" /100");
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
