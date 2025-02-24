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
    
      modbusTcpClientError = 0;
      modbusTcpStatus = MODBUSTCP_CLIENT_CONNECTED;
      modbusTcpTick = millis();
      break;

    case MODBUSTCP_CLIENT_CONNECTED:
      // Client connected....
      if (modbusTcpClient.connected())
      {
        if (modbusTcpClient.available())
        {
           #if (_MBTCP_SERIAL_DEBUG_ == 1)
           Serial.println("Modbus tcp request:");
           #endif

           mbFunction = MB_FUNC_NONE;
           modbusTcpIndex = 0;

           modbusTcpStatus = MODBUSTCP_ON_RX;
           modbusTcpTick = millis();
        }

        // Time out...
        if (millis() - modbusTcpTick >= MODBUS_TCP_TIMEOUT)
        {
          modbusTcpStatus = MODBUSTCP_INIT;
    
          #if (_MBTCP_SERIAL_DEBUG_ == 1)
          Serial.println("Modbus tcp time out");
          #endif
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
           Serial.print (modbusTcpByteArray[modbusTcpIndex] < 16 ? "0" : "");
           Serial.print (modbusTcpByteArray[modbusTcpIndex], HEX);
           #endif
           modbusTcpIndex++;

           modbusTcpTick = millis();
        }
        else
        {
          // RX Time out...
          if (millis() - modbusTcpTick >= MODBUS_TCP_RX_TIMEOUT)
          {
             #if (_MBTCP_SERIAL_DEBUG_ == 1)
             Serial.println (" ");
             #endif

             modbusTcpClient.flush();
            
             mbFunction = modbusTcpByteArray[MB_TCP_FUNC];
             modbusTcpStatus = MODBUSTCP_ON_ANALYSIS;
          }
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
      /*
      if (modbusTcpIndex < 4)
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println(F("Left bytes RX Error"));
        #endif

        modbusTcpStatus = MODBUSTCP_CLIENT_WAITING;
        break;
      }        
      */
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

      modbusTcpClient.flush();

      #if (_MBTCP_SERIAL_DEBUG_ == 1)
      Serial.print(F("Modbus tcp response: "));
      Serial.println(mbResponseLength);
      for (int i = 0; i< mbResponseLength; i++)
      {
        Serial.print (modbusTcpByteArray[i] < 16 ? "0" : "");
        Serial.print (modbusTcpByteArray[i], HEX);
      }
      Serial.println (" ");
      #endif

      modbusTcpClient.write((const uint8_t *)modbusTcpByteArray, mbResponseLength);      
      modbusTcpStatus = MODBUSTCP_CLIENT_CONNECTED;
      break;
  }
}

void _mbWriteMultipleHolding()
{
  int i, addr, nregs, value, exception = 0;

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
    value = (int)((modbusTcpByteArray[13] & 0x00FF)<<8)|(modbusTcpByteArray[14] & 0x00FF);
    if (value == MODE_AUTO)
      ctrMode = MODE_AUTO;
    else
      ctrMode = MODE_TEST;
    
    value  = (int)((modbusTcpByteArray[15] & 0x00FF)<<8)|(modbusTcpByteArray[16] & 0x00FF);
    if (value == IN_OFF)
      cfgLogicIns = IN_OFF;
    else 
      cfgLogicIns = IN_ON;
      
    value = (int)((modbusTcpByteArray[17] & 0x00FF)<<8)|(modbusTcpByteArray[18] & 0x00FF);
    if (value == OUT_OFF)
      cfgLogicOuts = OUT_OFF;
    else 
      cfgLogicOuts = OUT_ON;

    cfgIType[0] = (int)((modbusTcpByteArray[19] & 0x00FF)<<8)|(modbusTcpByteArray[20] & 0x00FF);
    cfgIACr[0]  = (int)((modbusTcpByteArray[21] & 0x00FF)<<8)|(modbusTcpByteArray[22] & 0x00FF);
    cfgIlim[0]  = (int)((modbusTcpByteArray[23] & 0x00FF)<<8)|(modbusTcpByteArray[24] & 0x00FF);
    cfgIsec[0]  = (int)((modbusTcpByteArray[25] & 0x00FF)<<8)|(modbusTcpByteArray[26] & 0x00FF);
  
    cfgIType[1] = (int)((modbusTcpByteArray[27] & 0x00FF)<<8)|(modbusTcpByteArray[28] & 0x00FF);
    cfgIACr[1]  = (int)((modbusTcpByteArray[29] & 0x00FF)<<8)|(modbusTcpByteArray[30] & 0x00FF);
    cfgIlim[1]  = (int)((modbusTcpByteArray[31] & 0x00FF)<<8)|(modbusTcpByteArray[32] & 0x00FF);
    cfgIsec[1]  = (int)((modbusTcpByteArray[33] & 0x00FF)<<8)|(modbusTcpByteArray[34] & 0x00FF);

    cfgVDCm[0]  = (int)((modbusTcpByteArray[35] & 0x00FF)<<8)|(modbusTcpByteArray[36] & 0x00FF);
    cfgVDCb[0]  = (int)((modbusTcpByteArray[37] & 0x00FF)<<8)|(modbusTcpByteArray[38] & 0x00FF);

    cfgVDCm[1]  = (int)((modbusTcpByteArray[39] & 0x00FF)<<8)|(modbusTcpByteArray[40] & 0x00FF);
    cfgVDCb[1]  = (int)((modbusTcpByteArray[41] & 0x00FF)<<8)|(modbusTcpByteArray[42] & 0x00FF);

    cfgVDCm[2]  = (int)((modbusTcpByteArray[43] & 0x00FF)<<8)|(modbusTcpByteArray[44] & 0x00FF);
    cfgVDCb[2]  = (int)((modbusTcpByteArray[45] & 0x00FF)<<8)|(modbusTcpByteArray[46] & 0x00FF);

    cfgVDCm[3]  = (int)((modbusTcpByteArray[47] & 0x00FF)<<8)|(modbusTcpByteArray[48] & 0x00FF);
    cfgVDCb[3]  = (int)((modbusTcpByteArray[49] & 0x00FF)<<8)|(modbusTcpByteArray[50] & 0x00FF);

    cfgVDCm[4]  = (int)((modbusTcpByteArray[51] & 0x00FF)<<8)|(modbusTcpByteArray[52] & 0x00FF);
    cfgVDCb[4]  = (int)((modbusTcpByteArray[53] & 0x00FF)<<8)|(modbusTcpByteArray[54] & 0x00FF);

    cfgVDCm[5]  = (int)((modbusTcpByteArray[55] & 0x00FF)<<8)|(modbusTcpByteArray[56] & 0x00FF);
    cfgVDCb[5]  = (int)((modbusTcpByteArray[57] & 0x00FF)<<8)|(modbusTcpByteArray[58] & 0x00FF);

    cfgCtrSecs[0] = (int)((modbusTcpByteArray[59] & 0x00FF)<<8)|(modbusTcpByteArray[60] & 0x00FF);
    cfgCtrSecs[1] = (int)((modbusTcpByteArray[61] & 0x00FF)<<8)|(modbusTcpByteArray[62] & 0x00FF);
    cfgCtrSecs[2] = (int)((modbusTcpByteArray[63] & 0x00FF)<<8)|(modbusTcpByteArray[64] & 0x00FF);
    cfgCtrSecs[3] = (int)((modbusTcpByteArray[65] & 0x00FF)<<8)|(modbusTcpByteArray[66] & 0x00FF);
    cfgCtrSecs[4] = (int)((modbusTcpByteArray[67] & 0x00FF)<<8)|(modbusTcpByteArray[68] & 0x00FF);
    cfgCtrSecs[5] = (int)((modbusTcpByteArray[69] & 0x00FF)<<8)|(modbusTcpByteArray[70] & 0x00FF);
    cfgCtrSecs[6] = (int)((modbusTcpByteArray[71] & 0x00FF)<<8)|(modbusTcpByteArray[72] & 0x00FF);

    _ram2eepromCONFIG();
  }
  else if ((addr == MB_HR_ADD_IP) && (nregs == MB_HR_NREG_IP))
  {
    ipMode        = (int)((modbusTcpByteArray[13] & 0x00FF)<<8)|(modbusTcpByteArray[14] & 0x00FF);
    ipAddress[0]  = (int)((modbusTcpByteArray[15] & 0x00FF)<<8)|(modbusTcpByteArray[16] & 0x00FF);
    ipAddress[1]  = (int)((modbusTcpByteArray[17] & 0x00FF)<<8)|(modbusTcpByteArray[18] & 0x00FF);
    ipAddress[2]  = (int)((modbusTcpByteArray[19] & 0x00FF)<<8)|(modbusTcpByteArray[20] & 0x00FF);
    ipAddress[3]  = (int)((modbusTcpByteArray[21] & 0x00FF)<<8)|(modbusTcpByteArray[22] & 0x00FF);
    netMask[0]    = (int)((modbusTcpByteArray[23] & 0x00FF)<<8)|(modbusTcpByteArray[24] & 0x00FF);
    netMask[1]    = (int)((modbusTcpByteArray[25] & 0x00FF)<<8)|(modbusTcpByteArray[26] & 0x00FF);
    netMask[2]    = (int)((modbusTcpByteArray[27] & 0x00FF)<<8)|(modbusTcpByteArray[28] & 0x00FF);
    netMask[3]    = (int)((modbusTcpByteArray[29] & 0x00FF)<<8)|(modbusTcpByteArray[30] & 0x00FF);
    gateWay[0]    = (int)((modbusTcpByteArray[31] & 0x00FF)<<8)|(modbusTcpByteArray[32] & 0x00FF);
    gateWay[1]    = (int)((modbusTcpByteArray[33] & 0x00FF)<<8)|(modbusTcpByteArray[34] & 0x00FF);
    gateWay[2]    = (int)((modbusTcpByteArray[35] & 0x00FF)<<8)|(modbusTcpByteArray[36] & 0x00FF);
    gateWay[3]    = (int)((modbusTcpByteArray[37] & 0x00FF)<<8)|(modbusTcpByteArray[38] & 0x00FF);
    cfgModbusPORT = (int)((modbusTcpByteArray[39] & 0x00FF)<<8)|(modbusTcpByteArray[40] & 0x00FF);

    _ram2eepromCONFIG();
  }
  else if ((addr == MB_HR_ADD_OUTS) && (nregs == MB_HR_NREG_OUTS))
  {
    // Only in MODE_TEST
    if (ctrMode == MODE_AUTO)
      exception = 1;
    else
    {
      for (int i = 0; i < MB_HR_NREG_OUTS; i++)
      {
        value = (int)((modbusTcpByteArray[i*2 + 13] & 0x00FF)<<8)|(modbusTcpByteArray[i*2 + 14] & 0x00FF);
        if (value == OUT_OFF)
          OutDig[i] = OUT_OFF;
        else
          OutDig[i] = OUT_ON;
      }
    }
  }
  else
    exception = 1;

  if (exception == 0)
  {
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbWriteMultipleHolding OK");
    #endif
    // modbusTcpByteArray[MB_TCP_TID]         00
    // modbusTcpByteArray[MB_TCP_TID + 1]     01
    // modbusTcpByteArray[MB_TCP_PID]         02
    // modbusTcpByteArray[MB_TCP_PID + 1]     03
    modbusTcpByteArray[MB_TCP_LEN]          = 0x00;
    modbusTcpByteArray[MB_TCP_LEN + 1]      = 0x06;
    // modbusTcpByteArray[MB_TCP_UID]         06
    modbusTcpByteArray[MB_TCP_FUNC]         = (char)MB_FUNC_WRITE_MULTIPLE_REGISTERS;
    modbusTcpByteArray[MB_TCP_REGS_ADD]     = (addr & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS_ADD + 1] = addr & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS_NUM]     = (nregs & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS_NUM + 1] = nregs & 0x00FF;

    // Num Bytes
    mbResponseLength = 12;
  }
  else
  {
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbWriteMultipleHolding NOK");
    #endif

    modbusTcpClientError++;

    // modbusTcpByteArray[MB_TCP_TID]         00
    // modbusTcpByteArray[MB_TCP_TID + 1]     01
    // modbusTcpByteArray[MB_TCP_PID]         02
    // modbusTcpByteArray[MB_TCP_PID + 1]     03
    modbusTcpByteArray[MB_TCP_LEN]     = 0x00;
    modbusTcpByteArray[MB_TCP_LEN + 1] = 0x03;
    // modbusTcpByteArray[MB_TCP_UID]         06
	  modbusTcpByteArray[MB_TCP_FUNC] = (char)(MB_FUNC_WRITE_MULTIPLE_REGISTERS | MB_NACK);
    modbusTcpByteArray[MB_TCP_NBYTES] = MB_EC_ILLEGAL_DATA_ADDRESS;

    // Num Bytes
    mbResponseLength = 9;
  }

  modbusTcpStatus = MODBUSTCP_ON_TX;
}

void _mbReadHolding()
{
  int i, addr, nregs, exception = 0;

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
    modbusTcpByteArray[MB_TCP_REGS]       = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 1]   = ctrMode;
    modbusTcpByteArray[MB_TCP_REGS + 2]   = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 3]   = cfgLogicIns;
    modbusTcpByteArray[MB_TCP_REGS + 4]   = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 5]   = cfgLogicOuts;

    // ADC0
    modbusTcpByteArray[MB_TCP_REGS + 6]   = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 7]   = cfgIType[0];

    modbusTcpByteArray[MB_TCP_REGS + 8]   = (cfgIACr[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 9]   = cfgIACr[0] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 10]  = (cfgIlim[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 11]  = cfgIlim[0] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 12]  = (cfgIsec[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 13]  = cfgIsec[0] & 0x00FF;

    // ADC1
    modbusTcpByteArray[MB_TCP_REGS + 14]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 15]  = cfgIType[1];

    modbusTcpByteArray[MB_TCP_REGS + 16]  = (cfgIACr[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 17]  = cfgIACr[1] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 18]  = (cfgIlim[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 19]  = cfgIlim[1] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 20]  = (cfgIsec[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 21]  = cfgIsec[1] & 0x00FF;

    // ADC2
    modbusTcpByteArray[MB_TCP_REGS + 22]  = (cfgVDCm[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 23]  = cfgVDCm[0] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 24]  = (cfgVDCb[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 25]  = cfgVDCb[0] & 0x00FF;

    // ADC3
    modbusTcpByteArray[MB_TCP_REGS + 26]  = (cfgVDCm[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 27]  = cfgVDCm[1] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 28]  = (cfgVDCb[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 29]  = cfgVDCb[1] & 0x00FF;

    // ADC4
    modbusTcpByteArray[MB_TCP_REGS + 30]  = (cfgVDCm[2] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 31]  = cfgVDCm[2] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 32]  = (cfgVDCb[2] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 33]  = cfgVDCb[2] & 0x00FF;

    // ADC5
    modbusTcpByteArray[MB_TCP_REGS + 34]  = (cfgVDCm[3] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 35]  = cfgVDCm[3] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 36]  = (cfgVDCb[3] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 37]  = cfgVDCb[3] & 0x00FF;

    // ADC6
    modbusTcpByteArray[MB_TCP_REGS + 38]  = (cfgVDCm[4] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 39]  = cfgVDCm[4] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 40]  = (cfgVDCb[4] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 41]  = cfgVDCb[4] & 0x00FF;

    // ADC7
    modbusTcpByteArray[MB_TCP_REGS + 42]  = (cfgVDCm[5] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 43]  = cfgVDCm[5] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 44]  = (cfgVDCb[5] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 45]  = cfgVDCb[5] & 0x00FF;

    modbusTcpByteArray[MB_TCP_REGS + 46]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 47]  = cfgCtrSecs[0];
    modbusTcpByteArray[MB_TCP_REGS + 48]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 49]  = cfgCtrSecs[1];
    modbusTcpByteArray[MB_TCP_REGS + 50]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 51]  = cfgCtrSecs[2];
    modbusTcpByteArray[MB_TCP_REGS + 52]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 53]  = cfgCtrSecs[3];
    modbusTcpByteArray[MB_TCP_REGS + 54]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 55]  = cfgCtrSecs[4];
    modbusTcpByteArray[MB_TCP_REGS + 56]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 57]  = cfgCtrSecs[5];
    modbusTcpByteArray[MB_TCP_REGS + 58]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 59]  = cfgCtrSecs[6];
  }
  else if ((addr == MB_HR_ADD_IP) && (nregs == MB_HR_NREG_IP))
  {
    modbusTcpByteArray[MB_TCP_REGS]       = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 1]   = ipMode;
    modbusTcpByteArray[MB_TCP_REGS + 2]   = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 3]   = ipAddress[0];
    modbusTcpByteArray[MB_TCP_REGS + 4]   = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 5]   = ipAddress[1];
    modbusTcpByteArray[MB_TCP_REGS + 6]   = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 7]   = ipAddress[2];
    modbusTcpByteArray[MB_TCP_REGS + 8]   = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 9]   = ipAddress[3];
    modbusTcpByteArray[MB_TCP_REGS + 10]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 11]  = netMask[0];
    modbusTcpByteArray[MB_TCP_REGS + 12]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 13]  = netMask[1];
    modbusTcpByteArray[MB_TCP_REGS + 14]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 15]  = netMask[2];
    modbusTcpByteArray[MB_TCP_REGS + 16]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 17]  = netMask[3];
    modbusTcpByteArray[MB_TCP_REGS + 18]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 19]  = gateWay[0];
    modbusTcpByteArray[MB_TCP_REGS + 20]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 21]  = gateWay[1];
    modbusTcpByteArray[MB_TCP_REGS + 22]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 23]  = gateWay[2];
    modbusTcpByteArray[MB_TCP_REGS + 24]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 25]  = gateWay[3];
    modbusTcpByteArray[MB_TCP_REGS + 26]  = (char)((cfgModbusPORT & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 27]  = (char)(cfgModbusPORT & 0x00FF);
  }
  else if ((addr == MB_HR_ADD_OUTS) && (nregs == MB_HR_NREG_OUTS))
  {
    modbusTcpByteArray[MB_TCP_NBYTES] = (char)((nregs*2) & 0x00FF);

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
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbReadHolding OK");
    #endif
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
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbReadHolding NOK");
    #endif

    modbusTcpClientError++;
    
    // modbusTcpByteArray[MB_TCP_TID]         00
    // modbusTcpByteArray[MB_TCP_TID + 1]     01
    // modbusTcpByteArray[MB_TCP_PID]         02
    // modbusTcpByteArray[MB_TCP_PID + 1]     03
    modbusTcpByteArray[MB_TCP_LEN]     = 0x00;
    modbusTcpByteArray[MB_TCP_LEN + 1] = 0x03;
    // modbusTcpByteArray[MB_TCP_UID]         06
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
  int ctrOutSecs;

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
    modbusTcpByteArray[MB_TCP_NBYTES]      = (char)((nregs*2) & 0x00FF);

    if (ctrInState == IN_STATE0)
    {
      modbusTcpByteArray[MB_TCP_REGS]      = 'E';
      modbusTcpByteArray[MB_TCP_REGS + 1]  = '0';
    }
    else if (ctrInState == IN_STATE1)
    {
      modbusTcpByteArray[MB_TCP_REGS]      = 'E';
      modbusTcpByteArray[MB_TCP_REGS + 1]  = '1';
    }
    else /* ctrInState == IN_STATE2 */
    {
      modbusTcpByteArray[MB_TCP_REGS]      = 'E';
      modbusTcpByteArray[MB_TCP_REGS + 1]  = '2';
    }

    if (ctrOutState == OUT_STATE0)
    {
      modbusTcpByteArray[MB_TCP_REGS + 2]  = 'O';
      modbusTcpByteArray[MB_TCP_REGS + 3]  = '0';
    }
      else if (ctrOutState == OUT_STATE1)
    {
      modbusTcpByteArray[MB_TCP_REGS + 2]  = 'O';
      modbusTcpByteArray[MB_TCP_REGS + 3]  = '1';
    }
    else /* ctrOutState == OUT_STATE2 */
    {
      modbusTcpByteArray[MB_TCP_REGS + 2]  = 'O';
      modbusTcpByteArray[MB_TCP_REGS + 3]  = '2';
    }  

    ctrOutSecs = (int)((millis() - ctrOutTick)/1000);
    modbusTcpByteArray[MB_TCP_REGS + 4]  = (char)((ctrOutSecs & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 5]  = (char)(ctrOutSecs & 0x00FF);
    
    modbusTcpByteArray[MB_TCP_REGS + 6]  = (char)((Ival[0] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 7]  = (char)(Ival[0] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 8]  = (char)((Ival[1] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 9]  = (char)(Ival[1] & 0x00FF);
    
    modbusTcpByteArray[MB_TCP_REGS + 10]  = (char)((Vval[0] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 11]  = (char)(Vval[0] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 12]  = (char)((Vval[1] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 13]  = (char)(Vval[1] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 14]  = (char)((Vval[2] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 15]  = (char)(Vval[2] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 16]  = (char)((Vval[3] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 17]  = (char)(Vval[3] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 18]  = (char)((Vval[4] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 19]  = (char)(Vval[4] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 20]  = (char)((Vval[5] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 21]  = (char)(Vval[5] & 0x00FF);

    modbusTcpByteArray[MB_TCP_REGS + 22] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 23] = InDig[0];
    modbusTcpByteArray[MB_TCP_REGS + 24] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 25] = InDig[1];
    modbusTcpByteArray[MB_TCP_REGS + 26] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 27] = OutDig[0];
    modbusTcpByteArray[MB_TCP_REGS + 28] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 29] = OutDig[1];
    modbusTcpByteArray[MB_TCP_REGS + 30] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 31] = OutDig[2];
    modbusTcpByteArray[MB_TCP_REGS + 32] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 33] = OutDig[3];
    modbusTcpByteArray[MB_TCP_REGS + 34] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 35] = OutDig[4];
    modbusTcpByteArray[MB_TCP_REGS + 36] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 37] = OutDig[5];

    modbusTcpByteArray[MB_TCP_REGS + 38] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 39] = ctrMode;

    modbusTcpByteArray[MB_TCP_REGS + 40]  = (char)((modbusTcpClientError & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 41]  = (char)(modbusTcpClientError & 0x00FF);
  }
  else if ((addr == MB_IR_ADD_INS) && (nregs == MB_IR_NREG_INS))
  {
    modbusTcpByteArray[MB_TCP_NBYTES] = (char)((nregs*2) & 0x00FF);

    for(int i = 0; i < MB_IR_NREG_INS; i++)
    {
      modbusTcpByteArray[MB_TCP_REGS     + i * 2] = 0x00;
      modbusTcpByteArray[MB_TCP_REGS + 1 + i * 2] = InDig[i];
    }
  }
  else if ((addr == MB_IR_ADD_OUTS) && (nregs == MB_IR_NREG_OUTS))
  {
    modbusTcpByteArray[MB_TCP_NBYTES] = (char)((nregs*2) & 0x00FF);

    for(int i = 0; i < MB_IR_NREG_OUTS; i++)
    {
      modbusTcpByteArray[MB_TCP_REGS     + i * 2] = 0x00;
      modbusTcpByteArray[MB_TCP_REGS + 1 + i * 2] = OutDig[i];
    }
  }
  else if ((addr == MB_IR_ADD_ADCS) && (nregs == MB_IR_NREG_ADCS))
  {
    modbusTcpByteArray[MB_TCP_NBYTES] = (char)((nregs*2) & 0x00FF);

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
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbReadInput OK");
    #endif
    
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
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbReadInput NOK");
    #endif

    modbusTcpClientError++;

    // modbusTcpByteArray[MB_TCP_TID]         00
    // modbusTcpByteArray[MB_TCP_TID + 1]     01
    // modbusTcpByteArray[MB_TCP_PID]         02
    // modbusTcpByteArray[MB_TCP_PID + 1]     03
    modbusTcpByteArray[MB_TCP_LEN]     = 0x00;
    modbusTcpByteArray[MB_TCP_LEN + 1] = 0x03;
    // modbusTcpByteArray[MB_TCP_UID]         06
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
  modbusTcpByteArray[MB_TCP_REGS + 3] = compdate[0];   //F
  modbusTcpByteArray[MB_TCP_REGS + 4] = compdate[1];   //e
  modbusTcpByteArray[MB_TCP_REGS + 5] = compdate[2];   //b
  modbusTcpByteArray[MB_TCP_REGS + 6] = compdate[3];   //
  modbusTcpByteArray[MB_TCP_REGS + 7] = compdate[4];   //d
  modbusTcpByteArray[MB_TCP_REGS + 8] = compdate[5];   //d
  modbusTcpByteArray[MB_TCP_REGS + 9] = compdate[6];   //
  modbusTcpByteArray[MB_TCP_REGS + 10] = compdate[7];  //y
  modbusTcpByteArray[MB_TCP_REGS + 11] = compdate[8];  //y
  modbusTcpByteArray[MB_TCP_REGS + 12] = compdate[9];  //y
  modbusTcpByteArray[MB_TCP_REGS + 13] = compdate[10]; //y
  modbusTcpByteArray[MB_TCP_REGS + 14] = 0;
  
  // 10 bytes
  modbusTcpByteArray[MB_TCP_REGS + 15] = comptime[0]; //h
  modbusTcpByteArray[MB_TCP_REGS + 16] = comptime[1]; //h
  modbusTcpByteArray[MB_TCP_REGS + 17] = comptime[2]; //-
  modbusTcpByteArray[MB_TCP_REGS + 18] = comptime[3]; //m
  modbusTcpByteArray[MB_TCP_REGS + 19] = comptime[4]; //m
  modbusTcpByteArray[MB_TCP_REGS + 20] = comptime[5]; //-
  modbusTcpByteArray[MB_TCP_REGS + 21] = comptime[6]; //s
  modbusTcpByteArray[MB_TCP_REGS + 22] = comptime[7]; //s
  modbusTcpByteArray[MB_TCP_REGS + 23] = '0';
  modbusTcpByteArray[MB_TCP_REGS + 24] = '0';

  mbResponseLength = 32;
  modbusTcpStatus = MODBUSTCP_ON_TX;
}

#endif // _USE_MBTCP_
