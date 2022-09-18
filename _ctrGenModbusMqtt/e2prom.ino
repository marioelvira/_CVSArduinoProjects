
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

    // Other Data
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  EEPROM_VAL_LOGIC_INS);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, EEPROM_VAL_LOGIC_OUTS);
    EEPROM.write(EEPROM_ADD_MBADD1,     EEPROM_VAL_MBADD1);
    EEPROM.write(EEPROM_ADD_MBADD2,     EEPROM_VAL_MBADD2);
    
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
    EEPROM.write(EEPROM_ADD_ADC_S, EEPROM_VAL_ADC_S);
    EEPROM.write(EEPROM_ADD_ADC_F, EEPROM_VAL_ADC_F);

    // Control
    EEPROM.write(EEPROM_ADD_1P_TIMER_GEN,   EEPROM_VAL_1P_TIMER_GEN);
    EEPROM.write(EEPROM_ADD_2P_TIMER_GEN,   EEPROM_VAL_2P_TIMER_GEN);
    EEPROM.write(EEPROM_ADD_3P_TIMER_GEN,   EEPROM_VAL_3P_TIMER_GEN);
    EEPROM.write(EEPROM_ADD_4P_TIMER_GEN,   EEPROM_VAL_4P_TIMER_GEN);
    EEPROM.write(EEPROM_ADD_5P_TIMER_GEN,   EEPROM_VAL_5P_TIMER_GEN);
    EEPROM.write(EEPROM_ADD_6P_TIMER_GEN,   EEPROM_VAL_6P_TIMER_GEN);
    EEPROM.write(EEPROM_ADD_7P_TIMER_GEN,   EEPROM_VAL_7P_TIMER_GEN);
    EEPROM.write(EEPROM_ADD_8P_TIMER_GEN,   EEPROM_VAL_8P_TIMER_GEN);
    EEPROM.write(EEPROM_ADD_9P_TIMER_GEN,   EEPROM_VAL_9P_TIMER_GEN);

    EEPROM.write(EEPROM_ADD_BUZZER_ON, EEPROM_VAL_BUZZER_ON);
    EEPROM.write(EEPROM_ADD_TSTART,    EEPROM_VAL_TSTART);
    EEPROM.write(EEPROM_ADD_TSTOP,     EEPROM_VAL_TSTOP);
    
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

  // Other Data
  cfgLogicIns       = (int)EEPROM.read(EEPROM_ADD_LOGIC_INS);
  cfgLogicOuts      = (int)EEPROM.read(EEPROM_ADD_LOGIC_OUTS);
  
  cfgMB1Add         = (int)EEPROM.read(EEPROM_ADD_MBADD1);
  cfgMB2Add         = (int)EEPROM.read(EEPROM_ADD_MBADD2);

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

  cfgTimeGenerador1P = (int)EEPROM.read(EEPROM_ADD_1P_TIMER_GEN); //*60; // Min
  cfgTimeGenerador2P = (int)EEPROM.read(EEPROM_ADD_2P_TIMER_GEN); //*60; // Min
  cfgTimeGenerador3P = (int)EEPROM.read(EEPROM_ADD_3P_TIMER_GEN); //*60; // Min
  cfgTimeGenerador4P = (int)EEPROM.read(EEPROM_ADD_4P_TIMER_GEN); //*60; // Min
  cfgTimeGenerador5P = (int)EEPROM.read(EEPROM_ADD_5P_TIMER_GEN); //*60; // Min
  cfgTimeGenerador6P = (int)EEPROM.read(EEPROM_ADD_6P_TIMER_GEN); //*3600; // Hour
  cfgTimeGenerador7P = (int)EEPROM.read(EEPROM_ADD_7P_TIMER_GEN); //*3600; // Hour
  cfgTimeGenerador8P = (int)EEPROM.read(EEPROM_ADD_8P_TIMER_GEN); //*3600; // Hour
  cfgTimeGenerador9P = (int)EEPROM.read(EEPROM_ADD_9P_TIMER_GEN); //*3600; // Hour

  cfgTimeBuzzerOn = (int)EEPROM.read(EEPROM_ADD_BUZZER_ON);    // Secs
  cfgTimeOutStart = (int)EEPROM.read(EEPROM_ADD_TSTART);       // Secs
  cfgTimeOutStop  = (int)EEPROM.read(EEPROM_ADD_TSTOP);        // Secs
  
  //DebugVal        = (int)EEPROM.read(EEPROM_ADD_DEBUG);
  
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("Logic Ins: ");     Serial.println(cfgLogicIns);
  Serial.print("Logic Outs: ");    Serial.println(cfgLogicOuts);
  Serial.print("Modbus Add1: ");   Serial.println(cfgMB1Add);
  Serial.print("Modbus Add2: ");   Serial.println(cfgMB2Add);

  Serial.print("ADC m: ");         Serial.print (cfgADCm);            Serial.println(" ");
  Serial.print("ADC b: ");         Serial.print (cfgADCb);            Serial.println(" (/1000)");
  Serial.print("ADC p: ");         Serial.print (cfgADCp);            Serial.println(" ");
  Serial.print("ADC s: ");         Serial.print (cfgADCs);            Serial.println(" +/-  1/0");
  Serial.print("ADC f: ");         Serial.print (cfgADCf);            Serial.println(" si/no 1/0");

  // Control
  Serial.print("Time 1P: ");  Serial.print (cfgTimeGenerador1P);  Serial.println(" min");
  Serial.print("Time 2P: ");  Serial.print (cfgTimeGenerador2P);  Serial.println(" min");
  Serial.print("Time 3P: ");  Serial.print (cfgTimeGenerador3P);  Serial.println(" min");
  Serial.print("Time 4P: ");  Serial.print (cfgTimeGenerador4P);  Serial.println(" min");
  Serial.print("Time 5P: ");  Serial.print (cfgTimeGenerador5P);  Serial.println(" min");
  Serial.print("Time 6P: ");  Serial.print (cfgTimeGenerador6P);  Serial.println(" hour");
  Serial.print("Time 7P: ");  Serial.print (cfgTimeGenerador7P);  Serial.println(" hour");
  Serial.print("Time 8P: ");  Serial.print (cfgTimeGenerador8P);  Serial.println(" hour");
  Serial.print("Time 9P: ");  Serial.print (cfgTimeGenerador9P);  Serial.println(" hour");

  Serial.print("Time Buzzer: "); Serial.print (cfgTimeBuzzerOn);  Serial.println(" secs");
  Serial.print("Time Start: ");  Serial.print (cfgTimeOutStart);  Serial.println(" secs");
  Serial.print("Time Stop: ");   Serial.print (cfgTimeOutStop);   Serial.println(" secs");
  
  //Serial.print("Debug: ");       Serial.print (DebugVal);       Serial.println(" ---");
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
