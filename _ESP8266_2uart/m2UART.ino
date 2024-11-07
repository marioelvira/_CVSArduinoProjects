#include "main.h"

#if (_USE_2UART_ == 1)

//////////////////
// 2UART set up //
//////////////////
void _2UARTSetup(void)
{
  delay(100);  // 100ms
  Serial.begin(9600);

  // Swat to UART_OF (UART2)
  Serial.swap();
  delay(100);  // 100ms

  m2UartRxBuffer.reserve(M2UART_ARRAY_SIZE);
  //m2UartTxBuffer.reserve(M2UART_ARRAY_SIZE);

  // 2UARTs in RX
  m2UartRXTX_INV = OUT_m2UART0_RX;
  m2UartRXTX_OF = OUT_m2UART2_RX;

  m2UartTxFrames = 0;
  m2UartRxFrames = 0;
  m2UartNoResponses = 0;

  m2UartRxNumBytes = 0;
  m2UartTxNumBytes = 0;

  m2Uarttick = millis();
  m2UartState = M2UART_LISTEN_IN_UART_OF;
}

////////////////
// 2UART Loop //
////////////////
void _2UARTLoop(void)
{
  int i;
  char inChar;

  switch (m2UartState)
  {
    case M2UART_LISTEN_IN_UART_OF:
      // UART_OF (UART2) in RX
      m2UartRXTX_INV = OUT_m2UART0_RX;
      m2UartRXTX_OF = OUT_m2UART2_RX;

      m2UartRxNumBytes = 0;
      if (Serial.available())
      {
        m2UartState = M2UART_ONRX_IN_UART_OF;
	      m2Uarttick = millis();
		    inChar = (char)Serial.read();
		    m2UartRxBuffer += inChar;
        m2UartRxNumBytes++;
	    }
	    break;

	  case M2UART_ONRX_IN_UART_OF:
      // UART_OF (UART2) in RX
      m2UartRXTX_INV = OUT_m2UART0_RX;
      m2UartRXTX_OF = OUT_m2UART2_RX;

	    if (Serial.available())
      {
	      m2Uarttick = millis();
		    inChar = (char)Serial.read();
		    m2UartRxBuffer += inChar;
        m2UartRxNumBytes++;
	    }
      
	    // Rx Time Out
	    if (millis() - m2Uarttick >= M2UART_RX_UART_OF_TOUT_MS)
		    m2UartState = M2UART_FRAMERX_IN_UART_OF;

	    break;

	  case M2UART_FRAMERX_IN_UART_OF:
      // If frame recived in UART_OF (UART2)...
      http2Uart0RxNumBytes = m2UartRxNumBytes;

      // Copy to TxBuffer
      for (i = 0; i < m2UartRxNumBytes; i++)
        m2UartTxBuffer[i] = m2UartRxBuffer[i];
      
      m2UartTxNumBytes = m2UartRxNumBytes;

      // UART_INV (UART0) in TX
      m2UartRXTX_INV = OUT_m2UART0_TX;
      m2UartRXTX_OF = OUT_m2UART2_RX;

      // Swat to UART_INV (UART0)
      Serial.swap();

      m2Uarttick = millis();
      m2UartState = M2UART_SWAT_TO_UART_INV;
	    break;

    case M2UART_SWAT_TO_UART_INV:
      // UART_INV (UART0) in TX
      m2UartRXTX_INV = OUT_m2UART0_TX;
      m2UartRXTX_OF = OUT_m2UART2_RX;
      
      if (millis() - m2Uarttick >= M2UART_SWAT_MS)
		    m2UartState = M2UART_FRAMETX_IN_UART_INV;
      break;

    case M2UART_FRAMETX_IN_UART_INV:
      // UART_INV (UART0) in TX
      m2UartRXTX_INV = OUT_m2UART0_TX;
      m2UartRXTX_OF = OUT_m2UART2_RX;
      
      m2UartTxFrames++;

      if (m2UartTxNumBytes > M2UART_ARRAY_SIZE)
        m2UartTxNumBytes = M2UART_ARRAY_SIZE;
      Serial.write(m2UartTxBuffer, m2UartTxNumBytes);

      http2Uart2TxNumBytes = m2UartTxNumBytes;

      m2Uarttick = millis();  
	    m2UartState = M2UART_ENDTX_IN_UART_INV;
      break;

    case M2UART_ENDTX_IN_UART_INV:
      // UART_INV (UART0) in TX
      m2UartRXTX_INV = OUT_m2UART0_TX;
      m2UartRXTX_OF = OUT_m2UART2_RX;
    
      // TX Time Out
      if (millis() - m2Uarttick >= M2UART_TX_UART_INV_TOUT_MS)
      {
        m2UartRxBuffer = "";
        m2Uarttick = millis();
        m2UartState = M2UART_LISTEN_IN_UART_INV;
      }      
      break;

    case M2UART_LISTEN_IN_UART_INV:
      // UART_INV (UART0) in RX
      m2UartRXTX_INV = OUT_m2UART0_RX;
      m2UartRXTX_OF = OUT_m2UART2_RX;

      m2UartRxNumBytes = 0;
      if (Serial.available())
      {
        m2UartState = M2UART_ONRX_IN_UART_INV;
	      m2Uarttick = millis();
		    inChar = (char)Serial.read();
		    m2UartRxBuffer += inChar;
        m2UartRxNumBytes++;
	    }

	    // Listen Time Out
	    if (millis() - m2Uarttick >= cfgUart2ToutMs /*M2UART_LISTEN_UART_INV_TOUT_MS*/)
      {
        // Swat to UART0
        Serial.swap();
        m2UartNoResponses++;
        m2UartState = M2UART_LISTEN_IN_UART_OF; // No response
      }
	    break;

	  case M2UART_ONRX_IN_UART_INV:
      // UART_INV (UART0) in RX
      m2UartRXTX_INV = OUT_m2UART0_RX;
      m2UartRXTX_OF = OUT_m2UART2_RX;

	    if (Serial.available())
      {
	      m2Uarttick = millis();
		    inChar = (char)Serial.read();
		    m2UartRxBuffer += inChar;
        m2UartRxNumBytes++;
	    }

	    // Rx Time Out
	    if (millis() - m2Uarttick >= M2UART_RX_UART_INV_TOUT_MS)
		    m2UartState = M2UART_FRAMERX_IN_UART_INV;

	    break;

	  case M2UART_FRAMERX_IN_UART_INV:
      // If frame recived in UART_INV (UART0)...
      http2Uart2RxNumBytes = m2UartRxNumBytes;
      
      m2UartRxFrames++;

      // Copy to TxBuffer
      for (i = 0; i < m2UartRxNumBytes; i++)
        m2UartTxBuffer[i] = m2UartRxBuffer[i];
      
      m2UartTxNumBytes = m2UartRxNumBytes;

      // UART_OF (UART2) in TX
      m2UartRXTX_INV = OUT_m2UART0_RX;
      m2UartRXTX_OF = OUT_m2UART2_TX;

      // Swat to UART0
      Serial.swap();

      m2Uarttick = millis();
      m2UartState = M2UART_SWAT_TO_UART_OF;
	    break;

    case M2UART_SWAT_TO_UART_OF:
      // UART_OF (UART2) in TX
      m2UartRXTX_INV = OUT_m2UART0_RX;
      m2UartRXTX_OF = OUT_m2UART2_TX;

      if (millis() - m2Uarttick >= M2UART_SWAT_MS)
		    m2UartState = M2UART_FRAMETX_IN_UART_OF;
      break;

    case M2UART_FRAMETX_IN_UART_OF:
      // UART_OF (UART2) in TX
      m2UartRXTX_INV = OUT_m2UART0_RX;
      m2UartRXTX_OF = OUT_m2UART2_TX;

      if (m2UartTxNumBytes > M2UART_ARRAY_SIZE)
        m2UartTxNumBytes = M2UART_ARRAY_SIZE;
      Serial.write(m2UartTxBuffer, m2UartTxNumBytes);

      http2Uart0TxNumBytes = m2UartTxNumBytes;

      m2Uarttick = millis();  
	    m2UartState = M2UART_ENDTX_IN_UART_OF;
      break;

    case M2UART_ENDTX_IN_UART_OF:
      // UART_OF (UART2) in TX
      m2UartRXTX_INV = OUT_m2UART0_RX;
      m2UartRXTX_OF = OUT_m2UART2_TX;
    
      // TX Time Out
      if (millis() - m2Uarttick >= M2UART_TX_UART_OF_TOUT_MS)
      {
        m2UartRxBuffer = "";
        m2Uarttick = millis();
        m2UartState = M2UART_LISTEN_IN_UART_OF;
      }      
      break;
   }
}

#endif
