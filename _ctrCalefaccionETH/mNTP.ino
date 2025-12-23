#include "main.h"

#if (_USE_NTP_ == 1)
	
void _ntpTimeString(void)
{
    if (mntpHour < 10)
      mntpTimeString = "0" + String(mntpHour);
    else
      mntpTimeString = String(mntpHour);

    mntpTimeString = mntpTimeString + ":";

    if (mntpMin < 10)
      mntpTimeString = mntpTimeString + "0" + String(mntpMin);
    else
      mntpTimeString = mntpTimeString + String(mntpMin);

    mntpTimeString = mntpTimeString + ":";

    if (mntpSec < 10)
      mntpTimeString = mntpTimeString + "0" + String(mntpSec);
    else
      mntpTimeString = mntpTimeString + String(mntpSec);

    if (mntpUpdated == 0)
      mntpTimeString = mntpTimeString + " NO Sync";
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
        mntpHour = 0;
    }
  }
  
  _ntpTimeString();
}

////////////////
// NTP set up //
////////////////
void _mNTPSetup(void)
{
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
void _mNTPLoop(void)
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
      mNtpClient.update();
      mntpUpdated = 1;

      mntpHour = mNtpClient.getHours();
      mntpMin  = mNtpClient.getMinutes();
      mntpSec  = mNtpClient.getSeconds();
      
      #if (_NTP_SERIAL_DEBUG_ == 1)
      Serial.println("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
      Serial.println("NTP Time Update ");
      Serial.println("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
      #endif
      
      break;

    case MNTP_STOP:
      break;
  }
}

#endif // (_USE_NTP_ == 1)