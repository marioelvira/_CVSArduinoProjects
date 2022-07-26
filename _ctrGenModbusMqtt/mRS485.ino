#include "main.h"

#if (_USE_MRS485_ == 1)

///////////////////
// MRS485 set up //
///////////////////
void _MRS485Setup(void)
{
  delay(100);  // 100ms
  Serial.begin(9600);

  mrs485State = MRS485_STANDBY;
  mrs485RxBuffer.reserve(MRS485_ARRAY_SIZE);
  mrs485TxBuffer.reserve(MRS485_ARRAY_SIZE);

  digitalWrite(PIN_RS485_RXTX, LOW);

  mrs485RxTick = millis();
}

/////////////////
// MRS485 Loop //
/////////////////
void _MRS485Loop(void)
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
      Serial.println("OK");
	    mrs485State = MRS485_ONTX;
	    // clear the string:
	    mrs485RxBuffer = "";
      
      delay(5); // TODO
      digitalWrite(PIN_RS485_RXTX, LOW);
      delay(5); // TODO
      
	    break;
	  
	  case MRS485_ONTX:
	    mrs485State = MRS485_STANDBY;
	    break;
  }
 
 }

#endif
