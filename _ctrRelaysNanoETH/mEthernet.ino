#include "main.h"

#if (_USE_ETHERNET_ == 1)

////////////////
// ETH set up //
////////////////
void _ETHSetup(void)
{
  ethStatus = ETH_START;
}

/////////////////////////
// ETH state machine //
/////////////////////////
void _ETHLoop()
{
  int status;

  switch (ethStatus)
  {
    case ETH_START:
      if (ipMode == DHCP_MODE)
      {
        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.println("Ethernet DHCP Start");
        #endif
        Ethernet.init(PIN_SPI_CS); // Set the CS pin
        status = Ethernet.begin(macAddress);
      }
      else
      {
        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.println("Ethernet FIX IP Start");
        #endif
        Ethernet.init(PIN_SPI_CS); // Set the CS pin
        Ethernet.begin(macAddress, ipAddress, dnsAddress, gateWay, netMask);
        status = 1;
      }

      if (status == 0)
      {
        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.println("Failed to configure");
        #endif
        ethStatus = ETH_ERROR;
      }
      else
      {
        ethStatus = ETH_OK;

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
        //_MQTTSetup();
        #endif
      }

      ethTick = millis();
      break;

    case ETH_OK:

      // Check HW
      if (Ethernet.hardwareStatus() == EthernetNoHardware)
      {
        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.println("HW ERROR: Ethernet shield not found");
        #endif
        ethStatus = ETH_ERROR;
      }

      // Check Link
      if (Ethernet.linkStatus() == LinkOFF)
      {
        #if (_ETH_SERIAL_DEBUG_ == 1)
        Serial.println("Ethernet Link OFF");
        #endif
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
      //_MQTTLoop();
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
      else
        ethStatus = ETH_START;  // TODO

      break;
  }
}

#endif
