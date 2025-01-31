#include "main.h"

#if (_USE_SOLAR_ == 1)

#include <SolarCalculator.h>

void _SolarString(void)
{
  char solarBuffer[40];

  if (sCalculated == true)
    sprintf(solarBuffer, "No Calculado");
  else
    sprintf(solarBuffer, "de %02d:%02d a %02d:%02d", sunrise_h, sunrise_m, sunset_h, sunset_m);
  
  solarString = String(solarBuffer);
}

/////////////////////////
// Solar SunriseSunset //
/////////////////////////
void _SolarSunriseSunset(void)
{ 
  // Location
  double latitude = 42.464;
  double longitude = -2.0293;
  int utc_offset = 1;
  int height = 450;  // in meters
  int m;

  double transit, srise, sset;
  double saltitude = SUNRISESET_STD_ALTITUDE - 0.0353 * sqrt(height);

  // Calculate the times of sunrise, transit, and sunset, in hours (UTC)
  calcSunriseSunset(mntpYear, mntpMonth, mntpDay, latitude, longitude, transit, srise, sset, saltitude);

  // sunrise
  m = int(round((srise + utc_offset) * 60));
  sunrise_h = (m / 60) % 24;
  sunrise_m = m % 60;

  // sunset
  m = int(round((sset + utc_offset) * 60));
  sunset_h = (m / 60) % 24;
  sunset_m = m % 60;

  _SolarString();

  #if (_SOLAR_SERIAL_DEBUG_ == 1)
  Serial.print("Solar Calculated: ");
  Serial.println(solarString); 
  #endif
}

#endif