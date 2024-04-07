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
#define IRMS_NUMBER     2
#define IRMS_UTICK      1000    // 1.0ms
#define IRMS_WINDOW     40      // Rms window of 40 samples, means 2 periods @50Hz
#define IRMS_CONT       1000    // 1s

// Vdc
#define VDC_NUMBER      2
#define VDC_MTICK       1000

#endif // _MEMON_H_

#ifdef __cplusplus
} // extern "C"
#endif
