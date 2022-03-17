
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
  int i;
  #if (_WRITE_SSID_EEPROM_ == 1)
  int j;
  #endif
  byte val[4];

  int eeprom_value_hi, eeprom_value_lo;
  
  //EEPROM.begin(512);
    
  i = EEPROM.read(EEPROM_ADD_OK);
  
  // Si NO esta grabada la configuracion...
  if (i != EEPROM_VAL_OK)
  {
    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.println("Config NOK");
    #endif
  
    EEPROM.write(EEPROM_ADD_OK,      EEPROM_VAL_OK);

    // Data Data
    //EEPROM.write(EEPROM_ADD_RESERVA,   EEPROM_VAL_RESERVA);
       
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
    EEPROM.write(EEPROM_ADD_DEBUG,     EEPROM_VAL_DEBUG);
    
    //EEPROM.commit();    //Store data to EEPROM
  }
  else
  {
    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.println("Config OK");
    #endif
  }
   
  TimeGenerador1P = (int)EEPROM.read(EEPROM_ADD_1P_TIMER_GEN);//*60; // Min
  TimeGenerador2P = (int)EEPROM.read(EEPROM_ADD_2P_TIMER_GEN);//*60; // Min
  TimeGenerador3P = (int)EEPROM.read(EEPROM_ADD_3P_TIMER_GEN);//*60; // Min
  TimeGenerador4P = (int)EEPROM.read(EEPROM_ADD_4P_TIMER_GEN);//*60; // Min
  TimeGenerador5P = (int)EEPROM.read(EEPROM_ADD_5P_TIMER_GEN);//*60; // Min
  TimeGenerador6P = (int)EEPROM.read(EEPROM_ADD_6P_TIMER_GEN);//*3600; // Hour
  TimeGenerador7P = (int)EEPROM.read(EEPROM_ADD_7P_TIMER_GEN);//*3600; // Hour
  TimeGenerador8P = (int)EEPROM.read(EEPROM_ADD_8P_TIMER_GEN);//*3600; // Hour
  TimeGenerador9P = (int)EEPROM.read(EEPROM_ADD_9P_TIMER_GEN);//*3600; // Hour

  TimeBuzzerOn = (int)EEPROM.read(EEPROM_ADD_BUZZER_ON);    // Secs
  TimeOutStart = (int)EEPROM.read(EEPROM_ADD_TSTART);       // Secs
  TimeOutStop  = (int)EEPROM.read(EEPROM_ADD_TSTOP);        // Secs
    
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  
  Serial.print("Time 1P: ");  Serial.print (TimeGenerador1P);  Serial.println(" min");
  Serial.print("Time 2P: ");  Serial.print (TimeGenerador2P);  Serial.println(" min");
  Serial.print("Time 3P: ");  Serial.print (TimeGenerador3P);  Serial.println(" min");
  Serial.print("Time 4P: ");  Serial.print (TimeGenerador4P);  Serial.println(" min");
  Serial.print("Time 5P: ");  Serial.print (TimeGenerador5P);  Serial.println(" min");
  Serial.print("Time 6P: ");  Serial.print (TimeGenerador6P);  Serial.println(" hour");
  Serial.print("Time 7P: ");  Serial.print (TimeGenerador7P);  Serial.println(" hour");
  Serial.print("Time 8P: ");  Serial.print (TimeGenerador8P);  Serial.println(" hour");
  Serial.print("Time 9P: ");  Serial.print (TimeGenerador9P);  Serial.println(" hour");

  Serial.print("Time Buzzer: "); Serial.print (TimeBuzzerOn);  Serial.println(" secs");
  Serial.print("Time Start: ");  Serial.print (TimeOutStart);  Serial.println(" secs");
  Serial.print("Time Stop: ");   Serial.print (TimeOutStop);   Serial.println(" secs");
  
  #endif

  // Debug options
  X_60 = 3;
  X_3600 = 180;
}

void _ResetEEPROM() {

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.println("Erasing E2PROM 512 size... ");
  #endif

  // write a 0 to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0xFF);
  }
  
  //EEPROM.commit();    //Store data to EEPROM
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
