
////////////////////
// Manitou set up //
////////////////////
void _ManitouSetup(void)
{
  //manitouControlMode = MODE_AUTO;
  //manitouNumberOfStarts;          // Read from E2PROM
  //manitouNumberOfHours            // Read from E2PROM
  manitouNumberOfOns2Save = 1;
  manitouNumberOfMins2Increment = 1;
  manitouOnFilter = 0;
}

///////////////////////////
// Manitou state machine //
///////////////////////////
void _ManitouLoop(void)
{
  int eeprom_value_hi, eeprom_value_lo;

  // If motor ON...
  if (inValue[INDEX_MOTOR] == IN_ON)
  {
    // Si tenemos que guardar...
    if (manitouNumberOfOns2Save == 1)
    {

     manitouOnFilter++;
     if (manitouOnFilter >= 100)
     { 
        manitouNumberOfOns++;
        
        // Save from E2PROM
        eeprom_value_lo = manitouNumberOfOns & 0x00FF;
        eeprom_value_hi = (manitouNumberOfOns & 0xFF00)>>8;
        EEPROM.write(EEPROM_ADD_NUMBEROF_ONS_LO, eeprom_value_lo);
        EEPROM.write(EEPROM_ADD_NUMBEROF_ONS_HI, eeprom_value_hi);
        EEPROM.commit();
           
        #if (_MANITOU_SERIAL_DEBUG_ == 1)
        Serial.print("Saving Ons -> "); Serial.println(manitouNumberOfOns);
        #endif
        
        manitouNumberOfOns2Save = 0;
      }
    }

    // Cada 20 minutos 
    #if (_MANITOU_DEBUG_ == 1)
    if (((timeSec % 19) == 0) && (timeSec != 0))
    #else
    if (((timeMin % 19) == 0) && (timeMin != 0))
    #endif
    {
      // Incrementamos en 20 minutos
      if (manitouNumberOfMins2Increment == 1)
      {       
        manitouNumberOfMins = manitouNumberOfMins + 20;

        if (manitouNumberOfMins >= 60)
        {
          manitouNumberOfMins = 0;
          manitouNumberOfHours++;

          // Save hours
          eeprom_value_lo = manitouNumberOfHours & 0x00FF;
          eeprom_value_hi = (manitouNumberOfHours & 0xFF00)>>8;
          EEPROM.write(EEPROM_ADD_NUMBEROF_HOURS_LO, eeprom_value_lo);
          EEPROM.write(EEPROM_ADD_NUMBEROF_HOURS_HI, eeprom_value_hi);
          
          #if (_MANITOU_SERIAL_DEBUG_ == 1)
          Serial.print("Saving Hours -> "); Serial.println(manitouNumberOfHours);
          #endif
        }

        // Save minutes         
        eeprom_value_lo = manitouNumberOfMins & 0x00FF;
        eeprom_value_hi = (manitouNumberOfMins & 0xFF00)>>8;
        EEPROM.write(EEPROM_ADD_NUMBEROF_MINS_LO, eeprom_value_lo);
        EEPROM.write(EEPROM_ADD_NUMBEROF_MINS_HI, eeprom_value_hi);
        EEPROM.commit();
        
        #if (_MANITOU_SERIAL_DEBUG_ == 1)
        Serial.print("Saving Mins -> "); Serial.println(manitouNumberOfMins);
        #endif
         
        manitouNumberOfMins2Increment = 0;
      }
    }
    else
      manitouNumberOfMins2Increment = 1;
  }
  // If motor Off
  else
  {
    _ManitouSetup();
    _TimeSetup();
  }
}
