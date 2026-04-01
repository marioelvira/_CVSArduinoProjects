#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTR_H_
#define _CTR_H_

extern String ctrStateString;
extern int ctrMode;
extern int ctrInState;
extern int ctrOutState;

extern int ctrTempPrin;
extern int ctrTemp;

/*      
        Notas Alberto
        -------------
        1)Se trata de controlar el calentamiento del aceite combustible,  el calentamiento del inyector, del quemador, y de la  
         circulación del agua de radiadores.  Tabien cotrolaremos , el encendido del quemador a traves del On Fire ,el  
         reinicio del quemador , y del drenaje del aceite, procedente del sangrado del inyector.
         Veremos en una pantalla LCD 2004, La temperaturas del aceite, del inyector, y los porcentajes de la tension de     
         caldeo del aceite y del inyector, asi como la temperatura del agua, y el estado ON OFF de la bomba de
         recirculación.
         El ON OFF del circuito lo efectuamos a traves del termostato instalado en la vivienda, y controlado a traves de  
         APP independiente y ajustado por el usuario.
         Todo la controlamos a traves de la APP MQTT desde el movil del usuario.

         Funcionamiento
         --------------
         2) El circuito estará alimentado con, 230v, 12v, 5v. e internet a traves de Ethernet.
         Termostato en ON  IN0 , GPIO02, Pin 35 en H.
         Atraves de la PTC 1 , leemos la temperatura del aceite si   < de la temperatura determinada , conecta la resistencia 
         R1  TR0  GPIO33, Pin 5.
         El usuario puede ajustar la temperatura maxima y el porcentaje de alimentación de la resistencia.:  Ejemplo:
         El maximo fijado es de 100 grados- hasta alcanzar los 90 grados, la resistencia recibe el 80%, y despues disminu   
         ye un 10% por grado Hasta alcanzar la temperatura fijada. Se intenta reducir la inercia y sobrecalentamiento.
         Cuando disminuye la temperatura aumentamos el porcentaje de forma inversa.
         Cuando,PTC1,esta al nivel predeterminado:
         Comienza el calentamiento del  inyector R2  TR1 GPIO32, Pin 6  controlado por PTC2 , y actuamos igual que con
         PTC1.
         Tenemos una salida auxiliar  R3 TR2 GPIO27, Pin 7 .Controlada  por PTC1 y con las mismas funciones  que R1.
         Cuando todas las temperaturas estan al nivel preajustado iniciamos el quemador, OUT0, GPIO54.Pin 21.
         El quemador tiene su termostato propio y seguira las pautas de funcionamiento.
         Para saber que el quemador esta funcionando tenemos una entrada ON FIRE  IN1 GPIO03, Pin 34.  Que avisara
         al usuario a traves de la APP . Tanto si esta en ON o OFF
         Si el quemador no arranca y avisa,tenemos la posibilidad de reiniciarlo desde la APP, a traves de Reset quemador
         OUT4  GPIO14,Pin 29..Tiene que actuar durante 10 segundos.
        3) Con la sonda PTC3 controlamos la recirculación del agua de calefacción, conectamos la bomba OUT3 GPIO15,  
         Pin 27,  cuando la temperatura llega a los 45 grados, y desconecta la bomba, cuando la temperatura baje de los
         40 grados.  Quedando en espera para el proximo ciclo
        4) Bomba de drenaje, GPIO19 OUT1 Pin 22. Tiene que  conectar 30 segundos cada cinco arranques del quemador
        5) Cuando GPIO02  Pin 35, pase a L DESCONECTARA TODAS LAS SALIDAS  EXCEPTO LA BOMBA DE
         RECIRCULACIÓN, OUT3,GPIO15.
         Seguira leyendo las temperaturas y mostrando en pantalla y APP
*/

/*
  Arranque
  --------
  Cuando la entrada TERMOSTATO_IN está a ON
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
  -> Salida QUEMADOR_OUT a ON ... incrementamos el contador ACT_QUEM_CONT + 1
    
  Cuando BOM_AGUA_TEMP llega a la temperatura BOM_AGUA_CONSIG_TEMP ->
  -> Salida BOM_AGUA_OUT a ON
  -> Salida QUEMADOR_OUT a OFF
  
  Cuando BOM_AGUA_TEMP baje hasta (BOM_AGUA_CONSIG_TEMP - BOM_AGUA_HYST_TEMP)
  -> Salida BOM_AGUA_OUT a ON
  -> Salida QUEMADOR_OUT a ON, y seguimos el ciclo

  Si RES_INYE_TEMP baje hasta RES_INYE_QUEM_OFF_TEMP ->
  -> Salida BOM_AGUA_OUT a ON
  -> Salida QUEMADOR_OUT a OFF
  
  Cuando RES_INYE_TEMP suba hasta RES_INYE_CONSIG_TEMP
   ???????????????????????????????????? DUDA ??????????????????????????????????????????????????????????
  -> Salida BOM_AGUA_OUT a ON
  -> Salida QUEMADOR_OUT a ON ... incrementamos el contador ACT_QUEM_CONT + 1, y seguimos el ciclo

  Confirmación
  ------------
  Cuando QUEMADOR_OUT a ON tenemos que leer en X segundos que QUEMADOR_IN a ON
  Sino ACT_REARM_OUT a ON x segundos, e indicar ALARM_REARM_AUTO, y repetir cliclo de arranque quemador
  Si el error pesiste X intentos -> ALARM_REARM_MANUAL

  Achique
  -------
  Cuando ACT_QUEM_CONT lleghe a ACT_ACHI_CONT
  -> ACT_ACHIQUE_OUT a ON durante X segundos y ACT_QUEM_CONT = 0

  Alarmas
  -------
  Si la RES_PRIN_TEMP no alcanza RES_PRIN_CONSIG_TEMP en RES_PRIN_CONSIG_MIN minutos - Se para el sistema y se indica ALARM_RES_PRIN
  Si la RES_INYE_TEMP no alcanza RES_INYE_CONSIG_TEMP en RES_INYE_CONSIG_MIN minutos - Se para el sistema y se indica ALARM_RES_INYE
  Si la BOM_AGUA_TEMP no alcanza BOM_AGUA_CONSIG_TEMP en BOM_AGUA_CONSIG_MIN minutos - Se para el sistema y se indica ALARM_BOM_AGUA

  Entradas
  --------
  - Encendido     TERMOSTATO_IN   DIO
  - Quemador      QUEMADOR_IN     DIO
  - Frecuencia    FREC_IN         INT

  Salidas
  -------
  - Resistencia principal   RES_PRIN_TRC
  - Resistencia inyector    RES_INYE_TRC
  - Quemador                QUEMADOR_OUT
  - Bomba                   BOM_AGUA_OUT
  - Achique                 ACHIQUE_OUT
*/

// Modos de Operación
#define MODE_TEST   1
#define MODE_AUTO   0

// OUTs Index
#define AGUA_OUT      3
#define ACHIQUE_OUT   4
#define QUEMADOR_OUT  5

// TRIAC Index
#define RES_PRIN_TRC  0
#define RES_INYE_TRC  1
#define RES_AUX_TRC   2

// INs Index
#define QUEMADOR_IN   2
#define TERMOSTATO_IN 3

// TEMPs Index
// Configuración

#endif // _CTR_H_

#ifdef __cplusplus
} // extern "C"
#endif
