#include "main.h"

#if (_USE_MB_ == 1)

////////////////////
// mModbus set up //
////////////77//////
void _MBSetup(void)
{
  mbState = MB_STANDBY;
  //mbTick = millis();
}

//////////////////
// mModbus Loop //
//////////////////
void _MBTLoop(void)
{

  switch (mbState)
  {
    case MB_STANDBY:
	    break;

    case MB_READINS:
      // Node
      mrs485TxBuffer[0] = 0xFF;
      // Read input regs
      mrs485TxBuffer[1] = 0x04;
      // Address
      mrs485TxBuffer[2] = 0x00;
      mrs485TxBuffer[3] = 0x00;
      // Length
      mrs485TxBuffer[4] = 0x00;
      mrs485TxBuffer[5] = 0x08;
      // Crc (TODO)
      //mrs485TxBuffer[6] = 0x00;
      //mrs485TxBuffer[7] = 0x00;
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
      break;
  }
}

#endif
