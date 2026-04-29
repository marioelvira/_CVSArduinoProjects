
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _PWM_H_
#define _PWM_H_

// Status
#define PWM_START	      1
#define PWM_CONFIG      2
#define PWM_STANDBY     3

//extern const int pwmPin;

extern int pwmFreq;
extern const int pwmResolution;

extern int pwmDutyCycle;

#endif // _PWM_H_

#ifdef __cplusplus
} // extern "C"
#endif
