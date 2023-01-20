#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ALARM_H_
#define _ALARM_H_

#define AL_SEC_LOOP       60
#define AL_NOTIFY_CONT    10

#define AL_ARRAY_SIZE     8

#define AL_ERROR0      0
#define AL_ERROR1      1
#define AL_ERROR2      2
#define AL_ERROR3      3

#define AL_ERROR0_STR   "Comunic tarjeta MB1"
#define AL_ERROR1_STR   "Comunic tarjeta MB1"
#define AL_ERROR2_STR   "Confirm. Generador"
#define AL_ERROR3_STR   "Bateria baja"
#define AL_ERROR4_STR   "Sin definir"
#define AL_ERROR5_STR   "Sin definir"
#define AL_ERROR6_STR   "Sin definir"
#define AL_ERROR7_STR   "Sin definir"

#define STATE_AL_LOOP         0
#define STATE_AL_ON           1
#define STATE_AL_ON_NOTIFY    2
#define STATE_AL_OFF_NOTIFY   3

#endif // _ALARM_H_

#ifdef __cplusplus
} // extern "C"
#endif
