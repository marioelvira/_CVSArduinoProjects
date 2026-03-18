#ifdef __cplusplus
extern "C" {
#endif

#ifndef _TRIAC_H_
#define _TRIAC_H_

extern const int triacZCPin;
extern int triacZCPeriod;
extern unsigned long triacTick;

extern int triacCtr1;
extern const int triacPin1;
extern hw_timer_t * triacTimer1;
extern int timeDelay1;
extern int triacCicle1;

#endif // _TRIAC_H_

#ifdef __cplusplus
} // extern "C"
#endif
