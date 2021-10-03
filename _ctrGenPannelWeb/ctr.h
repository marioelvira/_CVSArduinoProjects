#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTR_H_
#define _CTR_H_

/**********************************************************************************************************************
  Control de Panel de Generador para Campo de Vuelo Sesma.
  Creado  21/03/2019 Modificado 16/03/2021
  
  La salida de control será "GPIO16 -> D0" (salida base transistor, para relé)
  Siempre estará en H. (desde que la placa se alimente hasta que se apague después del tiempo fijado).
  El gobierno del incremento del tiempo, lo hacemos con "GPIO0 -> D3" (relé pulsador)
  El indicador de display lo hacemos con:
    "GPIO14 -> D5" - D3 - A
    "GPIO12 -> D6" - D4 - B
    "GPIO13 -> D7" - D5 - C
    "GPIO15 -> D8" - D6 - D
  
  Salida + Dislay: "GPIO5 -> D1" (salida base transistor, para relé) (siempre H, intermitente los 15 últimos segundos)
  Salida Zumbador: "GPIO4 -> D2" (salida base transistor, para relé) (intermitente solo los 15 últimos segundos)
  
  Cuando pulsamos "GPIO0 -> D3" por primera vez, se alimenta el arduino y se ponen en H las salidas D 1 y D 6.  
                                Durante 15 minutos y las salidas de display,  H L L L (el display indica  1 )   15 min
  Si volvemos a pulsar. Incrementamos 15 minutos y las salidas de display,  L H L L (el display indica  2 )   30 min
  Si volvemos a pulsar. Incrementamos 15 minutos y las salidas de display,  H H L L (el display indica  3 )   1h 00 min
  Si volvemos a pulsar. Incrementamos 30 minutos y las salidas de display,  L L H L (el display indica  4 )   1h 30 min
  Si volvemos a pulsar. Incrementamos 30 minutos y las salidas de display,  H L H L (el display indica  5 )   2h 00 min
  Si volvemos a pulsar. Incrementamos 60 minutos y las salidas de display,  H H L L (el display indica  6 )   3h 00 min
  Si volvemos a pulsar. Incrementamos 60 minutos y las salidas de display,  H H H L (el display indica  7 )   4h 00 min
  Si volvemos a pulsar. Incrementamos 60 minutos y las salidas de display,  L L L H (el display indica  8 )   5h 00 min
  Si volvemos a pulsar. Incrementamos 120 minutos y las salidas de display, H L L H (el display indica  9 )   7h 00 min
  No actuara después de llegar al 9, (para que no vuelva a uno)
  
  Cuando el tiempo se termine ->   L L L L (el display indicara  0)
  
  Las salidas "GPIO5 -> D1" - "GPIO4 -> D2" Se ponen intermitentes durante 15 segundos 
  Si en ese tiempo no se pulsa, se desconecta "GPIO16 -> D0" y se apaga el generador.

*************************************************************************************************************************/

#define MODE_TEST   1
#define MODE_AUTO   0

#define CTR_BUZZER_TICK          500     // 500ms

// Estados principales...
#define STATE_START         0
#define STATE_GEN_ON        1
#define STATE_GEN_ZUMB      2
#define STATE_GEN_OFF       3
#define STATE_AUTO_OFF      4

#endif // _CTR_H_

#ifdef __cplusplus
} // extern "C"
#endif
