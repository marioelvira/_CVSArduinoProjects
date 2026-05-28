#include "main.h"

#if (_USE_ETHERNET_ == 1)

////////////////
// ETH set up //
////////////////
void _ETHSetup(void)
{
  Ethernet.init(PIN_SPI_CS); // Set the CS pin
  ethStatus = ETH_START;
}

/////////////////////////
// ETH state machine //
/////////////////////////
void _ETHLoop()
{
  int status;
  String ipStr;

  switch (ethStatus)
  {
    case ETH_START:
      // Check HW
      if (Ethernet.hardwareStatus() == EthernetNoHardware)
      {
        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.println("START: Shield not found");
        #endif
        status = 0;
      }
      // Check Link
      else if (Ethernet.linkStatus() == LinkOFF)
      {
        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.println("START: Link OFF");
        #endif
        status = 0;
      }     
      else
      {
        if (ipMode == DHCP_MODE)
        {
          #if (_ETH_SERIAL_DEBUG_ == 1)
          Serial.println("START: DHCP");
          #endif

          status = Ethernet.begin(macAddress);
          /*
          Ethernet.begin(macAddress, 10000, 2000);
          if (Ethernet.localIP() == IPAddress(0,0,0,0))
            status = 0;
          else
            status = 1;
          */
        }
        else
        {
          #if (_ETH_SERIAL_DEBUG_ == 1)
          Serial.println("START: FIX IP");
          #endif

          Ethernet.begin(macAddress, ipAddress, dnsAddress, gateWay, netMask);
          //Ethernet.setRetransmissionCount(1);
          status = 1;
        }
      }

      if (status == 0)
        ethStatus = ETH_ERROR;
      else
      {
        ethStatus = ETH_OK;

        ipAddress = Ethernet.localIP();

        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.println("IP Settings: ");
        Serial.println(Ethernet.localIP());
        Serial.println(Ethernet.gatewayIP());
        Serial.println(Ethernet.subnetMask());
        Serial.print("HW: ");     Serial.println(Ethernet.hardwareStatus());
        Serial.print("Link: ");   Serial.println(Ethernet.linkStatus());
        #endif

        #if (_USE_MBTCP_ == 1)
        _ModbusTcpSetup();
        #endif

        #if (_USE_MQTT_ == 1)
        _MQTTSetup();
        #endif

        #if (_USE_NTP_ == 1)
        _mNTPSetup();
        #endif
      }
      break;

    case ETH_OK:
      // Check HW
      if (Ethernet.hardwareStatus() == EthernetNoHardware)
      {
        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.println("ETH OK: Ethernet shield not found");
        #endif
        ethStatus = ETH_ERROR;
      }
      // Check Link
      if (Ethernet.linkStatus() == LinkOFF)
      {
        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.println("Ethernet Link OFF");
        #endif
        ethStatus = ETH_ERROR;
      }
      
      // Only DHCP
      if (ipMode == DHCP_MODE)
      {
        status = Ethernet.maintain(); 

        #if (_ETH_SERIAL_DEBUG_ == 1)
        switch (status) 
        {
          case 1:
            Serial.println("Error: renewed fail");
            break;

          case 2:
            Serial.println("Renewed success");
            Serial.println("IP Settings: ");
            Serial.println(Ethernet.localIP());
            Serial.println(Ethernet.gatewayIP());
            Serial.println(Ethernet.subnetMask());
            break;

          case 3:
            Serial.println("Error: rebind fail");
            break;

          case 4:
            Serial.println("Rebind success");
            Serial.println("IP Settings: ");
            Serial.println(Ethernet.localIP());
            Serial.println(Ethernet.gatewayIP());
            Serial.println(Ethernet.subnetMask());
            break;

          default:
            break;
        }
        #endif
      }

      #if (_USE_MBTCP_ == 1)
      _ModbusTcpLoop();
      #endif

      #if (_USE_MQTT_ == 1)
      _MQTTLoop();
      #endif

      #if (_USE_NTP_ == 1)
      _mNTPLoop();
      #endif

      break;

    case ETH_ERROR:

      // Check HW
      if (Ethernet.hardwareStatus() == EthernetNoHardware)
      {
        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.println("HW ERROR: Ethernet shield not found");
        #endif
      }
      // Check Link
      else if (Ethernet.linkStatus() == LinkOFF)
      {
        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.print(".");
        #endif
      }
      else
      {
        ethTick = millis();
        ethStatus = ETH_WAIT;
      }
      break;

    case ETH_WAIT:
      if (millis() - ethTick >= ETH_WAIT_MS)
        ethStatus = ETH_START;
      break;
  }
}

#endif
