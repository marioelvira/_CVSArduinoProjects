#include "main.h"

#if (_USE_MUART_ == 1)

//////////////////
// MUART set up //
//////////////////
void _MUARTSetup(void)
{
  delay(100);  // 100ms
  Serial.begin(115200);

  uartState = UART_STANDBY;
  uartRxBuffer.reserve(MUART_ARRAY_SIZE);
  uartTxBuffer.reserve(MUART_ARRAY_SIZE);
}

////////////////
// MUART Loop //
////////////////
void _MUARTLoop(void)
{

  char inChar;
  
  switch (uartState)
  {
    case UART_STANDBY:
	    if (Serial.available())
      {
        uartState = UART_ONRX;
	      uartRxTick = millis();
		    inChar = (char)Serial.read();
		    uartRxBuffer += inChar;
	    }
	    break;
	  
	  case UART_ONRX:
	    if (Serial.available())
      {
        uartState = UART_ONRX;
	      uartRxTick = millis();
		    inChar = (char)Serial.read();
		    uartRxBuffer += inChar;
	    }
	  
	    // Time Out
	    if (millis() - uartRxTick >= 100)  // 100ms
		    uartState = UART_ENDRX;

	    break;
	  
	  case UART_ENDRX:
	    // Frame Received
	    Serial.println("Frame Rx");
	    // Analyze Frame and decide
	    uartState = UART_ONTX;
	    // clear the string:
	    uartRxBuffer = "";
	    break;
	  
	  case UART_ONTX:
	    Serial.println("OK");
	    uartState = UART_STANDBY;
	    break;
  }
}

#endif
