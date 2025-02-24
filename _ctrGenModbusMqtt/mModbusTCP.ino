#include "main.h"

#if (_USE_MBTCP_ == 1)

///////////////////////
// Modbus TCP set up //
///////////////////////
void _mMBTCPSetup(void)
{
  mbTCPState = MBTCP_STOP;
}

void _mMBTCPStart(void)
{
  mbTCPtick = millis();
  mbTCPState = MBTCP_WAIT_TO_CONNECT;
}

void _mMBTCPStop(void)
{
  mbTCPclient.stop();
  mbTCPState = MBTCP_STOP;
}

/////////////////////
// Modbus TCP loop //
/////////////////////
void _mMBTCPloop(void)
{
  char shexbuffer[12];

  #if (_MBTCP_SERIAL_DEBUG_ == 1)
  char hexc[3];
  #endif

  switch (mbTCPState)
  { 
    case MBTCP_WAIT_TO_CONNECT:
	    if (millis() - mbTCPtick >= MBTCP_CONNECT_MS)
		    mbTCPState = MBTCP_CONNECT;
      
      break;

    case MBTCP_CONNECT:

      #if (_MBTCP_SERIAL_DEBUG_ == 1)
      Serial.print("++++++> Modbus TCP: IP: ");
      Serial.print(mbIpAddress);
      Serial.print(" Port: ");
      Serial.println(mbPort);
      #endif

      if(!mbTCPclient.connect(mbIpAddress, mbPort))
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println("++++++++> Modbus TCP Connection error");
        #endif
        mbTCPState = MBTCP_WAIT_TO_CONNECT;
        mbTCPtick = millis();
      }
      else
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println("++++++++> Modbus TCP Connected");
        #endif

        mbTCPtick = millis();
        mbTCPState = MBTCP_WAIT_TX;
      }
      break;

    case MBTCP_WAIT_TX:
	    if (millis() - mbTCPtick >= MBTCP_ROUND_CONNETED_MS)
		    mbTCPState = MBTCP_TX;

      break;

    case MBTCP_TX:
      if(mbTCPclient.connected())
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println("+++++++> Modbus TCP TX");
        #endif

        //0000 0000 0006 0104 0000 0014
        shexbuffer[0]  = 0x00;
        shexbuffer[1]  = 0x00;
        shexbuffer[2]  = 0x00;
        shexbuffer[3]  = 0x00;
        shexbuffer[4]  = 0x00;
        shexbuffer[5]  = 0x06;

        shexbuffer[6]  = 0x01;
        shexbuffer[7]  = MB_FUNC_READ_INPUT_REGISTER;
        shexbuffer[8]  = (char)((MB_IR_ADD_ONLINE & 0xFF00)>>8);
        shexbuffer[9]  = (char)(MB_IR_ADD_ONLINE & 0x00FF);
        shexbuffer[10] = (char)((MB_IR_NREG_ONLINE & 0xFF00)>>8);
        shexbuffer[11] = (char)(MB_IR_NREG_ONLINE & 0x00FF);

        mbTCPclient.write(shexbuffer, 12);

        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        for (int i = 0; i < 12; i++)
        {  
          sprintf (hexc, "%02x", shexbuffer[i]);
          Serial.print(hexc);
        }
        Serial.println(" ");
        Serial.println("+++++++> Modbus TCP RX wait");
        #endif

        mbTCPState = MBTCP_RX;
        mbTCPtick = millis();
        mbTCPRxIndex = 0;
      }
      else
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println("++++++++> Modbus TCP Connection error. Try to reconnect");
        #endif

        mbTCPclient.stop();
        mbTCPState = MBTCP_WAIT_TO_CONNECT;
        mbTCPtick = millis();
      }

      break;

    case MBTCP_RX:

      if (millis() - mbTCPtick >= MBTCP_RESPONSE_MS)
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println(" ");
        Serial.println("+++++++> Modbus TCP RX end");
        #endif
        
        mbTCPState = MBTCP_ON_ANALYSIS;
      }

      if (mbTCPclient.available() > 0)
      {
        mbTCPRxBuffer[mbTCPRxIndex] = mbTCPclient.read();
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        sprintf (hexc, "%02x", mbTCPRxBuffer[mbTCPRxIndex]);
        Serial.print(hexc);
        #endif

        mbTCPRxIndex++;
        mbTCPtick = millis();
      }

      break;

    case MBTCP_ON_ANALYSIS:

      mbTCPFunction = mbTCPRxBuffer[MB_TCP_FUNC];

      #if (_MBTCP_SERIAL_DEBUG_ == 1)
      Serial.print(F("Function: "));
      Serial.println(mbTCPFunction);
      #endif

      switch(mbTCPFunction)
      {
        case MB_FUNC_READ_INPUT_REGISTER:
          _mbReadInput();
          break;
      }
      
      mbTCPState = MBTCP_WAIT_TX;
      mbTCPtick = millis();
      break;

    case MBTCP_STOP:
      break;
  }

}

void _mbReadInput()
{
  int nbytes;
  int ctrOutSecs;

  nbytes = (int)(mbTCPRxBuffer[MB_TCP_NBYTES]);

  #if (_MBTCP_SERIAL_DEBUG_ == 1)
  Serial.print(F("num bytes: "));
  Serial.println(nbytes);
  #endif

  if (nbytes == (MB_IR_ADD_ONLINE*2))
  {
    mbctrInState[0]  = mbTCPRxBuffer[MB_TCP_REGS];
    mbctrInState[1]  = mbTCPRxBuffer[MB_TCP_REGS + 1];
    mbctrOutState[0] = mbTCPRxBuffer[MB_TCP_REGS + 2];
    mbctrOutState[1] = mbTCPRxBuffer[MB_TCP_REGS + 3];
    mbctrOutTick     = (int)((mbTCPRxBuffer[MB_TCP_REGS + 4] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 5] & 0x00FF);
    mbRMSval[0]      = (int)((mbTCPRxBuffer[MB_TCP_REGS + 6] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 7] & 0x00FF);
    mbRMSval[1]      = (int)((mbTCPRxBuffer[MB_TCP_REGS + 8] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 9] & 0x00FF);
    mbDCval[0]       = (int)((mbTCPRxBuffer[MB_TCP_REGS + 10] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 11] & 0x00FF);
    mbDCval[1]       = (int)((mbTCPRxBuffer[MB_TCP_REGS + 12] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 13] & 0x00FF);
    mbDCval[2]       = (int)((mbTCPRxBuffer[MB_TCP_REGS + 14] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 15] & 0x00FF);
    mbDCval[3]       = (int)((mbTCPRxBuffer[MB_TCP_REGS + 16] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 17] & 0x00FF);
    mbDCval[4]       = (int)((mbTCPRxBuffer[MB_TCP_REGS + 18] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 19] & 0x00FF);
    mbDCval[5]       = (int)((mbTCPRxBuffer[MB_TCP_REGS + 20] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 21] & 0x00FF);
    //rInDig[0]     = (int)((mbTCPRxBuffer[MB_TCP_REGS + 22] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 23] & 0x00FF);
    //rInDig[1]     = (int)((mbTCPRxBuffer[MB_TCP_REGS + 24] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 25] & 0x00FF);
    //rOutDig[0]    = (int)((mbTCPRxBuffer[MB_TCP_REGS + 26] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 27] & 0x00FF);
    //rOutDig[1]    = (int)((mbTCPRxBuffer[MB_TCP_REGS + 28] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 29] & 0x00FF);
    //rOutDig[2]    = (int)((mbTCPRxBuffer[MB_TCP_REGS + 30] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 31] & 0x00FF);
    //rOutDig[3]    = (int)((mbTCPRxBuffer[MB_TCP_REGS + 32] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 33] & 0x00FF);
    //rOutDig[4]    = (int)((mbTCPRxBuffer[MB_TCP_REGS + 34] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 35] & 0x00FF);
    //rOutDig[5]    = (int)((mbTCPRxBuffer[MB_TCP_REGS + 36] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 37] & 0x00FF);
    //rctrMode      = (int)((mbTCPRxBuffer[MB_TCP_REGS + 38] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 39] & 0x00FF);
    //rMBError      = (int)((mbTCPRxBuffer[MB_TCP_REGS + 40] & 0x00FF)<<8)|(mbTCPRxBuffer[MB_TCP_REGS + 41] & 0x00FF);
  }
}

#endif // (_USE_MBTCP_ == 1)