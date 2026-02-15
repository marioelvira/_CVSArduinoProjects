#include "main.h"

#if (_USE_ETHERNET_ == 1)

void onEvent(arduino_event_id_t event)
{
  switch (event)
  {
    case ARDUINO_EVENT_ETH_START:
      #if (_ETH_SERIAL_DEBUG_ == 1)
      Serial.println("ETH event: Iniciado");
      #endif
      ETH.setHostname("ES32-P4-ETH");
      ethStatus = ETH_STARTED;
      break;

    case ARDUINO_EVENT_ETH_CONNECTED:
      #if (_ETH_SERIAL_DEBUG_ == 1)
      Serial.println("ETH event: Cable Conectado");
      #endif
      ethStatus = ETH_CONNECTED;
      break;

    case ARDUINO_EVENT_ETH_GOT_IP:
      #if (_ETH_SERIAL_DEBUG_ == 1)   
      Serial.println("ETH event: IP obtenida");
      #endif
      ethStatus = ETH_GOT_IP;
      break;

    case ARDUINO_EVENT_ETH_DISCONNECTED:
      #if (_ETH_SERIAL_DEBUG_ == 1)
      Serial.println("ETH event: Cable Desconectado");
      #endif
      #if (_USE_HTTP_ == 1)
      _HTTPStop();
      #endif
      ethStatus = ETH_DISCONNECTED;
      break;

    default:
      break;
  }
}

////////////////
// ETH set up //
////////////////
void _ETHSetup(void)
{
  ethStatus = ETH_START;
  Network.onEvent(onEvent);

  // Inicio de hardware
  if (!ETH.begin()) {
    #if (_ETH_SERIAL_DEBUG_ == 1)
    Serial.println("ETH: Error al iniciar hardware");
    #endif
  }
 
  if (ipMode == FIXIP_MODE)
  {
    if (!ETH.config(ipAddress, gateWay, netMask, dnsAddress)) {
      #if (_ETH_SERIAL_DEBUG_ == 1)
      Serial.println("ETH: Error al configurar IP Fija");
      #endif
    }
  }
}

/////////////////////////
// ETH state machine //
/////////////////////////
void _ETHLoop()
{
  //#if (_ETH_SERIAL_DEBUG_ == 1)
  //Serial.print("ETH: ethStatus "); Serial.println(ethStatus);
  //#endif

  switch (ethStatus)
  {
    case ETH_START:
    case ETH_STARTED:
    case ETH_CONNECTED:
      break;

    case ETH_GOT_IP:

      #if (_ETH_SERIAL_DEBUG_ == 1)
      
      if (ipMode == FIXIP_MODE)
        Serial.println("Fix IP");
      else 
        Serial.println("DHCP");

      Serial.println(ETH.localIP());
      Serial.println(ETH.gatewayIP());
      Serial.println(ETH.subnetMask());
      #endif

      #if (_USE_HTTP_ == 1)
      _HTTPStart();
      #endif

      #if (_USE_MQTT_ == 1)
      _MQTTStart();
      #endif

      #if (_USE_NTP_ == 1)
      _mNTPStart();
      #endif
      
      ethStatus = ETH_ON_SERVICE;
      break;

    case ETH_ON_SERVICE:

      #if (_USE_HTTP_ == 1)
      _HTTPLoop();
      #endif

      #if (_USE_MQTT_ == 1)
      _MQTTLoop();
      #endif

      #if (_USE_NTP_ == 1)
      _mNTPLoop();
      #endif

      break;

    case ETH_DISCONNECTED:
      break;
  }
}

#endif
