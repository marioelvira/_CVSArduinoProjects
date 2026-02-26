#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ALARM_H_
#define _ALARM_H_

#define AL_SEC_LOOP       60
#define AL_NOTIFY_CONT    5

#define AL_ARRAY_SIZE     8

#define AL_ERROR0      0
#define AL_ERROR1      1
#define AL_ERROR2      2
#define AL_ERROR3      3
#define AL_ERROR4      4
#define AL_ERROR5      5

#define AL_ERROR0_STR   "ALARM ERROR 0"
#define AL_ERROR1_STR   "ALARM ERROR 1"
#define AL_ERROR2_STR   "ALARM ERROR 2"
#define AL_ERROR3_STR   "ALARM ERROR 3"
#define AL_ERROR4_STR   "ALARM ERROR 4"
#define AL_ERROR5_STR   "ALARM ERROR 5"
#define AL_ERROR6_STR   "ALARM ERROR 6"
#define AL_ERROR7_STR   "ALARM ERROR 7"

#define STATE_AL_OFF          0
#define STATE_AL_ON           1
#define STATE_AL_ON_NOTIFY    2
#define STATE_AL_OFF_NOTIFY   3

#endif // _ALARM_H_

#ifdef __cplusplus
} // extern "C"
#endif
