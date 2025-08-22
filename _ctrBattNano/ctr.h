#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTR_H_
#define _CTR_H_

#define MODE_TEST   1
#define MODE_AUTO   0

/*
 * 
 ******************
 * Funcionamiento * 
 ******************
 La Salida Digital, va al inversor para que tire de la batería.
 Todo el control se basa en esa salida digital.

 Si la Entrada de relog está a 1 -> Relé abierto (NO permite funcionamiento al Inversor) y nos quedamos ahí
 Sino -> Cerrar Relé y ...

  Control Por Display
  -------------------
  Si Pulsador -> Pulsador corta -> incremanta la cuenta del display.
              -> Pulsador larga -> Display a 0.
  
  Si Display != 0 -> Relé abierto (NO permite funcionamiento al Inversor) y nos quedamos ahí.
  Si Display == 0 -> Cerrar Relé y ...
  
  Control en Corriente 
  --------------------
    Si Consumo > XXXX mA -> Relé abierto (NO permite funcionamiento al Inversor) y nos quedamos ahí
    Sino ->  Esperamos un tiempo T1 hasta volver a arrancar (aplicamos otras lógicas)

  Control por tensión
  -------------------
    Si Tensión < 10,5 V -> Relé abierto (NO permite funcionamiento al Inversor) y nos quedamos ahí
    Sino -> Esparamos hasta que la tensión llegue a las 14 V -> Relé cerrado (permite funcionamiento al Inversor)
*/


// Estados principales...
#define CTR_INV_STANDBY         0
#define CTR_INV_OFF             1

#define CTR_TICK_HIST           10000 // 10s

#define IN_CLOCK_INVERTER_DIS   0
#define IN_CLOCK_INVERTER_EN    1

#define OUT_RELE_INVERTER_OFF   0
#define OUT_RELE_INVERTER_ON    1

#define CTR_TICK_OUT2_ON        2000  // 2s
#define CTR_TICK_OUT2_OFF       1000  // 1s

//#define X_3600    3600

#endif // _CTR_H_

#ifdef __cplusplus
} // extern "C"
#endif
