#include "main.h"

#if (_USE_MUART_ == 1)

////////////////////
// mModbus set up //
////////////77//////
void _MMBSetup(void)
{
  mbState = MB_STANDBY;
  //mbTick = millis();
}

//////////////////
// mModbus Loop //
//////////////////
void _MMBTLoop(void)
{

  switch (mbState)
  {
    case MB_STANDBY:
	    break;

    case MB_READINS:
      // Node
      uartTxBuffer[0] = 0x01;
      // Read input regs
      uartTxBuffer[1] = 0x04;
      // Address
      uartTxBuffer[2] = 0x00;
      uartTxBuffer[3] = 0x00;
      // Length
      uartTxBuffer[4] = 0x00;
      uartTxBuffer[5] = 0x08;
      // Crc (TODO)
      //uartTxBuffer[6] = 0x00;
      //uartTxBuffer[7] = 0x00;
      break;

    case MB_WRITEOUTS:
      // Node
      uartTxBuffer[0] = 0x01;
      // Write single reg
      uartTxBuffer[1] = 0x06;
      // Address (out)
      uartTxBuffer[2] = 0x00;
      uartTxBuffer[3] = 0x00;
      // Value
      uartTxBuffer[4] = 0x00; // uartTxBuffer[4] = 0xFF;
      uartTxBuffer[5] = 0x00; // uartTxBuffer[5] = 0x00;
      // Crc (TODO)
      //uartTxBuffer[6] = 0x00;
      //uartTxBuffer[7] = 0x00;
      break;
  }
}

#endif
