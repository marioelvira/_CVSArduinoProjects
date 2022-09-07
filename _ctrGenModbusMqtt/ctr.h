#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTR_H_
#define _CTR_H_

#include "main.h"

#define MODE_TEST   1
#define MODE_AUTO   0

#define CTR_BUZZER_TICK          500     // 500ms

// Estados principales...
#define STATE_STANDBY       0
#define STATE_START         1
#define STATE_GEN_ON        2
#define STATE_GEN_ZUMB      3
#define STATE_GEN_OFF       4

// Pulsación
#define NO_PULSACION        0   // x10ms
#define PULSACION_OK        75  // x10ms

#define FLANCO_UP     0
#define FLANCO_DOWN   1
#define FLANCO        FLANCO_UP  // FLANCO_DOWN

#endif // _CTR_H_

#ifdef __cplusplus
} // extern "C"
#endif
