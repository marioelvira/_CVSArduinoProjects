#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ALARM_H_
#define _ALARM_H_

#define AL_SEC_LOOP       60
#define AL_NOTIFY_CONT    5

#define AL_ARRAY_SIZE     24

#define AL_ERROR0      0
#define AL_ERROR1      1
#define AL_ERROR2      2
#define AL_ERROR3      3
#define AL_ERROR4      4
#define AL_ERROR5      5

#define AL_ERROR0_STR   "Comunic tarjeta MB1"
#define AL_ERROR1_STR   "Comunic tarjeta MB1"
#define AL_ERROR2_STR   "Generador no arranca"
#define AL_ERROR3_STR   "Bateria baja"
#define AL_ERROR4_STR   "Sin definir"
#define AL_ERROR5_STR   "Sin definir"
#define AL_ERROR6_STR   "Sin definir"
#define AL_ERROR7_STR   "Sin definir"
// INs Mb1
#define AL_ERROR8_STR   "Fallo en Red IN1"
#define AL_ERROR9_STR   "Fallo en Red IN2"
#define AL_ERROR10_STR  "Sin definir"
#define AL_ERROR11_STR  "Sin definir"
#define AL_ERROR12_STR  "Sin definir"
#define AL_ERROR13_STR  "Sin definir"
#define AL_ERROR14_STR  "Sin definir"
#define AL_ERROR15_STR  "Sin definir"
// INs Mb2
#define AL_ERROR16_STR  "Sin definir"
#define AL_ERROR17_STR  "Sin definir"
#define AL_ERROR18_STR  "Sin definir"
#define AL_ERROR19_STR  "Sin definir"
#define AL_ERROR20_STR  "Sin definir"
#define AL_ERROR21_STR  "Sin definir"
#define AL_ERROR22_STR  "Sin definir"
#define AL_ERROR23_STR  "Sin definir"

#define STATE_AL_OFF          0
#define STATE_AL_ON           1
#define STATE_AL_ON_NOTIFY    2
#define STATE_AL_OFF_NOTIFY   3

#endif // _ALARM_H_

#ifdef __cplusplus
} // extern "C"
#endif
