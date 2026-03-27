#include "main.h"
#include "e2prom.h"

// Libraries
#include <EEPROM.h>

#if (_USE_ETHERNET_ == 1)
#include "mEthernet.h"
#endif

///////////////
// Variables //
///////////////
bool cfgLogicIns;
bool cfgLogicOuts;
byte cfgMB1Add;

// Temperaturas de Control
int cfgResPrimInyeTemp;
int cfgResPrimConsTemp;
int cfgResPrimHystTemp;
int cfgResInyeConsTemp;
int cfgResInyeHystTemp;
int cfgAguaConsTemp;
int cfgAguaHystTemp;

int cfgResPrimAlarMin;
int cfgResInyeAlarMin;
int cfgAguaAlarMin;

#if (_USE_TRIAC_ == 1)
int cfgTriacVout[3];
int cfgTriacUse[3];
#endif

#if (_USE_MBRTU_ == 1)
int cfgTempUse[4];
#endif

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

#if (_EEPROM_SERIAL_DEBUG_ == 1)
void _printNetworkCONFIG(void)
{
  #if (_USE_ETHERNET_ == 1)
  if (ipMode == FIXIP_MODE)
    Serial.println("IP Mode: FIX IP");
  else
    Serial.println("IP Mode: DHCP");
  
  Serial.print("IP: ");
  Serial.print(ipAddress[0]); Serial.print(".");Serial.print(ipAddress[1]); Serial.print(".");Serial.print(ipAddress[2]); Serial.print(".");Serial.print(ipAddress[3]);
  Serial.print(" Mask: ");
  Serial.print(netMask[0]); Serial.print(".");Serial.print(netMask[1]); Serial.print(".");Serial.print(netMask[2]); Serial.print(".");Serial.print(netMask[3]);
  Serial.print(" Gateway: ");
  Serial.print(gateWay[0]); Serial.print(".");Serial.print(gateWay[1]); Serial.print(".");Serial.print(gateWay[2]); Serial.print(".");Serial.print(gateWay[3]);
  Serial.println();
  #endif

  #if (_USE_MQTT_ == 1)
  Serial.print("Broker URL: ");
  Serial.println(brokerUrl);
  Serial.print("Broker Port: ");
  Serial.println(brokerPort);
  Serial.print("Broker User: ");
  Serial.println(brokerUser);
  Serial.print("Broker Password: ");
  Serial.println(brokerPswd);
  #endif 
}

void _printCtrCONFIG(void)
{  
  Serial.print("cfgLogicIns: ");        Serial.println (cfgLogicIns);
  Serial.print("cfgLogicOuts: ");       Serial.println (cfgLogicOuts);

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

  #if (_USE_TRIAC_ == 1)
  Serial.print("cfgTriacVout[0]: ");    Serial.println (cfgTriacVout[0]);
  Serial.print("cfgTriacVout[1]: ");    Serial.println (cfgTriacVout[1]);
  Serial.print("cfgTriacVout[2]: ");    Serial.println (cfgTriacVout[2]);

  Serial.print("cfgTriacUse[0]: ");     Serial.println (cfgTriacUse[0]);
  Serial.print("cfgTriacUse[1]: ");     Serial.println (cfgTriacUse[1]);
  Serial.print("cfgTriacUse[2]: ");     Serial.println (cfgTriacUse[2]);
  #endif

  #if (_USE_MBRTU_ == 1)
  Serial.print("cfgTempUse[0]: ");      Serial.println (cfgTempUse[0]);
  Serial.print("cfgTempUse[1]: ");      Serial.println (cfgTempUse[1]);
  Serial.print("cfgTempUse[2]: ");      Serial.println (cfgTempUse[2]);
  Serial.print("cfgTempUse[3]: ");      Serial.println (cfgTempUse[3]);
  #endif

  delay(1000);  // 100ms
}
#endif // _EEPROM_SERIAL_DEBUG_

void _readCONFIG (void)
{
  byte ok;
  int i, j;
  int eeprom_value_hi, eeprom_value_lo;
  
  if (!EEPROM.begin(512)) { // ESPXX
    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.println("Error al inicializar EEPROM");
    #endif
    return;
  }

  ok = EEPROM.read(EEPROM_ADD_OK);
  
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("EEPROM Value: "); Serial.println(ok, HEX);
  #endif

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

    // Other data
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  EEPROM_VAL_LOGIC_INS);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, EEPROM_VAL_LOGIC_OUTS);
    EEPROM.write(EEPROM_ADD_MBADD1,     EEPROM_VAL_MBADD1);

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

    #if (_USE_TRIAC_ == 1)
    EEPROM.write(EEPROM_ADD_TRIAC1_VOUT,        EEPROM_VAL_TRIAC1_VOUT);
    EEPROM.write(EEPROM_ADD_TRIAC2_VOUT,        EEPROM_VAL_TRIAC2_VOUT);
    EEPROM.write(EEPROM_ADD_TRIAC3_VOUT,        EEPROM_VAL_TRIAC3_VOUT);

    EEPROM.write(EEPROM_ADD_TRIAC1_USE,         EEPROM_VAL_TRIAC1_USE);
    EEPROM.write(EEPROM_ADD_TRIAC2_USE,         EEPROM_VAL_TRIAC2_USE);
    EEPROM.write(EEPROM_ADD_TRIAC3_USE,         EEPROM_VAL_TRIAC3_USE);
    #endif
    
    #if (_USE_MBRTU_ == 1)
    EEPROM.write(EEPROM_ADD_TEMP1_USE,          EEPROM_VAL_TEMP1_USE);
    EEPROM.write(EEPROM_ADD_TEMP2_USE,          EEPROM_VAL_TEMP2_USE);
    EEPROM.write(EEPROM_ADD_TEMP3_USE,          EEPROM_VAL_TEMP3_USE);
    EEPROM.write(EEPROM_ADD_TEMP4_USE,          EEPROM_VAL_TEMP4_USE);
    #endif

    EEPROM.commit();    // ESPXX Store data to EEPROM
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

  // Other data
  EEPROM.write(EEPROM_ADD_LOGIC_INS,  (byte)cfgLogicIns);
  EEPROM.write(EEPROM_ADD_LOGIC_OUTS, (byte)cfgLogicOuts);
  EEPROM.write(EEPROM_ADD_MBADD1,     (byte)cfgMB1Add);

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

  #if (_USE_TRIAC_ == 1)
  EEPROM.write(EEPROM_ADD_TRIAC1_VOUT,      (byte)cfgTriacVout[0]);
  EEPROM.write(EEPROM_ADD_TRIAC2_VOUT,      (byte)cfgTriacVout[1]);
  EEPROM.write(EEPROM_ADD_TRIAC3_VOUT,      (byte)cfgTriacVout[2]);

  EEPROM.write(EEPROM_ADD_TRIAC1_USE,       (byte)cfgTriacUse[0]);
  EEPROM.write(EEPROM_ADD_TRIAC2_USE,       (byte)cfgTriacUse[1]);
  EEPROM.write(EEPROM_ADD_TRIAC3_USE,       (byte)cfgTriacUse[2]);
  #endif

  #if (_USE_MBRTU_ == 1)
  EEPROM.write(EEPROM_ADD_TEMP1_USE,        (byte)cfgTempUse[0]);
  EEPROM.write(EEPROM_ADD_TEMP2_USE,        (byte)cfgTempUse[1]);
  EEPROM.write(EEPROM_ADD_TEMP3_USE,        (byte)cfgTempUse[2]);
  EEPROM.write(EEPROM_ADD_TEMP4_USE,        (byte)cfgTempUse[3]);
  #endif

  EEPROM.commit();    //Store data to EEPROM

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  _printNetworkCONFIG();
  _printCtrCONFIG();
  #endif
}

void _eeprom2ramCONFIG (void)
{
  int i;
  int eeprom_value_hi, eeprom_value_lo;

  #if (_USE_ETHERNET_ == 1)
  // IP Mode
  ipMode = EEPROM.read(EEPROM_ADD_IP_MODE);
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
  #endif // _USE_MQTT_
  
  // Rest of config
  cfgLogicIns         = (int)EEPROM.read(EEPROM_ADD_LOGIC_INS);
  cfgLogicOuts        = (int)EEPROM.read(EEPROM_ADD_LOGIC_OUTS); 
  cfgMB1Add           = (int)EEPROM.read(EEPROM_ADD_MBADD1);

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

  #if (_USE_TRIAC_ == 1)
  cfgTriacVout[0] = (int)EEPROM.read(EEPROM_ADD_TRIAC1_VOUT);
  cfgTriacVout[1] = (int)EEPROM.read(EEPROM_ADD_TRIAC2_VOUT);
  cfgTriacVout[2] = (int)EEPROM.read(EEPROM_ADD_TRIAC3_VOUT);

  cfgTriacUse[0] = (int)EEPROM.read(EEPROM_ADD_TRIAC1_USE);
  cfgTriacUse[1] = (int)EEPROM.read(EEPROM_ADD_TRIAC2_USE);
  cfgTriacUse[2] = (int)EEPROM.read(EEPROM_ADD_TRIAC3_USE);
  #endif

  #if (_USE_MBRTU_ == 1)
  cfgTempUse[0] = (int)EEPROM.read(EEPROM_ADD_TEMP1_USE);
  cfgTempUse[1] = (int)EEPROM.read(EEPROM_ADD_TEMP2_USE);
  cfgTempUse[2] = (int)EEPROM.read(EEPROM_ADD_TEMP3_USE);
  cfgTempUse[3] = (int)EEPROM.read(EEPROM_ADD_TEMP4_USE);
  #endif
  
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  _printNetworkCONFIG();
  _printCtrCONFIG();
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
  
  EEPROM.commit();    // ESPXX Store data to EEPROM
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
