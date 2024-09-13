#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MEASURES_H_
#define _MEASURES_H_

#include "main.h"

// Offsets
#define ADC_I_OFFSET        0
#define ADC_V_OFFSET        4

#define ADC_BITS            10
#define ADC_COUNTS          (1<<ADC_BITS)
#define ADC_SUPPLY_VOLTAGE  5000
#define ADC_FULL_SCALE      1024

// I
#define I_NUMBER            4   // Idem ADC_V_OFFSET
#define I_TYPE_IRMS         0
#define I_TYPE_IDC          1

// Irms
#define IRMS_FREQ_HZ        50
#define ADC_IRMS_RATIO_0    5  // 5A -> 1V
#define ADC_IRMS_RATIO_1    15 // 15A -> 1V

// Idc
#define IDC_MTICK           1000000 // 1s

// V
#define V_NUMBER            4

// Vdc
#define VDC_MTICK           1000000 // 1s

#endif // _MEMON_H_

#ifdef __cplusplus
} // extern "C"
#endif
