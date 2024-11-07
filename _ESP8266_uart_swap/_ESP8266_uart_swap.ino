
#define PIN_UART0_RXTX    5 // 0
#define PIN_UART2_RXTX    4 // D2
int uartInUse = 0;


void setup() {

  Serial.begin(9600);
  Serial.println();
  Serial.println("Serial Echo, type % to swap()");

  uartInUse = 0;

  pinMode(PIN_UART0_RXTX, OUTPUT);
  digitalWrite(PIN_UART0_RXTX, LOW);  // On RX

  pinMode(PIN_UART2_RXTX, OUTPUT);
  digitalWrite(PIN_UART2_RXTX, HIGH);  // On RX
}

void loop() {

  if (Serial.available())
  {
    delay (5);
    if (uartInUse == 0)
      digitalWrite(PIN_UART0_RXTX, HIGH); // On TX
    else
      digitalWrite(PIN_UART2_RXTX, LOW);  // On TX
    delay (5);

    char c = Serial.read();

    if (c == '%')
    {
      Serial.println("Swapping over");
      
      delay(10);
      Serial.swap();
      if (uartInUse == 0)
      {
        uartInUse = 2;
        digitalWrite(PIN_UART0_RXTX, LOW);    // On RX
        digitalWrite(PIN_UART2_RXTX, LOW);    // On TX
      }
      else
      {
        uartInUse = 0;
        digitalWrite(PIN_UART0_RXTX, HIGH);   // On TX
        digitalWrite(PIN_UART2_RXTX, HIGH);   // On RX
      }
      delay(10);

      Serial.println();
      Serial.println("Swapped to here");
    }
    else
      Serial.print(c);


    delay (5);
    if (uartInUse == 0)
      digitalWrite(PIN_UART0_RXTX, LOW);  // On RX
    else
      digitalWrite(PIN_UART2_RXTX, HIGH); // On RX
    delay (5);
  }
}
