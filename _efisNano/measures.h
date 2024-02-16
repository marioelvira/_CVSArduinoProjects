#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MEASURES_H_
#define _MEASURES_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "main.h"

#define EMON_NUMBER   2

#define EMON_INIT     0
#define EMON_READ     1
#define EMON_RESULT   2

// Emon
#if defined(__arm__)
#define ADC_BITS    12
#else
#define ADC_BITS    10
#endif

#define ADC_COUNTS    (1<<ADC_BITS)
#define SUPP_VOLTAGE  5000

#endif // _MEMON_H_

#ifdef __cplusplus
} // extern "C"
#endif
