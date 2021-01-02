 /*
  Control Flaps.
  14/07/2018 Viva Sanfermin!!!
*/

// Placas de Evaluacion.
#define ARDUINO_NANO      1   // Igual que OLIMEXINO-328
#define ARDUINO_UNO       2
#define ARDUINO_LEONARDO  3   // Igual que OLIMEXINO-32U4

// Placa en uso.
#define USAR                  ARDUINO_NANO
#define GRABACION             1

#include <EEPROM.h>

#define EEPROM_ADD_OK         0x00
//#define EEPROM_ADD_PHIST_INF  0x02
//#define EEPROM_ADD_PHIST_SUP  0x03
#define EEPROM_ADD_PMIN_LO    0x04
#define EEPROM_ADD_PMIN_HI    0x05
#define EEPROM_ADD_P1_LO      0x06
#define EEPROM_ADD_P1_HI      0x07
#define EEPROM_ADD_P2_LO      0x08
#define EEPROM_ADD_P2_HI      0x09
#define EEPROM_ADD_P3_LO      0x0A
#define EEPROM_ADD_P3_HI      0x0B
//#define EEPROM_ADD_PMAX_LO    0x0C
//#define EEPROM_ADD_PMAX_HI    0x0D

#define EEPROM_VALUE_OK       0xA5

#define RESET_CONFIG          0

// ADC de 0 a 1023 (0x0000 a 0x03FF)
#define EEPROM_VALUE_PMIN       840   // 835 // para MINº
#define EEPROM_VALUE_P1         860   // para 15º 
#define EEPROM_VALUE_P2         880   // para 30º  
#define EEPROM_VALUE_P3         900   // para 45º
#define EEPROM_VALUE_PMAX       910   // 930 // para MAXº

// Rango en Grados
#define FLAP_POS_MIN        0       // 0º
#define FLAP_POS_MAX        4500    // 45º

// Definicion de Tramos
#define FLAP_EN_MIN         0
#define FLAP_TRAMO_Tm1      5
#define FLAP_EN_P1          10
#define FLAP_TRAMO_T12      15
#define FLAP_EN_P2          20
#define FLAP_TRAMO_T2M      25
#define FLAP_EN_P3          30

#define VALUE_PHIST_INF  4 //4
#define VALUE_PHIST_SUP  4 //4

#if (USAR == ARDUINO_NANO)
// Salidas Servo Flap
#define OUT_FLAP_BAJAR  4
#define OUT_FLAP_SUBIR  3

// Leds indicadores de Flap
#define OUT_LED0  2   // Verde: No flaps
#define OUT_LED1  5   // Rojo: P1
#define OUT_LED2  6   // Rojo: P2
#define OUT_LED3  7   // Rojo: P3

// Led Indicador
//#define LED       13

// Entrada Digital
#define DIN_FLAP_BAJAR    10  // Entrada pulsador Sacar Flap
#define DIN_FLAP_SUBIR    9   // Entrada pulsador Recoger
#define DIN_AUTOMAN       8   // Entrada pulsador Automatico/Manual

// Entrada Analogica
#define FLAP_POS_ANA_IN   A0  // Entrada posicion Flap

#endif

#if (USAR == ARDUINO_UNO)
// TODO
#endif

#define OUT_ON    1
#define OUT_OFF   0

// Temporizaciones UpPulsaciones
#define NO_PULSACION          0     // x10ms
#define PULSACION_CORTA       50    // x10ms
#define PULSACION_LARGA       150   // x10ms
#define PULSACION_ERROR       10    // x10ms
#define AUTOMAN_FILTRO        25    // x10ms

// Duracion pulsos Led de Status
#define PULSO_LED_CORTO         20 // x10ms
#define PULSO_LED_LARGO         100 // x10ms

#define PULSO_LED_FLAP_CORTO    25 // x10ms
#define PULSO_LED_FLAP_LARGO    75 // x10ms

#define AUTOMAT_FLAP_COUNTER        6000 // x10ms
#define AUTOMAT_FLAP_COUNTER_MAX    18000 // x10ms

// Maquina estados
#define INIT_MODE             0
#define MANUAL_MODE           1
#define AUTOMAT_MODE          2
#define GRABACION_INIT_MODE   3
#define GRABACION_MODE        4

// Maquina estados Manual
#define MANUAL_STANDBY           0
#define MANUAL_FLAP_SUBIR        1
#define MANUAL_FLAP_BAJAR        2

// Maquina estados Automatica
#define AUTOMAT_STANDBY          0
#define AUTOMAT_FLAP_SUBIR       1
#define AUTOMAT_FLAP_BAJAR       2
#define AUTOMAT_WAIT             3

#define LED_AUTOMAT              1
#define LED_MANUAL               10

// Variables para leer las entradas digitals
int   BajarDigInStatus = 0;
int   BajarDigInStatus_ant = 0;
int   BajarDigInCounter = 0;
int   BajarPulsacion = 0;

int   SubirDigInStatus = 0;
int   SubirDigInStatus_ant = 0;
int   SubirDigInCounter = 0;
int   SubirPulsacion = 0;

int   AutomanDigInStatus = 0;
int   AutomanDigInStatus_ant = 0;
int   AutomanDigInCounter = 0;

// Variables para leer la entrada analogica
#define ANA_ARRAY_SIZE  20 //10
int   AnaInValue = 0;
int   AnaInArray[ANA_ARRAY_SIZE];
int   AnaInPointer = 0;

// Variables para Leds
bool  Led1NextState = false;
int   Led1Counter = 0;
int   Led1Duration = 0;
int   Led1Pulsos = 0;
/*
bool  Led2NextState = false;
int   Led2Counter = 0;
int   Led2Duration = 0;
int   Led2Pulsos = 0;

bool  Led3NextState = false;
int   Led3Counter = 0;
int   Led3Duration = 0;
int   Led3Pulsos = 0;

bool  LedSNextState = false;
int   LedSCounter = 0;
int   LedSDuration = 0;
int   LedSPulsos = 0;
*/
// Variables de configuracion con la posicion de los Flaps
int   CfgFlapPHIST_INF = 0;
int   CfgFlapPHIST_SUP = 0;
int   CfgFlapPMIN = 0;
int   CfgFlapP1  = 0;
int   CfgFlapP2  = 0;
int   CfgFlapP3  = 0;

int   FlapAdcTramo = 0;
int   FlapPHIST_INF = 0;
int   FlapPHIST_SUP = 0;

// Variables de Control
int   ControlState;
int   ManualState;
int   AutomatState;

// Control de Flap automatico
int   FlapAdcTramoStart;
int   FlapAdcTramoStop;

int   OutFlapSacar;
int   OutFlapRecoger;

int   TickSys = 0;

#if (GRABACION == 1)
int   GrabacionTickSec = 0;
int   GrabacionCounter = 0;
#endif

int StopTickSec = 0;
#define STOP_WAIT_SECS   2

// Dedug...
#define SERIAL_DEBUG        1
#define SERIAL_DEBUG_TIMER  50
int    DebugCounter = 0;

//////////////////////////////
// Funcion de Inicilizacion //
//////////////////////////////
void setup() {

  StopTickSec = 0;

  #if (SERIAL_DEBUG == 1)
  Serial.begin(9600);
  #endif
  
  _InitDigitalOutputs();
  _InitDigitalInputs();
  _InitAnalogInput();
  _InitLeds();
  
  delay(1000);

  _InitConfig();  
  _InitControl();

  delay(500);
}

/////////////////////////////////////////////
// Inicializacion de las salidas digitales //
/////////////////////////////////////////////
void _InitDigitalOutputs() {

  // Salidas de Servo
  pinMode(OUT_FLAP_BAJAR, OUTPUT);
  pinMode(OUT_FLAP_SUBIR, OUTPUT);
  digitalWrite(OUT_FLAP_BAJAR, LOW);
  digitalWrite(OUT_FLAP_SUBIR, LOW);

  OutFlapSacar   = OUT_OFF;
  OutFlapRecoger = OUT_OFF;
}

//////////////////////////////////////////////
// Inicializacion de las entradas digitales //
//////////////////////////////////////////////
void _InitDigitalInputs() {

  // Pines como entrada
  pinMode(DIN_FLAP_BAJAR, INPUT);
  pinMode(DIN_FLAP_SUBIR, INPUT);
  pinMode(DIN_AUTOMAN,    INPUT);

  BajarDigInStatus = digitalRead(DIN_FLAP_BAJAR);
  BajarDigInStatus_ant = BajarDigInStatus;
  BajarDigInCounter = 0;

  SubirDigInStatus = digitalRead(DIN_FLAP_SUBIR);
  SubirDigInStatus_ant = SubirDigInStatus;
  SubirDigInCounter = 0;

  AutomanDigInStatus = digitalRead(DIN_AUTOMAN);
  AutomanDigInStatus_ant = AutomanDigInStatus;
  AutomanDigInCounter = 0;

}

/////////////////////////////
// Inicializacion del Leds //
/////////////////////////////
void _InitLeds() {

  // Led Indicador de Estado
  pinMode(OUT_LED0, OUTPUT);
  pinMode(OUT_LED1, OUTPUT);
  pinMode(OUT_LED2, OUTPUT);
  pinMode(OUT_LED3, OUTPUT);
  digitalWrite(OUT_LED0, HIGH);
  digitalWrite(OUT_LED1, HIGH); 
  digitalWrite(OUT_LED2, HIGH);
  digitalWrite(OUT_LED3, HIGH);

  // Led Indicador de Estado
  //pinMode(LED, OUTPUT);
  //digitalWrite(LED, LOW);

  Led1NextState = false;
  Led1Counter = 0;
  Led1Duration = PULSO_LED_FLAP_CORTO;
  Led1Pulsos = 0;

  /*
  Led2NextState = false;
  Led2Counter = 0;
  Led2Duration = PULSO_LED_FLAP_CORTO;
  Led2Pulsos = 0;

  Led3NextState = false;
  Led3Counter = 0;
  Led3Duration = PULSO_LED_FLAP_CORTO;
  Led3Pulsos = 0;

  LedSNextState = false;
  LedSCounter = 0;
  LedSDuration = PULSO_LED_CORTO;
  LedSPulsos = 0;
  */
}

///////////////////////////////////////////////
// Inicializacion de la entrada Analogica    //
///////////////////////////////////////////////
void _InitAnalogInput() {

  AnaInValue = 0;

  for (int i = 0; i < ANA_ARRAY_SIZE; i++)
    AnaInArray[i] = 0;

  AnaInPointer = 0;
}

///////////////////////////////////////////////
// Inicializacion de la Configuracion        //
///////////////////////////////////////////////
void _InitConfig() {

  int eeprom_value_hi, eeprom_value_lo;
  
  eeprom_value_lo = EEPROM.read(EEPROM_ADD_OK);

  // Si NO esta grabada la configuracion...
  if (eeprom_value_lo != EEPROM_VALUE_OK)
  {
    #if (SERIAL_DEBUG == 1)
    Serial.println("Config NOK");
    #endif
    
    EEPROM.write(EEPROM_ADD_OK, EEPROM_VALUE_OK);
    
    eeprom_value_lo = EEPROM_VALUE_PMIN & 0x00FF;
    EEPROM.write(EEPROM_ADD_PMIN_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VALUE_PMIN & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_PMIN_HI, eeprom_value_hi);

    eeprom_value_lo = EEPROM_VALUE_P1 & 0x00FF;
    EEPROM.write(EEPROM_ADD_P1_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VALUE_P1 & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_P1_HI, eeprom_value_hi);
    
    eeprom_value_lo = EEPROM_VALUE_P2 & 0x00FF;
    EEPROM.write(EEPROM_ADD_P2_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VALUE_P2 & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_P2_HI, eeprom_value_hi);

    eeprom_value_lo = EEPROM_VALUE_P3 & 0x00FF;
    EEPROM.write(EEPROM_ADD_P3_LO, eeprom_value_lo);
    eeprom_value_hi = (EEPROM_VALUE_P3 & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_P3_HI, eeprom_value_hi);
  }
  else
  {
    #if (SERIAL_DEBUG == 1)
    Serial.println("Config OK");
    #endif
  }

  CfgFlapPHIST_INF = VALUE_PHIST_INF; //EEPROM.read(EEPROM_ADD_PHIST_INF);
  CfgFlapPHIST_SUP = VALUE_PHIST_SUP; //EEPROM.read(EEPROM_ADD_PHIST_SUP);

  eeprom_value_hi = EEPROM.read(EEPROM_ADD_PMIN_HI);
  eeprom_value_lo = EEPROM.read(EEPROM_ADD_PMIN_LO);   
  CfgFlapPMIN = ((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  eeprom_value_hi = EEPROM.read(EEPROM_ADD_P1_HI);
  eeprom_value_lo = EEPROM.read(EEPROM_ADD_P1_LO);   
  CfgFlapP1 = ((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
    
  eeprom_value_hi = EEPROM.read(EEPROM_ADD_P2_HI);
  eeprom_value_lo = EEPROM.read(EEPROM_ADD_P2_LO);   
  CfgFlapP2 = ((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);
    
  eeprom_value_hi = EEPROM.read(EEPROM_ADD_P3_HI);
  eeprom_value_lo = EEPROM.read(EEPROM_ADD_P3_LO);   
  CfgFlapP3 = ((eeprom_value_hi & 0x00FF)<<8)|(eeprom_value_lo & 0x00FF);

  #if (SERIAL_DEBUG == 1)
  Serial.print("Conf: Hist Inf: ");
  Serial.println(CfgFlapPHIST_INF);
  Serial.print("Conf: Hist Sup: ");
  Serial.println(CfgFlapPHIST_SUP);
  Serial.print("Conf: Pos 1: ");
  Serial.println(CfgFlapPMIN);
  Serial.print("Conf: Pos 2: "); 
  Serial.println(CfgFlapP1);
  Serial.print("Conf: Pos 3: ");
  Serial.println(CfgFlapP2);
  Serial.print("Conf: Pos 4: ");
  Serial.println(CfgFlapP3);
  #endif

  #if (RESET_CONFIG == 1)
  _ResetConfig();
  #endif
}

///////////////////////////////////////////////
// Reset de la Configuracion                 //
///////////////////////////////////////////////
void _ResetConfig() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0xFF);
  }
}

///////////////////////////////////////////////
// Inicializacion del Control                //
///////////////////////////////////////////////
void _InitControl() {

  ControlState = INIT_MODE;
  ManualState = MANUAL_STANDBY;
  AutomatState = AUTOMAT_STANDBY;
}

/////////////////////////////////////////////
// Funcion Principal                       //
// Se ejecuta en bucle continuo cada 10 ms //
/////////////////////////////////////////////
void loop() {

  // Leemos las entradas digitales
  _ReadDigitalInputs();
  // Leemos la entrada analogica
  _ReadAnalogInput();

  // 4 Leds de posicion de los Flaps
  _UpdateFlapPosition();

  // Control
  _StatusControl();

  // Actualizamos las salidas
  _UpdateOuts();
  
  #if (SERIAL_DEBUG == 1)
  DebugCounter++;
  if (DebugCounter > SERIAL_DEBUG_TIMER)
    DebugCounter = 0;
  #endif

  // Reset de Pulsaciones...
  BajarPulsacion = NO_PULSACION;
  SubirPulsacion = NO_PULSACION;
  
  // Contador de Segundos ...
  if (TickSys > 100)
  {
    TickSys = 0;
    
    #if (GRABACION == 1)
    GrabacionTickSec++;
    #endif

    StopTickSec++;
  }

  TickSys++;
  
  // Ponemos un retado de 10 milisegundos en cada iteracion.
  delay(10);
}

////////////////////////////////////////
// Lectura de las entrada digital     //
// con filtro software antirebotes    //
////////////////////////////////////////
void _ReadDigitalInputs() {

  int bajarInState;
  int subirInState;
  int automanInState;
  
  // Leemos las entradas digitales...
  bajarInState    = digitalRead(DIN_FLAP_BAJAR);
  subirInState    = digitalRead(DIN_FLAP_SUBIR);
  automanInState  = digitalRead(DIN_AUTOMAN);

  ////////////////
  // Sacar Flap //
  ////////////////

  if (BajarDigInStatus_ant == bajarInState)
    BajarDigInCounter++; // Incrementamos el contador.
  else
  {   
    // Si detectamos un flanco de bajada...
    if (BajarDigInStatus_ant == 0)
    {
      if (BajarDigInCounter > PULSACION_LARGA)
        BajarPulsacion = PULSACION_LARGA;
      else if (BajarDigInCounter > PULSACION_CORTA)
        BajarPulsacion = PULSACION_CORTA;
      else
        BajarPulsacion = PULSACION_ERROR;

      #if (SERIAL_DEBUG == 1)
      if (BajarPulsacion == PULSACION_LARGA)
        Serial.println(">> BAJAR -> Pulsacion Larga");
      else if (BajarPulsacion == PULSACION_CORTA)
        Serial.println(">> BAJAR -> Pulsacion Corta");
      else
        Serial.println(">> BAJAR -> Error Pulsacion");
      #endif
    }

    BajarDigInCounter = 0;
  }

  // Aplicamos el filto software en Modo ...
  if (BajarDigInCounter > AUTOMAN_FILTRO)
    BajarDigInStatus = bajarInState;

  ////////////////
  // Subir Flap //
  ////////////////
  
  if (SubirDigInStatus_ant == subirInState)
    SubirDigInCounter++; // Incrementamos el contador.
  else
  {   
    // Si detectamos un flanco de bajada...
    if (SubirDigInStatus_ant == 0)
    {
      if (SubirDigInCounter > PULSACION_LARGA)
        SubirPulsacion = PULSACION_LARGA;
      else if (SubirDigInCounter > PULSACION_CORTA)
        SubirPulsacion = PULSACION_CORTA;
      else
        SubirPulsacion = PULSACION_ERROR;

      #if (SERIAL_DEBUG == 1)
      if (SubirPulsacion == PULSACION_LARGA)
        Serial.println(">> SUBIR -> Pulsacion Larga");
      else if (SubirPulsacion == PULSACION_CORTA)
        Serial.println(">> SUBIR -> Pulsacion Corta");
      else
        Serial.println(">> SUBIR -> Error Pulsacion");
      #endif
    }

    SubirDigInCounter = 0;
  }

  // Aplicamos el filto software en Modo ...
  if (SubirDigInCounter > AUTOMAN_FILTRO)
    SubirDigInStatus = subirInState;

  /////////////////
  // Auto/Manual //
  /////////////////

  if (AutomanDigInStatus_ant == automanInState)
    AutomanDigInCounter++; // Incrementamos el contador.
  else
    AutomanDigInCounter = 0;

  // Aplicamos el filto software...
  if (AutomanDigInCounter > AUTOMAN_FILTRO)
    AutomanDigInStatus = automanInState;   // Actualizamos la lectura de la entrada...

  #if (SERIAL_DEBUG == 1)
  if (DebugCounter == SERIAL_DEBUG_TIMER)
  {
    Serial.println(" ");
    if (AutomanDigInStatus == HIGH)
      Serial.println("<<<<<<< Modo Manual >>>>>>>");
    else
      Serial.println("----- Modo Automatico -----");

    Serial.print(CfgFlapPMIN);
    Serial.print(" / "); 
    Serial.print(CfgFlapP1);
    Serial.print(" / ");
    Serial.print(CfgFlapP2);
    Serial.print(" / ");
    Serial.println(CfgFlapP3);
    
  }
  #endif

  // Almacenamos el valor anterior...
  BajarDigInStatus_ant  = bajarInState;
  SubirDigInStatus_ant  = subirInState;
  AutomanDigInStatus_ant  = automanInState;
}

//////////////////////////////////////
// Lectura de la entrada Analogica  //
// con filtro software              //
//////////////////////////////////////
void _ReadAnalogInput() {

  int aInAcc = 0;

  // Leemos la entrada analógica...
  AnaInArray[AnaInPointer] = analogRead(FLAP_POS_ANA_IN);
  AnaInPointer++;
  if (AnaInPointer >= ANA_ARRAY_SIZE)
    AnaInPointer = 0;

  // Calculamos la media del Array...
  for (int i = 0; i < ANA_ARRAY_SIZE; i++)
    aInAcc = aInAcc + AnaInArray[i];
  
  AnaInValue = aInAcc/ANA_ARRAY_SIZE;
}

////////////////////////
// Maquina de Control //
////////////////////////
void _StatusControl(void) {

  #if (GRABACION == 1)
  int eeprom_value_hi, eeprom_value_lo;
  #endif

  switch (ControlState) {
    
    case INIT_MODE:

      OutFlapSacar   = OUT_OFF;
      OutFlapRecoger = OUT_OFF;
      
      _InitControl();
    
      if (AutomanDigInStatus == HIGH)
        ControlState = MANUAL_MODE;
      else
        ControlState = AUTOMAT_MODE;
      break;
      
    case MANUAL_MODE:
      if (AutomanDigInStatus == HIGH)
        ControlState = MANUAL_MODE;
      else
        ControlState = INIT_MODE;
      
      _StatusManual();

      break;

    case AUTOMAT_MODE:
      if (AutomanDigInStatus == HIGH)
        ControlState = INIT_MODE;
      else
        ControlState = AUTOMAT_MODE;
      
      // Modo grabación (Los dos pulsadores pulsados a la vez)
      if ((SubirDigInStatus == LOW) && (BajarDigInStatus == LOW))
      {
        #if (GRABACION == 1)
        // Leds Off...
        _LedOff    (OUT_LED0);
        _LedOff    (OUT_LED1);
        _LedOff    (OUT_LED2);
        _LedOff    (OUT_LED3);
        
        GrabacionTickSec = 0;
        GrabacionCounter = 0;
        ControlState = GRABACION_INIT_MODE;
        #else
        break;
        #endif
      }
      else
      {
        // Modo Automático
        _StatusAutomatico();
      }
      
      break;

    #if (GRABACION == 1)
    case GRABACION_INIT_MODE:

      // Desactivamos las salidas por seguridad
      OutFlapSacar   = OUT_OFF;
      OutFlapRecoger = OUT_OFF;

      // Despues de 2 segundos...
      if (GrabacionTickSec >= 2)
      {
          GrabacionTickSec = 0;
          GrabacionCounter = 0;
          ControlState = GRABACION_MODE;
      }
      break;
    
    case GRABACION_MODE:

      _Led1Pulso (OUT_LED1, 1, PULSO_LED_FLAP_CORTO, PULSO_LED_FLAP_LARGO);
     
      // Desactivamos las salidas por seguridad
      OutFlapSacar   = OUT_OFF;
      OutFlapRecoger = OUT_OFF;

      // Confirmación de pulsación...
      if (SubirDigInStatus == LOW)
        _LedOn(OUT_LED0);
      else
        _LedOff(OUT_LED0);

      if (SubirPulsacion == PULSACION_CORTA)
        GrabacionCounter++;
    
      if (GrabacionTickSec >= 15)
      {
        // Memorizamos la posición...
        if (GrabacionCounter == 4)
          AnaInValue += 1;
        else if (GrabacionCounter == 1)
         AnaInValue -= 1;
        
        eeprom_value_lo = AnaInValue & 0x00FF;
        eeprom_value_hi = (AnaInValue & 0xFF00)>>8; 
        
        if (GrabacionCounter == 4)
        {
          EEPROM.write(EEPROM_ADD_P3_LO, eeprom_value_lo);
          EEPROM.write(EEPROM_ADD_P3_HI, eeprom_value_hi);
        }
        else if (GrabacionCounter == 3)
        {
          EEPROM.write(EEPROM_ADD_P2_LO, eeprom_value_lo);
          EEPROM.write(EEPROM_ADD_P2_HI, eeprom_value_hi);
        }
        else if (GrabacionCounter == 2)
        {
          EEPROM.write(EEPROM_ADD_P1_LO, eeprom_value_lo);
          EEPROM.write(EEPROM_ADD_P1_HI, eeprom_value_hi);
        }
        else if (GrabacionCounter == 1)
        {
          EEPROM.write(EEPROM_ADD_PMIN_LO, eeprom_value_lo);
          EEPROM.write(EEPROM_ADD_PMIN_HI, eeprom_value_hi);
        }

        #if (SERIAL_DEBUG == 1)
        Serial.print(">>>>> Grabacion ");
        if (GrabacionCounter == 0)
          Serial.println("NOOOOO!!!!! ");
        else 
        {
          Serial.print(GrabacionCounter);
          Serial.print(" -> ");
          Serial.println(AnaInValue);
        }
        #endif  

        // Iniciamos la configuración
        _InitConfig();
        
        ControlState = INIT_MODE;
      }
      break;
    #endif
  }
}

////////////////////////////
// Maquina de Modo Manual //
////////////////////////////
void _StatusManual(void) {

  switch (ManualState) {
    
    case MANUAL_STANDBY:

      //OutFlapSacar   = OUT_OFF;
      //OutFlapRecoger = OUT_OFF;
      
      if ((SubirDigInStatus == HIGH) && (BajarDigInStatus == LOW))
        ManualState = MANUAL_FLAP_BAJAR;
      else if ((SubirDigInStatus == LOW) && (BajarDigInStatus == HIGH))
        ManualState = MANUAL_FLAP_SUBIR;

      break;
      
    case MANUAL_FLAP_SUBIR:

      //OutFlapSacar   = OUT_OFF;
      //OutFlapRecoger = OUT_ON;
      
      if ((SubirDigInStatus == HIGH) && (BajarDigInStatus == LOW))
        ManualState = MANUAL_FLAP_SUBIR;
      else
        ManualState = MANUAL_STANDBY;

      #if (SERIAL_DEBUG == 1)
      if (DebugCounter == SERIAL_DEBUG_TIMER)  
        Serial.println("Manual -> Pulsando SUBIR **");
      #endif
      
      break;
      
    case MANUAL_FLAP_BAJAR:

      //OutFlapSacar   = OUT_ON;
      //OutFlapRecoger = OUT_OFF;

      if ((SubirDigInStatus == LOW) && (BajarDigInStatus == HIGH))
        ManualState = MANUAL_FLAP_BAJAR;
      else
        ManualState = MANUAL_STANDBY;

      #if (SERIAL_DEBUG == 1)
      if (DebugCounter == SERIAL_DEBUG_TIMER)
        Serial.println("Manual -> Pulsando BAJAR **");
      #endif

      break;
        
    default:
      break;
  }
}

////////////////////////////////
// Maquina de Modo Automatico //
////////////////////////////////
void _StatusAutomatico(void) {
  
  switch (AutomatState) {
    
    case AUTOMAT_STANDBY:

      // Histeresis...
      FlapPHIST_INF = CfgFlapPHIST_INF;
      FlapPHIST_SUP = CfgFlapPHIST_SUP;
    
      // Dos salidas a Off...
      OutFlapSacar   = OUT_OFF;
      OutFlapRecoger = OUT_OFF;

      // Subir...
      if ((SubirPulsacion != NO_PULSACION) && (BajarPulsacion == NO_PULSACION))
      {
        // Solo NO estamos en el Minimo...        
        if (FlapAdcTramo > FLAP_EN_MIN)
        {
          
          if (FlapAdcTramo <= FLAP_EN_P1)
            FlapAdcTramoStop = FLAP_EN_MIN;
          else if (FlapAdcTramo <= FLAP_EN_P2)
            FlapAdcTramoStop = FLAP_EN_P1;
          else /*if (FlapAdcTramo <= FLAP_EN_P3)*/
            FlapAdcTramoStop = FLAP_EN_P2;

          if (SubirPulsacion == PULSACION_LARGA)
            FlapAdcTramoStop = FLAP_EN_MIN;
          
          AutomatState = AUTOMAT_FLAP_SUBIR;
        }
      }
      // Bajar...
      else if ((BajarPulsacion != NO_PULSACION) && (SubirPulsacion == NO_PULSACION))
      {
        // Solo NO estamos en el Maximo...
        if (FlapAdcTramo < FLAP_EN_P3)
        {
          
          if (FlapAdcTramo >= FLAP_EN_P2)
            FlapAdcTramoStop = FLAP_EN_P3;
          else if (FlapAdcTramo >= FLAP_EN_P1)
            FlapAdcTramoStop = FLAP_EN_P2;
          else /*if (FlapAdcTramo >= FLAP_EN_MIN)*/
            FlapAdcTramoStop = FLAP_EN_P1;

          if (BajarPulsacion == PULSACION_LARGA)
            FlapAdcTramoStop = FLAP_EN_P3;
                    
          AutomatState = AUTOMAT_FLAP_BAJAR;
        }
      }
      
      break;

    case AUTOMAT_FLAP_SUBIR:

      // Al subir el eliminamos la histéresis inferior.
      //FlapPHIST_INF = 0;
      //FlapPHIST_SUP = CfgFlapPHIST_SUP;

      OutFlapSacar   = OUT_OFF;
      OutFlapRecoger = OUT_ON;

      // Hay que parar...
      if (FlapAdcTramo <= FlapAdcTramoStop)
      {
         // Si vamos al final estamos 1 segundo mas
         if ((FlapAdcTramoStop == FLAP_EN_MIN) || (FlapAdcTramoStop == FLAP_EN_P3))
         {
            StopTickSec = 0;
            AutomatState = AUTOMAT_WAIT;
         }
         else
            AutomatState = AUTOMAT_STANDBY;
      }

      if ((SubirPulsacion == NO_PULSACION) && (BajarPulsacion != NO_PULSACION))
      {
        AutomatState = AUTOMAT_STANDBY;
      
        #if (SERIAL_DEBUG == 1)
        Serial.println("Abortar SUBIR");
        #endif
      }
      
      #if (SERIAL_DEBUG == 1)
      if (DebugCounter == SERIAL_DEBUG_TIMER)
        Serial.println("Automat -> Flap SUBIR **");
      #endif

      break;
        
    case AUTOMAT_FLAP_BAJAR:

      // Al bajar el eliminamos la histéresis superior.
      //FlapPHIST_INF = CfgFlapPHIST_INF;
      //FlapPHIST_SUP = 0;

      OutFlapSacar   = OUT_ON;
      OutFlapRecoger = OUT_OFF;

      // Hay que parar...
      if (FlapAdcTramo >= FlapAdcTramoStop)
      {
         // Si vamos al final estamos 1 segundo mas
         if ((FlapAdcTramoStop == FLAP_EN_MIN) || (FlapAdcTramoStop == FLAP_EN_P3))
         {
            StopTickSec = 0;
            AutomatState = AUTOMAT_WAIT;
         }
         else
            AutomatState = AUTOMAT_STANDBY;
      }

      if ((SubirPulsacion != NO_PULSACION) && (BajarPulsacion == NO_PULSACION))
      {
        AutomatState = AUTOMAT_STANDBY;
      
        #if (SERIAL_DEBUG == 1)
        Serial.println("Abortar BAJAR");
        #endif
      }
      
      #if (SERIAL_DEBUG == 1)
      if (DebugCounter == SERIAL_DEBUG_TIMER)  
        Serial.println("Automat -> Flap BAJAR **");
      #endif
      
      break;

   case AUTOMAT_WAIT:
      // Despues de X segundo...
      if (StopTickSec >= STOP_WAIT_SECS)
        AutomatState = AUTOMAT_STANDBY;
      
      break;
   
    default:
      break;
  }

   BajarPulsacion = NO_PULSACION;
   SubirPulsacion = NO_PULSACION;
}

/////////////////////////////////////
// 4 Leds de posicion de los Flaps //
/////////////////////////////////////

/*
  Subir       Bajar     Paro
 
    MAX   |         |
          |         |
 ---------|   MAX   |---------
    T3    |         |
 ---------P3--------P3   T3   0 X X X
          |   T3    |
          |---------|---------
          |         |
 ---------|         |---------
    T2    |         |
 ---------P2--------P2   T2   0 X X o
          |   T2    |
          |---------|---------
          |         |
 ---------|         |---------
    T1    |         |
 ---------P1--------P1   T1   0 X o o
          |   T1    |
          |---------|---------
          |         |
 -------- |         |---------
    MIN   |         |
 -------PMIN------PMIN   MIN  X o o o
          |   MIN   |
          |---------|---------
   MIN    |         |
          |   MIN   |    MIN
          |         |
 */

void _UpdateFlapPosition(void) {

  // Tramos...
  if (AnaInValue <= CfgFlapPMIN + FlapPHIST_SUP)
    FlapAdcTramo = FLAP_EN_MIN;
  else if (AnaInValue <= CfgFlapP1 - FlapPHIST_INF)
    FlapAdcTramo = FLAP_TRAMO_Tm1;
  else if ((AnaInValue > CfgFlapP1 - FlapPHIST_INF) && (AnaInValue <= CfgFlapP1 + FlapPHIST_SUP))
    FlapAdcTramo = FLAP_EN_P1;
  else if ((AnaInValue > CfgFlapP1 + FlapPHIST_SUP) && (AnaInValue <= CfgFlapP2 - FlapPHIST_INF))
    FlapAdcTramo = FLAP_TRAMO_T12;
  else if ((AnaInValue > CfgFlapP2 - FlapPHIST_INF) && (AnaInValue <= CfgFlapP2 + FlapPHIST_SUP))
    FlapAdcTramo = FLAP_EN_P2;
  else if ((AnaInValue > CfgFlapP2 + FlapPHIST_SUP) && (AnaInValue <= CfgFlapP3 - FlapPHIST_INF))
    FlapAdcTramo = FLAP_TRAMO_T2M;
  else if (AnaInValue > CfgFlapP3 - FlapPHIST_INF)
    FlapAdcTramo = FLAP_EN_P3;


  #if (SERIAL_DEBUG == 1)
  if (DebugCounter == SERIAL_DEBUG_TIMER)
  {  
    Serial.print("Flap ");
    Serial.print(AnaInValue);
    Serial.print(" / ");
    Serial.print(FlapAdcTramo);
    Serial.print(" / ");
    Serial.println(FlapAdcTramoStop);
  }
  #endif

  #if (GRABACION == 1)
  if ((ControlState == GRABACION_INIT_MODE) || (ControlState == GRABACION_MODE))
    return;
  #endif

  // Indicadores Led...
  if (FlapAdcTramo >= FLAP_EN_P3)
  {
    _LedOff   (OUT_LED0);
    _LedOn    (OUT_LED1); 
    _LedOn    (OUT_LED2);
    _LedOn    (OUT_LED3);
  }
  else if (FlapAdcTramo >= FLAP_TRAMO_T2M)
  {
    _LedOff    (OUT_LED0);
    _LedOn     (OUT_LED1);
    _LedOn     (OUT_LED2);
  }
  else if (FlapAdcTramo >= FLAP_EN_P2)
  {
    _LedOff    (OUT_LED0);
    _LedOn     (OUT_LED1); 
    _LedOn     (OUT_LED2);
    _LedOff    (OUT_LED3); 
  }
  else if (FlapAdcTramo >= FLAP_TRAMO_T12)
  {
    _LedOff    (OUT_LED0);
    _LedOn     (OUT_LED1);
    _LedOff    (OUT_LED3); 
  }
  else if (FlapAdcTramo >= FLAP_EN_P1)
  {
    _LedOff    (OUT_LED0);
    _LedOn     (OUT_LED1); 
    _LedOff    (OUT_LED2);
    _LedOff    (OUT_LED3);    
  }
  else if (FlapAdcTramo >= FLAP_TRAMO_Tm1)
  {
    _LedOff    (OUT_LED2);
    _LedOff    (OUT_LED3); 
  }
  else
  {
    _LedOn     (OUT_LED0);
    _LedOff    (OUT_LED1); 
    _LedOff    (OUT_LED2);
    _LedOff    (OUT_LED3);
  }
}

////////////////////////////
// Update Outs            //
////////////////////////////
void _UpdateOuts(void) {
  
  if (OutFlapSacar == OUT_ON)
    digitalWrite(OUT_FLAP_BAJAR, HIGH);
  else
    digitalWrite(OUT_FLAP_BAJAR, LOW);

  if (OutFlapRecoger == OUT_ON)
    digitalWrite(OUT_FLAP_SUBIR, HIGH);
  else
    digitalWrite(OUT_FLAP_SUBIR, LOW);
}

//////////////////////
// Leds             //
//////////////////////
void _LedOn (int led_out) {
  digitalWrite(led_out, HIGH);
}

void _LedOff (int led_out) {
  digitalWrite(led_out, LOW);
}

void _Led1Pulso (int led_out, int pulsos, int pulso_corto, int pulso_largo) {

  // Incremento del contador...
  Led1Counter++;
  
  if (Led1Counter > Led1Duration)
  {
    Led1Counter = 0;
    
    if (Led1Pulsos < 2*pulsos)
    {
      Led1Duration = pulso_corto;
      Led1Pulsos++;

      // Cambio de estado del Led...
      if (Led1NextState == true)
        Led1NextState = false;
      else
        Led1NextState = true;
    }
    else
    {
      Led1Duration = pulso_largo;
      Led1Pulsos = 0;

      Led1NextState = false;
    }
    
    // Cambio de estado del Led...
    if (Led1NextState == true)
      digitalWrite(led_out, HIGH);
    else
      digitalWrite(led_out, LOW);
  }
}

/*
void _Led2Pulso (int led_out, int pulsos, int pulso_corto, int pulso_largo) {

  // Incremento del contador...
  Led2Counter++;
  
  if (Led2Counter > Led2Duration)
  {
    Led2Counter = 0;
    
    if (Led2Pulsos < 2*pulsos)
    {
      Led2Duration = pulso_corto;
      Led2Pulsos++;

      // Cambio de estado del Led...
      if (Led2NextState == true)
        Led2NextState = false;
      else
        Led2NextState = true;
    }
    else
    {
      Led2Duration = pulso_largo;
      Led2Pulsos = 0;

      Led2NextState = false;
    }
    
    // Cambio de estado del Led...
    if (Led2NextState == true)
      digitalWrite(led_out, HIGH);
    else
      digitalWrite(led_out, LOW);
  }
}

void _Led3Pulso (int led_out, int pulsos, int pulso_corto, int pulso_largo) {

  // Incremento del contador...
  Led3Counter++;
  
  if (Led3Counter > Led3Duration)
  {
    Led3Counter = 0;
    
    if (Led3Pulsos < 2*pulsos)
    {
      Led3Duration = pulso_corto;
      Led3Pulsos++;

      // Cambio de estado del Led...
      if (Led3NextState == true)
        Led3NextState = false;
      else
        Led3NextState = true;
    }
    else
    {
      Led3Duration = pulso_largo;
      Led3Pulsos = 0;

      Led3NextState = false;
    }
    
    // Cambio de estado del Led...
    if (Led3NextState == true)
      digitalWrite(led_out, HIGH);
    else
      digitalWrite(led_out, LOW);
  }
}

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
*/
