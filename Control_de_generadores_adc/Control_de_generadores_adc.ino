/*
  Control de Generadores para Campo de Vuelo Sesma.
  Creado  06/12/2015
  Modif   21/01/2018
  Modif   09/12/2023
  Modif   11/05/2024

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

// Entrada Analogica
#define ANA_IN0   A0
#define ANA_IN1   A1

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

#define A0_TIEMPO             1 // 200     // 4x500ms = 2 segundos
#define A1_TIEMPO             1 // 200     // 4x500ms = 2 segundos
#define STATE2_FORCED_TIEMPO  1000   // 18000x10ms = 3minutos

#define A0_LEVEL              800   // 600    // 1024 -> 5V así 600 -> 5V*600/1024 = 2,9V
#define A1_LEVEL              800   //500     // 1024 -> 5V así 500 -> 5V*500/1024 = 2,44V

// Estados Generales
#define STATE1        1
#define STATE2        2
#define STATE3        3

#define PULSO_CORTO   100   // 100x10ms
#define PULSO_LARGO   150   // 150x10ms

// Variables de salida
int Out1 = 0;
int Out2 = 0;
int Out3 = 0;
int Out4 = 0;
int Out5 = 0;

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

// Variables para Leds
bool  LedNextState = false;
int   LedCounter = 0;
int   LedDuration = 0;
int   LedPulsos = 0;

// Variables para leer la entradas analogicas
//#define ANA_ARRAY_SIZE  10 //10
//int     AnaInPointer = 0;

int   AnaIn0Value = 0;
//int   AnaIn0Array[ANA_ARRAY_SIZE];
int   AnaIn1Value = 0;
//int   AnaIn1Array[ANA_ARRAY_SIZE];

int   A0_Counter = 0;
int   A1_Counter = 0;
int   F_Counter = 0;
int   AINs_Counter = 0;

int ForcedState2 = 0;

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
  _InitAnalogInputs();
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

///////////////////////////////////////////////
// Inicializacion de la entrada Analogica    //
///////////////////////////////////////////////
void _InitAnalogInputs() {

  AnaIn0Value = 0;
  AnaIn1Value = 0;

  /*
  for (int i = 0; i < ANA_ARRAY_SIZE; i++)
  {
    AnaIn0Array[i] = 0;
    AnaIn1Array[i] = 0;
  }

  AnaInPointer = 0;
  */
}

/////////////////////////////////////////////
// Función Principal                       //
// Se ejecuta en bucle continuo cada 10 ms //
/////////////////////////////////////////////
void loop() {

  // Leemos las entradas digitales.
  _ReadInputs();

  // Leemos las entradas del ADC.
  if (AINs_Counter == 50)
    _ReadAnalogInputs();

  // Chequeo del estado general.
  _GeneralState();
  _Outs();

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

//////////////////////////////////////
// Lectura de la entrada Analogica  //
// con filtro software              //
//////////////////////////////////////
void _ReadAnalogInputs() {

  /*
  int aIn0Acc = 0;
  int aIn1Acc = 0;

  // Leemos la entrada analógica...
  AnaIn0Array[AnaInPointer] = analogRead(ANA_IN0);
  AnaIn1Array[AnaInPointer] = analogRead(ANA_IN1);
  
  AnaInPointer++;
  if (AnaInPointer >= ANA_ARRAY_SIZE)
    AnaInPointer = 0;

  // Calculamos la media del Array...
  for (int i = 0; i < ANA_ARRAY_SIZE; i++)
  {
    aIn0Acc = aIn0Acc + AnaIn0Array[i];
    aIn1Acc = aIn1Acc + AnaIn1Array[i];
    //delay(50);
  }
  
  AnaIn0Value = aIn0Acc/ANA_ARRAY_SIZE;
  AnaIn1Value = aIn1Acc/ANA_ARRAY_SIZE;
  */

  AnaIn0Value = analogRead(ANA_IN0);
  AnaIn1Value = analogRead(ANA_IN1);
  
  #if (SERIAL_DEBUG == 1)
  //if (DebugCounter == SERIAL_DEBUG_TIMER)
  {
    Serial.println(" ");
    Serial.print("AIN0 - Luces:     "); Serial.print(AnaIn0Value); Serial.print("    Cont: "); Serial.println(A0_Counter);
    Serial.print("AIN1 - Enchufes:  "); Serial.print(AnaIn1Value); Serial.print("    Cont: "); Serial.println(A1_Counter);
    Serial.println(" ");
  }
  #endif
  
}

////////////////////////////////
// Máquina de estados general //
////////////////////////////////
void _GeneralState () {

  // Si NO estamos en estado forzado...
  if (ForcedState2 == 0)
  {    
    // Chequemos las entradas...
    if ((In1Status == LOW) && (In2Status == LOW))
    {
      GeneralState = STATE1;
  
      if (AINs_Counter == 50)
      {
        A0_Counter++;
        A1_Counter++;

        // Lectura del A0, si estmos a menos del nivel resetemos...
        if (AnaIn0Value < A0_LEVEL)
          A0_Counter = 0;

        // Lectura del A1, si estmos a menos del nivel resetemos...
        if (AnaIn1Value < A1_LEVEL)
          A1_Counter = 0;

        // Comprobamos el tiempo...
        if ((A0_Counter > A0_TIEMPO) || (A1_Counter > A1_TIEMPO))
        {
          GeneralState = STATE2;
          ForcedState2 = 1;
          A0_Counter = 0;
          A1_Counter = 0;
          F_Counter = 0;
        }
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
    
    GeneralState = STATE2;

    if (F_Counter > STATE2_FORCED_TIEMPO)
    {
      ForcedState2 = 0;
      A0_Counter = 0;
      A1_Counter = 0;
    }
  }
    
  // Si hay cambio de estado...
  if (GeneralState_ant != GeneralState)
  {
    // Iniciamos la máquina de estados...
    StateCounter = 0;
    State = 0;

    Out1 = 0;
    Out2 = 0;
    Out3 = 0;
    Out4 = 0;
    Out5 = 0;
  }

  GeneralState_ant = GeneralState;
  StateCounter++; // Incrementamos el contador...

  AINs_Counter++;
  if (AINs_Counter > 51)
    AINs_Counter = 0;

  F_Counter++;

  if (GeneralState == STATE1)
    _State1();
  else if (GeneralState == STATE2)
    _State2();
  else
    _State3();

  #if (SERIAL_DEBUG == 1)
  if (DebugCounter == SERIAL_DEBUG_TIMER)
  {
    Serial.println("In1  In 2 | Out1  Out2  Out3  Out4  Out5");
    Serial.println("----------|-----------------------------");
    Serial.print("  ");
    Serial.print(In1Status); Serial.print("     ");
    Serial.print(In2Status); Serial.print("     ");
    Serial.print(Out1); Serial.print("     ");
    Serial.print(Out2); Serial.print("     ");
    Serial.print(Out3); Serial.print("     ");
    Serial.print(Out4); Serial.print("     ");
    Serial.print(Out5); Serial.print("   - Estado ");
    Serial.print(GeneralState);  Serial.print (" / "); Serial.println(StateCounter);
    Serial.print (" F "); Serial.print(ForcedState2); Serial.print (" / "); Serial.print(F_Counter);
    Serial.println(" ");
  }
  #endif

  // Led de estado...
  _LedState(GeneralState);
}

/////////////
// Salidas //
/////////////
void _Outs () {

  if (Out1 == 1)
    digitalWrite(OUT1, HIGH);
  else
    digitalWrite(OUT1, LOW);

  if (Out2 == 1)
    digitalWrite(OUT2, HIGH);
  else
    digitalWrite(OUT2, LOW);
  
  if (Out3 == 1)
    digitalWrite(OUT3, HIGH);
  else
    digitalWrite(OUT3, LOW);

  if (Out4 == 1)
    digitalWrite(OUT4, HIGH);
  else
    digitalWrite(OUT4, LOW);

  if (Out5 == 1)
    digitalWrite(OUT5, HIGH);
  else
    digitalWrite(OUT5, LOW);

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
      Out1 = 0;
      Out2 = 0;
      Out3 = 0;
      Out4 = 0;
      Out5 = 0;
    
      if (StateCounter >= STATE1_TIEMPO_0_1)
      {
        StateCounter = 0;
        State = 1;
      }
      break;

    case 1:
      Out1 = 0;
      Out2 = 1;
      Out3 = 0;
      Out4 = 0;
      Out5 = 0;
    
      if (StateCounter >= STATE1_TIEMPO_1_2)
      {
        StateCounter = 0;
        State = 2;
      }
      break;

    case 2:
      Out1 = 1;
      Out2 = 1;
      Out3 = 0;
      Out4 = 0;
      Out5 = 0;

      StateCounter = 0;
      
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
      Out1 = 0;
      Out2 = 0;
      Out3 = 0;
      Out4 = 0;
      Out5 = 0;
      
      if (StateCounter >= STATE2_TIEMPO_0_1)
      {
        StateCounter = 0;
        State = 1;
      }
      break;

    case 1:
      Out1 = 0;
      Out2 = 0;
      Out3 = 1;
      Out4 = 0;
      Out5 = 0;
    
      if (StateCounter >= STATE2_TIEMPO_1_2)
      {
        StateCounter = 0;
        State = 2;
      }
      break;

    case 2:
      Out1 = 0;
      Out2 = 0;
      Out3 = 1;
      Out4 = 1;
      Out5 = 0;

      StateCounter = 0;
    
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
      Out1 = 0;
      Out2 = 0;
      Out3 = 0;
      Out4 = 0;
      Out5 = 0;

      if (StateCounter >= STATE3_TIEMPO_0_1)
      {
        StateCounter = 0;
        State = 1;
      }
      break;

    case 1:
      Out1 = 0;
      Out2 = 0;
      Out3 = 0;
      Out4 = 0;
      Out5 = 1;
    
      if (StateCounter >= STATE3_TIEMPO_1_2)
      {
        StateCounter = 0;
        State = 2;
      }
      break;

    case 2:
      Out1 = 0;
      Out2 = 0;
      Out3 = 0;
      Out4 = 1;
      Out5 = 1;
    
      StateCounter = 0;
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

