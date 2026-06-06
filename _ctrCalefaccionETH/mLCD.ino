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
float         lcdTemp;

byte simboloGrado[] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

LiquidCrystal_I2C lcd(LCD_ADDR, 20, 4); 

void _lcdTemp()
{
  lcdTemp = 0;

  Wire.beginTransmission(TEMP_ADDR);
  Wire.write(0x05);

  if (Wire.endTransmission() != 0)
  {
    #if (_LCD_SERIAL_DEBUG_ == 1)
    Serial.println("Error i2c coms sensor temp.");
    #endif
    lcd.setCursor(10, 2);
    lcd.print("Error     ");
    delay(2000);
    return;
  }

  Wire.requestFrom(TEMP_ADDR, 2); // El dato de temperatura ocupa 2 bytes
  if (Wire.available() >= 2)
  {
    byte msb = Wire.read();
    byte lsb = Wire.read();

    // CONVERSIÓN MATEMÁTICA OFICIAL DEL DATASHEET
    // Limpiamos los bits de alertas superiores del byte más significativo
    msb = msb & 0x1F; 

    // Comprobamos si la temperatura es negativa (Bit 4 firmado)
    if ((msb & 0x10) == 0x10) { 
      msb = msb & 0x0F; // Filtramos el signo
      lcdTemp = 256.0 - ((msb * 16.0) + (lsb / 16.0));
    } else {
      lcdTemp = (msb * 16.0) + (lsb / 16.0);
    }
  }
}

void _lcdUpdate()
{
  String slcd = "";

  lcd.setCursor(1, 1);
  lcd.print(triacZCFrec, 2); lcd.print("Hz");

  lcd.setCursor(1, 2);
  lcd.print(mbfTemp[0]); lcd.write(0); lcd.print("C ");

  _lcdTemp();
  lcd.setCursor(11, 2);
  lcd.print(lcdTemp, 2); lcd.write(0); lcd.print("C ");

  lcd.setCursor(5, 3);
  slcd = String(timeDay) + "d " + timeOnString;
  lcd.print(slcd);
}

///////////////////////
// LCD state machine //
///////////////////////
void _LCDSetup()
{
  // Init i2c
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL); 
  Wire.setClock(50000);

	lcdState = STATE_LCD_INIT;
}

///////////////////////
// LCD state machine //
///////////////////////
void _LCDLoop()
{  
  switch (lcdState)
  {
	  case STATE_LCD_INIT:
      #if (_LCD_SERIAL_DEBUG_ == 1)
      Serial.println("LCD Init");
      #endif

      // Inicializa LCD
      lcd.init();
      lcd.backlight();
      lcd.clear();

      // Guardamos el símbolo de grado en la posición de memoria 0
      lcd.createChar(0, simboloGrado);

      // Limpiamos LCD
      lcd.setCursor(0, 0);
      lcd.print("   CTR CALEFACCION  ");
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("                    "); 

      lcdState = STATE_LCD_UPDATE;
      break;	  

    case STATE_LCD_TOUT:
      if (millis() - lcdTick >= 1000)
        lcdState = STATE_LCD_UPDATE;
      break;

    case STATE_LCD_UPDATE:
    
      #if (_LCD_SERIAL_DEBUG_ == 1)
      Serial.println("LCD Update");
      #endif

      _lcdUpdate();

      lcdTick = millis();
      lcdState = STATE_LCD_TOUT;
      break;
  }   
}

#endif  // (_USE_LCD_ == 1)