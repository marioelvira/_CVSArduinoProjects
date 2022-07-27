#include "main.h"

#if (_USE_RS485_ == 1)

///////////////////
// MRS485 set up //
///////////////////
void _RS485Setup(void)
{
  delay(100);  // 100ms
  Serial.begin(9600);

  mrs485State = MRS485_STANDBY;
  mrs485RxBuffer.reserve(MRS485_ARRAY_SIZE);
  //mrs485TxBuffer.reserve(MRS485_ARRAY_SIZE);

  digitalWrite(PIN_RS485_RXTX, LOW);
  //OutRS485rxtx = OUT_RS485_RX;

  mrs485RxTick = millis();
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
	      mrs485RxTick = millis();
		    inChar = (char)Serial.read();
		    mrs485RxBuffer += inChar;
	    }
      digitalWrite(PIN_RS485_RXTX, LOW);
	    break;
	  
	  case MRS485_ONRX:
	    if (Serial.available())
      {
        mrs485State = MRS485_ONRX;
	      mrs485RxTick = millis();
		    inChar = (char)Serial.read();
		    mrs485RxBuffer += inChar;
	    }
	    digitalWrite(PIN_RS485_RXTX, LOW);
     
	    // Time Out
	    if (millis() - mrs485RxTick >= 100)  // 100ms
      {
		    mrs485State = MRS485_ENDRX;
       
        delay(5); // TODO
        digitalWrite(PIN_RS485_RXTX, HIGH);
        delay(5); // TODO
      }

	    break;
	  
	  case MRS485_ENDRX:
	    // Frame Received
	    // Analyze Frame and decide
	    mrs485State = MRS485_ONTX;
	    // clear the string:
	    mrs485RxBuffer = "";

	    break;
	  
	  case MRS485_ONTX:
   
      // Send Frame
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
      
      // Num Bytes
      mrs485TxNumBytes = 6;
  
      // Send byffer
      if (mrs485TxNumBytes > MRS485_ARRAY_SIZE)
        mrs485TxNumBytes = MRS485_ARRAY_SIZE;
      Serial.write(mrs485TxBuffer, mrs485TxNumBytes);
      
      delay(5); // TODO
      digitalWrite(PIN_RS485_RXTX, LOW);
      delay(5); // TODO
      
	    mrs485State = MRS485_STANDBY;
	    break;
  }
 
 }

#endif
