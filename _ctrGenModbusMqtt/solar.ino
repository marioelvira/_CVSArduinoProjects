#include "main.h"

#if (_USE_SOLAR_ == 1)

#include <SolarCalculator.h>

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

  #if (_SOLAR_SERIAL_DEBUG_ == 1)
  Serial.println("Solar Calculated: ");
  Serial.print("Sunrise: "); Serial.print(sunrise_h); Serial.print(":");Serial.println(sunrise_m);
  Serial.print("Sunset:  "); Serial.print(sunset_h);  Serial.print(":");Serial.println(sunset_m);
  #endif
}

#endif