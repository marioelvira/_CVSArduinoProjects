#ifdef __cplusplus
extern "C" {
#endif

#ifndef _2UART_H_
#define _2UART_H_

#define M2UART_ARRAY_SIZE             200

#define M2UART_RX_UART_OF_TOUT_MS         5
#define M2UART_SWAT_MS                    5
#define M2UART_TX_UART_INV_TOUT_MS        10
//#define M2UART_LISTEN_UART_INV_TOUT_MS  100 // 5000
#define M2UART_RX_UART_INV_TOUT_MS        5
#define M2UART_TX_UART_OF_TOUT_MS         10

// Status
#define M2UART_LISTEN_IN_UART_OF      0
#define M2UART_ONRX_IN_UART_OF        1
#define M2UART_FRAMERX_IN_UART_OF     2
#define M2UART_SWAT_TO_UART_INV       3
#define M2UART_FRAMETX_IN_UART_INV    4
#define M2UART_ENDTX_IN_UART_INV      5
#define M2UART_LISTEN_IN_UART_INV     6
#define M2UART_ONRX_IN_UART_INV       7
#define M2UART_FRAMERX_IN_UART_INV    8
#define M2UART_SWAT_TO_UART_OF        9
#define M2UART_FRAMETX_IN_UART_OF     10
#define M2UART_ENDTX_IN_UART_OF       11

/*
#define OUT_m2UART0_RX      0 // TODO config
#define OUT_m2UART0_TX      1 // TODO config

#define OUT_m2UART2_RX      0 // TODO config
#define OUT_m2UART2_TX      1 // TODO config
*/

#endif // _2UART_H_

#ifdef __cplusplus
} // extern "C"
#endif
