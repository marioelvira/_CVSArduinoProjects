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

/////////////
// Screens //
/////////////

void _tftScreenInit(void)
{
  tft.drawCentreString(PROJECT, XMAX/2, YMAX/4, 4);
  // Version
  tft.drawCentreString(compdate, XMAX/2 - 30, YMAX/2 - 20, 2);
  tft.drawCentreString(comptime, XMAX/2 + 50, YMAX/2 - 20, 2);
  tft.drawCentreString("Starting", XMAX/2, (YMAX*2)/3, 4);
}

// Division
void tftScreen2data (void)
{
  tft.fillScreen(TFT_BLACK);  // All Black
  
  tft.drawLine(XMIN,   YMIN,   XMAX,   YMIN, TFT_GREY);  // TOP
  tft.drawLine(XMIN,   YMIN,   XMIN,   YMAX, TFT_GREY);  // RIGHT
  tft.drawLine(XMIN,   YMAX,   XMAX,   YMAX, TFT_GREY);  // BOT
  tft.drawLine(XMAX,   YMIN,   XMAX,   YMAX, TFT_GREY);  // RIGHT
  
  tft.drawLine(XMIN, YMAX/2,   XMAX, YMAX/2, TFT_GREY);  // MIDDLE
}

void tftScreen3data (void)
{
  tft.fillScreen(TFT_BLACK);  // All Black
  
  tft.drawLine(XMIN,   YMIN,   XMAX,   YMIN, TFT_GREY);  // TOP
  tft.drawLine(XMIN,   YMIN,   XMIN,   YMAX, TFT_GREY);  // RIGHT
  tft.drawLine(XMIN,   YMAX,   XMAX,   YMAX, TFT_GREY);  // BOT
  tft.drawLine(XMAX,   YMIN,   XMAX,   YMAX, TFT_GREY);  // RIGHT
  
  tft.drawLine(XMIN, YMAX/2,   XMAX, YMAX/3,     TFT_GREY);
  tft.drawLine(XMIN, YMAX/2,   XMAX, (YMAX*2)/3, TFT_GREY);
}

void tftScreen4data (void)
{
  tft.fillScreen(TFT_BLACK);  // All Black
  
  tft.drawLine(XMIN,   YMIN,   XMAX,   YMIN, TFT_GREY);  // TOP
  tft.drawLine(XMIN,   YMIN,   XMIN,   YMAX, TFT_GREY);  // RIGHT
  tft.drawLine(XMIN,   YMAX,   XMAX,   YMAX, TFT_GREY);  // BOT
  tft.drawLine(XMAX,   YMIN,   XMAX,   YMAX, TFT_GREY);  // RIGHT
  
  tft.drawLine(XMIN, YMAX/4,     XMAX, YMAX/4,     TFT_GREY);
  tft.drawLine(XMIN, YMAX/2,     XMAX, YMAX/2,     TFT_GREY);
  tft.drawLine(XMIN, (YMAX*3)/4, XMAX, (YMAX*3)/4, TFT_GREY);
}

void tftScreenMenuTop (void)
{
  tft.fillScreen(TFT_BLACK);  // All Black
  
  tft.drawLine(XMIN,   YMIN,   XMAX,   YMIN, TFT_GREY);  // TOP
  tft.drawLine(XMIN,   YMIN,   XMIN,   YMAX, TFT_GREY);  // RIGHT
  tft.drawLine(XMIN,   YMAX,   XMAX,   YMAX, TFT_GREY);  // BOT
  tft.drawLine(XMAX,   YMIN,   XMAX,   YMAX, TFT_GREY);  // RIGHT
  
  tft.drawLine(XMIN, YMAX/6,   XMAX, YMAX/6,     TFT_GREY);
}

// Menu
void tftScreenMenuState(void)
{
  for (int i = 0; i < TFT_MENU_NITEM; i++)
  {
    if (tftMenuSelection == i)
      tft.drawString(">", XMAX/9,  TFT_MENU_ITEM1 + i*TFT_MENU_NEXT, 4);
    else 
      tft.drawString("   ", XMAX/9,  TFT_MENU_ITEM1 + i*TFT_MENU_NEXT, 4);
  }
}

void tftScreenMenu (void)
{
  switch (tftMenuState)
  {
    case 0:
      tftScreenMenuTop();
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      //tftMenuSelection = 0;
      tftScreenMenuState();
      
      tftMenuState = 1;
      break;

    case 1:
      // Title
      tft.drawCentreString("Tittle - Menu 1", XMAX/2, TFT_MENU_TITLE, 4);
      for (int i = 0; i < TFT_MENU_NITEM; i++)
        tft.drawString("Item", XMAX/6,  TFT_MENU_ITEM1 + i*TFT_MENU_NEXT, 4);
                        
      tftMenuState = 2;
      break;

    case 2:

      if (joystickState == JOYSTICK_ST_UP)
      {
        tftMenuSelection++;
        if (tftMenuSelection == TFT_MENU_NITEM)
          tftMenuSelection = 0;
        tftScreenMenuState();

        tftMenuState = 3;
        tftMenuTick = millis();
      }
      else if (joystickState == JOYSTICK_ST_DOWN)
      {
        if (tftMenuSelection == 0)
          tftMenuSelection = (TFT_MENU_NITEM - 1);
        else
          tftMenuSelection--;

        tftScreenMenuState();

        tftMenuState = 3;
        tftMenuTick = millis();
      }
      else if (joystickState == JOYSTICK_ST_PUSH)
      {
        tftScreenTick = millis();
        tftScreenState = 0;
        tftState = TFT_SCREEN1;
      }
    
      break;

    case 3:
      if (millis() - tftMenuTick < SCREEN_BLIND_TICK)
        break;

      tftMenuState = 2;
      break;
  }
}

void _tftScreen1(void)
{
  switch (tftScreenState)
  {
    case 0:
      tftScreen2data();
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tftScreenUpdateTick = millis();
      tftScreenState = 1;
      break;

    case 1:
  
      if (millis() - tftScreenUpdateTick >= SCREEN_UPDATE_TICK)
      {
        String sengineRMP;
        String scarbPreasure;
    
        int mod, rest;
    
        // RPMs
        sengineRMP = String(engineRMP);
        
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
        tftScreenUpdateTick = millis();
      }

      // Joystick
      if (millis() - tftScreenTick < SCREEN_BLIND_TICK)
        break;
 
      if ((joystickState == JOYSTICK_ST_UP) || (joystickState == JOYSTICK_ST_DOWN))
      {
        tftScreenTick = millis();
        tftScreenState = 0;
        if (joystickState == JOYSTICK_ST_UP)
        {
          tftMenuState = 0;
          tftState = TFT_MENU_INIT;
        }
        else
          tftState = TFT_SCREEN2;
      }
      else if (joystickState == JOYSTICK_ST_PUSH)
        engineRMP = 4000;      
      
      break;
   }
}

void _tftScreen2(void)
{
  switch (tftScreenState)
  {
    case 0:
      tftScreen2data();
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tftScreenUpdateTick = millis();
      tftScreenState = 1;
      break;
        
    case 1:
      if (millis() - tftScreenUpdateTick >= SCREEN_UPDATE_TICK)
      {     
        // TOP
        yield();
        tft.drawCentreString("Time ON", XMAX/2, 10, 4);
        tft.drawCentreString(timeOnString, XMAX/2, YMAX/6, 7);
        
        // BOTTOM
        _analogOnString();
        tft.drawCentreString("ANA" + String (PIN_P3P3) + ": " + sAnalog, XMAX/2 - 75, (YMAX*2)/3, 4);
        tft.drawCentreString("JST: " + String(joystickState), XMAX/2 + 75, (YMAX*2)/3, 4);
            
        tft.drawCentreString("IN"  + String (PIN_P3P2) + ": " + String(boardP3P2), XMAX/2 - 75, (YMAX*5)/6, 4);    
        //tft.drawCentreString("OUT" + String (PIN_CN12) + ": " + String(boardCN1P2), XMAX/2 + 50, (YMAX*5)/6, 4);
            
        // Tick Update
        tftScreenUpdateTick = millis();
      }

      // Joystick
      if (millis() - tftScreenTick < SCREEN_BLIND_TICK)
        break;

      if ((joystickState == JOYSTICK_ST_UP) || (joystickState == JOYSTICK_ST_DOWN))
      {
        tftScreenTick = millis();
        tftScreenState = 0;
        if (joystickState == JOYSTICK_ST_UP)
          tftState = TFT_SCREEN1;
        else
        {
          tftMenuState = 0;
          tftState = TFT_MENU_INIT;
        }
      }
      else if (joystickState == JOYSTICK_ST_PUSH)
        _TimeSetup();
      break;
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

  tftScreenState = 0;
  tftScreenTick = millis();
  
  // Selection
  tftMenuSelection = 0;
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
        tftTick = millis();
        tftScreenState = 0;
        tftState = TFT_MENU_INIT;
      }
      break;

    case TFT_MENU_INIT:
      tftScreenMenu();
      break;
 
    case TFT_SCREEN1:
      _tftScreen1();
      break;
 
    case TFT_SCREEN2:
      _tftScreen2();       
      break;
  }
}
