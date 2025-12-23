#include "main.h"

#if (_USE_MBRTU_ == 1)

/**********************************************************************
*    6.-  MODULE PRIVATE VARIABLES.
***********************************************************************/
static const char aucCRCHi[] =
{
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40
};

static const char aucCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
    0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
    0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
    0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
    0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
    0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40
};

/////////////////////
// Local Functions //
/////////////////////
void _mbCRC(void)
{ 
  char  ucCRCHi = 0xFF;
  char  ucCRCLo = 0xFF;
  byte  iIndex;
  byte  tmpChar;
  int   sizeFrame = mrs485TxNumBytes - (int)CRCSIZE;
  
  for (int i=0; i<sizeFrame; i++)
  {
    tmpChar = (char)mrs485TxBuffer[i];
    iIndex = ucCRCLo ^ ( tmpChar & 0x00FF );
    ucCRCLo = (char)( ucCRCHi ^ aucCRCHi[iIndex] );
    ucCRCHi = aucCRCLo[iIndex];
  }

  mbCRC[1] = (ucCRCHi & 0xFF);   // highbyte
  mbCRC[0] = (ucCRCLo & 0xFF);   // lowbyte
}

// Tx: FF 02 00 00 00 08 6C 12
// Rx: FF 02 01 01 51 A0
void _mbReadIns(char address)
{
  // Num Bytes
  mrs485TxNumBytes = 8;

  mrs485TxBuffer[0] = (char)address;
  mrs485TxBuffer[1] = 0x02;
  mrs485TxBuffer[2] = 0x00;
  mrs485TxBuffer[3] = 0x00;
  mrs485TxBuffer[4] = 0x00;
  mrs485TxBuffer[5] = 0x08;
  // Crc
  _mbCRC();
  mrs485TxBuffer[6] = mbCRC[0];
  mrs485TxBuffer[7] = mbCRC[1];

  // Init RS485 Transmit
  mrs485State = MRS485_INITTX;
}

// Rx: FF 02 01 01 51 A0
int _mbAnalyseIns(char address)
{
  int error = 0;

  if ((mrs485RxBuffer[0] == (char)address) &&
      (mrs485RxBuffer[1] == 0x02) &&
      (mrs485RxBuffer[2] == 0x01))
  {
    // check CRC (TODO)
  }
  else
    error = 1;

  return error;
}

void _mbUdateIns (int board)
{
  if ((mrs485RxBuffer[3] & 0x01) != 0)
    mbIns[0][board] = IO_ON;
  else
    mbIns[0][board] = IO_OFF;

  if ((mrs485RxBuffer[3] & 0x02) != 0)
    mbIns[1][board] = IO_ON;
  else
    mbIns[1][board] = IO_OFF;

  if ((mrs485RxBuffer[3] & 0x04) != 0)
    mbIns[2][board] = IO_ON;
  else
    mbIns[2][board] = IO_OFF;

  if ((mrs485RxBuffer[3] & 0x08) != 0)
    mbIns[3][board] = IO_ON;
  else
    mbIns[3][board] = IO_OFF;

  if ((mrs485RxBuffer[3] & 0x10) != 0)
    mbIns[4][board] = IO_ON;
  else
    mbIns[4][board] = IO_OFF;

  if ((mrs485RxBuffer[3] & 0x20) != 0)
    mbIns[5][board] = IO_ON;
  else
    mbIns[5][board] = IO_OFF;

  if ((mrs485RxBuffer[3] & 0x40) != 0)
    mbIns[6][board] = IO_ON;
  else
    mbIns[6][board] = IO_OFF;

  if ((mrs485RxBuffer[3] & 0x80) != 0)
    mbIns[7][board] = IO_ON;
  else
    mbIns[7][board] = IO_OFF;
}

// Tx: FF 01 00 00 00 08 28 12
// Rx: FF 01 01 A1 AO
void _mbReadOuts(char address)
{
  // Num Bytes
  mrs485TxNumBytes = 8;

  mrs485TxBuffer[0] = (char)address;
  mrs485TxBuffer[1] = 0x01;
  mrs485TxBuffer[2] = 0x00;
  mrs485TxBuffer[3] = 0x00;
  mrs485TxBuffer[4] = 0x00;
  mrs485TxBuffer[5] = 0x08;
  _mbCRC();
  mrs485TxBuffer[6] = mbCRC[0];
  mrs485TxBuffer[7] = mbCRC[1];
  
  // Init RS485 Transmit
  mrs485State = MRS485_INITTX;
}

// Rx: FF 02 01 01 51 A0
int _mbAnalyseOuts(char address)
{
  int error = 0;

  if ((mrs485RxBuffer[0] == (char)address) &&
      (mrs485RxBuffer[1] == 0x01) &&
      (mrs485RxBuffer[2] == 0x01))
  {
    // check CRC (TODO)
  }
  else
    error = 1;

  return error;
}

void _mbUdateOuts (int board)
{
 
  if (mrs485RxBuffer[3] & 0x01)
    mbROuts[0][board] = IO_ON;
  else
    mbROuts[0][board] = IO_OFF;

  if (mrs485RxBuffer[3] & 0x02)
    mbROuts[1][board] = IO_ON;
  else
    mbROuts[1][board] = IO_OFF;

  if (mrs485RxBuffer[3] & 0x04)
    mbROuts[2][board] = IO_ON;
  else
    mbROuts[2][board] = IO_OFF;

  if (mrs485RxBuffer[3] & 0x08)
    mbROuts[3][board] = IO_ON;
  else
    mbROuts[3][board] = IO_OFF;

  if (mrs485RxBuffer[3] & 0x10)
    mbROuts[4][board] = IO_ON;
  else
    mbROuts[4][board] = IO_OFF;

  if (mrs485RxBuffer[3] & 0x20)
    mbROuts[5][board] = IO_ON;
  else
    mbROuts[5][board] = IO_OFF;

  if (mrs485RxBuffer[3] & 0x40)
    mbROuts[6][board] = IO_ON;
  else
    mbROuts[6][board] = IO_OFF;

  if (mrs485RxBuffer[3] & 0x80)
    mbROuts[7][board] = IO_ON;
  else
    mbROuts[7][board] = IO_OFF;
}

// Tx: FF 05 00 01 FF 00 C8 24 - Rele 2 a ON
// Rx: FF 05 00 01 FF 00 C8 24
// out: 0 to 7; 8 all relays
// val: 0 OFF, 1 ON
void _mbWriteOut (char address, int out, int val)
{
  // Num Bytes
  mrs485TxNumBytes = 8;
      
  mrs485TxBuffer[0] = (char)address;
  mrs485TxBuffer[1] = 0x05;
  mrs485TxBuffer[2] = 0x00;
  mrs485TxBuffer[3] = out;
  if (val == 0)
    mrs485TxBuffer[4] = 0x00;
  else
    mrs485TxBuffer[4] = 0xFF;
  mrs485TxBuffer[5] = 0x00;
  // Crc
  _mbCRC();
  mrs485TxBuffer[6] = mbCRC[0];
  mrs485TxBuffer[7] = mbCRC[1];

  // Init RS485 Transmit
  mrs485State = MRS485_INITTX;
}

// Rx: FF 05 00 01 FF 00 C8 24
int _mbAnalyseOut (char address, int out) //, int val)
{
  int error = 0;

  if ((mrs485RxBuffer[0] == (char)address) &&
      (mrs485RxBuffer[1] == 0x05) &&
	    (mrs485RxBuffer[2] == 0x00) &&
	    (mrs485TxBuffer[3] == out))
	    //(mrs485TxBuffer[3] == val))
  {
    // check CRC (TODO)
  }
  else
    error = 1;

  return error;
}

int _MBOutCheck(void)
{
  int i, j;

  // num boards
  for (j = 0; j < MB_NUM_BRS; j++)
  {
    // num outs
    for (i = 0; i < MB_NUM_IOS; i++)
    {
      if (mbOuts[i][j] != mbROuts[i][j])
      {
        mbOutBoard = j;
        mbOutNum = i;
        mbOutVal = mbOuts[i][j];
        
        // Write Out
        if (mbState == MB_STANDBY)
          mbState = MB_WRITEOUT;
        // Salimos
        return 1;
      }
    }
  }

  return 0;
}

void _mbInsAlarmInit (void)
{
  mbInsAlarm[0][0] = MB_IN_AL_VAL_0;
  mbInsAlarm[1][0] = MB_IN_AL_VAL_0;
  mbInsAlarm[2][0] = MB_IN_AL_DISABLE;
  mbInsAlarm[3][0] = MB_IN_AL_DISABLE;
  mbInsAlarm[4][0] = MB_IN_AL_DISABLE;
  mbInsAlarm[5][0] = MB_IN_AL_DISABLE;
  mbInsAlarm[6][0] = MB_IN_AL_DISABLE;
  mbInsAlarm[7][0] = MB_IN_AL_DISABLE;

  mbInsAlarm[0][1] = MB_IN_AL_DISABLE;
  mbInsAlarm[1][1] = MB_IN_AL_DISABLE;
  mbInsAlarm[2][1] = MB_IN_AL_DISABLE;
  mbInsAlarm[3][1] = MB_IN_AL_DISABLE;
  mbInsAlarm[4][1] = MB_IN_AL_DISABLE;
  mbInsAlarm[5][1] = MB_IN_AL_DISABLE;
  mbInsAlarm[6][1] = MB_IN_AL_DISABLE;
  mbInsAlarm[7][1] = MB_IN_AL_DISABLE;
}

void _mbInsAlarmCheck (void)
{
  int i, j;

  for (j = 0; j < MB_NUM_BRS; j++)
  {
    for (i = 0; i < MB_NUM_IOS; i++)
    {
      if (mbIns[i][j] == mbInsAlarm[i][j])
        alarm[8*(j + 1) + i] = 1;
      else
        alarm[8*(j + 1) + i] = 0;
    }
  }
}

////////////////////
// mModbus set up //
////////////////////
void _MBSetup(void)
{
  int i, j;
  mbState = MB_STANDBY;
  mbTick = millis();

  mbInNBoard = 0;
  mbOutBoard = 0;

  // Modbus DIOs reset
  for (j = 0; j < MB_NUM_BRS; j++)
  {
    for (i = 0; i < MB_NUM_IOS; i++)
    {
      mbIns[i][j] = 0;
      mbOuts[i][j] = 0;
    }
  }

  _mbInsAlarmInit();
}

//////////////////
// mModbus Loop //
//////////////////
void _MBLoop(void)
{
  int error = 0;
  
  switch (mbState)
  {
    case MB_STANDBY:
      
      if (millis() - mbTick >= MB_RXLOOP)
      {
        if (mbWhat2read < NUM_W2R)
          mbState = MB_READINS;
        else
          mbState = MB_READOUTS;

        mbWhat2read++;
        if (mbWhat2read > NUM_W2R)
          mbWhat2read = 0;
      }
    
	    break;

    // Read Ins
    case MB_READINS:
      if (mbInNBoard == 0)
        _mbReadIns((char)cfgMB1Add);
      else
        _mbReadIns((char)cfgMB2Add);      

      // Analyse Response
      mbTick = millis();
      mbState = MB_INSSTATUS;
      
      break;

    case MB_INSSTATUS:

      // wait for response
      if (millis() - mbTick >= MB_RXTOUT)
      {   
        mbTick = millis();
        mbState = MB_SLEEP; //MB_STANDBY;
        mbSWake = MB_STANDBY;
        mbNReply++;

        // Alarm
        if (mbInNBoard == 0)
        {
          alarm[AL_ERROR0] = 1;
          mbInNBoard = 1;
        }
        else
        {
          alarm[AL_ERROR1] = 1;
          mbInNBoard = 0;
        }
      }

      // if response received
      if (mrs485State == MRS485_FRAME_RX)
      {
        if (mbInNBoard == 0)
        {
          // Analyse response
          if (_mbAnalyseIns((char)cfgMB1Add) == MB_RX_OK)
          {
            _mbUdateIns(mbInNBoard);
            alarm[AL_ERROR0] = 0;
          }
          else
            mbNError++;
          
          // Next board
          mbInNBoard = 1;
        }
        else
        {
          // Analyse response
          if (_mbAnalyseIns((char)cfgMB2Add) == MB_RX_OK)
          {
            _mbUdateIns(mbInNBoard);
            alarm[AL_ERROR1] = 0;
          }
          else
            mbNError++;;
          
          // Next board
          mbInNBoard = 0;
        }
                
        mbTick = millis();
        mbState = MB_SLEEP; //MB_STANDBY;
        mbSWake = MB_STANDBY;
                
        // clear Rx buffer
        mrs485RxBuffer = "";
        mrs485State = MRS485_STANDBY;
      }

      break;

    // Read Outs
    case MB_READOUTS:
      if (mbOutNBoard == 0)
        _mbReadOuts((char)cfgMB1Add);
      else
        _mbReadOuts((char)cfgMB2Add);      

      // Analyse Response
      mbTick = millis();
      mbState = MB_OUTSSTATUS;
      
      break;

    case MB_OUTSSTATUS:

      // wait for response
      if (millis() - mbTick >= MB_RXTOUT)
      {   
        mbTick = millis();
        mbState = MB_SLEEP; //MB_STANDBY;
        mbSWake = MB_STANDBY;
        mbNReply++;
      }

      // if response received
      if (mrs485State == MRS485_FRAME_RX)
      {
        if (mbOutNBoard == 0)
        {
          // Analyse response
          if (_mbAnalyseOuts((char)cfgMB1Add) == MB_RX_OK)
            _mbUdateOuts(mbOutNBoard);
          else
            mbNError++;
          
          // Next board
          mbOutNBoard = 1;
        }
        else
        {
          // Analyse response
          if (_mbAnalyseOuts((char)cfgMB2Add) == MB_RX_OK)
            _mbUdateOuts(mbOutNBoard);
          else
            mbNError++;;
          
          // Next board
          mbOutNBoard = 0;
        }

        mbTick = millis();
        mbState = MB_SLEEP; //MB_STANDBY;
        mbSWake = MB_STANDBY;
                
        // clear Rx buffer
        mrs485RxBuffer = "";
        mrs485State = MRS485_STANDBY;
      }

      break;

    // Write Out
	  case MB_WRITEOUT:
      // select board
      if (mbOutBoard == 0)
	      _mbWriteOut((char)cfgMB1Add, mbOutNum, mbOutVal);
      else
       _mbWriteOut((char)cfgMB2Add, mbOutNum, mbOutVal);

      // Analyse Response
      mbTick = millis();
      mbState = MB_OUTSTATUS;
	  
	    break;

    case MB_OUTSTATUS:

      // wait for response
      if (millis() - mbTick >= MB_RXTOUT)
      {
        mbNReply++;
        
        // Retry ??
        if (mbRetry < MB_NUM_RETRY)
        {
          mbNRetry++;
          mbTick = millis();
          mbState = MB_SLEEP; //MB_WRITEOUT;
          mbSWake = MB_WRITEOUT;
          mbRetry++;
        }
        else
        {
          mbTick = millis();
          mbState = MB_SLEEP; //MB_STANDBY;
          mbSWake = MB_STANDBY;
          mbRetry = 0;
        }
      }

      // if response received
      if (mrs485State == MRS485_FRAME_RX)
      {
        // Analyse response
        if (mbOutBoard == 0)
          error = _mbAnalyseOut((char)cfgMB1Add, mbOutNum); //, mbOutVal);
        else 
          error = _mbAnalyseOut((char)cfgMB2Add, mbOutNum); //, mbOutVal);

        // If NO error
        if (error == 0)
        {
          if (mbOutVal == OUT_OFF)
            mbOuts[mbOutNum][mbOutBoard] = OUT_OFF;
          else
            mbOuts[mbOutNum][mbOutBoard] = OUT_ON;   

          mbTick = millis();
          mbState = MB_SLEEP; //MB_STANDBY;
          mbSWake = MB_STANDBY;      
        }
        else
        {
          mbNError++;
          // Retry ??
          if (mbRetry < MB_NUM_RETRY)
          {
            mbNRetry++;
            mbTick = millis();
            mbState = MB_SLEEP; //MB_WRITEOUT;
            mbSWake = MB_WRITEOUT;
            mbRetry++;
          }
          else
          {
            mbTick = millis();
            mbState = MB_SLEEP; //MB_STANDBY;
            mbSWake = MB_STANDBY;      
            mbRetry = 0;
          }
        }

        // clear Rx buffer
        mrs485RxBuffer = "";
        mrs485State = MRS485_STANDBY;
      }

      break;

    case MB_SLEEP:
      if (millis() - mbTick >= MB_TSLEEP)
        mbState = mbSWake;

      break;
      
  }
}

#endif // _USE_MBRTU_
