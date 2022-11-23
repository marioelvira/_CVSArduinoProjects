#include "mTft.h"

/*
void tftRefs (void)
{
  // Lines
  //tft.fillRect(  XMIN,   YMIN,   XMAX, YMIN+1, TFT_GREY);  // TOP
  //tft.fillRect(  XMIN,   YMIN, XMIN+1,   YMAX, TFT_GREY);  // RIGHT
  //tft.fillRect(  XMIN, YMAX-1,   XMAX,   YMAX, TFT_GREY);  // BOT
  //tft.fillRect(XMAX-1,   YMIN,   XMAX,   YMAX, TFT_GREY);  // RIGHT

  // Points
  tft.fillRect(  XMIN,   YMIN,  XMIN+1, YMIN+1, TFT_RED);   // TOP L
  tft.fillRect(XMAX-1,   YMIN,    XMAX, YMIN+1, TFT_RED);   // TOP R
  tft.fillRect(  XMIN, YMAX-1,  XMIN+1,   YMAX, TFT_RED);   // BOT L
  tft.fillRect(XMAX-1, YMAX-1,    XMAX,   YMAX, TFT_RED);   // BOT R
}
*/

void _tftScreenInit(void)
{
  tft.drawCentreString(PROJECT, XMAX/2, YMAX/2 - 50, 4);
  // Version
  tft.drawCentreString(compdate, XMAX/2 - 30, YMAX/2 - 20, 2);
  tft.drawCentreString(comptime, XMAX/2 + 50, YMAX/2 - 20, 2);
  tft.drawCentreString("Starting", XMAX/2, YMAX/2, 4);
}

void tftScreen2data (void)
{
  tft.fillScreen(TFT_BLACK);  // All Black
  
  tft.drawLine(XMIN,   YMIN,   XMAX,   YMIN, TFT_GREY);  // TOP
  tft.drawLine(XMIN,   YMIN,   XMIN,   YMAX, TFT_GREY);  // RIGHT
  tft.drawLine(XMIN,   YMAX,   XMAX,   YMAX, TFT_GREY);  // BOT
  tft.drawLine(XMAX,   YMIN,   XMAX,   YMAX, TFT_GREY);  // RIGHT  
  tft.drawLine(XMIN, YMAX/2,   XMAX, YMAX/2, TFT_GREY);  // MIDDLE
}

void _tftScreen1(void)
{
  if (millis() - screenTick >= SCREEN_UPDATE_TICK)
  {
    String sengineRMP;
    String scarbPreasure;

    int mod, rest;

    // RPMs
    sengineRMP    = String(engineRMP);
    
    // Preasure
    mod = carbPreasure/100;
    rest = carbPreasure%100;

    if (mod < 10)
      scarbPreasure = "0" + String(mod);
    else
      scarbPreasure = String(mod);
 
    scarbPreasure = scarbPreasure + ".";

    if (rest < 10)
      scarbPreasure = scarbPreasure + "0" + String(rest);
    else
      scarbPreasure = scarbPreasure + String(rest);
 
    // TOP
    yield();
    tft.drawCentreString(sengineRMP, XMAX/2 - 10, YMAX/6, 7);
    // Units
    tft.drawCentreString("RMP", XMAX/2 + 100, YMAX/6, 4);
    // Setpoint
    tft.drawCentreString("5800", XMAX/2 + 100, YMAX/6 + 28, 4);
    
    // BOTTOM
    tft.drawCentreString(scarbPreasure, XMAX/2 - 10, (YMAX*2)/3, 7);
    // Units
    tft.drawCentreString("IN Hg", XMAX/2 + 100, (YMAX*2)/3, 4);
    // Setpoint
    //tft.drawCentreString("XXXX", XMAX/2 + 100, (YMAX*2)/3 + 28, 4);
    
    // Tick Update
    screenTick = millis();
  }
}

void _tftScreen2(void)
{
  if (millis() - screenTick >= SCREEN_UPDATE_TICK)
  {     
    // TOP
    yield();
    tft.drawCentreString("Time ON", XMAX/2, 10, 4);
    tft.drawCentreString(timeOnString, XMAX/2, YMAX/6, 7);
    
    // BOTTOM
    _analogOnString();
    tft.drawCentreString(sAnalog, XMAX/2, (YMAX*2)/3, 4);
    
    tft.drawCentreString(String(boardIO1), XMAX/2 - 25, (YMAX*5)/6, 4);
    tft.drawCentreString(String(boardIO2), XMAX/2 + 25, (YMAX*5)/6, 4);
        
    // Tick Update
    screenTick = millis();
  }
}

////////////////
// TFT set up //
////////////////
void _mTftSetup(void)
{
  tft.begin();
  tft.setRotation(1);         // Horizontal
  tft.fillScreen(TFT_BLACK);  // All Black
  _tftScreenInit();

  // Init state
  tftState = TFT_INIT;
  tftTick = millis();
}

///////////////////////
// TFT state machine //
///////////////////////
void _mTftLoop(void)
{
  switch (tftState)
  {
    case TFT_INIT:
      if (millis() - tftTick >= SCREEN_INIT_TIMEOUT)
      {
        tft.fillScreen(TFT_BLACK);
        tftScreen2data();
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
 
        screenTick = millis();
        tftTick = millis();
        tftState = TFT_SCREEN1;
      }
      break;
 
    case TFT_SCREEN1:
      _tftScreen1();
      if (millis() - tftTick >= SCREEN_INIT_TIMEOUT)
      {
        tft.fillScreen(TFT_BLACK);
        tftScreen2data();
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        
        screenTick = millis();
        tftTick = millis();
        tftState = TFT_SCREEN2;
      }
      break;
 
    case TFT_SCREEN2:
      _tftScreen2();
      if (millis() - tftTick >= SCREEN_INIT_TIMEOUT)
      {
        tft.fillScreen(TFT_BLACK);
        tftScreen2data();
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        
        screenTick = millis();
        tftTick = millis();
        tftState = TFT_SCREEN1;
      }
      break;
  }
}
