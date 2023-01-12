#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ALARM_H_
#define _ALARM_H_

#define AL_SEC_LOOP       10
#define AL_NOTIFY_CONT    6

#define AL_ARRAY_SIZE     8

#define AL_ERROR_MB1      0
#define AL_ERROR_MB2      1
#define AL_ERROR_GEN      2
#define AL_ERROR_ADC      3

#define STATE_AL_LOOP         0
#define STATE_AL_ON           1
#define STATE_AL_ON_NOTIFY    2
#define STATE_AL_OFF_NOTIFY   3

#endif // _ALARM_H_

#ifdef __cplusplus
} // extern "C"
#endif
