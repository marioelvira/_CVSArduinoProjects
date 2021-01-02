/*
  Control de Panel de Generador para Campo de Vuelo Sesma.
  Creado  21/03/2019

La salida de control será D 2 (salida base transistor, para relé)
Siempre estará en H. (desde que la placa se alimente Hasta que se apague después del tiempo fijado.)
El gobierno del incremento del tiempo, lo hacemos con D 9 (relé pulsador)
El indicador de display lo hacemos con D 3 - D 4 - D 5 - D 6 (A B C D)
Salida + de dislay  D 7 (salida base transistor, para relé) (siempre H, intermitente los 15 últimos segundos)
Salida zumbador, D 8    (salida base transistor, para relé) (intermitente solo los 15 últimos segundos)
Cuando pulsamos D 9 por primera vez, se alimenta el arduino y se ponen en H las salidas D 2 y D 7.  
                                Durante 15 minutos y las salidas de display,  H L L L (el display indica  1 )   15 min
Si volvemos a pulsar D 9. Incrementamos 15 minutos y las salidas de display,  L H L L (el display indica  2 )   30 min
Si volvemos a pulsar D 9. Incrementamos 15 minutos y las salidas de display,  H H L L (el display indica  3 )   1h 00 min
Si volvemos a pulsar D 9. Incrementamos 30 minutos y las salidas de display,  L L H L (el display indica  4 )   1h 30 min
Si volvemos a pulsar D 9. Incrementamos 30 minutos y las salidas de display,  H L H L (el display indica  5 )   2h 00 min
Si volvemos a pulsar D 9. Incrementamos 60 minutos y las salidas de display,  H H L L (el display indica  6 )   3h 00 min
Si volvemos a pulsar D 9. Incrementamos 60 minutos y las salidas de display,  H H H L (el display indica  7 )   4h 00 min
Si volvemos a pulsar D 9. Incrementamos 60 minutos y las salidas de display,  L L L H (el display indica  8 )   5h 00 min
Si volvemos a pulsar D 9. Incrementamos 120 minutos y las salidas de display, H L L H (el display indica  9 )   7h 00 min
Si se puede no actuara D 9 después de llegar al 9, (para que no vuelva a uno)

Cuando el tiempo se termine ->   L L L L (el display indicara  0)
Las salidas D 7 - D 8 Se ponen intermitentes durante 15 segundos 
Si en ese tiempo no se pulsa D 9, se desconecta D 2 y se apaga el equipo


*/

// Placas de Evaluación.
#define ARDUINO_NANO   1
#define ARDUINO_UNO    2

// Placa en uso.
#define USAR    ARDUINO_UNO  

#define OUT_OFF        0
#define OUT_ON         1
#define OUT_PULSE      2

#define FLANCO_UP     0
#define FLANCO_DOWN   1
#define FLANCO        FLANCO_UP  // FLANCO_DOWN

#if (USAR == ARDUINO_NANO)

// Salidas Digitales
#define OUT_GEN         2
#define OUT_DISP        7
#define OUT_ZUMB        8

// LDC numérico
#define OUT_D3          3
#define OUT_D4          4
#define OUT_D5          5
#define OUT_D6          6

// Entradas Digitales
#define IN_PULSADOR     9   // Pulsador

// Led Indicador
#define LED             13

#endif

#if (USAR == ARDUINO_UNO)

// Salidas Digitales
#define OUT_GEN         2
#define OUT_DISP        7
#define OUT_ZUMB        8

// LDC numérico
#define OUT_D3          3
#define OUT_D4          4
#define OUT_D5          5
#define OUT_D6          6

// Entradas Digitales
#define IN_PULSADOR     9   // Pulsador

// Led Indicador
#define LED             13

#endif

// Temporizaciones
#define NO_PULSACION        0   // x10ms
#define PULSACION_OK        75  // x10ms
#define AUTOMAN_FILTRO      25  // x10ms

// Duración pulsos Led de Status
#define PULSO_LED_CORTO     50  // x10ms
#define PULSO_LED_LARGO     200 // x10ms

// Duración pulsos Zumbador
#define PULSO_ZUM_CORTO     50  // x10ms
#define PULSO_ZUM_LARGO     200 // x10ms

// Duración pulsos Display
#define PULSO_DISP_CORTO     50  // x10ms
#define PULSO_DISP_LARGO     200 // x10ms

#define TIMER_GEN_0H_15M_SEC  30 //900     // 60*15min
#define TIMER_GEN_0H_30M_SEC  35 //1800    // 60*30min
#define TIMER_GEN_1H_00M_SEC  40 //3600    // 60*60min
#define TIMER_GEN_1H_30M_SEC  45 //5400    // 60*90min
#define TIMER_GEN_2H_00M_SEC  50 //7200    // 60*120min
#define TIMER_GEN_3H_00M_SEC  55 //10800   // 60*180min
#define TIMER_GEN_4H_00M_SEC  60 //14400   // 60*240min
#define TIMER_GEN_5H_00M_SEC  65 //18000   // 60*300min
#define TIMER_GEN_7H_00M_SEC  70 //25200   // 60*420min
    
#define TIMER_GEN_END_SEC    15       // 15 segundos

// Estados principales...
#define STATE_GEN_ON        0
#define STATE_GEN_ON2OFF    1
#define STATE_GEN_OFF       2

// Salidas Digitales
int   OutGen;
int   OutDisp;
int   OutZumb;

int   OutD3;
int   OutD4;
int   OutD5;
int   OutD6;

// Variables para leer las Entradas
int   PulsadorDigInStatus = 0;
int   PulsadorDigInStatus_ant = 0;
int   PulsadorDigInCounter = 0;
int   PulsadorPulsacion = 0;

// Control del Led...
bool  LedSNextState = false;
int   LedSCounter = 0;
int   LedSDuration = 0;
int   LedSPulsos = 0;

int   LedStatePulse;

// Control del Zumbador...
bool  ZumNextState = false;
int   ZumCounter = 0;
int   ZumDuration = 0;
int   ZumPulsos = 0;

int   ZumStatePulse;

// Control del Display...
bool  DispNextState = false;
int   DispCounter = 0;
int   DispDuration = 0;
int   DispPulsos = 0;

int   DispStatePulse;

// Estado principal
int   ControlState;  
int   TimeControlSec = TIMER_GEN_0H_15M_SEC;  // Arrancamos con 15 minutos
int   DisplayIndicador = 1;

int   TickSys = 0;

// Dedug...
#define SERIAL_DEBUG  1
#define SERIAL_DEBUG_TIMER  100
int    DebugCounter = 0;

/////////////////////////////////////////////
// Inicialización de las salidas digitales //
/////////////////////////////////////////////
void _InitDigitalOutputs() {

  pinMode(OUT_GEN, OUTPUT);
  digitalWrite(OUT_GEN, HIGH);

  pinMode(OUT_DISP, OUTPUT);
  digitalWrite(OUT_DISP, HIGH);

  pinMode(OUT_ZUMB, OUTPUT);
  digitalWrite(OUT_ZUMB, LOW);

  pinMode(OUT_D3, OUTPUT);
  digitalWrite(OUT_D3, LOW);
  pinMode(OUT_D4, OUTPUT);
  digitalWrite(OUT_D4, LOW);
  pinMode(OUT_D5, OUTPUT);
  digitalWrite(OUT_D5, LOW);
  pinMode(OUT_D6, OUTPUT);
  digitalWrite(OUT_D6, LOW);

  OutGen   = OUT_ON;
  OutDisp  = OUT_ON;
  OutZumb  = OUT_OFF;

  OutD3 = OUT_OFF;
  OutD4 = OUT_OFF;
  OutD5 = OUT_OFF;
  OutD6 = OUT_OFF;
}

//////////////////////////////////////////////
// Inicialización de las entradas digitales //
//////////////////////////////////////////////
void _InitDigitalInputs() {

  pinMode(IN_PULSADOR,    INPUT);

  PulsadorDigInStatus = digitalRead(IN_PULSADOR);
  PulsadorDigInStatus_ant = PulsadorDigInStatus;
  PulsadorDigInCounter = 0;
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
  #endif

  _InitDigitalOutputs();
  _InitDigitalInputs();
  _InitLeds();

  ControlState = STATE_GEN_ON;
}

////////////////////////////////////////
// Lectura de las entrada digital     //
// con filtro software antirebotes    //
////////////////////////////////////////
void _ReadDigitalInputs() {

  int pulsadorInState;
  
  // Leemos las entradas digitales...
  pulsadorInState   = digitalRead(IN_PULSADOR);

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
      if (PulsadorDigInCounter > PULSACION_OK)
      {
        PulsadorPulsacion = PULSACION_OK;
      }

      #if (SERIAL_DEBUG == 1)
      if (PulsadorPulsacion == PULSACION_OK)
        Serial.println(">> Pulsador -> Pulsacion OK");
      else
        Serial.println(">> Pulsador -> Error Pulsacion");
      #endif
    }

    PulsadorDigInCounter = 0;
  }

  // Aplicamos el filto software en Modo ...
  if (PulsadorDigInCounter > AUTOMAN_FILTRO)
    PulsadorDigInStatus = pulsadorInState;

  // Almacenamos el valor anterior...
  PulsadorDigInStatus_ant  = pulsadorInState;
}

////////////////////////////
// Update Outs            //
////////////////////////////
void _UpdateOuts(void) {
  
  if (OutGen == OUT_ON)
    digitalWrite(OUT_GEN, HIGH);
  else
    digitalWrite(OUT_GEN, LOW);

  if (OutZumb == OUT_ON)
    digitalWrite(OUT_ZUMB, HIGH);
  else if (OutZumb == OUT_OFF)
    digitalWrite(OUT_ZUMB, LOW);
  else if (OutZumb == OUT_PULSE)
    _ZumPulso(OUT_ZUMB, 10, PULSO_ZUM_CORTO, PULSO_ZUM_LARGO);

  if (OutDisp == OUT_ON)
    digitalWrite(OUT_DISP, HIGH);
  else if (OutDisp == OUT_OFF)
    digitalWrite(OUT_DISP, LOW);
  else if (OutDisp == OUT_PULSE)
    _DispPulso(OUT_DISP, 10, PULSO_DISP_CORTO, PULSO_DISP_LARGO);

  if (OutD3 == OUT_ON)
    digitalWrite(OUT_D3, HIGH);
  else
    digitalWrite(OUT_D3, LOW);

  if (OutD4 == OUT_ON)
    digitalWrite(OUT_D4, HIGH);
  else
    digitalWrite(OUT_D4, LOW);

  if (OutD5 == OUT_ON)
    digitalWrite(OUT_D5, HIGH);
  else
    digitalWrite(OUT_D5, LOW);

  if (OutD6 == OUT_ON)
    digitalWrite(OUT_D6, HIGH);
   else
    digitalWrite(OUT_D6, LOW);   
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

//////////////////////////
// Control del Zumbador //
//////////////////////////
void _ZumPulso (int zum_out, int pulsos, int pulso_corto, int pulso_largo) {

  // Incremento del contador...
  ZumCounter++;
  
  if (ZumCounter > ZumDuration)
  {
    ZumCounter = 0;
    
    if (ZumPulsos < 2*pulsos)
    {
      ZumDuration = pulso_corto;
      ZumPulsos++;

      // Cambio de estado del Zumbador...
      if (ZumNextState == true)
        ZumNextState = false;
      else
        ZumNextState = true;
    }
    else
    {
      ZumDuration = pulso_largo;
      ZumPulsos = 0;

      ZumNextState = false;
    }
    
    // Cambio de estado del Zumbador...
    if (ZumNextState == true)
      digitalWrite(zum_out, HIGH);
    else
      digitalWrite(zum_out, LOW);
  }
}

/////////////////////////
// Control del Display //
/////////////////////////
void _DispPulso (int disp_out, int pulsos, int pulso_corto, int pulso_largo) {

  // Incremento del contador...
  DispCounter++;
  
  if (DispCounter > DispDuration)
  {
    DispCounter = 0;
    
    if (DispPulsos < 2*pulsos)
    {
      DispDuration = pulso_corto;
      DispPulsos++;

      // Cambio de estado del Display...
      if (DispNextState == true)
        DispNextState = false;
      else
        DispNextState = true;
    }
    else
    {
      DispDuration = pulso_largo;
      DispPulsos = 0;

      DispNextState = false;
    }
    
    // Cambio de estado del Display...
    if (DispNextState == true)
      digitalWrite(disp_out, HIGH);
    else
      digitalWrite(disp_out, LOW);
  }
}

////////////////////////
// Máquina de Control //
////////////////////////
void _StatusControl(void) {

  #if (SERIAL_DEBUG == 1)
  if (DebugCounter == SERIAL_DEBUG_TIMER)
  {
    if (ControlState == STATE_GEN_ON)
      Serial.println("Generador ON ");
    else if (ControlState == STATE_GEN_ON2OFF)
      Serial.println("Generador ON/OFF ");
    else
      Serial.println("Generador OFF ");
        
    Serial.print("Indicador: ");
    Serial.println(DisplayIndicador);
    Serial.print("Cuenta Atras: ");
    Serial.println(TimeControlSec);
    Serial.println("  ");
    
  }
  #endif


  switch (ControlState) {

    case STATE_GEN_ON:
      OutGen = OUT_ON;
      OutZumb = OUT_OFF;
      OutDisp = OUT_ON;

      LedStatePulse = 1;
       
      if (TimeControlSec <= TIMER_GEN_END_SEC)
        ControlState = STATE_GEN_ON2OFF;

      break;

    case STATE_GEN_ON2OFF:
      OutGen = OUT_ON;
      OutZumb = OUT_PULSE;
      OutDisp = OUT_PULSE;

      LedStatePulse = 4;

      if (TimeControlSec <= 0)
        ControlState = STATE_GEN_OFF;
    
      break;
   
    case STATE_GEN_OFF:
      OutGen = OUT_OFF;
      OutZumb = OUT_OFF;
      OutDisp = OUT_OFF;
      break;
  }
}

///////////////////////
// TimeOn de Control //
///////////////////////
void _TimeOnControl(void) {

  if (TimeControlSec > TIMER_GEN_5H_00M_SEC)
  {
    DisplayIndicador = 9;//TIMER_GEN_7H_00M_SEC; // 7h -> 9
    OutD3 = OUT_ON;
    OutD4 = OUT_OFF;
    OutD5 = OUT_OFF;
    OutD6 = OUT_ON;  
  }
  else if (TimeControlSec > TIMER_GEN_4H_00M_SEC)
  {
    DisplayIndicador = 8; //TIMER_GEN_5H_00M_SEC; // 5h -> 8
    OutD3 = OUT_OFF;
    OutD4 = OUT_OFF;
    OutD5 = OUT_OFF;
    OutD6 = OUT_ON;  
  }
  else if (TimeControlSec > TIMER_GEN_3H_00M_SEC)
  {
    DisplayIndicador = 7; //TIMER_GEN_4H_00M_SEC; // 4h -> 7
    OutD3 = OUT_ON;
    OutD4 = OUT_ON;
    OutD5 = OUT_ON;
    OutD6 = OUT_OFF;   
  }
  else if (TimeControlSec > TIMER_GEN_2H_00M_SEC)
  {
    DisplayIndicador = 6; //TIMER_GEN_3H_00M_SEC; // 3h -> 6
    OutD3 = OUT_OFF;
    OutD4 = OUT_ON;
    OutD5 = OUT_ON;
    OutD6 = OUT_OFF;   
  }
  else if (TimeControlSec > TIMER_GEN_1H_30M_SEC)
  {
    DisplayIndicador = 5; //TIMER_GEN_2H_00M_SEC; // 2h -> 5
    OutD3 = OUT_ON;
    OutD4 = OUT_OFF;
    OutD5 = OUT_ON;
    OutD6 = OUT_OFF;     
  }
  else if (TimeControlSec > TIMER_GEN_1H_00M_SEC)
  {
    DisplayIndicador = 4; //TIMER_GEN_1H_30M_SEC; // 1h30m -> 4
    OutD3 = OUT_OFF;
    OutD4 = OUT_OFF;
    OutD5 = OUT_ON;
    OutD6 = OUT_OFF;   
  }
  else if (TimeControlSec > TIMER_GEN_0H_30M_SEC)
  {
    DisplayIndicador = 3; //TIMER_GEN_1H_00M_SEC; // 1h -> 3
    OutD3 = OUT_ON;
    OutD4 = OUT_ON;
    OutD5 = OUT_OFF;
    OutD6 = OUT_OFF;  
  }
  else if (TimeControlSec > TIMER_GEN_0H_15M_SEC)
  {
    DisplayIndicador = 2; //TIMER_GEN_0H_30M_SEC; // 30m -> 2
    OutD3 = OUT_OFF;
    OutD4 = OUT_ON;
    OutD5 = OUT_OFF;
    OutD6 = OUT_OFF;    
  }
  else if (TimeControlSec > TIMER_GEN_END_SEC)
  {
    DisplayIndicador = 1; //TIMER_GEN_0H_15M_SEC; // 15m -> 1
    OutD3 = OUT_ON;
    OutD4 = OUT_OFF;
    OutD5 = OUT_OFF;
    OutD6 = OUT_OFF;  
  }
  else
  {
    DisplayIndicador = 0; //TIMER_GEN_END_SEC; // 15s -> 0
    OutD3 = OUT_OFF;
    OutD4 = OUT_OFF;
    OutD5 = OUT_OFF;
    OutD6 = OUT_OFF;  
  }
}

//////////////////////////
// Control de Pulsación //
//////////////////////////
void _PulsacionControl(void) {

  // Si se pulsa el pulsador...
  if (PulsadorPulsacion != NO_PULSACION)
  {

    ControlState = STATE_GEN_ON;  // reseteamos el estado...

    if (DisplayIndicador == 9)
      TimeControlSec = TIMER_GEN_7H_00M_SEC;
      
    else if (DisplayIndicador == 8)
      TimeControlSec = TIMER_GEN_7H_00M_SEC;
      
    else if (DisplayIndicador == 7)
      TimeControlSec = TIMER_GEN_5H_00M_SEC;
      
    else if (DisplayIndicador == 6)
      TimeControlSec = TIMER_GEN_4H_00M_SEC;
      
    else if (DisplayIndicador == 5)
      TimeControlSec = TIMER_GEN_3H_00M_SEC;
      
    else if (DisplayIndicador == 4)
      TimeControlSec = TIMER_GEN_2H_00M_SEC;
      
    else if (DisplayIndicador == 3)
      TimeControlSec = TIMER_GEN_1H_30M_SEC;
      
    else if (DisplayIndicador == 2)
      TimeControlSec = TIMER_GEN_1H_00M_SEC;
      
    else if (DisplayIndicador == 1)
      TimeControlSec = TIMER_GEN_0H_30M_SEC;
      
    else
      TimeControlSec = TIMER_GEN_0H_15M_SEC;
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

  // Control del tiempo a On
  _TimeOnControl();

  // Cobtrol de la pulsación
  _PulsacionControl();

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

  // Contador de Segundos ...
  if (TickSys > 100)
  {
    TickSys = 0;
    TimeControlSec--;
  }

  TickSys++;
  
  // Ponemos un retado de 10 milisegundos en cada iteración.
  delay(10);
}

