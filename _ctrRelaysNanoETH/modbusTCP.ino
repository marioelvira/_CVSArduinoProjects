#include "main.h"

#if (_USE_MBTCP_ == 1)

void _ModbusTcpSetup(void)
{
  // Modbus TCP status
  modbusTcpStatus = MODBUSTCP_INIT;
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
      #if (_MBTCP_SERIAL_DEBUG_ == 1)
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
      
      #if (_MBTCP_SERIAL_DEBUG_ == 1)
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
           #if (_MBTCP_SERIAL_DEBUG_ == 1)
           Serial.print(F("Modbus tcp request: "));
           #endif
           
           mbFunction = MB_FUNC_NONE;
           modbusTcpIndex = 0;
           modbusTcpStatus = MODBUSTCP_ON_RX;
        }    
      }
      // Client disconnected...
      else
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
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
           #if (_MBTCP_SERIAL_DEBUG_ == 1)
           Serial.print (modbusTcpByteArray[modbusTcpIndex]);
           #endif
           modbusTcpIndex++;
        }
        else
        {
           #if (_MBTCP_SERIAL_DEBUG_ == 1)
           Serial.println (" ");
           #endif

           modbusTcpClient.flush();
            
           mbFunction = modbusTcpByteArray[MB_TCP_FUNC];
           modbusTcpStatus = MODBUSTCP_ON_ANALYSIS;
        }
      }
      // Client disconnected...
      else
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println(F("Disconnecting from modbus tcp client"));
        #endif
        modbusTcpStatus = MODBUSTCP_CLIENT_WAITING;
      }
      break;
    
    case MODBUSTCP_ON_ANALYSIS:
      // Client connected...
      if (modbusTcpClient.connected())
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.print(F("Function: "));
        Serial.println(mbFunction);
        #endif

        switch(mbFunction)
        {
          // 0x03 Read Holding Registers
          case MB_FUNC_READ_HOLDING_REGISTER:
            _mbReadHolding();
            break;
          
          // 0x04 Read Input Registers
          case MB_FUNC_READ_INPUT_REGISTER:
            _mbReadInput();
            break;

          // 0x10 Write Holding Registers
          case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
            _mbWriteMultipleHolding();
            break;

          // 0x11 Slave ID
		      case MB_FUNC_OTHER_REPORT_SLAVEID:
			      _mbSlaveID();
			      break;

          default:
            modbusTcpStatus = MODBUSTCP_CLIENT_CONNECTED;
            break;
        }
      }
      // Client disconnected...
      else
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println(F("Disconnecting from modbus tcp client"));
        #endif
        modbusTcpStatus = MODBUSTCP_CLIENT_WAITING;
      }  
      break;
      
    case MODBUSTCP_ON_TX:
      #if (_MBTCP_SERIAL_DEBUG_ == 1)
      Serial.print(F("modbus tcp response "));
      Serial.println(mbResponseLength);
      #endif

      modbusTcpClient.write((const uint8_t *)modbusTcpByteArray, mbResponseLength);      
      modbusTcpStatus = MODBUSTCP_CLIENT_CONNECTED;
      break;
  }
}

void _mbWriteMultipleHolding()
{
}

void _mbReadHolding()
{
  int addr, nregs, exception = 0;

  addr  = (int)word(modbusTcpByteArray[MB_TCP_REGS_ADD], modbusTcpByteArray[MB_TCP_REGS_ADD + 1]);
  nregs = (int)word(modbusTcpByteArray[MB_TCP_REGS_NUM], modbusTcpByteArray[MB_TCP_REGS_NUM + 1]);

  #if (_MBTCP_SERIAL_DEBUG_ == 1)
  Serial.print(F("addr: "));
  Serial.print(addr);
  Serial.print(F(", nregs: "));
  Serial.println(nregs);
  #endif

  if ((addr == MB_HR_ADD_CFG) && (nregs == MB_HR_NREG_CFG))
  {
  }
  else if ((addr == MB_HR_ADD_OUTS) && (nregs == MB_HR_NREG_OUTS))
  {
    // modbusTcpByteArray[MB_TCP_FUNC]        07
    modbusTcpByteArray[MB_TCP_NBYTES] = nregs * 2;

    for(int i = 0; i < MB_HR_NREG_OUTS; i++)
    {
      modbusTcpByteArray[MB_TCP_REGS     + i * 2] = 0x00;
      modbusTcpByteArray[MB_TCP_REGS + 1 + i * 2] = OutDig[i];
    }
  }
  else
    exception = 1;

  if (exception == 0)
  {
    // modbusTcpByteArray[MB_TCP_TID]         00
    // modbusTcpByteArray[MB_TCP_TID + 1]     01
    // modbusTcpByteArray[MB_TCP_PID]         02
    // modbusTcpByteArray[MB_TCP_PID + 1]     03
    modbusTcpByteArray[MB_TCP_LEN]     = ((nregs + 3) & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_LEN + 1] = (nregs + 3) & 0x00FF;
    // modbusTcpByteArray[MB_TCP_UID]         06

    // Num Bytes
    mbResponseLength = nregs*2 + 9;
  }
  else
  {
	  modbusTcpByteArray[MB_TCP_FUNC] = (char)(MB_FUNC_READ_HOLDING_REGISTER | MB_NACK);
    modbusTcpByteArray[MB_TCP_NBYTES] = MB_EC_ILLEGAL_DATA_ADDRESS;

    // Num Bytes
    mbResponseLength = 9;
  }

  modbusTcpStatus = MODBUSTCP_ON_TX;
}

void _mbReadInput()
{
  int addr, nregs, exception = 0;

  addr  = (int)word(modbusTcpByteArray[MB_TCP_REGS_ADD], modbusTcpByteArray[MB_TCP_REGS_ADD + 1]);
  nregs = (int)word(modbusTcpByteArray[MB_TCP_REGS_NUM], modbusTcpByteArray[MB_TCP_REGS_NUM + 1]);

  #if (_MBTCP_SERIAL_DEBUG_ == 1)
  Serial.print(F("addr: "));
  Serial.print(addr);
  Serial.print(F(", nregs: "));
  Serial.println(nregs);
  #endif

  if ((addr == MB_IR_ADD_ONLINE) && (nregs == MB_IR_NREG_ONLINE))
  {
    modbusTcpByteArray[MB_TCP_REGS]      = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 1]  = ctrMode;
    modbusTcpByteArray[MB_TCP_REGS + 2]  = (char)((Irms[0] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 3]  = (char)(Irms[0] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 4]  = (char)((Irms[1] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 5]  = (char)(Irms[1] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 6]  = (char)((Vdc[0] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 7]  = (char)(Vdc[0] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 8]  = (char)((Vdc[1] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 9]  = (char)(Vdc[1] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 10] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 11] = InDig[0];
    modbusTcpByteArray[MB_TCP_REGS + 12] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 13] = InDig[1];
    modbusTcpByteArray[MB_TCP_REGS + 14] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 15] = OutDig[0];
    modbusTcpByteArray[MB_TCP_REGS + 16] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 17] = OutDig[1];
    modbusTcpByteArray[MB_TCP_REGS + 18] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 19] = OutDig[2];
    modbusTcpByteArray[MB_TCP_REGS + 20] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 21] = OutDig[3];
    modbusTcpByteArray[MB_TCP_REGS + 22] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 23] = OutDig[4];
    modbusTcpByteArray[MB_TCP_REGS + 24] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 25] = OutDig[5];
  }
  else if ((addr == MB_IR_ADD_INS) && (nregs == MB_IR_NREG_INS))
  { 
    // modbusTcpByteArray[MB_TCP_FUNC]        07
    modbusTcpByteArray[MB_TCP_NBYTES] = nregs * 2;

    for(int i = 0; i < MB_IR_NREG_INS; i++)
    {
      modbusTcpByteArray[MB_TCP_REGS     + i * 2] = 0x00;
      modbusTcpByteArray[MB_TCP_REGS + 1 + i * 2] = InDig[i];
    }
  }
  else if ((addr == MB_IR_ADD_OUTS) && (nregs == MB_IR_NREG_OUTS))
  {
    // modbusTcpByteArray[MB_TCP_FUNC]        07
    modbusTcpByteArray[MB_TCP_NBYTES] = nregs * 2;

    for(int i = 0; i < MB_IR_NREG_OUTS; i++)
    {
      modbusTcpByteArray[MB_TCP_REGS     + i * 2] = 0x00;
      modbusTcpByteArray[MB_TCP_REGS + 1 + i * 2] = OutDig[i];
    }
  }
  else if ((addr == MB_IR_ADD_ADCS) && (nregs == MB_IR_NREG_ADCS))
  {
    // modbusTcpByteArray[MB_TCP_FUNC]        07
    modbusTcpByteArray[MB_TCP_NBYTES] = nregs * 2;

    for(int i = 0; i < MB_IR_NREG_ADCS; i++)
    {
      modbusTcpByteArray[MB_TCP_REGS     + i * 2] = (char)((AdcDig[i] & 0xFF00)>>8);
      modbusTcpByteArray[MB_TCP_REGS + 1 + i * 2] = (char)(AdcDig[i] & 0x00FF);
    }
  }
  else
    exception = 1;

  if (exception == 0)
  {
    // modbusTcpByteArray[MB_TCP_TID]         00
    // modbusTcpByteArray[MB_TCP_TID + 1]     01
    // modbusTcpByteArray[MB_TCP_PID]         02
    // modbusTcpByteArray[MB_TCP_PID + 1]     03
    modbusTcpByteArray[MB_TCP_LEN]     = ((nregs + 3) & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_LEN + 1] = (nregs + 3) & 0x00FF;
    // modbusTcpByteArray[MB_TCP_UID]         06

    // Num Bytes
    mbResponseLength = nregs*2 + 9;
  }
  else
  {
	  modbusTcpByteArray[MB_TCP_FUNC] = (char)(MB_FUNC_READ_INPUT_REGISTER | MB_NACK);
    modbusTcpByteArray[MB_TCP_NBYTES] = MB_EC_ILLEGAL_DATA_ADDRESS;

    // Num Bytes
    mbResponseLength = 9;
  }

  modbusTcpStatus = MODBUSTCP_ON_TX;
}

void _mbSlaveID()
{
  // modbusTcpByteArray[MB_TCP_TID]         00
  // modbusTcpByteArray[MB_TCP_TID + 1]     01
  // modbusTcpByteArray[MB_TCP_PID]         02
  // modbusTcpByteArray[MB_TCP_PID + 1]     03
  modbusTcpByteArray[MB_TCP_LEN]     = ((13 + 3) & 0xFF00)>>8;
  modbusTcpByteArray[MB_TCP_LEN + 1] = (13 + 3) & 0x00FF;
  // modbusTcpByteArray[MB_TCP_UID]         06
	modbusTcpByteArray[MB_TCP_FUNC] = (char)MB_FUNC_OTHER_REPORT_SLAVEID;

  modbusTcpByteArray[MB_TCP_REGS] = (char)(24);

  modbusTcpByteArray[MB_TCP_REGS + 1] = 0x00;
  modbusTcpByteArray[MB_TCP_REGS + 2] = 0xFF;

  // 12 bytes
  modbusTcpByteArray[MB_TCP_REGS + 3] = '0';  //SN_VER0;
  modbusTcpByteArray[MB_TCP_REGS + 4] = '0';  //SN_VER1;
  modbusTcpByteArray[MB_TCP_REGS + 5] = '0';  //SN_VER2;
  modbusTcpByteArray[MB_TCP_REGS + 6] = '0';  //SN_VER3;
  modbusTcpByteArray[MB_TCP_REGS + 7] = '0';  //SN_VER4;
  modbusTcpByteArray[MB_TCP_REGS + 8] = '0'; //SN_VER5;
  modbusTcpByteArray[MB_TCP_REGS + 9] = '0'; //SN_VER6;
  modbusTcpByteArray[MB_TCP_REGS + 10] = '0'; //SN_VER7;
  modbusTcpByteArray[MB_TCP_REGS + 11] = '0'; //SN_VER8;
  modbusTcpByteArray[MB_TCP_REGS + 12] = '0'; //SN_VER9;
  modbusTcpByteArray[MB_TCP_REGS + 13] = '0'; //SN_VER10;
  modbusTcpByteArray[MB_TCP_REGS + 14] = '0'; //SN_VER11;
  
  // 10 bytes
  modbusTcpByteArray[MB_TCP_REGS + 15] = FW_Version[0]; //FW_VER0;
  modbusTcpByteArray[MB_TCP_REGS + 16] = FW_Version[1]; //FW_VER1;
  modbusTcpByteArray[MB_TCP_REGS + 17] = FW_Version[2]; //FW_VER2;
  modbusTcpByteArray[MB_TCP_REGS + 18] = FW_Version[3]; //FW_VER3;
  modbusTcpByteArray[MB_TCP_REGS + 19] = FW_Version[4]; //FW_VER4;
  modbusTcpByteArray[MB_TCP_REGS + 20] = '0'; //FW_VER5;
  modbusTcpByteArray[MB_TCP_REGS + 21] = '0'; //FW_VER6;
  modbusTcpByteArray[MB_TCP_REGS + 22] = '0'; //FW_VER7;
  modbusTcpByteArray[MB_TCP_REGS + 23] = '0'; //FW_VER8;
  modbusTcpByteArray[MB_TCP_REGS + 24] = '0'; //FW_VER9;

  mbResponseLength = 32;
  modbusTcpStatus = MODBUSTCP_ON_TX;
}

#endif // _USE_MBTCP_
