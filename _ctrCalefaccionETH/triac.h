#ifdef __cplusplus
extern "C" {
#endif

#ifndef _TRIAC_H_
#define _TRIAC_H_

#define TRIAC_NUMBER        3

#define TRIAC_ALARM_ZC_SEC  15

#define PIN_TRIAC_OFF       0
#define PIN_TRIAC_ON        1

#define TRIAC_OFF           0
#define TRIAC_ON            1

extern int   TriacCtr[];

extern const int triacZCPin;

extern int triacZCAlarmSec;
extern uint32_t triacZCTickUs;
extern int triacZCPeriodUs;
extern float triacZCFrec;
extern int triacZCcount;
/*
extern const int triac2ZCPin;
extern uint32_t triac2ZCTickUs;
extern int triac2ZCPeriodUs;
extern float triac2ZCFrec;
extern int triac2ZCcount;
*/
extern int triacCtr1;
extern const int triacPin1;
extern hw_timer_t * triacTimer1;
extern int timeDelay1;
extern int triacCicle1;

#endif // _TRIAC_H_

#ifdef __cplusplus
} // extern "C"
#endif
