#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CTR_H_
#define _CTR_H_

#define MODE_TEST   1
#define MODE_AUTO   0

#define CTR_BUZZER_TICK          500     // 500ms

// Estados principales...
#define STATE_START         0
#define STATE_GEN_ON        1
#define STATE_GEN_ZUMB      2
#define STATE_GEN_OFF       3
#define STATE_BOM_OFF       4
#define STATE_AUTO_OFF      5

#define TIMEOUT_AUTOOFF_MS      10000

#endif // _CTR_H_

#ifdef __cplusplus
} // extern "C"
#endif
