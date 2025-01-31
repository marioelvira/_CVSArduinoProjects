#include "main.h"

#if (_USE_NTP_ == 1)

void _ntpTimeString(void)
{
  char timeBuffer[40];

  if (mntpSync == false)
    sprintf(timeBuffer, "No Sincronizado");
  else
    sprintf(timeBuffer, "%02d/%02d/%4d %02d:%02d:%02d", day(), month(), year(), mntpHour, mntpMin, mntpSec);
    //sprintf(timeBuffer, "%02d/%02d/%4d %02d:%02d:%02d", day(), month(), year(), hour(), minute(), second());
  
  mntpTimeString = String(timeBuffer);
}     

void _mNTPfakeSec(void)
{
  mntpSec++;
  if (mntpSec >= 60)
  {
    mntpSec = 0;
    mntpMin++;
    if (mntpMin >= 60)
    {
      mntpMin = 0;
      mntpHour++;
      if (mntpHour >= 24)
      {
        mntpHour = 0;

        // New day!!!
        #if (_USE_SOLAR_ == 1)
        sCalculated = false;
        #endif
      }
    }
  }
  
  _ntpTimeString();
}

////////////////
// NTP set up //
////////////////
void _mNTPSetup(void)
{
  mntpSync = false;
  mntpStatus = MNTP_STOP;
}

void _mNTPStart(void)
{
  mntpStatus = MNTP_START;
}

void _mNTPStop(void)
{
  mntpStatus = MNTP_STOP;
}

///////////////
// mNTP loop //
///////////////
void _mNTPloop(void)
{   
  // Client mNTP...
  switch(mntpStatus)
  {
    case MNTP_START:
      mNtpClient.begin();
      mntpStatus = MNTP_UPDATE;
      
      #if (_NTP_SERIAL_DEBUG_ == 1)
      Serial.println("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
      Serial.println("NTP Client begin");
      Serial.println("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
      #endif
      break;

    case MNTP_UPDATE:
      if (mNtpClient.update() == false)
      {
        //mntpSync = false;
        #if (_NTP_SERIAL_DEBUG_ == 1)
        Serial.println("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT"); 
        Serial.println("NTP Not updated");
        Serial.println("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
        #endif
        break;
      }

      mntpSync = true;
      mntpEpochTime = mNtpClient.getEpochTime();
      setTime(mntpEpochTime);

      #if (_NTP_SERIAL_DEBUG_ == 1)
      _ntpTimeString();

      Serial.println("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT"); 
      Serial.println(mntpTimeString);
      Serial.println("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
      #endif

      mntpYear  = year();
      mntpMonth = month();
      mntpDay   = day();
      mntpHour  = hour();
      mntpMin   = minute();
      mntpSec   = second();
      
      #if (_USE_SOLAR_ == 1)
      if (sCalculated == false)
      {
        _SolarSunriseSunset();
        sCalculated = true;
      }
      #endif

      break;

    case MNTP_STOP:
      break;
  }
}

#endif // (_USE_MQTT_ == 1)