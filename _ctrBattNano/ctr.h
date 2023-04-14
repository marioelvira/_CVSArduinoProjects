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

 Si la Entrada de relog está a 1 -> Relé abierto (NO permite funcionamiento al Inversor) y nos quedamos ahí
 Sino -> Cerrar Relé y ...

  Control Por Display
  -------------------
  Si Pulsador -> Pulsador corta -> incremanta la cuenta del display.
              -> Pulsador larga -> Display a 0.
  
  Si Display != 0 -> Relé abierto (NO permite funcionamiento al Inversor) y nos quedamos ahí.
  Si Display == 0 -> Cerrar Relé y ...
  
  Control en Corriente (A0: 1024 -> 5A)
  ----------------------------------------
    Si Consumo en A0 > 0,54V -> señal en A0 es mayor -> Relé abierto (NO permite funcionamiento al Inversor) y nos quedamos ahí
    Sino ->  Esperamos un tiempo T1 hasta volver a arrancar (aplicamos otras lógicas)

  Control por tensión (A1: 1024 -> 25V)
  -------------------------------------
    Si Tensión < 10,5 V -> Relé abierto (NO permite funcionamiento al Inversor) y nos quedamos ahí
    Sino -> Esparamos hasta que la tensión llegue a las 14 V -> Relé cerrado (permite funcionamiento al Inversor)
*/


// Estados principales...
#define STATE_START       0
#define STATE_XXXX        1

#endif // _CTR_H_

#ifdef __cplusplus
} // extern "C"
#endif
