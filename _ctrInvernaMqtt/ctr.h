#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTR_H_
#define _CTR_H_

#include "main.h"

#define MODE_TEST   1
#define MODE_AUTO   0

// Estados principales...
#define STATE_STANDBY         0
#define STATE_TEMPHI          1
#define STATE_TEMPLO          2

// Estado de Ventana
#define STATE_WSTANDBY        0
#define STATE_WCLOSING        1
#define STATE_WOPENING        2

#define CLOSE_WINDOW          1
#define WAIT_TO_NCLOSE        0

#define OPEN_WINDOW           1
#define WAIT_TO_NOPEN         0

#define STATE_OUT_ON          1

#endif // _CTR_H_

#ifdef __cplusplus
} // extern "C"
#endif
