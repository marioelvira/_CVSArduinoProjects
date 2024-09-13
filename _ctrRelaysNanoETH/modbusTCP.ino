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
  int addr, nregs, value, exception = 0;

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
    cfgIACo[0]  = (int)((modbusTcpByteArray[23] & 0x00FF)<<8)|(modbusTcpByteArray[24] & 0x00FF);
    cfgIDCm[0]  = (int)((modbusTcpByteArray[25] & 0x00FF)<<8)|(modbusTcpByteArray[26] & 0x00FF);
    cfgIDCb[0]  = (int)((modbusTcpByteArray[27] & 0x00FF)<<8)|(modbusTcpByteArray[28] & 0x00FF);
    cfgIlim[0]  = (int)((modbusTcpByteArray[29] & 0x00FF)<<8)|(modbusTcpByteArray[30] & 0x00FF);
    cfgIsec[0]  = (int)((modbusTcpByteArray[31] & 0x00FF)<<8)|(modbusTcpByteArray[32] & 0x00FF);
      
    cfgIType[1] = (int)((modbusTcpByteArray[33] & 0x00FF)<<8)|(modbusTcpByteArray[34] & 0x00FF);
    cfgIACr[1]  = (int)((modbusTcpByteArray[35] & 0x00FF)<<8)|(modbusTcpByteArray[36] & 0x00FF);
    cfgIACo[1]  = (int)((modbusTcpByteArray[37] & 0x00FF)<<8)|(modbusTcpByteArray[38] & 0x00FF);
    cfgIDCm[1]  = (int)((modbusTcpByteArray[39] & 0x00FF)<<8)|(modbusTcpByteArray[40] & 0x00FF);
    cfgIDCb[1]  = (int)((modbusTcpByteArray[41] & 0x00FF)<<8)|(modbusTcpByteArray[42] & 0x00FF);
    cfgIlim[1]  = (int)((modbusTcpByteArray[43] & 0x00FF)<<8)|(modbusTcpByteArray[44] & 0x00FF);
    cfgIsec[1]  = (int)((modbusTcpByteArray[45] & 0x00FF)<<8)|(modbusTcpByteArray[46] & 0x00FF);

    cfgIType[2] = (int)((modbusTcpByteArray[47] & 0x00FF)<<8)|(modbusTcpByteArray[48] & 0x00FF);
    cfgIACr[2]  = (int)((modbusTcpByteArray[49] & 0x00FF)<<8)|(modbusTcpByteArray[50] & 0x00FF);
    cfgIACo[2]  = (int)((modbusTcpByteArray[51] & 0x00FF)<<8)|(modbusTcpByteArray[52] & 0x00FF);
    cfgIDCm[2]  = (int)((modbusTcpByteArray[53] & 0x00FF)<<8)|(modbusTcpByteArray[54] & 0x00FF);
    cfgIDCb[2]  = (int)((modbusTcpByteArray[55] & 0x00FF)<<8)|(modbusTcpByteArray[56] & 0x00FF);
    cfgIlim[2]  = (int)((modbusTcpByteArray[57] & 0x00FF)<<8)|(modbusTcpByteArray[58] & 0x00FF);
    cfgIsec[2]  = (int)((modbusTcpByteArray[59] & 0x00FF)<<8)|(modbusTcpByteArray[60] & 0x00FF);

    cfgIType[3] = (int)((modbusTcpByteArray[61] & 0x00FF)<<8)|(modbusTcpByteArray[62] & 0x00FF);
    cfgIACr[3]  = (int)((modbusTcpByteArray[63] & 0x00FF)<<8)|(modbusTcpByteArray[64] & 0x00FF);
    cfgIACo[3]  = (int)((modbusTcpByteArray[65] & 0x00FF)<<8)|(modbusTcpByteArray[66] & 0x00FF);
    cfgIDCm[3]  = (int)((modbusTcpByteArray[67] & 0x00FF)<<8)|(modbusTcpByteArray[68] & 0x00FF);
    cfgIDCb[3]  = (int)((modbusTcpByteArray[69] & 0x00FF)<<8)|(modbusTcpByteArray[70] & 0x00FF);
    cfgIlim[3]  = (int)((modbusTcpByteArray[71] & 0x00FF)<<8)|(modbusTcpByteArray[72] & 0x00FF);
    cfgIsec[3]  = (int)((modbusTcpByteArray[73] & 0x00FF)<<8)|(modbusTcpByteArray[74] & 0x00FF);

    cfgVDCm[0]  = (int)((modbusTcpByteArray[75] & 0x00FF)<<8)|(modbusTcpByteArray[76] & 0x00FF);
    cfgVDCb[0]  = (int)((modbusTcpByteArray[77] & 0x00FF)<<8)|(modbusTcpByteArray[78] & 0x00FF);

    cfgVDCm[1]  = (int)((modbusTcpByteArray[79] & 0x00FF)<<8)|(modbusTcpByteArray[80] & 0x00FF);
    cfgVDCb[1]  = (int)((modbusTcpByteArray[81] & 0x00FF)<<8)|(modbusTcpByteArray[82] & 0x00FF);

    cfgVDCm[2]  = (int)((modbusTcpByteArray[83] & 0x00FF)<<8)|(modbusTcpByteArray[84] & 0x00FF);
    cfgVDCb[2]  = (int)((modbusTcpByteArray[85] & 0x00FF)<<8)|(modbusTcpByteArray[86] & 0x00FF);

    cfgVDCm[3]  = (int)((modbusTcpByteArray[87] & 0x00FF)<<8)|(modbusTcpByteArray[88] & 0x00FF);
    cfgVDCb[3]  = (int)((modbusTcpByteArray[89] & 0x00FF)<<8)|(modbusTcpByteArray[90] & 0x00FF);

    _ram2eepromCONFIG();
  }
  else if ((addr == MB_HR_ADD_IP) && (nregs == MB_HR_NREG_IP))
  {
    ipMode  = (int)((modbusTcpByteArray[13] & 0x00FF)<<8)|(modbusTcpByteArray[14] & 0x00FF);
    ipAddress[0] = (int)((modbusTcpByteArray[15] & 0x00FF)<<8)|(modbusTcpByteArray[16] & 0x00FF);
    ipAddress[1] = (int)((modbusTcpByteArray[17] & 0x00FF)<<8)|(modbusTcpByteArray[18] & 0x00FF);
    ipAddress[2] = (int)((modbusTcpByteArray[19] & 0x00FF)<<8)|(modbusTcpByteArray[20] & 0x00FF);
    ipAddress[3] = (int)((modbusTcpByteArray[21] & 0x00FF)<<8)|(modbusTcpByteArray[22] & 0x00FF);
    gateWay[0]   = (int)((modbusTcpByteArray[23] & 0x00FF)<<8)|(modbusTcpByteArray[24] & 0x00FF);
    gateWay[1]   = (int)((modbusTcpByteArray[25] & 0x00FF)<<8)|(modbusTcpByteArray[26] & 0x00FF);
    gateWay[2]   = (int)((modbusTcpByteArray[27] & 0x00FF)<<8)|(modbusTcpByteArray[28] & 0x00FF);
    gateWay[3]   = (int)((modbusTcpByteArray[29] & 0x00FF)<<8)|(modbusTcpByteArray[30] & 0x00FF);
    netMask[0]   = (int)((modbusTcpByteArray[31] & 0x00FF)<<8)|(modbusTcpByteArray[32] & 0x00FF);
    netMask[1]   = (int)((modbusTcpByteArray[33] & 0x00FF)<<8)|(modbusTcpByteArray[34] & 0x00FF);
    netMask[2]   = (int)((modbusTcpByteArray[35] & 0x00FF)<<8)|(modbusTcpByteArray[36] & 0x00FF);
    netMask[3]   = (int)((modbusTcpByteArray[37] & 0x00FF)<<8)|(modbusTcpByteArray[38] & 0x00FF);

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
    // modbusTcpByteArray[MB_TCP_TID]         00
    // modbusTcpByteArray[MB_TCP_TID + 1]     01
    // modbusTcpByteArray[MB_TCP_PID]         02
    // modbusTcpByteArray[MB_TCP_PID + 1]     03
    modbusTcpByteArray[MB_TCP_LEN]     = ((nregs + 3) & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_LEN + 1] = (nregs + 3) & 0x00FF;
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
	  modbusTcpByteArray[MB_TCP_FUNC] = (char)(MB_FUNC_WRITE_MULTIPLE_REGISTERS | MB_NACK);
    modbusTcpByteArray[MB_TCP_NBYTES] = MB_EC_ILLEGAL_DATA_ADDRESS;

    // Num Bytes
    mbResponseLength = 9;
  }

  modbusTcpStatus = MODBUSTCP_ON_TX;
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
    modbusTcpByteArray[MB_TCP_REGS + 10]  = (cfgIACo[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 11]  = cfgIACo[0] & 0x00FF;

    modbusTcpByteArray[MB_TCP_REGS + 12]  = (cfgIDCm[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 13]  = cfgIDCm[0] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 14]  = (cfgIDCb[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 15]  = cfgIDCb[0] & 0x00FF;

    modbusTcpByteArray[MB_TCP_REGS + 16]  = (cfgIlim[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 17]  = cfgIlim[0] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 18]  = (cfgIsec[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 19]  = cfgIsec[0] & 0x00FF;

    // ADC1
    modbusTcpByteArray[MB_TCP_REGS + 20]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 21]  = cfgIType[1];

    modbusTcpByteArray[MB_TCP_REGS + 22]  = (cfgIACr[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 23]  = cfgIACr[1] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 24]  = (cfgIACo[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 25]  = cfgIACo[1] & 0x00FF;

    modbusTcpByteArray[MB_TCP_REGS + 26]  = (cfgIDCm[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 27]  = cfgIDCm[1] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 28]  = (cfgIDCb[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 29]  = cfgIDCb[1] & 0x00FF;

    modbusTcpByteArray[MB_TCP_REGS + 30]  = (cfgIlim[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 31]  = cfgIlim[1] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 32]  = (cfgIsec[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 33]  = cfgIsec[1] & 0x00FF;
  
    // ADC2
    modbusTcpByteArray[MB_TCP_REGS + 34]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 35]  = cfgIType[2];

    modbusTcpByteArray[MB_TCP_REGS + 36]  = (cfgIACr[2] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 37]  = cfgIACr[2] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 38]  = (cfgIACo[2] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 39]  = cfgIACo[2] & 0x00FF;

    modbusTcpByteArray[MB_TCP_REGS + 40]  = (cfgIDCm[2] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 41]  = cfgIDCm[2] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 42]  = (cfgIDCb[2] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 43]  = cfgIDCb[2] & 0x00FF;

    modbusTcpByteArray[MB_TCP_REGS + 44]  = (cfgIlim[2] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 45]  = cfgIlim[2] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 46]  = (cfgIsec[2] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 47]  = cfgIsec[2] & 0x00FF;

    // ADC3
    modbusTcpByteArray[MB_TCP_REGS + 48]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 49]  = cfgIType[3];

    modbusTcpByteArray[MB_TCP_REGS + 50]  = (cfgIACr[3] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 51]  = cfgIACr[3] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 52]  = (cfgIACo[3] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 53]  = cfgIACo[3] & 0x00FF;

    modbusTcpByteArray[MB_TCP_REGS + 54]  = (cfgIDCm[3] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 55]  = cfgIDCm[3] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 56]  = (cfgIDCb[3] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 57]  = cfgIDCb[3] & 0x00FF;

    modbusTcpByteArray[MB_TCP_REGS + 58]  = (cfgIlim[3] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 59]  = cfgIlim[3] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 60]  = (cfgIsec[3] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 61]  = cfgIsec[3] & 0x00FF;

    // ADC4
    modbusTcpByteArray[MB_TCP_REGS + 62]  = (cfgVDCm[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 63]  = cfgVDCm[0] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 64]  = (cfgVDCb[0] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 65]  = cfgVDCb[0] & 0x00FF;

    // ADC5
    modbusTcpByteArray[MB_TCP_REGS + 66]  = (cfgVDCm[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 67]  = cfgVDCm[1] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 68]  = (cfgVDCb[1] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 69]  = cfgVDCb[1] & 0x00FF;

    // ADC6
    modbusTcpByteArray[MB_TCP_REGS + 70]  = (cfgVDCm[2] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 71]  = cfgVDCm[2] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 72]  = (cfgVDCb[2] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 73]  = cfgVDCb[2] & 0x00FF;

    // ADC7
    modbusTcpByteArray[MB_TCP_REGS + 74]  = (cfgVDCm[3] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 75]  = cfgVDCm[3] & 0x00FF;
    modbusTcpByteArray[MB_TCP_REGS + 76]  = (cfgVDCb[3] & 0xFF00)>>8;
    modbusTcpByteArray[MB_TCP_REGS + 77]  = cfgVDCb[3] & 0x00FF;
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
    modbusTcpByteArray[MB_TCP_REGS + 11]  = gateWay[0];
    modbusTcpByteArray[MB_TCP_REGS + 12]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 13]  = gateWay[1];
    modbusTcpByteArray[MB_TCP_REGS + 14]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 15]  = gateWay[2];
    modbusTcpByteArray[MB_TCP_REGS + 16]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 17]  = gateWay[3];
    modbusTcpByteArray[MB_TCP_REGS + 18]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 19]  = netMask[0];
    modbusTcpByteArray[MB_TCP_REGS + 20]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 21]  = netMask[1];
    modbusTcpByteArray[MB_TCP_REGS + 22]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 23]  = netMask[2];
    modbusTcpByteArray[MB_TCP_REGS + 24]  = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 25]  = netMask[3];
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
    modbusTcpByteArray[MB_TCP_REGS + 2]  = (char)((Ival[0] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 3]  = (char)(Ival[0] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 4]  = (char)((Ival[1] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 5]  = (char)(Ival[1] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 6]  = (char)((Ival[2] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 7]  = (char)(Ival[2] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 8]  = (char)((Ival[3] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 9]  = (char)(Ival[3] & 0x00FF);
    
    modbusTcpByteArray[MB_TCP_REGS + 10]  = (char)((Vval[0] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 11]  = (char)(Vval[0] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 12]  = (char)((Vval[1] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 13]  = (char)(Vval[1] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 14]  = (char)((Vval[2] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 15]  = (char)(Vval[2] & 0x00FF);
    modbusTcpByteArray[MB_TCP_REGS + 16]  = (char)((Vval[3] & 0xFF00)>>8);
    modbusTcpByteArray[MB_TCP_REGS + 17]  = (char)(Vval[3] & 0x00FF);

    modbusTcpByteArray[MB_TCP_REGS + 18] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 19] = InDig[0];
    modbusTcpByteArray[MB_TCP_REGS + 20] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 21] = InDig[1];
    modbusTcpByteArray[MB_TCP_REGS + 22] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 23] = OutDig[0];
    modbusTcpByteArray[MB_TCP_REGS + 24] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 25] = OutDig[1];
    modbusTcpByteArray[MB_TCP_REGS + 26] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 27] = OutDig[2];
    modbusTcpByteArray[MB_TCP_REGS + 28] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 29] = OutDig[3];
    modbusTcpByteArray[MB_TCP_REGS + 30] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 31] = OutDig[4];
    modbusTcpByteArray[MB_TCP_REGS + 32] = 0x00;
    modbusTcpByteArray[MB_TCP_REGS + 33] = OutDig[5];
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
