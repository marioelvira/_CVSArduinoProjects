
void _ModbusTcpSetup(void)
{
  // Modbus TCP status
  modbusTcpStatus = MODBUSTCP_INIT;

  for (int i = 0; i < MB_MAX_HR; i++)
    modbusHoldingRegs[i] = 0;
}

void _ModbusTcpEnd(void)
{
  modbusTcpServer.stop();
}

//////////////////////////////
// Modbus TCP state machine //
//////////////////////////////
void _ModbusTcpLoop()
{
  switch (modbusTcpStatus)
  {
    case MODBUSTCP_INIT:
      modbusTcpServer.begin(cfgModbusPORT);
      #if (_SERIAL_DEBUG_ == 1)
      Serial.println("Modbus TCP server started");
      #endif
      modbusTcpStatus = MODBUSTCP_CLIENT_WAITING;
      break;

    case MODBUSTCP_CLIENT_WAITING:
    
      // Check if a client has connected
      modbusTcpClient = modbusTcpServer.available();
      if (!modbusTcpClient) {
        break;
      }
      
      #if (_SERIAL_DEBUG_ == 1)
      Serial.println(F("new client Modbus TCP"));
      #endif
    
      modbusTcpClient.setTimeout(5000); // default is 1000

      modbusTcpStatus = MODBUSTCP_CLIENT_CONNECTED;
      break;

    case MODBUSTCP_CLIENT_CONNECTED:
      // Client connected....
      if (modbusTcpClient.connected())
      {
        if (modbusTcpClient.available())
        {
           #if (_SERIAL_DEBUG_ == 1)
           Serial.println(F("Modbus tcp request: "));
           #endif
           
           mbFunction = MB_FC_NONE;
           modbusTcpIndex = 0;
           modbusTcpStatus = MODBUSTCP_ON_RX;
        }    
      }
      // Client disconnected...
      else
      {
        #if (_SERIAL_DEBUG_ == 1)
        Serial.println(F("Disconnecting from modbus tcp client"));
        #endif
        modbusTcpStatus = MODBUSTCP_CLIENT_WAITING;
      }
      break;

    case MODBUSTCP_ON_RX:
      // Client connected...
      if (modbusTcpClient.connected())
      {
        if (modbusTcpClient.available())
        {
           modbusTcpByteArray[modbusTcpIndex] = modbusTcpClient.read();
           #if (_SERIAL_DEBUG_ == 1)
           Serial.print(modbusTcpByteArray[modbusTcpIndex]);
           #endif
           modbusTcpIndex++;
        }
        else
        {
           modbusTcpClient.flush();
            
           mbFunction = modbusTcpByteArray[MB_TCP_FUNC];
           mbStartAddress = word(modbusTcpByteArray[MB_TCP_REGISTER_STR], modbusTcpByteArray[MB_TCP_REGISTER_STR + 1]);
           mbNumRegisters = word(modbusTcpByteArray[MB_TCP_REGISTER_NUM], modbusTcpByteArray[MB_TCP_REGISTER_NUM + 1]);

           modbusTcpStatus = MODBUSTCP_ON_ANALYSIS;
        }
      }
      // Client disconnected...
      else
      {
        #if (_SERIAL_DEBUG_ == 1)
        Serial.println(F("Disconnecting from modbus tcp client"));
        #endif
        modbusTcpStatus = MODBUSTCP_CLIENT_WAITING;
      }
      break;
    
    case MODBUSTCP_ON_ANALYSIS:
      // Client connected...
      if (modbusTcpClient.connected())
      {
        switch(mbFunction)
        {
          // 03 Read Holding Registers
          case MB_FC_READ_REGISTERS:

            // Update HR values
            _Outs2HR();
            _In2HR();

            mbNumBytes = mbNumRegisters * 2;
            modbusTcpByteArray[5] = mbNumBytes + 3;
            modbusTcpByteArray[8] = mbNumBytes;
            for(int i = 0; i < mbNumRegisters; i++)
            {
              modbusTcpByteArray[ 9 + i * 2] = highByte(modbusHoldingRegs[mbStartAddress + i]);
              modbusTcpByteArray[10 + i * 2] = lowByte (modbusHoldingRegs[mbStartAddress + i]);
            }
            mbResponseLength = mbNumBytes + 9;
            modbusTcpStatus = MODBUSTCP_ON_TX;
            break;
    
          // 06 Write Holding Register
          case MB_FC_WRITE_REGISTER:
            modbusHoldingRegs[mbStartAddress] = word(modbusTcpByteArray[MB_TCP_REGISTER_NUM], modbusTcpByteArray[MB_TCP_REGISTER_NUM + 1]);
            modbusTcpByteArray[5] = 6;
            mbResponseLength = 12;
            _HR2Outs();  // Outs update
            modbusTcpStatus = MODBUSTCP_ON_TX;
            break;

          // 16 Write Holding Registers
          case MB_FC_WRITE_MULTIPLE_REGISTERS:
            mbNumBytes = mbNumRegisters * 2;
            modbusTcpByteArray[5] = mbNumBytes + 3;
            for(int i = 0; i < mbNumRegisters; i++)
            {
              modbusHoldingRegs[mbStartAddress + i] = word(modbusTcpByteArray[ 13 + i * 2], modbusTcpByteArray[14 + i * 2]);
            }
            mbResponseLength = 12;
            _HR2Outs();  // Outs update
            modbusTcpStatus = MODBUSTCP_ON_TX;
            break;

          default:
            modbusTcpStatus = MODBUSTCP_CLIENT_CONNECTED;
            break;
        }
      }
      // Client disconnected...
      else
      {
        #if (_SERIAL_DEBUG_ == 1)
        Serial.println(F("Disconnecting from modbus tcp client"));
        #endif
        modbusTcpStatus = MODBUSTCP_CLIENT_WAITING;
      }  
      break;
      
    case MODBUSTCP_ON_TX:
      modbusTcpClient.write((const uint8_t *)modbusTcpByteArray, mbResponseLength);      
      modbusTcpStatus = MODBUSTCP_CLIENT_CONNECTED;
      break;
  }
}

////////////////////////////////
// Modbus Holding Regs 2 Outs //
////////////////////////////////
void _HR2Outs()
{
  if (modbusHoldingRegs[0] == IO_OFF)
    outLed = OUT_OFF;
  else
    outLed = IO_ON;

  if (modbusHoldingRegs[1] == IO_OFF)
    ioOutA = OUT_OFF;
  else
    ioOutA = OUT_ON;
}

////////////////////////////////
// Outs 2 Modbus Holding Regs //
////////////////////////////////
void _Outs2HR()
{
  modbusHoldingRegs[0] = outLed;
  modbusHoldingRegs[1] = ioOutA;
}

//////////////////////////////
// In 2 Modbus Holding Regs //
//////////////////////////////
void _In2HR()
{
  modbusHoldingRegs[2] = ioInA;
}
