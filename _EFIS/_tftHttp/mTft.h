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
#define SCREEN_INIT_TIMEOUT   5000  // 5s
#define SCREEN_UPDATE_TICK    100
#define SCREEN_BLIND_TICK     500

// Colors
#define TFT_GREY      0x5AEB

// TFT States
#define TFT_INIT        0
#define TFT_MENU_INIT   10
#define TFT_SCREEN1     20
#define TFT_SCREEN2     30

// TFT Menu
#define TFT_MENU_TITLE  10

#define TFT_MENU_ITEM1  55
#define TFT_MENU_NEXT   25
#define TFT_MENU_NITEM  7

#endif // _MTFT_H_

#ifdef __cplusplus
} // extern "C"
#endif
