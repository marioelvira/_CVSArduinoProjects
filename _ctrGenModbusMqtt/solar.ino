#include "main.h"

#if (_USE_SOLAR_ == 1)

#include <SolarCalculator.h>

#if (_SOLAR_SERIAL_DEBUG_ == 1)
// Rounded HH:mm format
char * solarHoursToString(double h, char *str)
{
  int m = int(round(h * 60));
  int hr = (m / 60) % 24;
  int mn = m % 60;

  str[0] = (hr / 10) % 10 + '0';
  str[1] = (hr % 10) + '0';
  str[2] = ':';
  str[3] = (mn / 10) % 10 + '0';
  str[4] = (mn % 10) + '0';
  str[5] = '\0';
  return str;
}
#endif

/////////////////////////
// Solar SunriseSunset //
/////////////////////////
void _SolarSunriseSunset(void)
{
  double sun_altitude = SUNRISESET_STD_ALTITUDE - 0.0353 * sqrt(sheight);

  // Calculate the times of sunrise, transit, and sunset, in hours (UTC)
  calcSunriseSunset(syear, smonth, sday, slatitude, slongitude, stransit, sunrise, sunset, sun_altitude);

  #if (_SOLAR_SERIAL_DEBUG_ == 1)
  char str[6];

  Serial.println("Solar Data: ");
  Serial.print("Sunrise: "); Serial.println(solarHoursToString(sunrise + sutc_offset, str));
  Serial.print("Sunset: ");  Serial.println(solarHoursToString(sunset + sutc_offset, str));
  //Serial.print("Transit: ");Serial.println(solarHoursToString(stransit + utc_offset, str));
  #endif
}

#endif