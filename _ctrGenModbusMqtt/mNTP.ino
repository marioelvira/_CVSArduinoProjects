
void _ntpTimeString(void)
{
  /*
  if (mntpSync == false)
    sprintf(timeBuffer, "No Sincronizado");
  else
    sprintf(timeBuffer, "%02d/%02d/%4d %02d:%02d:%02d", mntpDay, mntpMonth, mntpYear, mntpHour, mntpMin, mntpSec);
  
  mntpTimeString = String(timeBuffer);
  */

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

  if (mntpSync == false)
    mntpTimeString = mntpTimeString + " NO Sync";
}     

void _mNTPfakeSec(void)
{
  mntpSec++;
  if (mntpSec >= 60)
  {
    mntpSec = 0;
    mntpMin++;

    #if (_USE_SOLAR_ == 1)
    if (sCalculated == true)
      _SolarDayNight();
    #endif

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
        Serial.println("NTP NOT Update ");
        Serial.println("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
        #endif
      }
      else
      {
        mntpSync = true;
        mntpEpochTime = mNtpClient.getEpochTime();
        setTime(mntpEpochTime);

        mntpYear  = year();
        mntpMonth = month();
        mntpDay   = day();
        mntpHour  = hour();
        mntpMin   = minute();
        mntpSec   = second();
      
        #if (_NTP_SERIAL_DEBUG_ == 1)
        Serial.println("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
        Serial.println("NTP Time Update ");
        Serial.println("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
        #endif

        #if (_USE_SOLAR_ == 1)
        if (sCalculated == false)
        {
          _SolarSunriseSunset();
          solarCount++;
          sCalculated = true;
        }
        #endif
      }
      break;

    case MNTP_STOP:
      break;
  }
}
