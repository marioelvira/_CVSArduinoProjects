#include "main.h"

#if (_USE_MBTCP_ == 1)

void _ModbusTcpSetup(void)
{
  mbTcpServerStatus = MB_SERVER_INIT;

  mbTcpClientStatus = MB_CLIENT_INIT;
  mbTcpClientConnected = false;

  mbTcpRxIndex = 0;
  mbTcpRxTick = millis();
}

void _ModbusTcpLoop()
{ 
  switch (mbTcpServerStatus)
  {
    case MB_SERVER_INIT:
      mbTcpServer.begin(cfgModbusPORT);

      #if (_MBTCP_SERIAL_DEBUG_ == 1)
      Serial.println("Modbus TCP server started");
      #endif
      mbTcpServerStatus = MB_SERVER_ON;
      break;

    case MB_SERVER_ON:
      _mbClientLoop();
      break;
  }
}

void _mbClientLoop ()
{
  //#if (_MBTCP_SERIAL_DEBUG_ == 1)
  //Serial.print("Modbuds tcp State "); Serial.print(mbTcpClientStatus); Serial.println(" ***");
  //#endif

  switch (mbTcpClientStatus)
  {
    case MB_CLIENT_INIT:
      mbTcpClient = mbTcpServer.available();
      if (mbTcpClient)
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.print("Status "); Serial.print(mbTcpClientStatus); Serial.println(" ---");
        #endif

        mbTcpClientStatus = MB_CLIENT_CONNECTED;
        mbTcpClientConnected = true;
        mbTcpRxIndex = 0;
        mbTcpRxTick = millis();
      }
      break;

    case MB_CLIENT_CONNECTED:
      // Client connected....
      if (mbTcpClient.connected())
      {
        if (mbTcpClient.available())
        {
          #if (_MBTCP_SERIAL_DEBUG_ == 1)
          Serial.print("Modbus tcp client request.");
          #endif

          mbTcpFunc = MB_FUNC_NONE;
          mbTcpClientStatus = MB_CLIENT_ON_RX;
          mbTcpRxTick = millis();
          mbTcpRxIndex = 0;
        }
        else
        {
          // Time out no RX...
          if (millis() - mbTcpRxTick >= MB_CONNECTION_TIMEOUT)
          {
            #if (_MBTCP_SERIAL_DEBUG_ == 1)
            Serial.print("Modbus tcp client timeout no RX.");
            #endif
            mbTcpClientStatus = MB_CLIENT_INIT;
            mbTcpClientConnected = false;
          }
        }
      }
      // Client time out disconnected...
      else
      {
        if (millis() - mbTcpRxTick >= MB_CONNECTION_TIMEOUT)
        {
          #if (_MBTCP_SERIAL_DEBUG_ == 1)
          Serial.print("Modbus tcp client timeout disconnected.");
          #endif
          mbTcpClientStatus = MB_CLIENT_INIT;
          mbTcpClientConnected = false;
        }
      }
      break;

    case MB_CLIENT_ON_RX:
      // Client connected...
      if (mbTcpClient.connected())
      {
        if (mbTcpClient.available())
        {
          char newChar = mbTcpClient.read();
          #if (_MBTCP_SERIAL_DEBUG_ == 1)
          Serial.print (newChar < 16 ? "0" : "");
          Serial.print (newChar, HEX);
          #endif

          mbTcpRxArray[mbTcpRxIndex] = newChar;
          mbTcpRxIndex++;
          mbTcpRxTick = millis();
        }
        else
        {
          // RX Time out...
          if (millis() - mbTcpRxTick >= MB_RX_TIMEOUT)
          {
             #if (_MBTCP_SERIAL_DEBUG_ == 1)
             Serial.println (".");
             #endif

             mbTcpClient.flush();
            
             mbTcpFunc = mbTcpRxArray[MB_TCP_FUNC];
             mbTcpClientStatus = MB_CLIENT_ON_ANALYSIS;
          }
        }
      }
      // Client disconnected...
      else
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.print("Modbus tcp client disconnected.");
        #endif
        mbTcpClientStatus = MB_CLIENT_INIT;
        mbTcpClientConnected = false;
      }
      break;
    
    case MB_CLIENT_ON_ANALYSIS:

      // Client connected...
      if (mbTcpClient.connected())
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.print("Function: ");
        Serial.println(mbTcpFunc);
        #endif

        switch(mbTcpFunc)
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
            mbTcpClientStatus = MB_CLIENT_CONNECTED;
            break;
        }
      }
      // Client disconnected...
      else
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.print("Modbus tcp client disconnected.");
        #endif
        mbTcpClientStatus = MB_CLIENT_INIT;
        mbTcpClientConnected = false;
      }  
      break;
      
    case MB_CLIENT_ON_TX:

      mbTcpClient.flush();

      #if (_MBTCP_SERIAL_DEBUG_ == 1)
      Serial.print("Modbus tcp client response ");
      Serial.println(mbTcpTxLength);
      for (int i = 0; i< mbTcpTxLength; i++)
      {
        Serial.print (mbTcpTxArray[i] < 16 ? "0" : "");
        Serial.print (mbTcpTxArray[i], HEX);
      }
      Serial.println (" ");
      #endif

      mbTcpClient.write((const uint8_t *)mbTcpTxArray, mbTcpTxLength);

      mbTcpClientStatus = MB_CLIENT_CONNECTED;
      mbTcpRxIndex = 0;
      mbTcpRxTick = millis();

      break;
  }
}

void _mbWriteMultipleHolding()
{
  int i, addr, nregs, value, exception = 0;

  addr  = (int)word(mbTcpRxArray[MB_TCP_REGS_ADD], mbTcpRxArray[MB_TCP_REGS_ADD + 1]);
  nregs = (int)word(mbTcpRxArray[MB_TCP_REGS_NUM], mbTcpRxArray[MB_TCP_REGS_NUM + 1]);

  #if (_MBTCP_SERIAL_DEBUG_ == 1)
  Serial.print(F("addr: "));
  Serial.print(addr);
  Serial.print(F(", nregs: "));
  Serial.println(nregs);
  #endif

  if ((addr == MB_HR_ADD_CFG) && (nregs == MB_HR_NREG_CFG))
  {
    value = (int)((mbTcpRxArray[13] & 0x00FF)<<8)|(mbTcpRxArray[14] & 0x00FF);
    if (value == MODE_AUTO)
      ctrMode = MODE_AUTO;
    else
      ctrMode = MODE_TEST;
    
    value  = (int)((mbTcpRxArray[15] & 0x00FF)<<8)|(mbTcpRxArray[16] & 0x00FF);
    if (value == IN_OFF)
      cfgLogicIns = IN_OFF;
    else 
      cfgLogicIns = IN_ON;
      
    value = (int)((mbTcpRxArray[17] & 0x00FF)<<8)|(mbTcpRxArray[18] & 0x00FF);
    if (value == OUT_OFF)
      cfgLogicOuts = OUT_OFF;
    else 
      cfgLogicOuts = OUT_ON;

    cfgIType[0] = (int)((mbTcpRxArray[19] & 0x00FF)<<8)|(mbTcpRxArray[20] & 0x00FF);
    cfgIACr[0]  = (int)((mbTcpRxArray[21] & 0x00FF)<<8)|(mbTcpRxArray[22] & 0x00FF);
    cfgIlim[0]  = (int)((mbTcpRxArray[23] & 0x00FF)<<8)|(mbTcpRxArray[24] & 0x00FF);
    cfgIsec[0]  = (int)((mbTcpRxArray[25] & 0x00FF)<<8)|(mbTcpRxArray[26] & 0x00FF);
  
    cfgIType[1] = (int)((mbTcpRxArray[27] & 0x00FF)<<8)|(mbTcpRxArray[28] & 0x00FF);
    cfgIACr[1]  = (int)((mbTcpRxArray[29] & 0x00FF)<<8)|(mbTcpRxArray[30] & 0x00FF);
    cfgIlim[1]  = (int)((mbTcpRxArray[31] & 0x00FF)<<8)|(mbTcpRxArray[32] & 0x00FF);
    cfgIsec[1]  = (int)((mbTcpRxArray[33] & 0x00FF)<<8)|(mbTcpRxArray[34] & 0x00FF);

    cfgVDCm[0]  = (int)((mbTcpRxArray[35] & 0x00FF)<<8)|(mbTcpRxArray[36] & 0x00FF);
    cfgVDCb[0]  = (int)((mbTcpRxArray[37] & 0x00FF)<<8)|(mbTcpRxArray[38] & 0x00FF);

    cfgVDCm[1]  = (int)((mbTcpRxArray[39] & 0x00FF)<<8)|(mbTcpRxArray[40] & 0x00FF);
    cfgVDCb[1]  = (int)((mbTcpRxArray[41] & 0x00FF)<<8)|(mbTcpRxArray[42] & 0x00FF);

    cfgVDCm[2]  = (int)((mbTcpRxArray[43] & 0x00FF)<<8)|(mbTcpRxArray[44] & 0x00FF);
    cfgVDCb[2]  = (int)((mbTcpRxArray[45] & 0x00FF)<<8)|(mbTcpRxArray[46] & 0x00FF);

    cfgVDCm[3]  = (int)((mbTcpRxArray[47] & 0x00FF)<<8)|(mbTcpRxArray[48] & 0x00FF);
    cfgVDCb[3]  = (int)((mbTcpRxArray[49] & 0x00FF)<<8)|(mbTcpRxArray[50] & 0x00FF);

    cfgVDCm[4]  = (int)((mbTcpRxArray[51] & 0x00FF)<<8)|(mbTcpRxArray[52] & 0x00FF);
    cfgVDCb[4]  = (int)((mbTcpRxArray[53] & 0x00FF)<<8)|(mbTcpRxArray[54] & 0x00FF);

    cfgVDCm[5]  = (int)((mbTcpRxArray[55] & 0x00FF)<<8)|(mbTcpRxArray[56] & 0x00FF);
    cfgVDCb[5]  = (int)((mbTcpRxArray[57] & 0x00FF)<<8)|(mbTcpRxArray[58] & 0x00FF);

    cfgCtrSecs[0] = (int)((mbTcpRxArray[59] & 0x00FF)<<8)|(mbTcpRxArray[60] & 0x00FF);
    cfgCtrSecs[1] = (int)((mbTcpRxArray[61] & 0x00FF)<<8)|(mbTcpRxArray[62] & 0x00FF);
    cfgCtrSecs[2] = (int)((mbTcpRxArray[63] & 0x00FF)<<8)|(mbTcpRxArray[64] & 0x00FF);
    cfgCtrSecs[3] = (int)((mbTcpRxArray[65] & 0x00FF)<<8)|(mbTcpRxArray[66] & 0x00FF);
    cfgCtrSecs[4] = (int)((mbTcpRxArray[67] & 0x00FF)<<8)|(mbTcpRxArray[68] & 0x00FF);
    cfgCtrSecs[5] = (int)((mbTcpRxArray[69] & 0x00FF)<<8)|(mbTcpRxArray[70] & 0x00FF);
    cfgCtrSecs[6] = (int)((mbTcpRxArray[71] & 0x00FF)<<8)|(mbTcpRxArray[72] & 0x00FF);

    _ram2eepromCONFIG();
  }
  else if ((addr == MB_HR_ADD_IP) && (nregs == MB_HR_NREG_IP))
  {
    ipMode        = (int)((mbTcpRxArray[13] & 0x00FF)<<8)|(mbTcpRxArray[14] & 0x00FF);
    ipAddress[0]  = (int)((mbTcpRxArray[15] & 0x00FF)<<8)|(mbTcpRxArray[16] & 0x00FF);
    ipAddress[1]  = (int)((mbTcpRxArray[17] & 0x00FF)<<8)|(mbTcpRxArray[18] & 0x00FF);
    ipAddress[2]  = (int)((mbTcpRxArray[19] & 0x00FF)<<8)|(mbTcpRxArray[20] & 0x00FF);
    ipAddress[3]  = (int)((mbTcpRxArray[21] & 0x00FF)<<8)|(mbTcpRxArray[22] & 0x00FF);
    netMask[0]    = (int)((mbTcpRxArray[23] & 0x00FF)<<8)|(mbTcpRxArray[24] & 0x00FF);
    netMask[1]    = (int)((mbTcpRxArray[25] & 0x00FF)<<8)|(mbTcpRxArray[26] & 0x00FF);
    netMask[2]    = (int)((mbTcpRxArray[27] & 0x00FF)<<8)|(mbTcpRxArray[28] & 0x00FF);
    netMask[3]    = (int)((mbTcpRxArray[29] & 0x00FF)<<8)|(mbTcpRxArray[30] & 0x00FF);
    gateWay[0]    = (int)((mbTcpRxArray[31] & 0x00FF)<<8)|(mbTcpRxArray[32] & 0x00FF);
    gateWay[1]    = (int)((mbTcpRxArray[33] & 0x00FF)<<8)|(mbTcpRxArray[34] & 0x00FF);
    gateWay[2]    = (int)((mbTcpRxArray[35] & 0x00FF)<<8)|(mbTcpRxArray[36] & 0x00FF);
    gateWay[3]    = (int)((mbTcpRxArray[37] & 0x00FF)<<8)|(mbTcpRxArray[38] & 0x00FF);
    cfgModbusPORT = (int)((mbTcpRxArray[39] & 0x00FF)<<8)|(mbTcpRxArray[40] & 0x00FF);

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
        value = (int)((mbTcpRxArray[i*2 + 13] & 0x00FF)<<8)|(mbTcpRxArray[i*2 + 14] & 0x00FF);
        if (value == OUT_OFF)
          OutDig[i] = OUT_OFF;
        else
          OutDig[i] = OUT_ON;
      }
    }
  }
  #if (_USE_WDE_ == 1)
  else if ((addr == MB_HR_ADD_WD) && (nregs == MB_HR_NREG_WD))
  {
    wdeForceReset = (int)((mbTcpRxArray[13] & 0x00FF)<<8)|(mbTcpRxArray[14] & 0x00FF);
  }
  #endif
  else
    exception = 1;

  if (exception == 0)
  {
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbWriteMultipleHolding OK");
    #endif

    mbTcpTxArray[MB_TCP_TID]     = mbTcpRxArray[MB_TCP_TID];         //00
    mbTcpTxArray[MB_TCP_TID + 1] = mbTcpRxArray[MB_TCP_TID + 1];     //01
    mbTcpTxArray[MB_TCP_PID]     = mbTcpRxArray[MB_TCP_PID];         //02
    mbTcpTxArray[MB_TCP_PID + 1] = mbTcpRxArray[MB_TCP_PID + 1];     //03
    mbTcpTxArray[MB_TCP_LEN]     = 0x00;                             //04
    mbTcpTxArray[MB_TCP_LEN + 1] = 0x06;                             //05
    mbTcpTxArray[MB_TCP_UID]     = mbTcpRxArray[MB_TCP_UID];         //06
    mbTcpTxArray[MB_TCP_FUNC]    = (char)(MB_FUNC_WRITE_MULTIPLE_REGISTERS); //07
    mbTcpTxArray[MB_TCP_REGS_ADD]     = (addr & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS_ADD + 1] = addr & 0x00FF;
    mbTcpTxArray[MB_TCP_REGS_NUM]     = (nregs & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS_NUM + 1] = nregs & 0x00FF;

    // Num Bytes
    mbTcpTxLength = 12;
  }
  else
  {
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbWriteMultipleHolding NOK");
    #endif

    mbTcpRxError++;

    mbTcpTxArray[MB_TCP_TID]     = mbTcpRxArray[MB_TCP_TID];     //00
    mbTcpTxArray[MB_TCP_TID + 1] = mbTcpRxArray[MB_TCP_TID + 1]; //01
    mbTcpTxArray[MB_TCP_PID]     = mbTcpRxArray[MB_TCP_PID];     //02
    mbTcpTxArray[MB_TCP_PID + 1] = mbTcpRxArray[MB_TCP_PID + 1]; //03
    mbTcpTxArray[MB_TCP_LEN]     = 0x00;                         //04
    mbTcpTxArray[MB_TCP_LEN + 1] = 0x03;                         //05
    mbTcpTxArray[MB_TCP_UID]     = mbTcpRxArray[MB_TCP_UID];     //06
	  mbTcpTxArray[MB_TCP_FUNC] = (char)(MB_FUNC_WRITE_MULTIPLE_REGISTERS | MB_NACK);
    mbTcpTxArray[MB_TCP_NBYTES] = MB_EC_ILLEGAL_DATA_ADDRESS;

    // Num Bytes
    mbTcpTxLength = 9;
  }

  mbTcpClientStatus = MB_CLIENT_ON_TX;
}

void _mbReadHolding()
{
  int i, addr, nregs, exception = 0;

  addr  = (int)word(mbTcpRxArray[MB_TCP_REGS_ADD], mbTcpRxArray[MB_TCP_REGS_ADD + 1]);
  nregs = (int)word(mbTcpRxArray[MB_TCP_REGS_NUM], mbTcpRxArray[MB_TCP_REGS_NUM + 1]);

  #if (_MBTCP_SERIAL_DEBUG_ == 1)
  Serial.print(F("addr: "));
  Serial.print(addr);
  Serial.print(F(", nregs: "));
  Serial.println(nregs);
  #endif

  if ((addr == MB_HR_ADD_CFG) && (nregs == MB_HR_NREG_CFG))
  {
    mbTcpTxArray[MB_TCP_REGS]       = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 1]   = ctrMode;
    mbTcpTxArray[MB_TCP_REGS + 2]   = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 3]   = cfgLogicIns;
    mbTcpTxArray[MB_TCP_REGS + 4]   = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 5]   = cfgLogicOuts;

    // ADC0
    mbTcpTxArray[MB_TCP_REGS + 6]   = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 7]   = cfgIType[0];

    mbTcpTxArray[MB_TCP_REGS + 8]   = (cfgIACr[0] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 9]   = cfgIACr[0] & 0x00FF;
    mbTcpTxArray[MB_TCP_REGS + 10]  = (cfgIlim[0] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 11]  = cfgIlim[0] & 0x00FF;
    mbTcpTxArray[MB_TCP_REGS + 12]  = (cfgIsec[0] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 13]  = cfgIsec[0] & 0x00FF;

    // ADC1
    mbTcpTxArray[MB_TCP_REGS + 14]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 15]  = cfgIType[1];

    mbTcpTxArray[MB_TCP_REGS + 16]  = (cfgIACr[1] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 17]  = cfgIACr[1] & 0x00FF;
    mbTcpTxArray[MB_TCP_REGS + 18]  = (cfgIlim[1] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 19]  = cfgIlim[1] & 0x00FF;
    mbTcpTxArray[MB_TCP_REGS + 20]  = (cfgIsec[1] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 21]  = cfgIsec[1] & 0x00FF;

    // ADC2
    mbTcpTxArray[MB_TCP_REGS + 22]  = (cfgVDCm[0] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 23]  = cfgVDCm[0] & 0x00FF;
    mbTcpTxArray[MB_TCP_REGS + 24]  = (cfgVDCb[0] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 25]  = cfgVDCb[0] & 0x00FF;

    // ADC3
    mbTcpTxArray[MB_TCP_REGS + 26]  = (cfgVDCm[1] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 27]  = cfgVDCm[1] & 0x00FF;
    mbTcpTxArray[MB_TCP_REGS + 28]  = (cfgVDCb[1] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 29]  = cfgVDCb[1] & 0x00FF;

    // ADC4
    mbTcpTxArray[MB_TCP_REGS + 30]  = (cfgVDCm[2] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 31]  = cfgVDCm[2] & 0x00FF;
    mbTcpTxArray[MB_TCP_REGS + 32]  = (cfgVDCb[2] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 33]  = cfgVDCb[2] & 0x00FF;

    // ADC5
    mbTcpTxArray[MB_TCP_REGS + 34]  = (cfgVDCm[3] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 35]  = cfgVDCm[3] & 0x00FF;
    mbTcpTxArray[MB_TCP_REGS + 36]  = (cfgVDCb[3] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 37]  = cfgVDCb[3] & 0x00FF;

    // ADC6
    mbTcpTxArray[MB_TCP_REGS + 38]  = (cfgVDCm[4] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 39]  = cfgVDCm[4] & 0x00FF;
    mbTcpTxArray[MB_TCP_REGS + 40]  = (cfgVDCb[4] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 41]  = cfgVDCb[4] & 0x00FF;

    // ADC7
    mbTcpTxArray[MB_TCP_REGS + 42]  = (cfgVDCm[5] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 43]  = cfgVDCm[5] & 0x00FF;
    mbTcpTxArray[MB_TCP_REGS + 44]  = (cfgVDCb[5] & 0xFF00)>>8;
    mbTcpTxArray[MB_TCP_REGS + 45]  = cfgVDCb[5] & 0x00FF;

    mbTcpTxArray[MB_TCP_REGS + 46]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 47]  = cfgCtrSecs[0];
    mbTcpTxArray[MB_TCP_REGS + 48]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 49]  = cfgCtrSecs[1];
    mbTcpTxArray[MB_TCP_REGS + 50]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 51]  = cfgCtrSecs[2];
    mbTcpTxArray[MB_TCP_REGS + 52]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 53]  = cfgCtrSecs[3];
    mbTcpTxArray[MB_TCP_REGS + 54]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 55]  = cfgCtrSecs[4];
    mbTcpTxArray[MB_TCP_REGS + 56]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 57]  = cfgCtrSecs[5];
    mbTcpTxArray[MB_TCP_REGS + 58]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 59]  = cfgCtrSecs[6];
  }
  else if ((addr == MB_HR_ADD_IP) && (nregs == MB_HR_NREG_IP))
  {
    mbTcpTxArray[MB_TCP_REGS]       = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 1]   = ipMode;
    mbTcpTxArray[MB_TCP_REGS + 2]   = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 3]   = ipAddress[0];
    mbTcpTxArray[MB_TCP_REGS + 4]   = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 5]   = ipAddress[1];
    mbTcpTxArray[MB_TCP_REGS + 6]   = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 7]   = ipAddress[2];
    mbTcpTxArray[MB_TCP_REGS + 8]   = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 9]   = ipAddress[3];
    mbTcpTxArray[MB_TCP_REGS + 10]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 11]  = netMask[0];
    mbTcpTxArray[MB_TCP_REGS + 12]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 13]  = netMask[1];
    mbTcpTxArray[MB_TCP_REGS + 14]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 15]  = netMask[2];
    mbTcpTxArray[MB_TCP_REGS + 16]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 17]  = netMask[3];
    mbTcpTxArray[MB_TCP_REGS + 18]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 19]  = gateWay[0];
    mbTcpTxArray[MB_TCP_REGS + 20]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 21]  = gateWay[1];
    mbTcpTxArray[MB_TCP_REGS + 22]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 23]  = gateWay[2];
    mbTcpTxArray[MB_TCP_REGS + 24]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 25]  = gateWay[3];
    mbTcpTxArray[MB_TCP_REGS + 26]  = (char)((cfgModbusPORT & 0xFF00)>>8);
    mbTcpTxArray[MB_TCP_REGS + 27]  = (char)(cfgModbusPORT & 0x00FF);
  }
  else if ((addr == MB_HR_ADD_OUTS) && (nregs == MB_HR_NREG_OUTS))
  {
    mbTcpTxArray[MB_TCP_NBYTES] = (char)((nregs*2) & 0x00FF);

    for(int i = 0; i < MB_HR_NREG_OUTS; i++)
    {
      mbTcpTxArray[MB_TCP_REGS     + i * 2] = 0x00;
      mbTcpTxArray[MB_TCP_REGS + 1 + i * 2] = OutDig[i];
    }
  }
  #if (_USE_WDE_ == 1)
  else if ((addr == MB_HR_ADD_WD) && (nregs == MB_HR_NREG_WD))
  {
    mbTcpTxArray[MB_TCP_REGS]       = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 1]   = wdeForceReset;
  }
  #endif
  else
    exception = 1;

  if (exception == 0)
  {
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbReadHolding OK");
    #endif

    mbTcpTxArray[MB_TCP_TID]     = mbTcpRxArray[MB_TCP_TID];     //00
    mbTcpTxArray[MB_TCP_TID + 1] = mbTcpRxArray[MB_TCP_TID + 1]; //01
    mbTcpTxArray[MB_TCP_PID]     = mbTcpRxArray[MB_TCP_PID];     //02
    mbTcpTxArray[MB_TCP_PID + 1] = mbTcpRxArray[MB_TCP_PID + 1]; //03
    mbTcpTxArray[MB_TCP_LEN]     = ((nregs + 3) & 0xFF00)>>8;    //04
    mbTcpTxArray[MB_TCP_LEN + 1] = (nregs + 3) & 0x00FF;         //05
    mbTcpTxArray[MB_TCP_UID]     = mbTcpRxArray[MB_TCP_UID];     //06
    mbTcpTxArray[MB_TCP_FUNC] = (char)(MB_FUNC_READ_HOLDING_REGISTER);

    // Num Bytes
    mbTcpTxLength = nregs*2 + 9;
  }
  else
  {
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbReadHolding NOK");
    #endif

    mbTcpRxError++;
    
    mbTcpTxArray[MB_TCP_TID]     = mbTcpRxArray[MB_TCP_TID];     //00
    mbTcpTxArray[MB_TCP_TID + 1] = mbTcpRxArray[MB_TCP_TID + 1]; //01
    mbTcpTxArray[MB_TCP_PID]     = mbTcpRxArray[MB_TCP_PID];     //02
    mbTcpTxArray[MB_TCP_PID + 1] = mbTcpRxArray[MB_TCP_PID + 1]; //03
    mbTcpTxArray[MB_TCP_LEN]     = 0x00;                         //04
    mbTcpTxArray[MB_TCP_LEN + 1] = 0x03;                         //05
    mbTcpTxArray[MB_TCP_UID]     = mbTcpRxArray[MB_TCP_UID];     //06
	  mbTcpTxArray[MB_TCP_FUNC] = (char)(MB_FUNC_READ_HOLDING_REGISTER | MB_NACK);
    mbTcpTxArray[MB_TCP_NBYTES] = MB_EC_ILLEGAL_DATA_ADDRESS;

    // Num Bytes
    mbTcpTxLength = 9;
  }

  mbTcpClientStatus = MB_CLIENT_ON_TX;
}

void _mbReadInput()
{
  int addr, nregs, exception = 0;
  int ctrOutSecs;

  addr  = (int)word(mbTcpRxArray[MB_TCP_REGS_ADD], mbTcpRxArray[MB_TCP_REGS_ADD + 1]);
  nregs = (int)word(mbTcpRxArray[MB_TCP_REGS_NUM], mbTcpRxArray[MB_TCP_REGS_NUM + 1]);
  
  #if (_MBTCP_SERIAL_DEBUG_ == 1)
  Serial.print("addr: ");
  Serial.print(addr);
  Serial.print(", nregs: ");
  Serial.println(nregs);
  #endif

  if ((addr == MB_IR_ADD_ONLINE) && (nregs == MB_IR_NREG_ONLINE))
  {
    mbTcpTxArray[MB_TCP_NBYTES]      = (char)((nregs*2) & 0x00FF);

    if (ctrInState == IN_STATE0)
    {
      mbTcpTxArray[MB_TCP_REGS]      = 'E';
      mbTcpTxArray[MB_TCP_REGS + 1]  = '0';
    }
    else if (ctrInState == IN_STATE1)
    {
      mbTcpTxArray[MB_TCP_REGS]      = 'E';
      mbTcpTxArray[MB_TCP_REGS + 1]  = '1';
    }
    else /* ctrInState == IN_STATE2 */
    {
      mbTcpTxArray[MB_TCP_REGS]      = 'E';
      mbTcpTxArray[MB_TCP_REGS + 1]  = '2';
    }

    if (ctrOutState == OUT_STATE0)
    {
      mbTcpTxArray[MB_TCP_REGS + 2]  = 'O';
      mbTcpTxArray[MB_TCP_REGS + 3]  = '0';
    }
      else if (ctrOutState == OUT_STATE1)
    {
      mbTcpTxArray[MB_TCP_REGS + 2]  = 'O';
      mbTcpTxArray[MB_TCP_REGS + 3]  = '1';
    }
    else /* ctrOutState == OUT_STATE2 */
    {
      mbTcpTxArray[MB_TCP_REGS + 2]  = 'O';
      mbTcpTxArray[MB_TCP_REGS + 3]  = '2';
    }  

    ctrOutSecs = (int)((millis() - ctrOutTick)/1000);
    mbTcpTxArray[MB_TCP_REGS + 4]  = (char)((ctrOutSecs & 0xFF00)>>8);
    mbTcpTxArray[MB_TCP_REGS + 5]  = (char)(ctrOutSecs & 0x00FF);
    
    mbTcpTxArray[MB_TCP_REGS + 6]  = (char)((Ival[0] & 0xFF00)>>8);
    mbTcpTxArray[MB_TCP_REGS + 7]  = (char)(Ival[0] & 0x00FF);
    mbTcpTxArray[MB_TCP_REGS + 8]  = (char)((Ival[1] & 0xFF00)>>8);
    mbTcpTxArray[MB_TCP_REGS + 9]  = (char)(Ival[1] & 0x00FF);
    
    mbTcpTxArray[MB_TCP_REGS + 10]  = (char)((Vval[0] & 0xFF00)>>8);
    mbTcpTxArray[MB_TCP_REGS + 11]  = (char)(Vval[0] & 0x00FF);
    mbTcpTxArray[MB_TCP_REGS + 12]  = (char)((Vval[1] & 0xFF00)>>8);
    mbTcpTxArray[MB_TCP_REGS + 13]  = (char)(Vval[1] & 0x00FF);
    mbTcpTxArray[MB_TCP_REGS + 14]  = (char)((Vval[2] & 0xFF00)>>8);
    mbTcpTxArray[MB_TCP_REGS + 15]  = (char)(Vval[2] & 0x00FF);
    mbTcpTxArray[MB_TCP_REGS + 16]  = (char)((Vval[3] & 0xFF00)>>8);
    mbTcpTxArray[MB_TCP_REGS + 17]  = (char)(Vval[3] & 0x00FF);
    mbTcpTxArray[MB_TCP_REGS + 18]  = (char)((Vval[4] & 0xFF00)>>8);
    mbTcpTxArray[MB_TCP_REGS + 19]  = (char)(Vval[4] & 0x00FF);
    mbTcpTxArray[MB_TCP_REGS + 20]  = (char)((Vval[5] & 0xFF00)>>8);
    mbTcpTxArray[MB_TCP_REGS + 21]  = (char)(Vval[5] & 0x00FF);

    mbTcpTxArray[MB_TCP_REGS + 22] = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 23] = InDig[0];
    mbTcpTxArray[MB_TCP_REGS + 24] = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 25] = InDig[1];
    mbTcpTxArray[MB_TCP_REGS + 26] = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 27] = OutDig[0];
    mbTcpTxArray[MB_TCP_REGS + 28] = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 29] = OutDig[1];
    mbTcpTxArray[MB_TCP_REGS + 30] = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 31] = OutDig[2];
    mbTcpTxArray[MB_TCP_REGS + 32] = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 33] = OutDig[3];
    mbTcpTxArray[MB_TCP_REGS + 34] = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 35] = OutDig[4];
    mbTcpTxArray[MB_TCP_REGS + 36] = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 37] = OutDig[5];

    mbTcpTxArray[MB_TCP_REGS + 38] = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 39] = ctrMode;

    mbTcpTxArray[MB_TCP_REGS + 40]  = 0x00;
    mbTcpTxArray[MB_TCP_REGS + 41]  = (char)(mbTcpClientConnected);
    mbTcpTxArray[MB_TCP_REGS + 42]  = (char)((mbTcpRxError & 0xFF00)>>8);
    mbTcpTxArray[MB_TCP_REGS + 43]  = (char)(mbTcpRxError & 0x00FF);
  }
  else if ((addr == MB_IR_ADD_INS) && (nregs == MB_IR_NREG_INS))
  {
    mbTcpTxArray[MB_TCP_NBYTES] = (char)((nregs*2) & 0x00FF);

    for(int i = 0; i < MB_IR_NREG_INS; i++)
    {
      mbTcpTxArray[MB_TCP_REGS     + i * 2] = 0x00;
      mbTcpTxArray[MB_TCP_REGS + 1 + i * 2] = InDig[i];
    }
  }
  else if ((addr == MB_IR_ADD_OUTS) && (nregs == MB_IR_NREG_OUTS))
  {
    mbTcpTxArray[MB_TCP_NBYTES] = (char)((nregs*2) & 0x00FF);

    for(int i = 0; i < MB_IR_NREG_OUTS; i++)
    {
      mbTcpTxArray[MB_TCP_REGS     + i * 2] = 0x00;
      mbTcpTxArray[MB_TCP_REGS + 1 + i * 2] = OutDig[i];
    }
  }
  else if ((addr == MB_IR_ADD_ADCS) && (nregs == MB_IR_NREG_ADCS))
  {
    mbTcpTxArray[MB_TCP_NBYTES] = (char)((nregs*2) & 0x00FF);

    for(int i = 0; i < MB_IR_NREG_ADCS; i++)
    {
      mbTcpTxArray[MB_TCP_REGS     + i * 2] = (char)((AdcDig[i] & 0xFF00)>>8);
      mbTcpTxArray[MB_TCP_REGS + 1 + i * 2] = (char)(AdcDig[i] & 0x00FF);
    }
  }
  else
    exception = 1;

  if (exception == 0)
  {
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbReadInput OK");
    #endif

    mbTcpTxArray[MB_TCP_TID]     = mbTcpRxArray[MB_TCP_TID];     //00
    mbTcpTxArray[MB_TCP_TID + 1] = mbTcpRxArray[MB_TCP_TID + 1]; //01
    mbTcpTxArray[MB_TCP_PID]     = mbTcpRxArray[MB_TCP_PID];     //02
    mbTcpTxArray[MB_TCP_PID + 1] = mbTcpRxArray[MB_TCP_PID + 1]; //03
    mbTcpTxArray[MB_TCP_LEN]     = ((nregs + 3) & 0xFF00)>>8;    //04
    mbTcpTxArray[MB_TCP_LEN + 1] = (nregs + 3) & 0x00FF;         //05
    mbTcpTxArray[MB_TCP_UID]     = mbTcpRxArray[MB_TCP_UID];     //06
    mbTcpTxArray[MB_TCP_FUNC] = (char)(MB_FUNC_READ_INPUT_REGISTER);

    // Num Bytes
    mbTcpTxLength = nregs*2 + 9;
  }
  else
  {
    #if (_MBTCP_SERIAL_DEBUG_ == 1)
    Serial.println("_mbReadInput NOK");
    #endif

    mbTcpRxError++;

    mbTcpTxArray[MB_TCP_TID]     = mbTcpRxArray[MB_TCP_TID];     //00
    mbTcpTxArray[MB_TCP_TID + 1] = mbTcpRxArray[MB_TCP_TID + 1]; //01
    mbTcpTxArray[MB_TCP_PID]     = mbTcpRxArray[MB_TCP_PID];     //02
    mbTcpTxArray[MB_TCP_PID + 1] = mbTcpRxArray[MB_TCP_PID + 1]; //03
    mbTcpTxArray[MB_TCP_LEN]     = 0x00;                         //04
    mbTcpTxArray[MB_TCP_LEN + 1] = 0x03;                         //05
    mbTcpTxArray[MB_TCP_UID]     = mbTcpRxArray[MB_TCP_UID];     //06
	  mbTcpTxArray[MB_TCP_FUNC] = (char)(MB_FUNC_READ_INPUT_REGISTER | MB_NACK);
    mbTcpTxArray[MB_TCP_NBYTES] = MB_EC_ILLEGAL_DATA_ADDRESS;

    // Num Bytes
    mbTcpTxLength = 9;
  }

  mbTcpClientStatus = MB_CLIENT_ON_TX;
}

void _mbSlaveID()
{
  mbTcpTxArray[MB_TCP_TID]     = mbTcpRxArray[MB_TCP_TID];     //00
  mbTcpTxArray[MB_TCP_TID + 1] = mbTcpRxArray[MB_TCP_TID + 1]; //01
  mbTcpTxArray[MB_TCP_PID]     = mbTcpRxArray[MB_TCP_PID];     //02
  mbTcpTxArray[MB_TCP_PID + 1] = mbTcpRxArray[MB_TCP_PID + 1]; //03
  mbTcpTxArray[MB_TCP_LEN]     = ((13 + 3) & 0xFF00)>>8;       //04
  mbTcpTxArray[MB_TCP_LEN + 1] = (13 + 3) & 0x00FF;            //05
  mbTcpTxArray[MB_TCP_UID]     = mbTcpRxArray[MB_TCP_UID];     //06
	mbTcpTxArray[MB_TCP_FUNC] = (char)MB_FUNC_OTHER_REPORT_SLAVEID;

  mbTcpTxArray[MB_TCP_REGS] = (char)(24);

  mbTcpTxArray[MB_TCP_REGS + 1] = 0x00;
  mbTcpTxArray[MB_TCP_REGS + 2] = 0xFF;

  // 12 bytes
  mbTcpTxArray[MB_TCP_REGS + 3] = compdate[0];   //F
  mbTcpTxArray[MB_TCP_REGS + 4] = compdate[1];   //e
  mbTcpTxArray[MB_TCP_REGS + 5] = compdate[2];   //b
  mbTcpTxArray[MB_TCP_REGS + 6] = compdate[3];   //
  mbTcpTxArray[MB_TCP_REGS + 7] = compdate[4];   //d
  mbTcpTxArray[MB_TCP_REGS + 8] = compdate[5];   //d
  mbTcpTxArray[MB_TCP_REGS + 9] = compdate[6];   //
  mbTcpTxArray[MB_TCP_REGS + 10] = compdate[7];  //y
  mbTcpTxArray[MB_TCP_REGS + 11] = compdate[8];  //y
  mbTcpTxArray[MB_TCP_REGS + 12] = compdate[9];  //y
  mbTcpTxArray[MB_TCP_REGS + 13] = compdate[10]; //y
  mbTcpTxArray[MB_TCP_REGS + 14] = 0;
  
  // 10 bytes
  mbTcpTxArray[MB_TCP_REGS + 15] = comptime[0]; //h
  mbTcpTxArray[MB_TCP_REGS + 16] = comptime[1]; //h
  mbTcpTxArray[MB_TCP_REGS + 17] = comptime[2]; //-
  mbTcpTxArray[MB_TCP_REGS + 18] = comptime[3]; //m
  mbTcpTxArray[MB_TCP_REGS + 19] = comptime[4]; //m
  mbTcpTxArray[MB_TCP_REGS + 20] = comptime[5]; //-
  mbTcpTxArray[MB_TCP_REGS + 21] = comptime[6]; //s
  mbTcpTxArray[MB_TCP_REGS + 22] = comptime[7]; //s
  mbTcpTxArray[MB_TCP_REGS + 23] = '0';
  mbTcpTxArray[MB_TCP_REGS + 24] = '0';

  mbTcpTxLength = 32;
  mbTcpClientStatus = MB_CLIENT_ON_TX;
}

#endif // _USE_MBTCP_
