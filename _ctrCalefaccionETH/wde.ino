#include "main.h"

#if (_USE_WDE_ == 1)

#if (_WD_SERIAL_DEBUG_ == 1)
void printResetFlagRegister()
{
   // Reset Controller Reset Flag Register of megaAVR 0-series (e.g. ATmega4809)
   // --------------------------------------------------------------------------
   // Defined in e.g. iom4809.h for ATmega4809 via io.h
   // Before io.h:      #define __AVR_ATmega4809__
   // Within iom4809.h: #define _AVR_IOXXX_H_ "iom4809.h"
   //                   #define _AVR_ATMEGA4809_H_INCLUDED
   // Windows path:     C:\Program Files (x86)\Arduino\hardware\tools\avr\avr\include\avr
   //
   // RSTCTRL           - Reset Controller (struct)
   // RSTCTRL.RSTFR     - Reset Flag Register (byte), also RSTCTRL_RSTFR
   // RSTCTRL_PORF_bm   - Power on Reset flag bit mask
   // RSTCTRL_PORF_bp   - Power on Reset flag bit position
   // RSTCTRL_BORF_bm   - Brown out detector Reset flag bit mask
   // RSTCTRL_BORF_bp   - Brown out detector Reset flag bit position
   // RSTCTRL_EXTRF_bm  - External Reset flag bit mask
   // RSTCTRL_EXTRF_bp  - External Reset flag bit position
   // RSTCTRL_WDRF_bm   - Watch dog Reset flag bit mask
   // RSTCTRL_WDRF_bp   - Watch dog Reset flag bit position
   // RSTCTRL_SWRF_bm   - Software Reset flag bit mask
   // RSTCTRL_SWRF_bp   - Software Reset flag bit position
   // RSTCTRL_UPDIRF_bm - UPDI (Unified Program and Debug Interface) Reset flag bit mask
   // RSTCTRL_UPDIRF_bp - UPDI (Unified Program and Debug Interface) Reset flag bit position

   Serial.println("RSTCTRL.RSTFR\tUPDIRF\tSWRF\tWDRF\tEXTRF\tBORF\tPORF\t");
   Serial.print(RSTCTRL.RSTFR, BIN);
   Serial.print("\t\t");
   Serial.print((RSTCTRL.RSTFR & RSTCTRL_UPDIRF_bm ? true : false));
   Serial.print("\t");
   Serial.print((RSTCTRL.RSTFR & RSTCTRL_SWRF_bm ? true : false));
   Serial.print("\t");
   Serial.print((RSTCTRL.RSTFR & RSTCTRL_WDRF_bm ? true : false));
   Serial.print("\t");
   Serial.print((RSTCTRL.RSTFR & RSTCTRL_EXTRF_bm ? true : false));
   Serial.print("\t");
   Serial.print((RSTCTRL.RSTFR & RSTCTRL_BORF_bm ? true : false));
   Serial.print("\t");
   Serial.print((RSTCTRL.RSTFR & RSTCTRL_PORF_bm ? true : false));
   Serial.println("");
}
#endif

void clearResetFlagRegister()
{
   RSTCTRL.RSTFR =   RSTCTRL_UPDIRF_bm 
                   | RSTCTRL_SWRF_bm
                   | RSTCTRL_WDRF_bm
                   | RSTCTRL_EXTRF_bm
                   | RSTCTRL_BORF_bm
                   | RSTCTRL_PORF_bm;
}

void softwareReset()
{
   // Reset Controller Reset Flag Register of megaAVR 0-series (e.g. ATmega4809)
   // --------------------------------------------------------------------------
   // Defined in e.g. iom4809.h for ATmega4809 via io.h
   // Before io.h:      #define __AVR_ATmega4809__
   // Within iom4809.h: #define _AVR_IOXXX_H_ "iom4809.h"
   //                   #define _AVR_ATMEGA4809_H_INCLUDED
   // Windows path:     C:\Program Files (x86)\Arduino\hardware\tools\avr\avr\include\avr
   //
   // RSTCTRL         - Reset Controller (struct)
   // RSTCTRL.SWRR    - Software Reset register (byte), also RSTCTRL_SWRR
   // RSTCTRL_SWRE_bm - Software reset enable bit mask
   // RSTCTRL_SWRE_bp - Software reset enable bit position

   // CPU Change Protection of megaAVR 0-series (e.g. ATmega4809)
   // -----------------------------------------------------------
   // Defined in e.g. iom4809.h for ATmega4809 via io.h
   // Before io.h:      #define __AVR_ATmega4809__
   // Within iom4809.h: #define _AVR_IOXXX_H_ "iom4809.h"
   //                   #define _AVR_ATMEGA4809_H_INCLUDED
   // Windows path:     C:\Program Files (x86)\Arduino\hardware\tools\avr\avr\include\avr
   //
   // CPU_CCP - CPU Change Protection register, also CCP
   // CPU Change Protection keys (typedef enum CCP_enum { ... } CCP_t;)
   // CCP_SPM_gc   - SPM Instruction Protection
   // CCP_IOREG_gc - IO Register Protection (including RSTCTRL.SWRR)

   CPU_CCP = CCP_enum::CCP_IOREG_gc;
   RSTCTRL.SWRR = RSTCTRL_SWRE_bm;
}

void setWatchdogTimer(WDT_PERIOD_enum period,
                      WINDOW_enum     window )
{
   // Watchdog Timer (WDT) of megaAVR 0-series (e.g. ATmega4809)
   // ----------------------------------------------------------
   // Defined in e.g. iom4809.h for ATmega4809 via io.h
   // Before io.h:      #define __AVR_ATmega4809__
   // Within iom4809.h: #define _AVR_IOXXX_H_ "iom4809.h"
   //                   #define _AVR_ATMEGA4809_H_INCLUDED
   // Windows path:     C:\Program Files (x86)\Arduino\hardware\tools\avr\avr\include\avr
   //
   // Note: The timings are based on a 1kHz clock (from 32kHz ultra low-power oscillator OSCULP32K).
   //   
   // Watchdog Period (typedef enum WDT_PERIOD_enum { ... } WDT_PERIOD_t;)
   // WDT_PERIOD_OFF_gc    -     off
   // WDT_PERIOD_8CLK_gc   -    8ms
   // WDT_PERIOD_16CLK_gc  -   16ms
   // WDT_PERIOD_32CLK_gc  -   32ms
   // WDT_PERIOD_64CLK_gc  -   64ms
   // WDT_PERIOD_128CLK_gc -  128ms
   // WDT_PERIOD_256CLK_gc -  256ms
   // WDT_PERIOD_512CLK_gc -  512ms
   // WDT_PERIOD_1KCLK_gc  - 1024ms
   // WDT_PERIOD_2KCLK_gc  - 2048ms
   // WDT_PERIOD_4KCLK_gc  - 4096ms
   // WDT_PERIOD_8KCLK_gc  - 8192ms
   //
   // Watchdog Window (typedef enum WINDOW_enum { ... } WINDOW_t;)
   // WINDOW_OFF_gc    -    off
   // WINDOW_8CLK_gc   -   8ms
   // WINDOW_16CLK_gc  -  16ms
   // WINDOW_32CLK_gc  -  32ms
   // WINDOW_64CLK_gc  -  64ms
   // WINDOW_128CLK_gc -  128ms
   // WINDOW_256CLK_gc -  256ms
   // WINDOW_512CLK_gc -  512ms
   // WINDOW_1KCLK_gc  - 1024ms
   // WINDOW_2KCLK_gc  - 2048ms
   // WINDOW_4KCLK_gc  - 4096ms
   // WINDOW_8KCLK_gc  - 8192ms
   //
   // Defined in wdt.h
   // Windows path: C:\Program Files (x86)\Arduino\hardware\tools\avr\avr\include\avr
   //
   // Note: Calling wdt_disable() might disable wdt_enable() permanently!
   //       Use wtd_enabled(WDT_PERIOD_enum::WDT_PERIOD_OFF_gc) instead.
   //
   // wdt_enable(argument)

   wdt_enable(period | window);
}

void resetWatchdogTimer()
{
   // Watchdog Timer (WDT) of megaAVR 0-series (e.g. ATmega4809)
   // ----------------------------------------------------------
   // Defined in wdt.h
   // Windows path: C:\Program Files (x86)\Arduino\hardware\tools\avr\avr\include\avr
   //
   // wdt_reset()

   wdt_reset();
}

///////////////////////
// WDE state machine //
///////////////////////
void _WDESetup()
{
  wdeForceReset = 0;

  #if (_WD_SERIAL_DEBUG_ == 1)
  printResetFlagRegister();
  #endif

  clearResetFlagRegister();

  #if (_WD_SERIAL_DEBUG_ == 1)
  printResetFlagRegister();
  #endif

  setWatchdogTimer(WDT_PERIOD_enum::WDT_PERIOD_1KCLK_gc,
                   WINDOW_enum::WINDOW_512CLK_gc        );
}

///////////////////////
// WDE state machine //
///////////////////////
void _WDELoop()
{
  resetWatchdogTimer();
  if (wdeForceReset == 1)
    while(1);
}
#endif
