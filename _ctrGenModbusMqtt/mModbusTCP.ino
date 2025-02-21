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
  const uint mbtcpport = 502;
  const char* mbtcpip = "192.168.0.9";

  char shexbuffer[12];
  char c;

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
      if(!mbTCPclient.connect(mbtcpip, mbtcpport))
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
        shexbuffer[7]  = 0x04;
        shexbuffer[8]  = 0x00;
        shexbuffer[9]  = 0x00;
        shexbuffer[10] = 0x00;
        shexbuffer[11] = 0x15;

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
        
        mbTCPState = MBTCP_WAIT_TX;
        mbTCPtick = millis();
      }

      if (mbTCPclient.available() > 0)
      {
        c = mbTCPclient.read();
        mbTCPtick = millis();

        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        sprintf (hexc, "%02x", c);
        Serial.print(hexc);
        #endif
      }

      break;

    case MBTCP_STOP:
      break;
  }

}

#endif // (_USE_MBTCP_ == 1)