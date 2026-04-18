#include "main.h"
#include "mRS485.h"
#include "io.h"

#if (_USE_RS485_ == 1)

#if (_USE_MBRTU_ == 1)
#include "modbusRTU.h"
#endif

///////////////
// Variables //
///////////////
int             mrs485State;
String          mrs485RxBuffer = "";
unsigned long   mrs485tick;
char            mrs485TxBuffer[MRS485_ARRAY_SIZE];
int             mrs485TxNumBytes;

int             OutRS485rxtx;

///////////////////
// MRS485 set up //
///////////////////
void _RS485Setup(void)
{
  delay(100);  // 100ms
  
  Serial2.begin(9600, SERIAL_8N1, PIN_RS485_RX, PIN_RS485_TX);
  
  mrs485State = MRS485_STANDBY;
  mrs485RxBuffer.reserve(MRS485_ARRAY_SIZE);
  //mrs485TxBuffer.reserve(MRS485_ARRAY_SIZE);

  pinMode(PIN_RS485_RXTX, OUTPUT);
  digitalWrite(PIN_RS485_RXTX, LOW);
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
      OutRS485rxtx = OUT_RS485_RX;
	    if (Serial2.available())
      {
        mrs485State = MRS485_ONRX;
	      mrs485tick = millis();
		    inChar = (char)Serial2.read();
		    mrs485RxBuffer += inChar;
	    }    
	    break;
	  
	  case MRS485_ONRX:
      OutRS485rxtx = OUT_RS485_RX;
	    if (Serial2.available())
      {
        mrs485State = MRS485_ONRX;
	      mrs485tick = millis();
		    inChar = (char)Serial2.read();
		    mrs485RxBuffer += inChar;
	    }
      
	    // Rx Time Out
	    if (millis() - mrs485tick >= MRS485_RX_TOUT_MS)
      {
		    mrs485State = MRS485_FRAME_RX;
        OutRS485rxtx = OUT_RS485_TX;
      }
	    break;
	  
	  case MRS485_FRAME_RX:
      OutRS485rxtx = OUT_RS485_RX;
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
      if (millis() - mrs485tick >= MRS485_INIT_TX_MS)
        mrs485State = MRS485_ONTX;

      break;
      
	  case MRS485_ONTX:
      OutRS485rxtx = OUT_RS485_TX;
      // Send buffer
      if (mrs485TxNumBytes > MRS485_ARRAY_SIZE)
        mrs485TxNumBytes = MRS485_ARRAY_SIZE;
      Serial2.write(mrs485TxBuffer, mrs485TxNumBytes);

      mrs485tick = millis();  
	    mrs485State = MRS485_ENDTX;
	    break;

    case MRS485_ENDTX:
      OutRS485rxtx = OUT_RS485_TX;   
      // TX Time Out
      if (millis() - mrs485tick >= MRS485_END_TX_MS)
      {
        mrs485RxBuffer = "";
        mrs485State = MRS485_STANDBY;
        OutRS485rxtx = OUT_RS485_RX;
      }      
      break;
   }

  if (OutRS485rxtx == OUT_RS485_RX)
    digitalWrite(PIN_RS485_RXTX, LOW);
  else
    digitalWrite(PIN_RS485_RXTX, HIGH);
}

#endif
