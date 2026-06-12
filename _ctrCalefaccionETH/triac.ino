#include "main.h"
#include "triac.h"

#if (_USE_TRIAC_ == 1)
#include "driver/gpio.h"
#include "driver/gpio_filter.h"

///////////////
// Variables //
///////////////
int   TriacCtr[TRIAC_NUMBER];
hw_timer_t * triac1Timer = NULL;
hw_timer_t * triac2Timer = NULL;
hw_timer_t * triac3Timer = NULL;

//const int triacZCPin = PIN_ZDA;
const gpio_num_t PIN_ZC = GPIO_NUM_22;  // PIN_ZDA

int triacZCAlarmSec = 0;
uint32_t triacZCTickUs = 0;
int triacZCPeriodUs;
float triacZCFrec = 0;
int triacZCcount = 0;
int triacZCerror = 0;

volatile int triac1Delay = 0;
int triac1Cicle = 50;
volatile int triac2Delay = 0;
int triac2Cicle = 50;
volatile int triac3Delay = 0;
int triac3Cicle = 50;

#if (_TRIAC_PIN_DEBUG_ == 1)
bool triacZCdebug = false;
#endif

////////////////
// Interrupts //
////////////////
void IRAM_ATTR isrTriac1Timer()
{
  digitalWrite(PIN_TRIAC1, PIN_TRIAC_ON);
  esp_rom_delay_us(10); // delayMicroseconds(10);
  digitalWrite(PIN_TRIAC1, PIN_TRIAC_OFF);
}

void IRAM_ATTR isrTriac2Timer()
{
  digitalWrite(PIN_TRIAC2, PIN_TRIAC_ON);
  esp_rom_delay_us(10); // delayMicroseconds(10);
  digitalWrite(PIN_TRIAC2, PIN_TRIAC_OFF);
}

void IRAM_ATTR isrTriac3Timer()
{
  digitalWrite(PIN_TRIAC3, PIN_TRIAC_ON);
  esp_rom_delay_us(10); // delayMicroseconds(10);
  digitalWrite(PIN_TRIAC3, PIN_TRIAC_OFF);
}

void IRAM_ATTR isrZeroCross()
{
  // LEER EL PIN INMEDIATAMENTE: Solo procesamos si el pin está en HIGH
  // (Si tu pulso es invertido y cae a masa en el cruce por cero, cambia == HIGH por == LOW)
  //if (gpio_get_level(PIN_ZC) == HIGH) 
  //{
    uint32_t periodUs, nowUs = micros();

    #if (_TRIAC_PIN_DEBUG_ == 1)
    if (triacZCdebug == false)
    {
      digitalWrite(PIN_DEBUG, PIN_OUT_OFF);
      triacZCdebug = true;
    }
    else
    {
      digitalWrite(PIN_DEBUG, PIN_OUT_ON);
      triacZCdebug = false;
    }
    #endif

    // ZC Period
    periodUs = int (nowUs - triacZCTickUs);

    // Ruido
    if (periodUs < 10000)
      triacZCerror++;
    else
    {
      if ((TriacCtr[0] == TRIAC_ON) && (cfgTriacVout[0] < cfgTriacRedVout))
      {
        timerRestart(triac1Timer);
        // timerAlarm(timer, valor_alarma, autoreload, reload_count)
        timerAlarm(triac1Timer, triac1Delay, false, 0);
      }

      if ((TriacCtr[1] == TRIAC_ON) && (cfgTriacVout[1] < cfgTriacRedVout))
      {
        timerRestart(triac2Timer);
        // timerAlarm(timer, valor_alarma, autoreload, reload_count)
        timerAlarm(triac2Timer, triac2Delay, false, 0);
      }

      if ((TriacCtr[2] == TRIAC_ON) && (cfgTriacVout[2] < cfgTriacRedVout))
      {
        timerRestart(triac3Timer);
        // timerAlarm(timer, valor_alarma, autoreload, reload_count)
        timerAlarm(triac3Timer, triac3Delay, false, 0);
      }

      triacZCPeriodUs = periodUs;
      triacZCTickUs = nowUs;
      triacZCAlarmSec = 0;
      triacZCcount++;
    }
  //}
}

//////////////////
// TRIAC set up //
//////////////////
void _TRIACSetup()
{
  // TRIAC
  pinMode(PIN_TRIAC1, OUTPUT);
  pinMode(PIN_TRIAC2, OUTPUT);
  pinMode(PIN_TRIAC3, OUTPUT);

  digitalWrite(PIN_TRIAC1, PIN_TRIAC_OFF);
  digitalWrite(PIN_TRIAC2, PIN_TRIAC_OFF);
  digitalWrite(PIN_TRIAC3, PIN_TRIAC_OFF);
  
  for (int i = 0; i < TRIAC_NUMBER; i++)
    TriacCtr[i] = TRIAC_OFF;
  
  // NUEVA API v3.0: timerBegin solo recibe la FRECUENCIA en Hz
  // Configuramos 1MHz para que cada "tick" sea de 1 microsegundo
  triac1Timer = timerBegin(1000000);
  timerAttachInterrupt(triac1Timer, &isrTriac1Timer);
  triac2Timer = timerBegin(1000000);
  timerAttachInterrupt(triac2Timer, &isrTriac2Timer);
  triac3Timer = timerBegin(1000000);
  timerAttachInterrupt(triac3Timer, &isrTriac3Timer);

  _TRIACUpdate();

  /////////////////
  // ZC detector //
  /////////////////
  gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << PIN_ZC),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,       // GPIO_PULLUP_DISABLE Tenemos Pull up externo
    .pull_down_en = GPIO_PULLDOWN_DISABLE,  // Tenemos Pull up externo
    //.intr_type = GPIO_INTR_POSEDGE          // Interrupción en High Level
    //.intr_type = GPIO_INTR_HIGH_LEVEL     // Interrupción en High Level
    .intr_type = GPIO_INTR_ANYEDGE          // <--- CAMBIA A ESTO (Cualquier flanco)
  };
  gpio_config(&io_conf);

  /*
  gpio_flex_glitch_filter_config_t filter_config = {
    .clk_src = GLITCH_FILTER_CLK_SRC_DEFAULT,
    .gpio_num = PIN_ZC,
    //.window_width_ns = 1200000,  //1.2ms 
    //.window_thres_ns = 1000000,  //0.8ms
    .window_width_ns = 20000,   // Reduce a 20 microsegundos (antes 1.2ms)
    .window_thres_ns = 15000,   // Reduce a 15 microsegundos (antes 1.0ms)
  };

  gpio_glitch_filter_handle_t filter_handle = NULL;
  if (gpio_new_flex_glitch_filter(&filter_config, &filter_handle) == ESP_OK) {
    gpio_glitch_filter_enable(filter_handle);
  }
  */
  gpio_install_isr_service(0); 
  gpio_isr_handler_add(PIN_ZC, (gpio_isr_t)isrZeroCross, NULL);

  triacZCFrec = 0;
  triacZCPeriodUs = 0;
  triacZCTickUs = micros();
  triacZCAlarmSec = 0;
  triacZCcount = 0;

  #if (_TRIAC_PIN_DEBUG_ == 1)
  pinMode(PIN_DEBUG, OUTPUT);
  digitalWrite(PIN_DEBUG, PIN_OUT_OFF);
  triacZCdebug = false;
  #endif
}

////////////////
// TRIAC loop //
////////////////
void _TRIACLoop()
{
  if (cfgTriacVout[0] >= cfgTriacRedVout)
  {
    if (TriacCtr[0] == TRIAC_ON)
      digitalWrite(PIN_TRIAC1, PIN_TRIAC_ON);
    else
      digitalWrite(PIN_TRIAC1, PIN_TRIAC_OFF);
  }

  if (cfgTriacVout[1] >= cfgTriacRedVout)
  {
    if (TriacCtr[1] == TRIAC_ON)
      digitalWrite(PIN_TRIAC2, PIN_TRIAC_ON);
    else
      digitalWrite(PIN_TRIAC2, PIN_TRIAC_OFF);
  }

  if (cfgTriacVout[2] >= cfgTriacRedVout)
  {
    if (TriacCtr[2] == TRIAC_ON)
      digitalWrite(PIN_TRIAC3, PIN_TRIAC_ON);
    else
      digitalWrite(PIN_TRIAC3, PIN_TRIAC_OFF);
  }

  // Check Alarm
  triacZCAlarmSec++;
  if (triacZCAlarmSec > TRIAC_ALARM_ZC_SEC)
  {
    triacZCFrec = 0;
    triacZCPeriodUs = 0;
    
    #if (_USE_ALARM_ == 1)
    alarmOn[AL_ERROR1] = 1;
    #endif
  }
  else
  {
    if (triacZCPeriodUs > 0) {
      triacZCFrec = 500000.0 / triacZCPeriodUs;
    } else {
      triacZCFrec = 0;
    }
    
    #if (_USE_ALARM_ == 1)
    alarmOn[AL_ERROR1] = 0;
    #endif
  }
}

void _TRIACUpdate()
{
  triac1Cicle = (int)(cfgTriacVout[0]*100)/cfgTriacRedVout;
  triac2Cicle = (int)(cfgTriacVout[1]*100)/cfgTriacRedVout;
  triac3Cicle = (int)(cfgTriacVout[2]*100)/cfgTriacRedVout;

  // En v3.0, el tiempo se maneja según la frecuencia configurada en timerBegin
  // Si configuramos 1,000,000 Hz, 1 tick = 1 microsegundo.
  triac1Delay = map(triac1Cicle, 0, 100, 9500, 100);
  triac2Delay = map(triac2Cicle, 0, 100, 9500, 100);
  triac3Delay = map(triac3Cicle, 0, 100, 9500, 100);

  #if (_TRIAC_SERIAL_DEBUG_ == 1)
  Serial.print("triac1Cicle: ");     Serial.println (triac1Cicle);
  Serial.print("triac2Cicle: ");     Serial.println (triac2Cicle);
  Serial.print("triac3Cicle: ");     Serial.println (triac3Cicle);
  
  Serial.print("triac1Delay: ");     Serial.println (triac1Delay);
  Serial.print("triac2Delay: ");     Serial.println (triac2Delay);
  Serial.print("triac3Delay: ");     Serial.println (triac3Delay);
  #endif
}

#endif // (_USE_TRIAC_ == 1)