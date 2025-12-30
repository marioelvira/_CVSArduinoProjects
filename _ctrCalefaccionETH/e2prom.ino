
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
  bool ok;
  int i, j;
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
    #endif

    // Logic
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  EEPROM_VAL_LOGIC_INS);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, EEPROM_VAL_LOGIC_OUTS);

    EEPROM.write(EEPROM_ADD_RES_PRIM_VOUT,      EEPROM_VAL_RES_PRIM_VOUT);
    EEPROM.write(EEPROM_ADD_RES_INYE_VOUT,      EEPROM_VAL_RES_INYE_VOUT);
    EEPROM.write(EEPROM_ADD_RES_PRIM_INYE_TEMP, EEPROM_VAL_RES_PRIM_INYE_TEMP);
    EEPROM.write(EEPROM_ADD_RES_PRIM_CONS_TEMP, EEPROM_VAL_RES_PRIM_CONS_TEMP);
    EEPROM.write(EEPROM_ADD_RES_PRIM_HYST_TEMP, EEPROM_VAL_RES_PRIM_HYST_TEMP);
    EEPROM.write(EEPROM_ADD_RES_INYE_CONS_TEMP, EEPROM_VAL_RES_INYE_CONS_TEMP);
    EEPROM.write(EEPROM_ADD_RES_PRIM_HYST_TEMP, EEPROM_VAL_RES_PRIM_HYST_TEMP);
    EEPROM.write(EEPROM_ADD_AGUA_CONS_TEMP,     EEPROM_VAL_AGUA_CONS_TEMP);
    EEPROM.write(EEPROM_ADD_AGUA_HYST_TEMP,     EEPROM_VAL_AGUA_HYST_TEMP);
    EEPROM.write(EEPROM_ADD_RES_PRIM_ALAR_MIN,  EEPROM_VAL_RES_PRIM_ALAR_MIN);
    EEPROM.write(EEPROM_ADD_RES_INYE_ALAR_MIN,  EEPROM_VAL_RES_INYE_ALAR_MIN);
    EEPROM.write(EEPROM_ADD_AGUA_ALAR_MIN,      EEPROM_VAL_AGUA_ALAR_MIN);
    
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

/*
void _ram2eepromCONFIG (void)
{
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

  // Data Data
  EEPROM.write(EEPROM_ADD_LOGIC_INS,  (byte)cfgLogicIns);
  EEPROM.write(EEPROM_ADD_LOGIC_OUTS, (byte)cfgLogicOuts);

  EEPROM.write(EEPROM_ADD_RES_PRIM1_VOUT,     (byte)cfgResPrim1Vout);
  EEPROM.write(EEPROM_ADD_RES_PRIM2_VOUT,     (byte)cfgResPrim2Vout);
  EEPROM.write(EEPROM_ADD_RES_INYE_VOUT,      (byte)cfgResInyeVout);
  EEPROM.write(EEPROM_ADD_RES_PRIM_INYE_TEMP, (byte)cfgResPrimInyeTemp);
  EEPROM.write(EEPROM_ADD_RES_PRIM_CONS_TEMP, (byte)cfgResPrimConsTemp);
  EEPROM.write(EEPROM_ADD_RES_PRIM_HYST_TEMP, (byte)cfgResPrimHystTemp);
  EEPROM.write(EEPROM_ADD_RES_INYE_CONS_TEMP, (byte)cfgResInyeConsTemp);
  EEPROM.write(EEPROM_ADD_RES_PRIM_HYST_TEMP, (byte)cfgResInyeHystTemp);
  EEPROM.write(EEPROM_ADD_AGUA_CONS_TEMP,     (byte)cfgAguaConsTemp);
  EEPROM.write(EEPROM_ADD_AGUA_HYST_TEMP,     (byte)cfgAguaHystTemp);
  EEPROM.write(EEPROM_ADD_RES_PRIM_ALAR_MIN,  (byte)cfgResPrimAlarMin);
  EEPROM.write(EEPROM_ADD_RES_INYE_ALAR_MIN,  (byte)cfgResInyeAlarMin);
  EEPROM.write(EEPROM_ADD_AGUA_ALAR_MIN,      (byte)cfgAguaAlarMin);
}
*/

void _eeprom2ramCONFIG (void)
{
  int i;
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

  #endif

  cfgLogicIns       = (int)EEPROM.read(EEPROM_ADD_LOGIC_INS);
  cfgLogicOuts      = (int)EEPROM.read(EEPROM_ADD_LOGIC_OUTS); 

  cfgResPrimVout      = (int)EEPROM.read(EEPROM_ADD_RES_PRIM_VOUT);
  cfgResInyeVout      = (int)EEPROM.read(EEPROM_ADD_RES_INYE_VOUT);
  cfgResPrimInyeTemp  = (int)EEPROM.read(EEPROM_ADD_RES_PRIM_INYE_TEMP);
  cfgResPrimConsTemp  = (int)EEPROM.read(EEPROM_ADD_RES_PRIM_CONS_TEMP);
  cfgResPrimHystTemp  = (int)EEPROM.read(EEPROM_ADD_RES_PRIM_HYST_TEMP);
  cfgResInyeConsTemp  = (int)EEPROM.read(EEPROM_ADD_RES_INYE_CONS_TEMP);
  cfgResInyeHystTemp  = (int)EEPROM.read(EEPROM_ADD_RES_PRIM_HYST_TEMP);
  cfgAguaConsTemp     = (int)EEPROM.read(EEPROM_ADD_AGUA_CONS_TEMP);
  cfgAguaHystTemp     = (int)EEPROM.read(EEPROM_ADD_AGUA_HYST_TEMP);
  cfgResPrimAlarMin   = (int)EEPROM.read(EEPROM_ADD_RES_PRIM_ALAR_MIN);
  cfgResInyeAlarMin   = (int)EEPROM.read(EEPROM_ADD_RES_INYE_ALAR_MIN);
  cfgAguaAlarMin      = (int)EEPROM.read(EEPROM_ADD_AGUA_ALAR_MIN);
 
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("cfgLogicIns: ");        Serial.println (cfgLogicIns);
  Serial.print("cfgLogicOuts: ");       Serial.println (cfgLogicOuts);
  Serial.print("cfgResPrim1Vout: ");    Serial.println (cfgResPrim1Vout);
  Serial.print("cfgResPrim2Vout: ");    Serial.println (cfgResPrim2Vout);
  Serial.print("cfgResInyeVout: ");     Serial.println (cfgResInyeVout);
  Serial.print("cfgResPrimInyeTemp: "); Serial.println (cfgResPrimInyeTemp);
  Serial.print("cfgResPrimConsTemp: "); Serial.println (cfgResPrimConsTemp);
  Serial.print("cfgResPrimHystTemp: "); Serial.println (cfgResPrimHystTemp);
  Serial.print("cfgResInyeConsTemp: "); Serial.println (cfgResInyeConsTemp);
  Serial.print("cfgResInyeHystTemp: "); Serial.println (cfgResInyeHystTemp);
  Serial.print("cfgAguaConsTemp: ");    Serial.println (cfgAguaConsTemp);
  Serial.print("cfgAguaHystTemp: ");    Serial.println (cfgAguaHystTemp);
  Serial.print("cfgResPrimAlarMin: ");  Serial.println (cfgResPrimAlarMin);
  Serial.print("cfgResInyeAlarMin: ");  Serial.println (cfgResInyeAlarMin);
  Serial.print("cfgAguaAlarMin: ");     Serial.println (cfgAguaAlarMin);

  delay(1000);  // 100ms

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
