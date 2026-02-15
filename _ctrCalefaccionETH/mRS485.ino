#include "main.h"

#if (_USE_RS485_ == 1)

#if (_USE_RS485_ == 1)
#include "modbusRTU.h"
#endif

///////////////////
// MRS485 set up //
///////////////////
void _RS485Setup(void)
{
  delay(100);  // 100ms
  Serial.begin(9600);

  //Serial.begin(baud, config, rxPin, txPin); TODO

  mrs485State = MRS485_STANDBY;
  mrs485RxBuffer.reserve(MRS485_ARRAY_SIZE);
  //mrs485TxBuffer.reserve(MRS485_ARRAY_SIZE);

  OutRS485rxtx = OUT_RS485_RX;

  mrs485tick = millis();
}

/////////////////
// MRS485 Loop //
/////////////////
void _RS485Loop(void)
{
  char inChar;
  
  switch (mrs485State)
  {
    case MRS485_STANDBY:
	    if (Serial.available())
      {
        mrs485State = MRS485_ONRX;
	      mrs485tick = millis();
		    inChar = (char)Serial.read();
		    mrs485RxBuffer += inChar;
	    }
      OutRS485rxtx = OUT_RS485_RX;
	    
	    break;
	  
	  case MRS485_ONRX:
	    if (Serial.available())
      {
        mrs485State = MRS485_ONRX;
	      mrs485tick = millis();
		    inChar = (char)Serial.read();
		    mrs485RxBuffer += inChar;
	    }
      OutRS485rxtx = OUT_RS485_RX;
      
	    // Rx Time Out
	    if (millis() - mrs485tick >= MRS485_RX_TOUT_MS)
      {
		    mrs485State = MRS485_FRAME_RX;
        OutRS485rxtx = OUT_RS485_TX;
      }

	    break;
	  
	  case MRS485_FRAME_RX:
      // Must back to standby other part...
      // Time Out just in case
      if (millis() - mrs485tick >= MRS485_BACK_TOUT_MS)
      {
        // clear Rx buffer
        mrs485RxBuffer = "";
        mrs485State = MRS485_STANDBY;
      }

	    break;

    case MRS485_INITTX:
      OutRS485rxtx = OUT_RS485_TX;
      // Init Tx Time wait
      if (millis() - mrs485tick >= MRS485_INITTX_TOUT_MS)
        mrs485State = MRS485_ONTX;

      break;
      
	  case MRS485_ONTX:
      
      // Send buffer
      if (mrs485TxNumBytes > MRS485_ARRAY_SIZE)
        mrs485TxNumBytes = MRS485_ARRAY_SIZE;
      Serial.write(mrs485TxBuffer, mrs485TxNumBytes);

      mrs485tick = millis();  
	    mrs485State = MRS485_ENDTX;
     
	    break;

    case MRS485_ENDTX:
      OutRS485rxtx = OUT_RS485_TX;
    
      // TX Time Out
      if (millis() - mrs485tick >= MRS485_TX_TOUT_MS)
      {
        mrs485RxBuffer = "";
        mrs485State = MRS485_STANDBY;
        OutRS485rxtx = OUT_RS485_RX;
      }      
      break;
   }
 }

#endif
