#include "main.h"

#if (_USE_MB_ == 1)

///////////
// CRC16 //
///////////
void _MBCRC(void)
{
  int reg_crc = 0xFFFF;
  int sizeFrame = mrs485TxNumBytes - 2;

  for (int i=0; i<sizeFrame; i++)
  {
    reg_crc ^= (byte)mrs485TxBuffer[i];
    for (int j=0; j<8; j++);
    {
      if (reg_crc & 0x01)
        reg_crc = (reg_crc >> 1) ^ 0xA001;
      else
        reg_crc >>= 1;
    }
  }
  
  mbCRC[1] = (reg_crc >> 8) & 0xFF;   // highbyte
  mbCRC[0] = (reg_crc & 0xFF);        // lowbyte
}

////////////////////
// mModbus set up //
////////////77//////
void _MBSetup(void)
{
  mbState = MB_STANDBY;
  mbTick = millis();
}

//////////////////
// mModbus Loop //
//////////////////
void _MBLoop(void)
{

  switch (mbState)
  {
    case MB_STANDBY:
      
      if (millis() - mbTick >= 2000)
      {
        mbState = MB_READINS;
      }
    
	    break;

    case MB_READINS:
    
      // Num Bytes
      mrs485TxNumBytes = 8;
      
      // Node
      mrs485TxBuffer[0] = 0xFF;
      // Read input regs
      mrs485TxBuffer[1] = 0x02;
      // Address
      mrs485TxBuffer[2] = 0x00;
      mrs485TxBuffer[3] = 0x00;
      // Length
      mrs485TxBuffer[4] = 0x00;
      mrs485TxBuffer[5] = 0x08;
      // Crc
      _MBCRC();
      mrs485TxBuffer[6] = mbCRC[0];
      mrs485TxBuffer[7] = mbCRC[1];

      mrs485State = MRS485_ONTX;

      // Back
      mbTick = millis();
      mbState = MB_STANDBY;
      
      break;

    case MB_WRITEOUTS:
      // Node
      mrs485TxBuffer[0] = 0xFF;
      // Write single reg
      mrs485TxBuffer[1] = 0x06;
      // Address (out)
      mrs485TxBuffer[2] = 0x00;
      mrs485TxBuffer[3] = 0x00;
      // Value
      mrs485TxBuffer[4] = 0x00; // mrs485TxBuffer[4] = 0xFF;
      mrs485TxBuffer[5] = 0x00; // mrs485TxBuffer[5] = 0x00;
      // Crc (TODO)
      //mrs485TxBuffer[6] = 0x00;
      //mrs485TxBuffer[7] = 0x00;
      
      // Num Bytes
      mrs485TxNumBytes = 8;
      break;
  }
}

#endif
