/*
  Control de Luz Exterior para Campo de Vuelo Sesma.
  Creado  03/12/2016
  Modif   

  Salidas
  -------
  Activacion_Luz: OFF: 0 -> ON: 1
  Ataca un transistor que cierra un Relé.
  Cuando activa la salida está encendido durante 30 minutos.

  Buzzer: Ataca un Buzzer con 0-5V
  Indica que quedan 20 segundos para que se apague la luz exterior.

  Entradas
  --------
  Pulsador: OFF: 1 -> ON: 0
  OFF    ON    OFF
  -----|_____|----- 
  Si se da un pulso y la luz Apagada -> Encender Luz.
  Si se da un pulso y la luz Encendida -> Apagar Luz.

  Telemando: OFF: 1 -> ON: 0
  OFF       ON
  --------|_________
  Si está a ON -> Encender Luz, sino apagar Luz.
    
  Salida Alarma Encendido: OFF: 1 -> ON: 0
  OFF    ON    OFF
  -----|_____|----- 
  Cuando se activa la alarma, se da un pulso -> Apagar Luz.

  Generador: OFF: 1 -> ON: 0
  OFF       ON
  --------|_________
  Si está a ON no se aplica el temporizador.

  Alarma Detección Intruso: OFF: 1 -> ON: 0
  OFF    ON    OFF
  -----|_____|----- 
  Si se da un pulso -> Encender Luz.
  
  LDR: Entrada que indica si hay luz solar.
  Si está a OFF -> Hay Luz Solar
  Si está a ON -> NO hay Luz Solar

*/

// Placas de Evaluación.
#define ARDUINO_NANO   1
#define ARDUINO_UNO    2

// Placa en uso.
#define USAR    ARDUINO_NANO  

#define OUT_OFF   0
#define OUT_ON    1
#define OUT_PULSE 2

#define FLANCO_UP     0
#define FLANCO_DOWN   1
#define FLANCO        FLANCO_DOWN

#if (USAR == ARDUINO_NANO)
// Salidas Digitales
#define OUT_LUZ         2
#define OUT_BUZZER      3

// Entradas Digitales
#define IN_PULSADOR     4   // Pulsador
#define IN_TELEMANDO    5   // Telemando
#define IN_ALARMA_ACT   6   // Activación de Alarma
#define IN_GENERADOR    7   // Detección de generador
#define IN_INTRUSO      8   // Salto de alarma por intruso 

// Led Indicador
#define LED             13

// Entrada Analógica
#define LDR_POS_ANA_IN   A0  // Entrada posición LDR

#define ANA_LUZ_ON      450 // 0 a 1024

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

#define TIMER_LUZ_ON_SEC    30

// Estados principales...
#define STATE_STANDBY       0
#define STATE_LUZ_ON        1
#define STATE_LUZ_OFF       2

#define GENERATOR_DETEC     LOW
#define TELEMANDO_DETEC     LOW
#define INTRUSO_DETEC       LOW

// Salidas Digitales
int   OutLuz;
int   OutBuzzer;

// Variables para leer las Entradas
int   PulsadorDigInStatus = 0;
int   PulsadorDigInStatus_ant = 0;
int   PulsadorDigInCounter = 0;
int   PulsadorPulsacion = 0;

int   TelemandoDigInStatus = 0;
int   TelemandoDigInStatus_ant = 0;
int   TelemandoDigInCounter = 0;

int   AlarmaDigInStatus = 0;
int   AlarmaDigInStatus_ant = 0;
int   AlarmaDigInCounter = 0;
int   AlarmaPulsacion = 0;

int   GeneradorDigInStatus = 0;
int   GeneradorDigInStatus_ant = 0;
int   GeneradorDigInCounter = 0;

int   IntrusoDigInStatus = 0;
int   IntrusoDigInStatus_ant = 0;
int   IntrusoDigInCounter = 0;

/*
int   DigInStatus = 0;
int   DigInStatus_ant = 0;
int   DigInCounter = 0;
int   Pulsacion = 0;
*/

// Control del Led...
bool  LedSNextState = false;
int   LedSCounter = 0;
int   LedSDuration = 0;
int   LedSPulsos = 0;

int   LedStatePulse;

// Control del Buzzer...
bool  BuzzerNextState = false;
int   BuzzerCounter = 0;
int   BuzzerDuration = 0;
int   BuzzerPulsos = 0;

int   BuzzerState;

// Estado principal
int   ControlState;
int   TimeLuzOnSec = 0;

int   TickSys = 0;

// Variables para leer la entrada analógica
int   AnaInValue = 0;
int   AnaInValue_ant = 0;

bool  bTelemandoStatus = false;
bool  bIntrusoStatus = false;

// Dedug...
#define SERIAL_DEBUG  1
#define SERIAL_DEBUG_TIMER  100
int    DebugCounter = 0;

/////////////////////////////////////////////
// Inicialización de las salidas digitales //
/////////////////////////////////////////////
void _InitDigitalOutputs() {

  pinMode(OUT_LUZ,    OUTPUT);
  pinMode(OUT_BUZZER, OUTPUT);
  digitalWrite(OUT_LUZ,    LOW);
  digitalWrite(OUT_BUZZER, LOW);

  OutLuz   = OUT_OFF;
  OutBuzzer = OUT_OFF;
}

//////////////////////////////////////////////
// Inicialización de las entradas digitales //
//////////////////////////////////////////////
void _InitDigitalInputs() {

  pinMode(IN_PULSADOR,    INPUT);
  pinMode(IN_TELEMANDO,   INPUT);
  pinMode(IN_ALARMA_ACT,  INPUT);
  pinMode(IN_GENERADOR,   INPUT);
  pinMode(IN_INTRUSO,    INPUT);

  PulsadorDigInStatus = digitalRead(IN_PULSADOR);
  PulsadorDigInStatus_ant = PulsadorDigInStatus;
  PulsadorDigInCounter = 0;

  TelemandoDigInStatus = digitalRead(IN_TELEMANDO);
  TelemandoDigInStatus_ant = TelemandoDigInStatus;
  TelemandoDigInCounter = 0;

  AlarmaDigInStatus = digitalRead(IN_ALARMA_ACT);
  AlarmaDigInStatus_ant = AlarmaDigInStatus;
  AlarmaDigInCounter = 0;

  GeneradorDigInStatus = digitalRead(IN_GENERADOR);
  GeneradorDigInStatus_ant = GeneradorDigInStatus;
  GeneradorDigInCounter = 0;

  IntrusoDigInStatus = digitalRead(IN_INTRUSO);
  IntrusoDigInStatus_ant = IntrusoDigInStatus;
  IntrusoDigInCounter = 0;

  bTelemandoStatus = false;
  bIntrusoStatus = false;
  
  /*
  DigInStatus = digitalRead(IN_);
  DigInStatus_ant = DigInStatus;
  DigInCounter = 0;
  */  
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


///////////////////////////////////////////////
// Inicialización de la entrada Analógica    //
///////////////////////////////////////////////
void _InitAnalogInput() {
  
  AnaInValue = 0;
  AnaInValue_ant = 0;
}

//////////////////////////////
// Función de Inicilización //
//////////////////////////////
void setup() {

  #if (SERIAL_DEBUG == 1)
  Serial.begin(9600);
  #endif

  _InitDigitalOutputs();
  _InitDigitalInputs();
  _InitAnalogInput();
  _InitLeds();

  ControlState = STATE_STANDBY;
}

////////////////////////////////////////
// Lectura de las entrada digital     //
// con filtro software antirebotes    //
////////////////////////////////////////
void _ReadDigitalInputs() {

  int pulsadorInState;
  int telemandoInState;
  int alarmaInState;
  int generadorInState;
  int intrusoInState;
  //int _InState;
  
  // Leemos las entradas digitales...
  pulsadorInState   = digitalRead(IN_PULSADOR);
  telemandoInState  = digitalRead(IN_TELEMANDO);
  alarmaInState     = digitalRead(IN_ALARMA_ACT);
  generadorInState  = digitalRead(IN_GENERADOR);
  intrusoInState    = digitalRead(IN_INTRUSO);
  //_InState      = digitalRead(IN_XXXXXXXX);

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
  // Entrada Telemando //
  ///////////////////////
  
  if (TelemandoDigInStatus_ant == telemandoInState)
    TelemandoDigInCounter++; // Incrementamos el contador.
  else
    TelemandoDigInCounter = 0;

  // Aplicamos el filto software en Modo ...
  if (TelemandoDigInCounter > AUTOMAN_FILTRO)
    TelemandoDigInStatus = telemandoInState;

  #if (SERIAL_DEBUG == 1)
  if (DebugCounter == SERIAL_DEBUG_TIMER)
  {
    if (TelemandoDigInStatus == TELEMANDO_DETEC)
      Serial.println("*** Telemando On ***");
    else
      Serial.println("*** Telemando Off ***");
  }
  #endif

  ///////////////////////////////
  // Entrada Alarma Activación //
  ///////////////////////////////
  if (AlarmaDigInStatus_ant == alarmaInState)
    AlarmaDigInCounter++; // Incrementamos el contador.
  else
  {   
    // Si detectamos un flanco...
    if (AlarmaDigInStatus_ant == FLANCO)
    {
      if (AlarmaDigInCounter > PULSACION_LARGA)
      {
        AlarmaPulsacion = PULSACION_LARGA;
      }
      else if (AlarmaDigInCounter > PULSACION_CORTA)
      {
        AlarmaPulsacion = PULSACION_CORTA;
      }

      #if (SERIAL_DEBUG == 1)
      if (AlarmaPulsacion == PULSACION_LARGA)
        Serial.println(">> Alarma -> Pulsacion Larga");
      else if (AlarmaPulsacion == PULSACION_CORTA)
        Serial.println(">> Alarma -> Pulsacion Corta");
      else
        Serial.println(">> Alarma -> Error Pulsacion");
      #endif
    }

    AlarmaDigInCounter = 0;
  }

  // Aplicamos el filto software en Modo ...
  if (AlarmaDigInCounter > AUTOMAN_FILTRO)
    AlarmaDigInStatus = alarmaInState;

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

  #if (SERIAL_DEBUG == 1)
  if (DebugCounter == SERIAL_DEBUG_TIMER)
  {
    if (GeneradorDigInStatus == GENERATOR_DETEC)
      Serial.println("*** Generador On ***");
    else
      Serial.println("*** Generador Off ***");
  }
  #endif


  /////////////////////
  // Entrada Intruso //
  ////////////////////
  
  if (IntrusoDigInStatus_ant == intrusoInState)
    IntrusoDigInCounter++; // Incrementamos el contador.
  else
    IntrusoDigInCounter = 0;

  // Aplicamos el filto software en Modo ...
  if (IntrusoDigInCounter > AUTOMAN_FILTRO)
    IntrusoDigInStatus = intrusoInState;

  #if (SERIAL_DEBUG == 1)
  if (DebugCounter == SERIAL_DEBUG_TIMER)
  {
    if (IntrusoDigInStatus == INTRUSO_DETEC)
      Serial.println("!!!!!! Alarma Intruso !!!!!!");
   }
  #endif

  /*
  if (DigInStatus_ant == _InState)
    DigInCounter++; // Incrementamos el contador.
  else
  {   
    // Si detectamos un flanco...
    if (DigInStatus_ant == FLANCO)
    {
      if (DigInCounter > PULSACION_LARGA)
      {
        Pulsacion = PULSACION_LARGA;
      }
      else if (DigInCounter > PULSACION_CORTA)
      {
        Pulsacion = PULSACION_CORTA;
      }

      #if (SERIAL_DEBUG == 1)
      if (Pulsacion == PULSACION_LARGA)
        Serial.println(">> xxxxx -> Pulsacion Larga");
      else if (Pulsacion == PULSACION_CORTA)
        Serial.println(">> xxxxx -> Pulsacion Corta");
      else
        Serial.println(">> xxxxx -> Error Pulsacion");
      #endif
    }

    DigInCounter = 0;
  }

  // Aplicamos el filto software en Modo ...
  if (DigInCounter > AUTOMAN_FILTRO)
    DigInStatus = _InState;
  */

  // Almacenamos el valor anterior...
  PulsadorDigInStatus_ant  = pulsadorInState;
  TelemandoDigInStatus_ant = telemandoInState;
  AlarmaDigInStatus_ant    = alarmaInState;
  GeneradorDigInStatus_ant = generadorInState;
  IntrusoDigInStatus_ant   = intrusoInState;
  //DigInStatus_ant       = _InState;
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
    
    if (LedSPulsos < 2*pulsos)
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
// Control del Buzzer //
////////////////////////
void _BuzzerPulso (int buzzer_out, int pulsos, int pulso_corto, int pulso_largo) {

  // Incremento del contador...
  BuzzerCounter++;
  
  if (BuzzerCounter > BuzzerDuration)
  {
    BuzzerCounter = 0;
    
    if (BuzzerPulsos < 2*pulsos)
    {
      BuzzerDuration = pulso_corto;
      BuzzerPulsos++;

      // Cambio de estado del Buzzer...
      if (BuzzerNextState == true)
        BuzzerNextState = false;
      else
        BuzzerNextState = true;
    }
    else
    {
      BuzzerDuration = pulso_largo;
      BuzzerPulsos = 0;

      BuzzerNextState = false;
    }
    
    // Cambio de estado del Buzzer...
    if (BuzzerNextState == true)
      digitalWrite(buzzer_out, HIGH);
    else
      digitalWrite(buzzer_out, LOW);
  }
}

//////////////////////////////////////
// Lectura de la entrada Analogica  //
// con filtro software              //
//////////////////////////////////////
void _ReadAnalogInput() {

  int   aInValue;
  long  flapPosition;

  aInValue = analogRead(LDR_POS_ANA_IN);
  AnaInValue = (AnaInValue_ant + aInValue)/2;
  AnaInValue_ant = aInValue;
  
  #if (SERIAL_DEBUG == 1)
  if (DebugCounter == SERIAL_DEBUG_TIMER)
  {   
    Serial.println("LDR");
    Serial.println(AnaInValue);

    if (AnaInValue >= ANA_LUZ_ON)
      Serial.println("Noche (((");
    else
      Serial.println("Dia ***");
      
    Serial.println(" ");
  }
  #endif
}

////////////////////////
// Máquina de Control //
////////////////////////
void _StatusControl(void) {

  // Si es Día...
  if (AnaInValue < ANA_LUZ_ON)
  {
     ControlState = STATE_STANDBY;
     LedStatePulse = 2;
  }

  switch (ControlState) {
    
    case STATE_STANDBY:
      OutLuz = OUT_OFF;
      BuzzerState = OUT_OFF;

      LedStatePulse = 1;

      // Si se pulsa el pulsador...
      if (PulsadorPulsacion != NO_PULSACION)
      {
        TimeLuzOnSec = 0;
        ControlState = STATE_LUZ_ON;

        LedStatePulse = 4;
      }

      // Si Telemando a ON...
      bTelemandoStatus = false;
      if (TelemandoDigInStatus == TELEMANDO_DETEC)
      {
        TimeLuzOnSec = 0;
        
        bTelemandoStatus = true;
        ControlState = STATE_LUZ_ON;
        
        LedStatePulse = 6;
      }
      
      // Si Intruso a ON...
      bIntrusoStatus = false;
      if (IntrusoDigInStatus == INTRUSO_DETEC)
      {
        TimeLuzOnSec = 0;
        
        bIntrusoStatus = true;
        ControlState = STATE_LUZ_ON;
        
        LedStatePulse = 8;
      }
      
      break;

    case STATE_LUZ_ON:
      OutLuz = OUT_ON;

      // Si el generador está encendido...
      if (GeneradorDigInStatus == GENERATOR_DETEC)
        TimeLuzOnSec = 0;   // Reseteamos el contador...

      if (TimeLuzOnSec > TIMER_LUZ_ON_SEC - 10)
        BuzzerState = OUT_PULSE;  // Avisamos a los XX segudos...
      else
        BuzzerState = OUT_OFF;  
        
      if (TimeLuzOnSec > TIMER_LUZ_ON_SEC)
        ControlState = STATE_STANDBY;

      // Si llega un pulso desde Alarma...
      if (AlarmaPulsacion != NO_PULSACION)
      {
        TimeLuzOnSec = 0;
        ControlState = STATE_STANDBY;
      }

      // Si se pulsa el pulsador...
      if (PulsadorPulsacion != NO_PULSACION)
      {
        TimeLuzOnSec = 0;
        ControlState = STATE_STANDBY;
      }

      // Si el telemando ha sido activado...
      if ((bTelemandoStatus == true) && (TelemandoDigInStatus != TELEMANDO_DETEC))
      {
        TimeLuzOnSec = 0;

        bTelemandoStatus = false;
        ControlState = STATE_STANDBY;
      }

      // Si el telemando ha sido activado...
      if ((bIntrusoStatus == true) && (IntrusoDigInStatus != INTRUSO_DETEC))
      {
        TimeLuzOnSec = 0;

        bIntrusoStatus = false;
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
  // Leemos la entrada analógica
  _ReadAnalogInput();

  _UpdateOuts();

  // Maquina de control
  _StatusControl();

  // Control del Buzzer...
  if (BuzzerState == OUT_PULSE) {
    _BuzzerPulso (OUT_BUZZER, 3, PULSO_LED_CORTO, PULSO_LED_LARGO);
  } else {
    digitalWrite(OUT_BUZZER, LOW);
  }

  // Mostramos el estado...
  _LedSPulso(LED, LedStatePulse, PULSO_LED_CORTO, PULSO_LED_LARGO);

  #if (SERIAL_DEBUG == 1)
  DebugCounter++;
  if (DebugCounter > SERIAL_DEBUG_TIMER)
  {
    DebugCounter = 0;
  }
  #endif

  // Reset de Pulsaciones...
  PulsadorPulsacion   = NO_PULSACION;
  AlarmaPulsacion     = NO_PULSACION;
  //Pulsacion         = NO_PULSACION;

  // Contador de Segundos ...
  if (TickSys > 100)
  {
    TickSys = 0;
    TimeLuzOnSec++;
  }

  TickSys++;
  
  // Ponemos un retado de 10 milisegundos en cada iteración.
  delay(10);
}

