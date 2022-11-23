#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MTFT_H_
#define _MTFT_H_

// Define meter size
#define XMIN    0
#define YMIN    0
#define XMAX    319 //320
#define YMAX    239 //240

// Timers
#define SCREEN_UPDATE_TICK    100
#define SCREEN_INIT_TIMEOUT   10000  // 10s

// Colors
#define TFT_GREY      0x5AEB

// TFT States
#define TFT_INIT      0
#define TFT_SCREEN1   1
#define TFT_SCREEN2   2

#endif // _MTFT_H_

#ifdef __cplusplus
} // extern "C"
#endif
