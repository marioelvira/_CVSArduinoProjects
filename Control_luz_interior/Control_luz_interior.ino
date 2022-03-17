/*
  Control de Luz Interior para Campo de Vuelo Sesma.
  Creado  08/01/2019
  Modif   11/02/2019
  Modif   15/03/2022

  Salidas
  -------
  Activacion_Luz: OFF: 0 -> ON: 1
  Cuando activa la salida está encendido durante 30 minutos.
  
  Entradas
  --------
  Pulsador: OFF: 0 -> ON: 1
  OFF    ON    OFF
  _____|------|_____
  Si se da un pulso y la luz Apagada -> Encender Luz.
  Si se da un pulso y la luz Encendida -> Apagar Luz.

  Generador: ON: 1 -> OFF: 0
  ON       OFF
  --------|_________
  Si está a ON no se aplica el temporizador.

  El sistema arranca y no hace caso al pulsador hasta TIMER_INIT_SEC segundos.
  El sistema arranca con la salida 2 a uno.

*/

// Placas de Evaluación.
#define ARDUINO_NANO   1
#define ARDUINO_UNO    2

// Placa en uso.
#define USAR    ARDUINO_NANO  

#define OUT_OFF        0
#define OUT_ON         1

#define FLANCO_UP     0
#define FLANCO_DOWN   1
#define FLANCO        FLANCO_UP  // FLANCO_DOWN

#if (USAR == ARDUINO_NANO)
// Salidas Digitales
#define OUT_LUZ         2

// Entradas Digitales
#define IN_PULSADOR     4   // Pulsador
#define IN_GENERADOR    7   // Detección de generador

// Led Indicador
#define LED             13

#endif

#if (USAR == ARDUINO_UNO)
// TODO
#endif

// Temporizaciones
#define NO_PULSACION        0   // x10ms
#define PULSACION_CORTA     50  // x10ms
#define PULSACION_LARGA     200 // x10ms
#define AUTOMAN_FILTRO      25  // x10ms

// Duración pulsos Led de Status
#define PULSO_LED_CORTO     50  // x10ms
#define PULSO_LED_LARGO     200 // x10ms

#define TIMER_LUZ_ON_SEC      900  // 15x60 15 minutos 
//#define TIMER_LUZ_ON_SEC    15   // (Variable a cambiar)
#define TIMER_INIT_SEC        10   // (Variable a cambiar)

// Estados principales...
#define STATE_INIT          1
#define STATE_STANDBY       2
#define STATE_LUZ_ON        3

#define GENERATOR_DETEC     HIGH

// Salidas Digitales
int   OutLuz;

// Variables para leer las Entradas
int   PulsadorDigInStatus = 0;
int   PulsadorDigInStatus_ant = 0;
int   PulsadorDigInCounter = 0;
int   PulsadorPulsacion = 0;
int   pulsadorInState;

int   GeneradorDigInStatus = 0;
int   GeneradorDigInStatus_ant = 0;
int   GeneradorDigInCounter = 0;
int   generadorInState;

// Control del Led...
bool  LedSNextState = false;
int   LedSCounter = 0;
int   LedSDuration = 0;
int   LedSPulsos = 0;

int   LedStatePulse;

// Estado principal
int   ControlState;
int   TimeControlSec = 0;

int   TickSys = 0;

// Dedug...
#define SERIAL_DEBUG  1
#define SERIAL_DEBUG_TIMER  100
int    DebugCounter = 0;

/////////////////////////////////////////////
// Inicialización de las salidas digitales //
/////////////////////////////////////////////
void _InitDigitalOutputs() {

  pinMode(OUT_LUZ,    OUTPUT);
  digitalWrite(OUT_LUZ,    LOW);

  OutLuz   = OUT_ON; // OUT_OFF;
}

//////////////////////////////////////////////
// Inicialización de las entradas digitales //
//////////////////////////////////////////////
void _InitDigitalInputs() {

  pinMode(IN_PULSADOR,    INPUT);
  pinMode(IN_GENERADOR,   INPUT);

  PulsadorDigInStatus = digitalRead(IN_PULSADOR);
  PulsadorDigInStatus_ant = PulsadorDigInStatus;
  PulsadorDigInCounter = 0;

  GeneradorDigInStatus = digitalRead(IN_GENERADOR);
  GeneradorDigInStatus_ant = GeneradorDigInStatus;
  GeneradorDigInCounter = 0;
}

/////////////////////////////
// Inicialización del Leds //
/////////////////////////////
void _InitLeds() {

  // Led Indicador de Estado
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW); 

  LedSNextState = false;
  LedSCounter = 0;
  LedSDuration = PULSO_LED_CORTO;
  LedSPulsos = 0;
}

//////////////////////////////
// Función de Inicilización //
//////////////////////////////
void setup() {

  #if (SERIAL_DEBUG == 1)
  Serial.begin(9600);
  Serial.println(">> Starting !!!");
  #endif

  _InitDigitalOutputs();
  _InitDigitalInputs();
  _InitLeds();

  ControlState = STATE_INIT;
}

////////////////////////////////////////
// Lectura de las entrada digital     //
// con filtro software antirebotes    //
////////////////////////////////////////
void _ReadDigitalInputs() {
  
  // Leemos las entradas digitales...
  pulsadorInState   = digitalRead(IN_PULSADOR);
  generadorInState  = digitalRead(IN_GENERADOR);

  //////////////////////
  // Entrada Pulsador //
  //////////////////////
  if (PulsadorDigInStatus_ant == pulsadorInState)
    PulsadorDigInCounter++; // Incrementamos el contador.
  else
  {
    // Si detectamos un flanco ...
    if (PulsadorDigInStatus_ant == FLANCO)
    {
      if (PulsadorDigInCounter > PULSACION_LARGA)
      {
        PulsadorPulsacion = PULSACION_LARGA;
      }
      else if (PulsadorDigInCounter > PULSACION_CORTA)
      {
        PulsadorPulsacion = PULSACION_CORTA;
      }

      #if (SERIAL_DEBUG == 1)
      if (PulsadorPulsacion == PULSACION_LARGA)
        Serial.println(">> Pulsador -> Pulsacion Larga");
      else if (PulsadorPulsacion == PULSACION_CORTA)
        Serial.println(">> Pulsador -> Pulsacion Corta");
      else
        Serial.println(">> Pulsador -> Error Pulsacion");
      #endif
    }

    PulsadorDigInCounter = 0;
  }

  // Aplicamos el filto software en Modo ...
  if (PulsadorDigInCounter > AUTOMAN_FILTRO)
    PulsadorDigInStatus = pulsadorInState;

  ///////////////////////
  // Entrada Generador //
  ///////////////////////

  if (GeneradorDigInStatus_ant == generadorInState)
    GeneradorDigInCounter++; // Incrementamos el contador.
  else
    GeneradorDigInCounter = 0;

  // Aplicamos el filto software...
  if (GeneradorDigInCounter > AUTOMAN_FILTRO)
    GeneradorDigInStatus = generadorInState;   // Actualizamos la lectura de la entrada...

  // Almacenamos el valor anterior...
  PulsadorDigInStatus_ant  = pulsadorInState;
  GeneradorDigInStatus_ant = generadorInState;
}

////////////////////////////
// Update Outs            //
////////////////////////////
void _UpdateOuts(void) {
  
  if (OutLuz == OUT_ON)
    digitalWrite(OUT_LUZ, HIGH);
  else
    digitalWrite(OUT_LUZ, LOW);
}

/////////////////////
// Control del Led //
/////////////////////
void _LedSPulso (int led_out, int pulsos, int pulso_corto, int pulso_largo) {

  // Incremento del contador...
  LedSCounter++;
  
  if (LedSCounter > LedSDuration)
  {
    LedSCounter = 0;
    
    if (LedSPulsos < pulsos)
    {
      LedSDuration = pulso_corto;
      LedSPulsos++;

      // Cambio de estado del Led...
      if (LedSNextState == true)
        LedSNextState = false;
      else
        LedSNextState = true;
    }
    else
    {
      LedSDuration = pulso_largo;
      LedSPulsos = 0;

      LedSNextState = false;
    }
    
    // Cambio de estado del Led...
    if (LedSNextState == true)
      digitalWrite(led_out, HIGH);
    else
      digitalWrite(led_out, LOW);
  }
}

////////////////////////
// Máquina de Control //
////////////////////////
void _StatusControl(void) {

  switch (ControlState) {

    case STATE_INIT:
      OutLuz   = OUT_ON;

      if (TimeControlSec > TIMER_INIT_SEC)
      {
        ControlState = STATE_LUZ_ON;
        TimeControlSec = 0;
      }
      
      break;
      
    case STATE_STANDBY:
      OutLuz = OUT_OFF;

      LedStatePulse = 1;

      // Si se pulsa el pulsador...
      if ((PulsadorPulsacion == PULSACION_LARGA) || (PulsadorPulsacion == PULSACION_CORTA))
      {
        TimeControlSec = 0;
        ControlState = STATE_LUZ_ON;
      }
    
      break;

    case STATE_LUZ_ON:
      OutLuz = OUT_ON;

      // Si el generador está encendido...
      if (GeneradorDigInStatus == GENERATOR_DETEC)
        TimeControlSec = 0;   // Reseteamos el contador...
       
      if (TimeControlSec > TIMER_LUZ_ON_SEC)
        ControlState = STATE_STANDBY;

      if (GeneradorDigInStatus == GENERATOR_DETEC)
        LedStatePulse = 4;
      else
        LedStatePulse = 8;

      // Si se pulsa el pulsador...
      if ((PulsadorPulsacion == PULSACION_LARGA) || (PulsadorPulsacion == PULSACION_CORTA))
      {
        TimeControlSec = 0;
        ControlState = STATE_STANDBY;
      }

      break;
  }
}

/////////////////////////////////////////////
// Función Principal                       //
// Se ejecuta en bucle continuo cada 10 ms //
/////////////////////////////////////////////
void loop() {

  // Leemos las entradas digitales
  _ReadDigitalInputs();

  _UpdateOuts();

  // Maquina de control
  _StatusControl();

  // Mostramos el estado...
  _LedSPulso(LED, LedStatePulse, PULSO_LED_CORTO, PULSO_LED_LARGO);

  #if (SERIAL_DEBUG == 1)
  if (DebugCounter == SERIAL_DEBUG_TIMER)
  {
    Serial.print("Control State: "); Serial.println(ControlState);

    if (OutLuz == OUT_ON)
      Serial.println("  -> Out Luz: ON");
    else
      Serial.println("  -> Out Luz: OFF");

    if (pulsadorInState == 0)
      Serial.println("  <- In Puls: 0");
    else
      Serial.println("  <- In Puls: 1");

    if (GeneradorDigInStatus == GENERATOR_DETEC)
      Serial.println("  <- In Gen: ON");
    else
      Serial.println("  <- In Gen: OFF");

    Serial.println("------------------");
  }

  DebugCounter++;
  if (DebugCounter > SERIAL_DEBUG_TIMER)
    DebugCounter = 0;

  #endif

  // Reset de Pulsaciones...
  PulsadorPulsacion   = NO_PULSACION;
  //Pulsacion         = NO_PULSACION;

  // Contador de Segundos ...
  if (TickSys > 100)
  {
    TickSys = 0;
    TimeControlSec++;
  }

  TickSys++;
  
  // Ponemos un retado de 10 milisegundos en cada iteración.
  delay(10);
}
