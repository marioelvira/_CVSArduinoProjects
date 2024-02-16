#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ADCS_H_
#define _ADCS_H_

// Nota: user VREFF para tener toda la 
// escala de bits del ADC

#define ADC_TICK            1000
#define VDC_NUMBER          2

//#define ADC_BITS      10
//#define ADC_COUNTS    (1<<ADC_BITS)

#define ADC_EMON_OFFSET     0
#define ADC_VDC_OFFSET      2

//#define ADC_EMON_RATIO      5   // 5A -> 1V
//#define ADC_EMON_SAMPLES    1480

#endif // _ADCS_H_

#ifdef __cplusplus
} // extern "C"
#endif
