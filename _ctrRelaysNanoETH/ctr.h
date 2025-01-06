#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTR_H_
#define _CTR_H_

#define MODE_TEST   1
#define MODE_AUTO   0

/*
  Control por Entradas
  --------------------

  In0 - Gen Diesel
  In1 - Grupo Gasolina
  Out0 - Inv Baterias: Enchufes
  Out1 - Inv Baterias: Luces
  Out2 - Gen Diesel: Enchufes
  Out3 - Gen Diesel: Luces
  Out4 - Grupo Gasolina: Enchufes
  Out5 - Grupo Gasolina: Luces

  In0 In1 |   Out0    Out1    Out2    Out3    Out4
  --------------------------------------------------
  0   0   |   1       1       0       0       0   IN_STATE0 - Inversor BAT
  1   0   |   0       0       1       1       0   IN_STATE1 - Generador Diesel
  0   1   |   0       0       0       1       1   IN_STATE2 - Grupo Gasolina
  1   1   |   0       0       1       1       0   IN_STATE1 - *Generador Diesel
 
  Control por consumos:
  ---------------------
    Si, estamos en IN_STATE0, y el consumo en AIN0 > X amps o AIN1 > X amps durante mas de 3 segundos
    vamos al IN_STATE1 y permanecemos durante 3 minutos.
*/

// Estados Generales
#define IN_STATE0        0
#define IN_STATE1        1
#define IN_STATE2        2

#define OUT_STATE0       0
#define OUT_STATE1       1
#define OUT_STATE2       2

#define IRMS_STATE0       0
#define IRMS_STATE1       1
#define IRMS_STATE2       2

// Tiempos
#define STATE0_0_1_TICKS    1500      // 1.5s
#define STATE0_1_2_TICKS    180000    // 3m
#define STATE1_0_1_TICKS    1500      // 1.5s
#define STATE1_1_2_TICKS    1500      // 1.5s
#define STATE2_0_1_TICKS    1500      // 1.5s
#define STATE2_1_2_TICKS    1500      // 1.5s

#define IRMS_STATE1_TICKS   3000      // 3s
#define IRMS_STATE2_SECS    180       // 3min

//#define X_3600    3600

#endif // _CTR_H_

#ifdef __cplusplus
} // extern "C"
#endif
