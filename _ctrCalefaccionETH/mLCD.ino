#include "main.h"
#include "mLCD.h"

#if (_USE_LCD_ == 1)
#include "io.h"
#include "mTime.h"

#if (_USE_NTP_ == 1)
#include "mNTP.h"
#endif

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
	
///////////////
// Variables //
///////////////
int           lcdState;
unsigned long lcdTick = 0;

// Configura la dirección I2C y dimensiones de la pantalla (16 columnas x 2 filas)
// La dirección más común suele ser 0x27 o 0x3F.
LiquidCrystal_I2C lcd(0x27, 20, 4); 

///////////////////////
// LCD state machine //
///////////////////////
void _LCDSetup()
{
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

	lcdState = STATE_LCD_INIT;
}

///////////////////////
// LCD state machine //
///////////////////////
void _LCDLoop()
{  
  String slcd = "";

  switch (lcdState)
  {
	  case STATE_LCD_INIT:
      lcd.init();
      lcd.backlight();

      lcdState = STATE_LCD_UPDATE;
      break;	  

    case STATE_LCD_TOUT:
      if (millis() - lcdTick >= 1000)
        lcdState = STATE_LCD_UPDATE;
      break;

    case STATE_LCD_UPDATE:
      lcd.setCursor(0, 0);
      lcd.print("Tiempo ON");
      
      lcd.setCursor(0, 1);
      slcd = "ton: " + String(timeDay) + "d " + timeOnString;
      lcd.print(slcd);

      lcd.setCursor(0, 2);
      lcd.print("Tiempo NTP");

      lcd.setCursor(0, 3);
      #if (_USE_NTP_ == 1)
      slcd = "time: " + mntpTimeString;
      lcd.print(slcd);
      #else
      lcd.print("No NTP");
      #endif
      


      lcdTick = millis();
      lcdState = STATE_LCD_TOUT;
      break;
  }   
}

#endif  // (_USE_LCD_ == 1)