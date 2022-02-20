#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTR_H_
#define _CTR_H_

#include "main.h"

#define MODE_TEST   1
#define MODE_AUTO   0

// Estados principales...
#define STATE_CHARGE_BATTA      0
#define STATE_CHARGE_BATTAB     1
#define STATE_CHARGE_BATTB      2
#define STATE_CHARGE_BATTBC     3
#define STATE_CHARGE_BATTC      4
#define STATE_CHARGE_BATTCA     5

#if (_CTR_DEBUG_ == 1)
#define _SCALE_15M_   1000
#else
#define _SCALE_15M_   900000
#endif

#endif // _CTR_H_

#ifdef __cplusplus
} // extern "C"
#endif
