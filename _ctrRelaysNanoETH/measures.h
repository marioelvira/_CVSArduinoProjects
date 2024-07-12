#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MEASURES_H_
#define _MEASURES_H_

#include "main.h"

// Offsets
#define ADC_EMON_OFFSET     0
#define ADC_VDC_OFFSET      2

// Irms
#define IRMS_NUMBER         2
#define IRMS_FREQ_HZ        50

#define ADC_IRMS_RATIO_0    5 // 5A -> 1V
#define ADC_IRMS_RATIO_1    15 // 5A -> 1V

#define ADC_BITS            10
#define ADC_COUNTS          (1<<ADC_BITS)
#define ADC_SUPPLY_VOLTAGE  5000

// Vdc
#define VDC_NUMBER      2
#define VDC_MTICK       1000

#endif // _MEMON_H_

#ifdef __cplusplus
} // extern "C"
#endif
