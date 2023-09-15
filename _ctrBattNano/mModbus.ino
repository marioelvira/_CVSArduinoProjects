#include "main.h"
#include "io.h"

#if (_USE_MB_ == 1)

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
  byte   iIndex;
  byte   tmpChar;
  int   sizeFrame = mrs485TxNumBytes - (int)CRCSIZE;
  
  for (int i = 0; i < sizeFrame; i++)
  {
    tmpChar = (char)mrs485TxBuffer[i];
    iIndex = ucCRCLo ^ ( tmpChar & 0x00FF );
    ucCRCLo = (char)( ucCRCHi ^ aucCRCHi[iIndex] );
    ucCRCHi = aucCRCLo[iIndex];
  }

  mbCRC[1] = (ucCRCHi & 0xFF);   // highbyte
  mbCRC[0] = (ucCRCLo & 0xFF);   // lowbyte
}

/*
void _mbWriteSingleHolding(char modbusID)
{
  int addr, value, i, exception = 0;

  addr  = (int)((mrs485RxBuffer[2] & 0x00FF)<<8)|(mrs485RxBuffer[3] & 0x00FF);
  value = (int)((mrs485RxBuffer[4] & 0x00FF)<<8)|(mrs485RxBuffer[5] & 0x00FF);

  if ((addr >= MB_HR_ADD_OUTS) && (addr <= MB_HR_ADD_OUTS + MB_HR_NREG_OUTS))
  {
    // Only in MODE_TEST
    if (ControlMode == MODE_AUTO)
      exception = 1;
    else
    {
      i = addr - MB_HR_ADD_OUTS;
      if (value == OUT_OFF)
        OutDig[i] = OUT_OFF;
      else
        OutDig[i] = OUT_ON;
    }
  }
  else
    exception = 1;
  
  // NO Expection
  if (exception == 0)
  {
    mrs485TxBuffer[0] = (char)modbusID;
    mrs485TxBuffer[1] = (char)MB_FUNC_WRITE_REGISTER;
    mrs485TxBuffer[2] = mrs485RxBuffer[2];
    mrs485TxBuffer[3] = mrs485RxBuffer[3];
    mrs485TxBuffer[4] = mrs485RxBuffer[4];
    mrs485TxBuffer[5] = mrs485RxBuffer[5];
      
    // Num Bytes
    mrs485TxNumBytes = 8;
  }
  else
  {
    mrs485TxBuffer[0] = (char)modbusID;
    mrs485TxBuffer[1] = (char)(MB_FUNC_WRITE_REGISTER | MB_NACK);
    mrs485TxBuffer[2] = 0x02; // Illegal data address

    // Num Bytes
    mrs485TxNumBytes = 5;
  }

  // Crc
  _mbCRC();
  mrs485TxBuffer[mrs485TxNumBytes - 2] = mbCRC[0];
  mrs485TxBuffer[mrs485TxNumBytes - 1] = mbCRC[1];
  
  // Init RS485 Transmit
  mrs485State = MRS485_INITTX;
}
*/

void _mbWriteMultipleHolding(char modbusID)
{
  int addr, nregs, value, exception = 0;
  int eeprom_value_hi, eeprom_value_lo;

  addr  = (int)((mrs485RxBuffer[2] & 0x00FF)<<8)|(mrs485RxBuffer[3] & 0x00FF);
  nregs = (int)((mrs485RxBuffer[4] & 0x00FF)<<8)|(mrs485RxBuffer[5] & 0x00FF);

  if ((addr == MB_HR_ADD_CFG) && (nregs == MB_HR_NREG_CFG))
  {
    value = (int)((mrs485RxBuffer[7] & 0x00FF)<<8)|(mrs485RxBuffer[8] & 0x00FF);
    if (value == MODE_AUTO)
      ctrMode = MODE_AUTO;
    else
      ctrMode = MODE_TEST;

    value = (int)((mrs485RxBuffer[9] & 0x00FF)<<8)|(mrs485RxBuffer[10] & 0x00FF);
    if (value < 250)
      cfgMbId = value;
    
    value  = (int)((mrs485RxBuffer[11] & 0x00FF)<<8)|(mrs485RxBuffer[12] & 0x00FF);
    if (value == IO_OFF)
      cfgLogicIns = IO_OFF;
    else 
      cfgLogicIns = IO_ON;
      
    value = (int)((mrs485RxBuffer[13] & 0x00FF)<<8)|(mrs485RxBuffer[14] & 0x00FF);
    if (value == OUT_OFF)
      cfgLogicOuts = OUT_OFF;
    else 
      cfgLogicOuts = OUT_ON;

    cfgADCm[0] = (int)((mrs485RxBuffer[15] & 0x00FF)<<8)|(mrs485RxBuffer[16] & 0x00FF);
    cfgADCb[0] = (int)((mrs485RxBuffer[17] & 0x00FF)<<8)|(mrs485RxBuffer[18] & 0x00FF);
    cfgADCs[0] = (int)(mrs485RxBuffer[20] & 0x00FF);
    cfgADCt[0] = (int)((mrs485RxBuffer[21] & 0x00FF)<<8)|(mrs485RxBuffer[22] & 0x00FF);
    
    cfgADCm[1] = (int)((mrs485RxBuffer[23] & 0x00FF)<<8)|(mrs485RxBuffer[24] & 0x00FF);
    cfgADCb[1] = (int)((mrs485RxBuffer[25] & 0x00FF)<<8)|(mrs485RxBuffer[26] & 0x00FF);
    cfgADCs[1] = (int)(mrs485RxBuffer[28] & 0x00FF);
    cfgADCt[1] = (int)((mrs485RxBuffer[29] & 0x00FF)<<8)|(mrs485RxBuffer[30] & 0x00FF);
 
    // Data Data
    EEPROM.write(EEPROM_ADD_MODBUS_ID,  (byte)cfgMbId);
    EEPROM.write(EEPROM_ADD_LOGIC_INS,  (byte)cfgLogicIns);
    EEPROM.write(EEPROM_ADD_LOGIC_OUTS, (byte)cfgLogicOuts);

    for (int i = 0; i < ADC_NUMBER; i++)
    {
      eeprom_value_lo = cfgADCm[i] & 0x00FF;
      EEPROM.write(EEPROM_ADD_ADC_M_LO + i*EEPROM_ADC_SIZE, eeprom_value_lo);
      eeprom_value_hi = (cfgADCm[i] & 0xFF00)>>8;
      EEPROM.write(EEPROM_ADD_ADC_M_HI + i*EEPROM_ADC_SIZE, eeprom_value_hi);
      
      eeprom_value_lo = cfgADCb[i] & 0x00FF;
      EEPROM.write(EEPROM_ADD_ADC_B_LO + i*EEPROM_ADC_SIZE, eeprom_value_lo);
      eeprom_value_hi = (cfgADCb[i] & 0xFF00)>>8;
      EEPROM.write(EEPROM_ADD_ADC_B_HI + i*EEPROM_ADC_SIZE, eeprom_value_hi);
            
      EEPROM.write(EEPROM_ADD_ADC_S + i*EEPROM_ADC_SIZE,  cfgADCs[i]);

      eeprom_value_lo = cfgADCt[i] & 0x00FF;
      EEPROM.write(EEPROM_ADD_ADC_T_LO + i*EEPROM_ADC_SIZE, eeprom_value_lo);
      eeprom_value_hi = (cfgADCt[i] & 0xFF00)>>8;
      EEPROM.write(EEPROM_ADD_ADC_T_HI + i*EEPROM_ADC_SIZE, eeprom_value_hi);
    }
  }
  else if ((addr == MB_HR_ADD_OUTS) && (nregs == MB_HR_NREG_OUTS))
  {
    // Only in MODE_TEST
    if (ctrMode == MODE_AUTO)
      exception = 1;
    else
    {
      for (int i = 0; i < MB_HR_NREG_OUTS; i++)
      {
        value = (int)((mrs485RxBuffer[i*2 + 7] & 0x00FF)<<8)|(mrs485RxBuffer[i*2 + 8] & 0x00FF);
        if (value == OUT_OFF)
          OutDig[i] = OUT_OFF;
        else
          OutDig[i] = OUT_ON;
      }
    }
  }
  else
    exception = 1;
  
  // NO Expection
  if (exception == 0)
  {
    mrs485TxBuffer[0] = (char)modbusID;
    mrs485TxBuffer[1] = (char)MB_FUNC_WRITE_MULTIPLE_REGISTERS;
    mrs485TxBuffer[2] = mrs485RxBuffer[2];
    mrs485TxBuffer[3] = mrs485RxBuffer[3];
    mrs485TxBuffer[4] = mrs485RxBuffer[4];
    mrs485TxBuffer[5] = mrs485RxBuffer[5];
      
    // Num Bytes
    mrs485TxNumBytes = 8;
  }
  else
  {
    mrs485TxBuffer[0] = (char)modbusID;
    mrs485TxBuffer[1] = (char)(MB_FUNC_WRITE_MULTIPLE_REGISTERS | MB_NACK);
    mrs485TxBuffer[2] = 0x02; // Illegal data address

    // Num Bytes
    mrs485TxNumBytes = 5;
  }
  
  // Crc
  _mbCRC();
  mrs485TxBuffer[mrs485TxNumBytes - 2] = mbCRC[0];
  mrs485TxBuffer[mrs485TxNumBytes - 1] = mbCRC[1];
  
  // Init RS485 Transmit
  mrs485State = MRS485_INITTX;
}

void _mbReadHolding(char modbusID)
{
  int addr, nregs, exception = 0;

  addr  = (int)((mrs485RxBuffer[2] & 0x00FF)<<8)|(mrs485RxBuffer[3] & 0x00FF);
  nregs = (int)((mrs485RxBuffer[4] & 0x00FF)<<8)|(mrs485RxBuffer[5] & 0x00FF);

  if ((addr == MB_HR_ADD_CFG) && (nregs == MB_HR_NREG_CFG))
  {
    mrs485TxBuffer[3]   = 0x00;
    mrs485TxBuffer[4]   = ctrMode;
    mrs485TxBuffer[5]   = 0x00;
    mrs485TxBuffer[6]   = cfgMbId;
    mrs485TxBuffer[7]   = 0x00;
    mrs485TxBuffer[8]   = cfgLogicIns;
    mrs485TxBuffer[9]   = 0x00;
    mrs485TxBuffer[10]  = cfgLogicOuts;
    
    mrs485TxBuffer[11]  = (cfgADCm[0] & 0xFF00)>>8;
    mrs485TxBuffer[12]  = cfgADCm[0] & 0x00FF;
    mrs485TxBuffer[13]  = (cfgADCb[0] & 0xFF00)>>8;
    mrs485TxBuffer[14]  = cfgADCb[0] & 0x00FF;
    mrs485TxBuffer[15]  = 0x00;
    mrs485TxBuffer[16]  = cfgADCs[0];
    mrs485TxBuffer[17]  = (cfgADCt[0] & 0xFF00)>>8;
    mrs485TxBuffer[18]  = cfgADCt[0] & 0x00FF;
     
    mrs485TxBuffer[19]  = (cfgADCm[1] & 0xFF00)>>8;
    mrs485TxBuffer[20]  = cfgADCm[1] & 0x00FF;
    mrs485TxBuffer[21]  = (cfgADCb[1] & 0xFF00)>>8;
    mrs485TxBuffer[22]  = cfgADCb[1] & 0x00FF;
    mrs485TxBuffer[23]  = 0x00;
    mrs485TxBuffer[24]  = cfgADCs[1];
    mrs485TxBuffer[25]  = (cfgADCt[1] & 0xFF00)>>8;
    mrs485TxBuffer[26]  = cfgADCt[1] & 0x00FF;
  }
  else if ((addr == MB_HR_ADD_OUTS) && (nregs == MB_HR_NREG_OUTS))
  {
    for (int i = 0; i < MB_HR_NREG_OUTS; i++)
    {
      mrs485TxBuffer[i*2 + 3]  = 0x00;
      mrs485TxBuffer[i*2 + 4]  = OutDig[i];
    }
  }
  else
    exception = 1;

  // NO Expection
  if (exception == 0)
  {
    mrs485TxBuffer[0] = (char)modbusID;
    mrs485TxBuffer[1] = (char)MB_FUNC_READ_HOLDING_REGISTER;
    mrs485TxBuffer[2] = nregs*2;
      
    // Num Bytes
    mrs485TxNumBytes = mrs485TxBuffer[2] + 5;
  }
  else
  {
	  mrs485TxBuffer[0] = (char)modbusID;
	  mrs485TxBuffer[1] = (char)(MB_FUNC_READ_HOLDING_REGISTER | MB_NACK);
	  mrs485TxBuffer[2] = 0x02;	// Illegal data address

    // Num Bytes
    mrs485TxNumBytes = 5;
  }

  // Crc
  _mbCRC();
  mrs485TxBuffer[mrs485TxNumBytes - 2] = mbCRC[0];
  mrs485TxBuffer[mrs485TxNumBytes - 1] = mbCRC[1];
  
  // Init RS485 Transmit
  mrs485State = MRS485_INITTX;
}

void _mbReadInput(char modbusID)
{
  int i, addr, nregs, exception = 0;

  addr  = (int)((mrs485RxBuffer[2] & 0x00FF)<<8)|(mrs485RxBuffer[3] & 0x00FF);
  nregs = (int)((mrs485RxBuffer[4] & 0x00FF)<<8)|(mrs485RxBuffer[5] & 0x00FF);

  if ((addr == MB_IR_ADD_ONLINE) && (nregs == MB_IR_NREG_ONLINE))
  {

    mrs485TxBuffer[3]  = (char)((AdcVal[0] & 0xFF00)>>8);
    mrs485TxBuffer[4]  = (char)(AdcVal[0] & 0x00FF);
    mrs485TxBuffer[5]  = (char)((AdcVal[1] & 0xFF00)>>8);
    mrs485TxBuffer[6]  = (char)(AdcVal[1] & 0x00FF);
    mrs485TxBuffer[7]  = 0x00;
    mrs485TxBuffer[8]  = ctrMode;
    mrs485TxBuffer[9]  = 0x00;
    mrs485TxBuffer[10] = ctrInClock;
    mrs485TxBuffer[11] = 0x00;
    mrs485TxBuffer[12] = inPulsState;
    mrs485TxBuffer[13] = 0x00;
    mrs485TxBuffer[14] = ctrOutRele;
    mrs485TxBuffer[15] = 0x00;
    mrs485TxBuffer[16] = ctrDisplay;
    mrs485TxBuffer[17]  = (char)((ctrDisplaySec & 0xFF00)>>8);
    mrs485TxBuffer[18]  = (char)(ctrDisplaySec & 0x00FF);
    
  }
  else if ((addr == MB_IR_ADD_INS) && (nregs == MB_IR_NREG_INS))
  { 
    for (i = 0; i < MB_IR_NREG_INS; i++)
    {
      mrs485TxBuffer[i*2 + 3]  = 0x00;
      mrs485TxBuffer[i*2 + 4]  = InDig[i];
    }
  }
  else if ((addr == MB_IR_ADD_OUTS) && (nregs == MB_IR_NREG_OUTS))
  {
    for (i = 0; i < MB_IR_NREG_OUTS; i++)
    {
      mrs485TxBuffer[i*2 + 3]  = 0x00;
      mrs485TxBuffer[i*2 + 4]  = OutDig[i];
    }
  }
  else if ((addr == MB_IR_ADD_ADCS) && (nregs == MB_IR_NREG_ADCS))
  {
    for (i = 0; i < MB_IR_NREG_ADCS; i++)
    {
      mrs485TxBuffer[i*2 + 3]  = (char)((AdcDig[i] & 0xFF00)>>8);
      mrs485TxBuffer[i*2 + 4]  = (char)(AdcDig[i] & 0x00FF);
    }
  }
  else
    exception = 1;

  // NO Expection
  if (exception == 0)
  {
    mrs485TxBuffer[0] = (char)modbusID;
    mrs485TxBuffer[1] = (char)MB_FUNC_READ_INPUT_REGISTER;
    mrs485TxBuffer[2] = nregs*2;
      
    // Num Bytes
    mrs485TxNumBytes = mrs485TxBuffer[2] + 5;
  }
  else
 {
    mrs485TxBuffer[0] = (char)modbusID;
    mrs485TxBuffer[1] = (char)(MB_FUNC_READ_INPUT_REGISTER | MB_NACK);
    mrs485TxBuffer[2] = 0x02; // Illegal data address

    // Num Bytes
    mrs485TxNumBytes = 5;
  }

  // Crc
  _mbCRC();
  mrs485TxBuffer[mrs485TxNumBytes - 2] = mbCRC[0];
  mrs485TxBuffer[mrs485TxNumBytes - 1] = mbCRC[1];
  
  // Init RS485 Transmit
  mrs485State = MRS485_INITTX;
}

void _mbSlaveID(char modbusID)
{  
  // Num Bytes
  mrs485TxNumBytes = 30;

  mrs485TxBuffer[0] = (char)modbusID;
  mrs485TxBuffer[1] = (char)MB_FUNC_OTHER_REPORT_SLAVEID;

  mrs485TxBuffer[2] = (char)(mrs485TxNumBytes - 6);

  mrs485TxBuffer[3] = 0x00;
  mrs485TxBuffer[4] = 0xFF;

  // 12 bytes
  mrs485TxBuffer[5] = '0';  //SN_VER0;
  mrs485TxBuffer[6] = '0';  //SN_VER1;
  mrs485TxBuffer[7] = '0';  //SN_VER2;
  mrs485TxBuffer[8] = '0';  //SN_VER3;
  mrs485TxBuffer[9] = '0';  //SN_VER4;
  mrs485TxBuffer[10] = '0'; //SN_VER5;
  mrs485TxBuffer[11] = '0'; //SN_VER6;
  mrs485TxBuffer[12] = '0'; //SN_VER7;
  mrs485TxBuffer[13] = '0'; //SN_VER8;
  mrs485TxBuffer[14] = '0'; //SN_VER9;
  mrs485TxBuffer[15] = '0'; //SN_VER10;
  mrs485TxBuffer[16] = '0'; //SN_VER11;
  
  // 10 bytes
  mrs485TxBuffer[17] = FW_Version[0]; //FW_VER0;
  mrs485TxBuffer[18] = FW_Version[1]; //FW_VER1;
  mrs485TxBuffer[19] = FW_Version[1]; //FW_VER2;
  mrs485TxBuffer[20] = FW_Version[2]; //FW_VER3;
  mrs485TxBuffer[21] = FW_Version[3]; //FW_VER4;
  mrs485TxBuffer[23] = '0'; //FW_VER5;
  mrs485TxBuffer[24] = '0'; //FW_VER6;
  mrs485TxBuffer[25] = '0'; //FW_VER7;
  mrs485TxBuffer[26] = '0'; //FW_VER8;
  mrs485TxBuffer[27] = '0'; //FW_VER9;
  
  // Crc
  _mbCRC();
  mrs485TxBuffer[28] = mbCRC[0];
  mrs485TxBuffer[29] = mbCRC[1];

  // Init RS485 Transmit
  mrs485State = MRS485_INITTX;
}

int _mbN7(void)
{
	int error = 0;

	switch (mrs485RxBuffer[1])
	{
		case MB_FUNC_READ_HOLDING_REGISTER:
      _mbReadHolding((char)cfgMbId);
			break;
 
		case MB_FUNC_READ_INPUT_REGISTER:
			_mbReadInput((char)cfgMbId);
			break;
			
		//case MB_FUNC_WRITE_REGISTER:
    //  _mbWriteSingleHolding((char)cfgMbId);
		//  break;
		
		case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
      _mbWriteMultipleHolding((char)cfgMbId);
		  break;
		
		case MB_FUNC_OTHER_REPORT_SLAVEID:
			_mbSlaveID((char)cfgMbId);
			break;
      
		default:
			error = 1;
			break;
	}
  
  return error;
}

int _mbN1(char modbusID)
{
  int error = 0;

  if (mrs485RxBuffer[0] == (char)modbusID)
  {
    // check CRC (TODO)
  }
  else
    error = 1;

  return error;
}

////////////////////
// mModbus set up //
////////////////////
void _MBSetup(void)
{
  int i, j;
  mbState = MB_STANDBY;
  mbTick = millis();
}

//////////////////
// mModbus Loop //
//////////////////
void _MBLoop(void)
{
  
  switch (mbState)
  {
    case MB_STANDBY:
      // If frame RX
      if (mrs485State == MRS485_FRAME_RX)
      {
        if (_mbN1((char)cfgMbId) == MB_RX_OK)
          mbState = MB_ANALYSE_FRAME;
      }
	    break;

    case MB_ANALYSE_FRAME:
      if (_mbN7() == MB_RX_OK)
        mbState = MB_SEND_RESPONSE;
	    else
		    mbState = MB_STANDBY;
      break;

    case MB_SEND_RESPONSE:
	  // If TX ended
      if (mrs485State == MRS485_STANDBY)
	    mbState = MB_STANDBY;
      break;
  }
}

#endif
