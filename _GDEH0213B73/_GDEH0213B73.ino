#include "images.h"
#include "io.h"

/////////////////
// IO settings //
/////////////////

/*
 *                         ----------                                         ----------------
 *                    A0 -| A0    D0 |- GPIO16 <- BUSY ------------- <- BUSY -|              |
 *                    G  -| G     D1 |- GPIO5  -> RES  ------------- -> RES  -|              |
 *                    VU -| VU    D2 |- GPIO4  -> DC   ------------- -> DC   -|              |
 *                 GPIO9 -| S3    D3 |- GPIO0            |---------- -> CS   -|     EPD      |
 *                 GPIO? -| S2    D4 |- GPIO2            | |-------- -> SCK  -|              |
 *                  MOSI -| S1    3V |- 3V               | | |------ -> SDI  -|              |
 *                    CS -| SC     G |- G                | | | |---- -> GND  -|              |
 *                  MISO -| SD    D5 |- GPIO14 -> CS   --| | | | |-- -> 3V3  -|              |
 *                GPIO10 -| SK    D6 |- GPIO12 -> SCK  ----| | | |            ----------------
 *                     G -| G     D7 |- GPIO13 -> SDI  ------| | |
 *                    3V -| 3V    D8 |- GPIO15                 | |
 *                    EN -| EN    RX |- GPIO3                  | |
 *                   RST -| RST   TX |- GPIO1                  | |
 *                     G -| G      G |- G              --------| |
 *                   VIN -| VIN   3V |- 3V             ----------|
 *                        ------------
 */

#define EPD_W21_MOSI_0    digitalWrite(SDI_Pin, LOW)
#define EPD_W21_MOSI_1    digitalWrite(SDI_Pin, HIGH) 
#define EPD_W21_CLK_0     digitalWrite(SCK_Pin, LOW)
#define EPD_W21_CLK_1     digitalWrite(SCK_Pin, HIGH)
#define EPD_W21_CS_0      digitalWrite(CS_Pin,  LOW)
#define EPD_W21_CS_1      digitalWrite(CS_Pin,  HIGH)
#define EPD_W21_DC_0      digitalWrite(DC_Pin,  LOW)
#define EPD_W21_DC_1      digitalWrite(DC_Pin,  HIGH)
#define EPD_W21_RST_0     digitalWrite(RES_Pin, LOW)
#define EPD_W21_RST_1     digitalWrite(RES_Pin, HIGH)
#define isEPD_W21_BUSY    digitalRead (BUSY_Pin)

#define MONOMSB_MODE        1
#define MONOLSB_MODE        2 
#define RED_MODE            3

#define MAX_LINE_BYTES          16  // 128/8
#define MAX_COLUMN_BYTES        250
#define ALLSCREEN_GRAGHBYTES    4000

///////////////
// Functions //
///////////////
void SPI_Delay            (unsigned char xrate);
void SPI_Write            (unsigned char value);
void Epaper_Write_Command (unsigned char command);
void Epaper_Write_Data    (unsigned char command);

// EPD //
void Epaper_READBUSY      (void);
void SPI_Write            (u8 TxData);
void Epaper_Write_Command (u8 cmd);
void Epaper_Write_Data    (u8 data);

void EPD_HW_Init          (void);   // Electronic paper init
void EPD_Part_Init        (void);   // Local refresh init

void EPD_Part_Update      (void); 
void EPD_Update           (void);

void EPD_WhiteScreen_Black  (void);
void EPD_WhiteScreen_White  (void);
void EPD_DeepSleep          (void);

// Display 
void EPD_WhiteScreen_ALL      (const unsigned char * datas);
void EPD_SetRAMValue_BaseMap  (const unsigned char * datas);
void EPD_Dis_Part             (unsigned int x_start, unsigned int y_start, const unsigned char * datas, unsigned int PART_COLUMN, unsigned int PART_LINE);

void Sys_run(void)
{
  ESP.wdtFeed(); // Feed dog to prevent system reset
}

void LED_run(void)
{
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}

void setup()
{
  pinMode(BUSY_Pin, INPUT);
  pinMode(RES_Pin,  OUTPUT);
  pinMode(DC_Pin,   OUTPUT);
  pinMode(CS_Pin,   OUTPUT);
  pinMode(SCK_Pin,  OUTPUT);
  pinMode(SDI_Pin,  OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  
  ESP.wdtDisable();
}

//******//
// Tips //
//******//
// When the electronic paper is refreshed in full screen,
// the picture flicker is a normal phenomenon, and the main function
// is to clear the display afterimage in the previous picture.
// When the local refresh is performed, the screen does not flash.

// When you need to transplant the driver, you only need to change the corresponding IO.
// The BUSY pin is the input mode and the others are the output mode.

void loop()
{
  //unsigned char fen_L, fen_H, miao_L, miao_H; 

  /*
  EPD_HW_Init();
  EPD_WhiteScreen_ALL(gImage_1);
  delay(2000);
  */
  // Partial refresh digital presentation 
  /*
  EPD_HW_Init();
  EPD_SetRAMValue_BaseMap(gImage_basemap);
  delay(100);
  EPD_Dis_Part(0,32,gImage_num1,32,32);
  EPD_Dis_Part(0,32,gImage_num2,32,32);
  EPD_Dis_Part(0,32,gImage_num3,32,32);
  EPD_Dis_Part(0,32,gImage_num4,32,32);
  EPD_Dis_Part(0,32,gImage_num5,32,32);
  //delay(2000);

  // Clean
  EPD_HW_Init();
  EPD_WhiteScreen_White();
  EPD_DeepSleep();
  */
  while(1) 
  {
    EPD_HW_Init();
    EPD_SetRAMValue_BaseMap(gImage_basemap);
    delay(100);
    EPD_Dis_Part(0,32,gImage_num1,32,32); // [0,32] - 32x32
    EPD_Dis_Part(0,32,gImage_num2,32,32); // [0,32] - 32x32
    
    EPD_Dis_Part(0,32,gImage_num3,32,32);
    EPD_Dis_Part(0,32,gImage_num4,32,32);
    EPD_Dis_Part(0,32,gImage_num5,32,32);
    EPD_Dis_Part(0,32,gImage_num6,32,32);
    EPD_Dis_Part(0,32,gImage_num7,32,32);
    EPD_Dis_Part(0,32,gImage_num8,32,32);
    EPD_Dis_Part(0,32,gImage_num9,32,32);
    delay(1000);
    EPD_HW_Init();
    EPD_WhiteScreen_White();
    delay(2000);
    Sys_run(); // System run
    LED_run(); // Breathing lamp
  }
}

/////////
// SPI //
/////////
void SPI_Delay(unsigned char xrate)
{
  unsigned char i;
  while(xrate)
  {
    for(i = 0; i < 2; i++);
    xrate--;
  }
}

void SPI_Write(unsigned char value)                                    
{                                                           
  unsigned char i;  
  
  SPI_Delay(1);
  for(i = 0; i < 8; i++)   
  {
    EPD_W21_CLK_0;
    SPI_Delay(1);
    
    if(value & 0x80)
      EPD_W21_MOSI_1;
    else
      EPD_W21_MOSI_0;   
    
    value = (value << 1); 
    SPI_Delay(1);
    delayMicroseconds(1);
    EPD_W21_CLK_1; 
    SPI_Delay(1);
  }
}

void Epaper_Write_Command(unsigned char command)
{
  SPI_Delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_0;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}

void Epaper_Write_Data(unsigned char command)
{
  SPI_Delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_1;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}

////////////////////////////
// EPD Settings Functions //
////////////////////////////
void EPD_HW_Init(void)
{
  EPD_W21_RST_0;  // Module reset      
  delay(100);     // At least 10ms 
  EPD_W21_RST_1; 
  delay(100); 

  Epaper_READBUSY();   
  Epaper_Write_Command(0x12);  // SW Reset
  Epaper_READBUSY();   
    
  Epaper_Write_Command(0x01);  // Driver output control      
  Epaper_Write_Data(0xF9);
  Epaper_Write_Data(0x00);
  Epaper_Write_Data(0x00);

  Epaper_Write_Command(0x11);   // Data entry mode       
  Epaper_Write_Data(0x01);

  Epaper_Write_Command(0x44);   // Set Ram-X address start/end position   
  Epaper_Write_Data(0x00);
  Epaper_Write_Data(0x0F);      // 0x0F -->(15+1)*8 = 128

  Epaper_Write_Command(0x45);   // Set Ram-Y address start/end position          
  Epaper_Write_Data(0xF9);      // 0xF9 -->(249+1) = 250
  Epaper_Write_Data(0x00);
  Epaper_Write_Data(0x00);
  Epaper_Write_Data(0x00); 

  Epaper_Write_Command(0x3C);   // BorderWavefrom
  Epaper_Write_Data(0x01);  
      
  Epaper_Write_Command(0x18);   // Reading temperature sensor
  Epaper_Write_Data(0x80);

  Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
  Epaper_Write_Data(0x00);
  Epaper_Write_Command(0x4F);   // set RAM y address count to 0xF9;    
  Epaper_Write_Data(0xF9);
  Epaper_Write_Data(0x00);
  Epaper_READBUSY();  
}

///////////////////////
// All screen update //
///////////////////////
/*
void EPD_WhiteScreen_ALL(const unsigned char * datas)
{
  unsigned int i;
   
  Epaper_Write_Command(0x24);     // Write RAM for black(0)/white (1)
  for(i = 0; i < ALLSCREEN_GRAGHBYTES; i++)
  {      
    Epaper_Write_Data(pgm_read_byte(&datas[i]));
  }
  EPD_Update();   
}
*/
void EPD_Update(void)
{   
  Epaper_Write_Command(0x22); // Display Update Control 
  Epaper_Write_Data(0xF7);
  Epaper_Write_Command(0x20);
  Epaper_READBUSY();
}

void EPD_Part_Update(void)
{
  Epaper_Write_Command(0x22); // Display Update Control 
  Epaper_Write_Data(0xFF);
  Epaper_Write_Command(0x20);
  Epaper_READBUSY();    
}

void EPD_DeepSleep(void)
{  
  Epaper_Write_Command(0x10); //enter deep sleep
  Epaper_Write_Data(0x01); 
  delay(100);
}

void Epaper_READBUSY(void)
{ 
  while(1)
  {   
    // 1 BUSY
    if(isEPD_W21_BUSY == 0)
      break;
    ESP.wdtFeed(); // Feed dog to prevent system reset
  }
}

/////////////////
// Part update //
/////////////////
void EPD_SetRAMValue_BaseMap( const unsigned char * datas)
{
  unsigned int i;   
  const unsigned char *datas_flag;
   
  datas_flag = datas;
  Epaper_Write_Command(0x24);
  for(i = 0; i < ALLSCREEN_GRAGHBYTES; i++)
  {               
    Epaper_Write_Data(pgm_read_byte(&datas[i]));
  }
  
  datas = datas_flag;
  Epaper_Write_Command(0x26);
  for(i = 0; i < ALLSCREEN_GRAGHBYTES; i++)
  {               
    Epaper_Write_Data(pgm_read_byte(&datas[i]));
  }
  EPD_Update();   
}

void EPD_Dis_Part(unsigned int x_start,
                  unsigned int y_start,
                  const unsigned char * datas,
                  unsigned int PART_COLUMN,
                  unsigned int PART_LINE)
{
  unsigned int i;
  unsigned int x_end, y_start1, y_start2, y_end1, y_end2;
  
  x_start = x_start/8;
  x_end = x_start+PART_LINE/8-1; 
  
  y_start1 = 0;
  y_start2 = y_start;
  if(y_start >= 256)
  {
    y_start1 = y_start2/256;
    y_start2 = y_start2%256;
  }
  
  y_end1 = 0;
  y_end2 = y_start + PART_COLUMN - 1;
  if(y_end2 >= 256)
  {
    y_end1 = y_end2/256;
    y_end2 = y_end2%256;    
  }   
  
  Epaper_Write_Command(0x44);   // Set RAM x address start/end, in page 35
  Epaper_Write_Data(x_start);   // RAM x address start at 00h;
  Epaper_Write_Data(x_end);     // RAM x address end at 0fh(15+1)*8->128 
  Epaper_Write_Command(0x45);   // set RAM y address start/end, in page 35
  Epaper_Write_Data(y_start2);  // RAM y address start at 0127h;
  Epaper_Write_Data(y_start1);  // RAM y address start at 0127h;
  Epaper_Write_Data(y_end2);    // RAM y address end at 00h;
  Epaper_Write_Data(y_end1);    // ???? = 0 

  Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
  Epaper_Write_Data(x_start); 
  Epaper_Write_Command(0x4F);   // set RAM y address count to 0X127;    
  Epaper_Write_Data(y_start2);
  Epaper_Write_Data(y_start1);
    
  Epaper_Write_Command(0x24);   // Write Black and White image to RAM
  for(i = 0; i < PART_COLUMN*PART_LINE/8; i++)
  {                         
    Epaper_Write_Data(pgm_read_byte(&datas[i]));
  } 
  EPD_Part_Update();
}

////////////////////
// Single display //
////////////////////
void EPD_WhiteScreen_Black(void)
{
  unsigned int i,k;
  
  Epaper_Write_Command(0x24);   // Write RAM for black(0)/white (1)
  for(k = 0; k < 250; k++)
  {
    for(i = 0; i < 16; i++)
    {
      Epaper_Write_Data(0x00);
    }
  }
  EPD_Update();
}

void EPD_WhiteScreen_White(void)
{
  unsigned int i, k;
   
  Epaper_Write_Command(0x24);   // Write RAM for black(0)/white(1)
  for(k = 0; k < 250; k++)
  {
    for(i = 0; i < 16; i++)
    {
      Epaper_Write_Data(0xff);
    }
  }
  EPD_Update();
}
