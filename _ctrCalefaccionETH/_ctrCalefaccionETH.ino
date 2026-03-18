#include "main.h"

#if (_USE_HTTP_ == 1)
#include <WebServer.h>
#endif

#if (_USE_UID_ == 1)
#include <ArduinoUniqueID.h>
#endif

#include "alarm.h"
#include "ctr.h"
#include "e2prom.h"
#include "io.h"
#include "ip.h"
#include "mTime.h"

#if (_USE_ETHERNET_ == 1)
#include "mEthernet.h"
#endif
#if (_USE_MQTT_ == 1)
#include "MQTT.h"
#endif
#if (_USE_HTTP_ == 1)
#include "http.h"
#endif
#if (_USE_NTP_ == 1)
#include "mNTP.h"
#endif
#if (_USE_RS485_ == 1)
#include "mRS485.h"
#endif
#if (_USE_MBRTU_ == 1)
#include "modbusRTU.h"
#endif
#if (_USE_TRIAC_ == 1)
#include "triac.h"
#endif
#if (_USE_PWM_ == 1)
#include "pwm.h"
#endif
#if (_USE_WDE_ == 1)
#include "wde.h"
#endif

/////////////
// Version //
/////////////
// Get from compile time
const char* compdate = __DATE__;
const char* comptime = __TIME__;
#if (_USE_UID_ == 1)
String UniqueIdStr;
#endif

//============//
// MAIN SETUP //
//============//
void setup(void)
{
  #if (_SERIAL_DEBUG_ == 1)
  delay(2000);  // 100ms
  Serial.begin(115200);
  Serial.print("Project: ");
  Serial.println(PROJECT);
  Serial.print("Version: ");
  Serial.println(compdate);
  Serial.print("Time: ");
  Serial.println(comptime);
  #endif

  #if (_USE_UID_ == 1)
  UniqueIdStr = "";
  for (size_t i = 0; i < UniqueIDsize; i++) {
    if (UniqueID[i] < 0x10) UniqueIdStr += "0";
    UniqueIdStr += String(UniqueID[i], HEX);
  }

  #if (_SERIAL_DEBUG_ == 1)
  Serial.print("UniqueID: ");
  Serial.println(UniqueIdStr);
  #endif
  #endif

  // PIN & IO Setup
  _IOSetup();
  _PINSetup();

  // Config setup
  _ConfigSetup();

  _ALARMSetup();

  #if (_USE_TRIAC_ == 1)
  _TRIACSetup();
  #endif

  #if (_USE_PWM_ == 1)
  _PWMSetup();
  #endif

  // Time setup
  _TimeSetup();

  // Ctr setup
  _CtrSetup();

  #if (_USE_WDE_ == 1)
  _WDESetup();
  #endif

  #if (_USE_ETHERNET_ == 1)
  _ETHSetup();

  #if (_USE_HTTP_ == 1)
  _HTTPSetup();
  #endif

  #if (_USE_MQTT_ == 1)
  _MQTTSetup();
  #endif

  #if (_USE_NTP_ == 1)
  _mNTPSetup();
  #endif

  #if (_USE_RS485_ == 1)
  _RS485Setup();
  #if (_USE_MBRTU_ == 1)
  _MBSetup();
  #endif
  #endif

  #endif // _USE_ETHERNET_
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _PINLoop();

  #if (_USE_TRIAC_ == 1)
  _TRIACLoop();
  #endif

  if (ctrMode == MODE_AUTO)
    _CtrLoop();

  _TimeLoop();

  #if (_USE_ETHERNET_ == 1)
  _ETHLoop();
  #endif

  #if (_USE_RS485_ == 1)
  _RS485Loop();
  #if (_USE_MBRTU_ == 1)
  _MBLoop();
  #endif
  #endif

  //_ALARMLoop();
}
