#include "main.h"

#if (_USE_MBTCP_ == 1)

///////////////////////
// Modbus TCP set up //
///////////////////////
void _mMBTCPSetup(void)
{
  mbTCPState = MBTCP_NOT_CONNECTED;
}

void _mMBTCPStart(void)
{
  mbTCPState = MBTCP_CONNECT;
  mbTCPtick = millis();
}

void _mMBTCPStop(void)
{
  mbTCPclient.stop();
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
    case MBTCP_NOT_CONNECTED:
      break;
    
    case MBTCP_CONNECT:
	    if (millis() - mbTCPtick >= MBTCP_TROUND_MS /*MBTCP_INIT_MS*/)
		    mbTCPState = MBTCP_CONNECTING;
      
      break;

    case MBTCP_CONNECTING:
      if(!mbTCPclient.connect(mbtcpip, mbtcpport))
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println("++++++++> Modbus TCP Connection error");
        #endif
        mbTCPState = MBTCP_CONNECT;
        mbTCPtick = millis();
      }
      else
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println("++++++++> Modbus TCP Connected");
        #endif
        mbTCPState = MBTCP_TX_RX; //MBTCP_TX;  //MBTCP_WAIT;
      }
      break;

    case MBTCP_TX_RX:
      if(mbTCPclient.connected())
      {
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println("+++++++> Modbus TCP TX");
        #endif

        delay(100);
        mbTCPclient.flush();
        delay(50);

        //0000 0000 0006 0104 0000 0014
        /*
        mbTCPclient.write(0x00);
        delay(1);
        mbTCPclient.write(0x00);
        delay(1);
        mbTCPclient.write(0x00);
        delay(1);
        mbTCPclient.write(0x00);
        delay(1);
        mbTCPclient.write(0x00);
        delay(1);
        mbTCPclient.write(0x06);
        delay(1);

        mbTCPclient.write(0x01);
        delay(1);
        mbTCPclient.write(0x04);
        delay(1);
        mbTCPclient.write(0x00);
        delay(1);
        mbTCPclient.write(0x00);
        delay(1);
        mbTCPclient.write(0x00);
        delay(1);
        mbTCPclient.write(0x14);
        delay(1);
        */
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
        shexbuffer[11] = 0x14;

        for (int i = 0; i < 12; i++) {
          
          c = shexbuffer[i];
          mbTCPclient.write(c);
          #if (_MBTCP_SERIAL_DEBUG_ == 1)
          sprintf (hexc, "%02x", c);
          Serial.print(hexc);
          #endif
          delay(1);
        }
        
        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println(" ");
        #endif

        // Send Frame
        //mbTCPclient.write(shexbuffer);
        delay(500);

        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println("+++++++> Modbus TCP RX");
        #endif

        while (mbTCPclient.available() > 0) {
          c = mbTCPclient.read();
          #if (_MBTCP_SERIAL_DEBUG_ == 1)
          sprintf (hexc, "%02x", c);
          Serial.print(hexc);
          #endif
          delay(10);
        }
      }
      #if (_MBTCP_SERIAL_DEBUG_ == 1)
      Serial.println(" ");
      #endif

      _mMBTCPStop();

      #if (_MBTCP_SERIAL_DEBUG_ == 1)
      Serial.println("+++++++> Modbus TCP disconnected");
      #endif

      mbTCPState = MBTCP_CONNECT;
      mbTCPtick = millis();

      break;

    /*
    case MBTCP_TX:
      if(mbTCPclient.connected())
      {
        delay(100);

        // Send frame
        mbTCPclient.write(0x00);
        mbTCPclient.write(0x00);
        mbTCPclient.write(0x00);
        mbTCPclient.write(0x00);
        mbTCPclient.write(0x00);
        mbTCPclient.write(0x02);
        mbTCPclient.write(0x01);
        mbTCPclient.write(0x11);

        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println("+++++++> Modbus TCP TX");
        #endif

        mbTCPState = MBTCP_RX;
      }
      else
       mbTCPState = MBTCP_DISCONNECT; 

      break;

    case MBTCP_RX:
      if(mbTCPclient.connected())
      {
        delay(100);

        #if (_MBTCP_SERIAL_DEBUG_ == 1)
        Serial.println("+++++++> Modbus TCP RX");
        #endif

        while (mbTCPclient.available() > 0) {
          char c = mbTCPclient.read();
          #if (_MBTCP_SERIAL_DEBUG_ == 1)
          Serial.print(c, HEX);
          #endif
          delay(2);
        }

        //mbTCPclient.flush();
      }

      mbTCPState = MBTCP_DISCONNECT;
      //mbTCPState = MBTCP_WAIT;
      //mbTCPtick = millis();

      break;
    */
    /*
    case MBTCP_WAIT:
	    if (millis() - mbTCPtick >= MBTCP_TROUND_MS)
      {
		    mbTCPState = MBTCP_TX;
      }
      break;
    */
    case MBTCP_DISCONNECT:

      _mMBTCPStop();

      #if (_MBTCP_SERIAL_DEBUG_ == 1)
      Serial.println(" ");
      Serial.println("+++++++> Modbus TCP disconnected");
      #endif

      mbTCPState = MBTCP_CONNECT;
      mbTCPtick = millis();

      break;
  }

}

#endif // (_USE_MBTCP_ == 1)