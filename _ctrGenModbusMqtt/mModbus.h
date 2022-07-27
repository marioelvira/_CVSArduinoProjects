#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MMODBUS_H_
#define _MMODBUS_H_

// Status
#define MB_STANDBY	  1
#define MB_READINS	  2
#define MB_WRITEOUTS  3

extern void _MBCRC(void);

#endif // _MMODBUS_H_

#ifdef __cplusplus
} // extern "C"
#endif
