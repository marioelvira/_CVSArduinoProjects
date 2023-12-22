#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTR_H_
#define _CTR_H_

#define MODE_TEST   1
#define MODE_AUTO   0

/*
  Tabla de Verdad
  ---------------

  In1 In2 |   OutA 1  OutB 2  OutC 3  OutD 4  OutE 5
  --------------------------------------------------
  0   0   |   1       1       0       0       0   Estado 0
  1   0   |   0       0       1       1       0   Estado 1
  1   1   |   0       0       1       1       0   Estado 1
  0   1   |   0       0       0       1       1   Estado 2
 

  Cambio de Estado 1 a Estado 2 si:
    In1 > 0,3V mas de 3 segundos
    o 
    In2 > 0,115 mas de 3 segundos

  Permanece en Estado 2 durante 3 minutos
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

//#define X_3600    3600

#endif // _CTR_H_

#ifdef __cplusplus
} // extern "C"
#endif
