/*
  Control de Generadores para Campo de Vuelo Sesma.
  Creado  06/12/2015
  Modif   21/01/2018

  Tabla de Verdad
  ---------------

  In1 In2 |   Out1  Out2  Out3  Out4  Out5
  ----------------------------------------
  0   0   |   1     1     0     0     0   Estado 1
  1   0   |   0     0     1     1     0   Estado 2
  1   1   |   0     0     1     1     0   Estado 2
  0   1   |   0     0     0     1     1   Estado 3

  El Led indica el estado en que está 1 pulso Estado 1,
  dos pulsos en el Estado 2 y 3 pulsos en el Estado 3.

  Cambio de Estado 1 a Estado 2 si:
    In1 > 0,3V mas de 3 segundos
    o 
    In2 > 0,115 mas de 3 segundos

  Permanece en Estado 2 durante 3 minutos

*/

// Placas de Evaluación.
#define ARDUINO_NANO   1
#define ARDUINO_UNO    2

// Placa en uso.
#define USAR    ARDUINO_NANO  

// Adc ads1115
#include <Wire.h>
#include "Adafruit_ADS1015.h"

#if (USAR == ARDUINO_NANO)
// Salidas Digitales
#define OUT1  2
#define OUT2  3
#define OUT3  4
#define OUT4  5
#define OUT5  6
// Led Indicador
#define LED   13
// Entradas Digitales
#define IN1   8
#define IN2   9
#endif

#if (USAR == ARDUINO_UNO)
// TODO
#endif

// Temporizaciones
#define FILTRO_INS          100     // 100x10ms
#define STATE1_TIEMPO_0_1   150     // 150x10ms
#define STATE1_TIEMPO_1_2   18000   // 18000x10ms = 3minutos
#define STATE2_TIEMPO_0_1   150     // 150x10ms
#define STATE2_TIEMPO_1_2   150     // 150x10ms
#define STATE3_TIEMPO_0_1   150     // 150x10ms
#define STATE3_TIEMPO_1_2   150     // 150x10ms

#define A0_1_TIEMPO           200     // 200x10ms = 2 segundos
#define A2_3_TIEMPO           200     // 200x10ms = 2 segundos
#define STATE2_FORCED_TIEMPO  18000   // 18000x10ms = 3minutos

// Estados Generales
#define STATE1        1
#define STATE2        2
#define STATE3        3

#define PULSO_CORTO   100   // 50x10ms
#define PULSO_LARGO   200  // 150x10ms

// Variables para estados
int   GeneralState = 1;
int   GeneralState_ant = 1;
int   State = 0;
int   StateCounter = 0;

// Variables para leer el Estado de la entrada 1
int   In1Status = 0;
int   In1Status_ant = 0;
int   In1Counter = 0;

// Variables para leer el Estado de la entrada 2
int   In2Status = 0;
int   In2Status_ant = 0;
int   In2Counter = 0;

// Variables del Adc
int16_t AdcDiff_0_1 = 0;
int16_t AdcDiff_2_3 = 0;

int   A0_1_Counter = 0;
int   A2_3_Counter = 0;

// Variables para Leds
bool  LedNextState = false;
int   LedCounter = 0;
int   LedDuration = 0;
int   LedPulsos = 0;

// Adc ads1115
Adafruit_ADS1115 AdcAds;
//const float AdcGain = 0.1875F;

#define A0_1_LEVEL 1600  // 300mV / 0.1875 (bits/mV) = 1600
#define A2_3_LEVEL 614   // 115mV / 0.1875 (bits/mV) = 614

boolean ForcedState2 = false;

// Dedug...
#define SERIAL_DEBUG  1
#define SERIAL_DEBUG_TIMER  100
int    DebugCounter = 0;

//////////////////////////////
// Función de Inicilización //
//////////////////////////////
void setup() {

  #if (SERIAL_DEBUG == 1)
  Serial.begin(9600);
  #endif
  
  // Inicialización de las Salidas Digitales
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  pinMode(OUT5, OUTPUT);

  digitalWrite(OUT1, LOW);
  digitalWrite(OUT2, LOW);
  digitalWrite(OUT3, LOW);
  digitalWrite(OUT4, LOW); 
  digitalWrite(OUT5, LOW);
  
  // Led Indicador de Estado
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW); 

  // Inicialización de las Entradas Digitales
  pinMode(IN1, INPUT);
  pinMode(IN2, INPUT);

  _InitInputs();
  _InitLed();
  _InitAdc();
}

//////////////////////////////////////////////
// Inicialización de las entradas digitales //
//////////////////////////////////////////////
void _InitInputs() {

  In1Status = digitalRead(IN1);
  In1Status_ant = In1Status;
  In1Counter = 0;

  In2Status = digitalRead(IN1);
  In2Status_ant = In2Status;
  In2Counter = 0;
}

////////////////////////////
// Inicialización del Led //
////////////////////////////
void _InitLed() {
  
  LedNextState = false;
  LedCounter = 0;
  LedDuration = PULSO_CORTO;
  LedPulsos = 0;
}

////////////////////////////////////////////
// Inicialización del ADC ADS1115 por I2C //
////////////////////////////////////////////
void _InitAdc(){
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  AdcAds.begin();
   
}

/////////////////////////////////////////////
// Función Principal                       //
// Se ejecuta en bucle continuo cada 10 ms //
/////////////////////////////////////////////
void loop() {

  // Leemos las entradas digitales.
  _ReadInputs();

  // Leemos las entradas del ADC.
  _ReadAdc();

  // Chequeo del estado general.
  _GeneralState();

  #if (SERIAL_DEBUG == 1)
  DebugCounter++;
  if (DebugCounter > SERIAL_DEBUG_TIMER)
  {
    DebugCounter = 0;
  }
  #endif
  
  // Ponemos un retado de 10 milisegundos en cada iteración.
  delay(10);
}

////////////////////////////////////////
// Lectura de las entradas digitales  //
// con filtro software antirebotes    //
////////////////////////////////////////
void _ReadInputs() {

  int in1State, in2State;
  
  // Leemos las entrada digital 1...
  in1State = digitalRead(IN1);

  if (In1Status_ant == in1State)
    In1Counter++; // Incrementamos el contador.
  else
    In1Counter = 0;

  // Aplicamos el filto software...
  if (In1Counter > FILTRO_INS)
    In1Status = in1State;   // Actualizamos la lectura de la entrada...

  // Almacenamos el valor anterior...
  In1Status_ant = in1State;

  // Leemos las entrada digital 2...
  in2State = digitalRead(IN2);

  if (In2Status_ant == in2State)
    In2Counter++; // Incrementamos el contador.
  else
    In2Counter = 0;

  // Aplicamos el filto software...
  if (In2Counter > FILTRO_INS)
    In2Status = in2State;   // Actualizamos la lectura de la entrada...

  // Almacenamos el valor anterior...
  In2Status_ant = in2State;
}

/////////////////////////////////////
// Lectura del ADC ADS1115 por I2C //
/////////////////////////////////////
void _ReadAdc() {

  AdcDiff_0_1 = AdcAds.readADC_Differential_0_1();
  AdcDiff_2_3 = AdcAds.readADC_Differential_2_3();

  #if (SERIAL_DEBUG == 1)
  if (DebugCounter == SERIAL_DEBUG_TIMER)
  {
    //Serial.print("AIN0: "); Serial.println(AdcDiff_0_1 * AdcGain);
    //Serial.print("AIN1: "); Serial.println(AdcDiff_2_3 * AdcGain);
    Serial.print("AIN0: "); Serial.println(AdcDiff_0_1);
    Serial.print("AIN1: "); Serial.println(AdcDiff_2_3);
  }
  #endif

}

////////////////////////////////
// Máquina de estados general //
////////////////////////////////
void _GeneralState () {

  // Si NO estamos en estado forzado...
  if (ForcedState2 == false)
  {
    
    #if (SERIAL_DEBUG == 1)
    if (DebugCounter == SERIAL_DEBUG_TIMER)
    {
      Serial.println("Estado NO forzado");
    }
    #endif
    
    // Chequemos las entradas...
    if ((In1Status == LOW) && (In2Status == LOW))
    {
      GeneralState = STATE1;
  
      // Lectura del A0_1, si estmos a menos del nivel resetemos...
      if (AdcDiff_0_1 < A0_1_LEVEL)
        A0_1_Counter = 0;

      // Lectura del A2_3, si estmos a menos del nivel resetemos...
      if (AdcDiff_2_3 < A2_3_LEVEL)
        A2_3_Counter = 0;

      // Comprobamos el tiempo...
      if ((A0_1_Counter > A0_1_TIEMPO) || (A2_3_Counter > A2_3_TIEMPO))
      {
        GeneralState = STATE2;
        ForcedState2 = true;
        A0_1_Counter = 0;
        A2_3_Counter = 0;
      }
  
    }
    else if ((In1Status == HIGH))
    {
      GeneralState = STATE2;
    }
    else if ((In1Status == LOW) && (In2Status == HIGH))
      GeneralState = STATE3;

  }
  // Si estamos en estado forzado 2...
  else
  {

    #if (SERIAL_DEBUG == 1)
    if (DebugCounter == SERIAL_DEBUG_TIMER)
    {
      Serial.println("Estado 2 forzado");
    }
    #endif
    
    GeneralState = STATE2;

    if (A0_1_Counter > STATE2_FORCED_TIEMPO)
    {
      ForcedState2 = false;
      A0_1_Counter = 0;
      A2_3_Counter = 0;
    }
  }

    
  // Si hay cambio de estado...
  if (GeneralState_ant != GeneralState)
  {
    // Iniciamos la máquina de estados...
    StateCounter = 0;
    State = 0;

    digitalWrite(OUT1, LOW);
    digitalWrite(OUT2, LOW);
    digitalWrite(OUT3, LOW);   
    digitalWrite(OUT4, LOW);
    digitalWrite(OUT5, LOW);
  }

  GeneralState_ant = GeneralState;
  StateCounter++; // Incrementamos el contador...

  A0_1_Counter++;
  A2_3_Counter++;

  if (GeneralState == STATE1)
    _State1();
  else if (GeneralState == STATE2)
    _State2();
  else
    _State3();

  #if (SERIAL_DEBUG == 1)
  if (DebugCounter == SERIAL_DEBUG_TIMER)
  {
    if (GeneralState == STATE1)
      Serial.println("*** Estado 1 ***");
    else if (GeneralState == STATE2)
      Serial.println("*** Estado 2 ***");
    else
      Serial.println("*** Estado 3 ***");
  }
  #endif

  // Led de estado...
  _LedState(GeneralState);
}

////////////////////////////////////////////////////////
//  In1 In2 |   Out1  Out2  Out3  Out4  Out5          //
//  ----------------------------------------          //
//  0   0   |   1     1     0     0     0   Estado 1  //
////////////////////////////////////////////////////////
void _State1 () {

  switch (State)
  {
    case 0:
      digitalWrite(OUT1, LOW);
      digitalWrite(OUT2, LOW);
      digitalWrite(OUT3, LOW);   
      digitalWrite(OUT4, LOW);
      digitalWrite(OUT5, LOW);
      if (StateCounter >= STATE1_TIEMPO_0_1)
      {
        StateCounter = 0;
        State = 1;
      }
      break;

    case 1:
      digitalWrite(OUT1, LOW);
      digitalWrite(OUT2, HIGH);
      digitalWrite(OUT3, LOW);   
      digitalWrite(OUT4, LOW); 
      digitalWrite(OUT5, LOW);
      if (StateCounter >= STATE1_TIEMPO_1_2)
      {
        StateCounter = 0;
        State = 2;
      }
      break;

    case 2:
      digitalWrite(OUT1, HIGH);
      digitalWrite(OUT2, HIGH);
      digitalWrite(OUT3, LOW);   
      digitalWrite(OUT4, LOW); 
      digitalWrite(OUT5, LOW);
      break;
  }
}

////////////////////////////////////////////////////////
//  In1 In2 |   Out1  Out2  Out3  Out4  Out5          //
//  ----------------------------------------          //
//  1   0   |   0     0     1     1     0   Estado 2  //
//  1   1   |   0     0     1     1     0   Estado 2  //
////////////////////////////////////////////////////////
void _State2 () {

  switch (State)
  {
    case 0:
      digitalWrite(OUT1, LOW);
      digitalWrite(OUT2, LOW);
      digitalWrite(OUT3, LOW);   
      digitalWrite(OUT4, LOW);
      digitalWrite(OUT5, LOW);
      if (StateCounter >= STATE2_TIEMPO_0_1)
      {
        StateCounter = 0;
        State = 1;
      }
      break;

    case 1:
      digitalWrite(OUT1, LOW);
      digitalWrite(OUT2, LOW);
      digitalWrite(OUT3, HIGH);   
      digitalWrite(OUT4, LOW);
      digitalWrite(OUT5, LOW);
      if (StateCounter >= STATE2_TIEMPO_1_2)
      {
        StateCounter = 0;
        State = 2;
      }
      break;

    case 2:
      digitalWrite(OUT1, LOW);
      digitalWrite(OUT2, LOW);
      digitalWrite(OUT3, HIGH);   
      digitalWrite(OUT4, HIGH); 
      digitalWrite(OUT5, LOW);
      break;
  }
}

////////////////////////////////////////////////////////
//  In1 In2 |   Out1  Out2  Out3  Out4  Out5          //
//  ----------------------------------------          //
//  0   1   |   0     0     0     1     1   Estado 3  //
////////////////////////////////////////////////////////
void _State3 () {

  switch (State)
  {
    case 0:
      digitalWrite(OUT1, LOW);
      digitalWrite(OUT2, LOW);
      digitalWrite(OUT3, LOW);   
      digitalWrite(OUT4, LOW);
      digitalWrite(OUT5, LOW);
      if (StateCounter >= STATE3_TIEMPO_0_1)
      {
        StateCounter = 0;
        State = 1;
      }
      break;

    case 1:
      digitalWrite(OUT1, LOW);
      digitalWrite(OUT2, LOW);
      digitalWrite(OUT3, LOW);   
      digitalWrite(OUT4, LOW);
      digitalWrite(OUT5, HIGH);
      if (StateCounter >= STATE3_TIEMPO_1_2)
      {
        StateCounter = 0;
        State = 2;
      }
      break;

    case 2:
      digitalWrite(OUT1, LOW);
      digitalWrite(OUT2, LOW);
      digitalWrite(OUT3, LOW);   
      digitalWrite(OUT4, HIGH); 
      digitalWrite(OUT5, HIGH);
      break;
  }
}

//////////////////////
// Parpadeo del Led //
//////////////////////
void _LedState (int pulsos) {

  // Incremento del contador...
  LedCounter++;
  
  if (LedCounter > LedDuration)
  {
    LedCounter = 0;
    
    if (LedPulsos < 2*pulsos)
    {
      LedDuration = PULSO_CORTO;
      LedPulsos++;

      // Cambio de estado del Led...
      if (LedNextState == true)
        LedNextState = false;
      else
        LedNextState = true;
    }
    else
    {
      LedDuration = PULSO_LARGO;
      LedPulsos = 0;

      LedNextState = false;
    }
    
    // Cambio de estado del Led...
    if (LedNextState == true)
      digitalWrite(LED, HIGH);
    else
      digitalWrite(LED, LOW);

  }
}

