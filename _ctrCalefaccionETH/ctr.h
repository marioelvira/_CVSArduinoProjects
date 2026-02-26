#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTR_H_
#define _CTR_H_

/*
  Arranque
  --------
  Cuando la entrada TERMO_ON_IN está a ON
  -> Salida RES_PRIN_OUT a ON una tensión RES_PRIN_VOUT ... La temperatura RES_PRIN_TEMP commienza a subir.
  Cuando RES_PRIN_TEMP sube a RES_PRIN_TEMP_INYE_ON
  -> Salida RES_INYE_OUT a ON una tensión RES_INYE_VOUT ... La temperatura RES_INYE_TEMP commienza a subir.
  
  Ambas salidas se mantienen a ON hasta que lleguén a RES_PRIN_CONSIG_TEMP y RES_INYE_CONSIG_TEMP
    -> La RES_PRIN_TEMP, RES_INYE_TEMP siguen subiendo...

  Cuando RES_PRIN_TEMP llega a RES_PRIN_CONSIG_TEMP
  -> Salida RES_PRIN_OUT a OFF ... La temperatura RES_PRIN_TEMP commienza a bajar.
  Cuando RES_PRIN_TEMP baje hasta (RES_PRIN_CONSIG_TEMP - RES_PRIN_HYST_TEMP)
  -> Salida RES_PRIN_OUT a ON una tensión RES_PRIN_VOUT y seguimos el ciclo.
  
  Cuando RES_INYE_TEMP llega a RES_INYE_CONSIG_TEMP
  -> Salida RES_INYE_OUT a OFF ... La temperatura RES_INYE_TEMP commienza a bajar.
  Cuando RES_INYE_TEMP baje hasta (RES_INYE_CONSIG_TEMP - RES_INYE_HYST_TEMP)
  -> Salida RES_INYE_OUT a ON una tensión RES_INYE_VOUT y seguimos el ciclo.

  Cuando RES_PRIN_TEMP suba hasta RES_PRIN_CONSIG_TEMP y RES_INYE_TEMP suba hasta RES_INYE_CONSIG_TEMP 
  ???????????????????????????????????? DUDA ??????????????????????????????????????????????????????????
  -> Salida BOM_AGUA_OUT a ON
  -> Salida ACT_QUEM_OUT a ON ... incrementamos el contador ACT_QUEM_CONT + 1
    
  Cuando BOM_AGUA_TEMP llega a la temperatura BOM_AGUA_CONSIG_TEMP ->
  -> Salida BOM_AGUA_OUT a ON
  -> Salida ACT_QUEM_OUT a OFF
  
  Cuando BOM_AGUA_TEMP baje hasta (BOM_AGUA_CONSIG_TEMP - BOM_AGUA_HYST_TEMP)
  -> Salida BOM_AGUA_OUT a ON
  -> Salida ACT_QUEM_OUT a ON, y seguimos el ciclo

  Si RES_INYE_TEMP baje hasta RES_INYE_QUEM_OFF_TEMP ->
  -> Salida BOM_AGUA_OUT a ON
  -> Salida ACT_QUEM_OUT a OFF
  
  Cuando RES_INYE_TEMP suba hasta RES_INYE_CONSIG_TEMP
   ???????????????????????????????????? DUDA ??????????????????????????????????????????????????????????
  -> Salida BOM_AGUA_OUT a ON
  -> Salida ACT_QUEM_OUT a ON ... incrementamos el contador ACT_QUEM_CONT + 1, y seguimos el ciclo

  Confirmación
  ------------
  Cuando ACT_QUEM_OUT a ON tenemos que leer en X segundos que ACT_QUEM_IN a ON
  Sino ACT_REARM_OUT a ON x segundos, e indicar ALARM_REARM_AUTO, y repetir cliclo de arranque quemador
  Si el error pesiste X intentos -> ALARM_REARM_MANUAL

  Achique
  -------
  Cuando ACT_QUEM_CONT lleghe a ACT_ACHI_CONT
  -> ACT_ACHI_OUT a ON durante X segundos y ACT_QUEM_CONT = 0

  Alarmas
  -------
  Si la RES_PRIN_TEMP no alcanza RES_PRIN_CONSIG_TEMP en RES_PRIN_CONSIG_MIN minutos - Se para el sistema y se indica ALARM_RES_PRIN
  Si la RES_INYE_TEMP no alcanza RES_INYE_CONSIG_TEMP en RES_INYE_CONSIG_MIN minutos - Se para el sistema y se indica ALARM_RES_INYE
  Si la BOM_AGUA_TEMP no alcanza BOM_AGUA_CONSIG_TEMP en BOM_AGUA_CONSIG_MIN minutos - Se para el sistema y se indica ALARM_BOM_AGUA

  Entradas
  --------
  - Encendido     TERMO_ON_IN     DIO
  - Quemador      ACT_QUEM_IN     DIO
  - Frecuencia    FREC_IN         INT

  Salidas
  -------
  - Resistencia principal   RES_PRIN_OUT    TRIAK
  - Resistencia inyector    RES_INYE_OUT    TRIAK
  - Quemador                ACT_QUEM_OUT    DIO
  - Bomba                   BOM_AGUA_OUT    DIO
  - Achique                 ACT_ACHI_OUT    DIO
*/

#define MODE_TEST   1
#define MODE_AUTO   0

#endif // _CTR_H_

#ifdef __cplusplus
} // extern "C"
#endif
