#include "main.h"

#if (_USE_MUART_ == 1)

//////////////////
// MUART set up //
//////////////////
void _MUARTSetup(void)
{
  delay(100);  // 100ms
  Serial.begin(115200);

  uartCMD = false;
  uartBuffer.reserve(MUART_ARRAY_SIZE);
}

////////////////
// MUART Loop //
////////////////
void _MUARTLoop(void)
{
  if (uartCMD)
  {
    int i;
    
    if (uartBuffer.startsWith("INS"))
    {
      for (i = 0; i< IN_NUMBER; i++)
      {
        Serial.print("IN ");
        Serial.println(i);
        Serial.print("Dig: ");
        Serial.println(InDig[i]);
      }
    }
    else if (uartBuffer.startsWith("OUTS"))
    {
      for (i = 0; i< OUT_NUMBER; i++)
      {
        Serial.print("OUT ");
        Serial.println(i);
        Serial.print("Dig: ");
        Serial.println(OutDig[i]);
      }
    }
    else if (uartBuffer.startsWith("SET"))
    {
      String substr = uartBuffer.substring(3,4);
      Serial.print(substr);
      i = substr.toInt();
            
      if (uartBuffer.substring(4,5) == "1")
        OutDig[i] = OUT_ON;
      else
        OutDig[i] = OUT_OFF;
    }
    else if (uartBuffer.startsWith("ADCS"))
    {
      for (i = 0; i< ADC_NUMBER; i++)
      {
        Serial.print("ADC ");
        Serial.println(i);
        Serial.print("Dig: ");
        Serial.println(AdcDig[i]);
      }
    }
    else
      Serial.println("No CMD");
    
    // clear the string:
    uartBuffer = "";
    uartCMD = false;
  }
}

//////////////////
// Serial Event //
//////////////////
void serialEvent()
{
  while (Serial.available())
  {
    char inChar = (char)Serial.read();
    Serial.print(inChar);

    uartBuffer += inChar;
    if (inChar == '\n')
      uartCMD = true;
  }
}

#endif
