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
void _mbWriteSingleHolding(char address)
{
  int addr, value, i;

  addr  = (int)((mrs485RxBuffer[2] & 0x00FF)<<8)|(mrs485RxBuffer[3] & 0x00FF);
  value = (int)((mrs485RxBuffer[4] & 0x00FF)<<8)|(mrs485RxBuffer[5] & 0x00FF);

  if ((addr >= MB_ADD_OUTS) && (addr <= MB_ADD_OUTS + MB_NREG_OUTS))
  {
    i = addr - MB_ADD_OUTS;
    if (value == OUT_OFF)
      OutDig[i] = OUT_OFF;
    else
      OutDig[i] = OUT_ON;

    mrs485TxBuffer[0] = (char)address;
    mrs485TxBuffer[1] = (char)MB_FUNC_WRITE_REGISTER;
    mrs485TxBuffer[2] = mrs485RxBuffer[2];
    mrs485TxBuffer[3] = mrs485RxBuffer[3];
    mrs485TxBuffer[4] = mrs485RxBuffer[4];
    mrs485TxBuffer[5] = mrs485RxBuffer[5];
    
    // Num Bytes
    mrs485TxNumBytes = 8;
  }
  // Expection
  else
  {
    mrs485TxBuffer[0] = (char)address;
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

void _mbWriteMultipleHolding(char address)
{
  int addr, nregs, value;

  addr  = (int)((mrs485RxBuffer[2] & 0x00FF)<<8)|(mrs485RxBuffer[3] & 0x00FF);
  nregs = (int)((mrs485RxBuffer[4] & 0x00FF)<<8)|(mrs485RxBuffer[5] & 0x00FF);

  // OUTs 
  if ((addr == MB_ADD_OUTS) && (nregs == MB_NREG_OUTS))
  { 
    value = (int)((mrs485RxBuffer[7] & 0x00FF)<<8)|(mrs485RxBuffer[8] & 0x00FF);
    if (value == OUT_OFF)
      OutDig[0] = OUT_OFF;
    else
      OutDig[0] = OUT_ON;

    value = (int)((mrs485RxBuffer[9] & 0x00FF)<<8)|(mrs485RxBuffer[10] & 0x00FF);
    if (value == OUT_OFF)
      OutDig[1] = OUT_OFF;
    else
      OutDig[1] = OUT_ON;

    value = (int)((mrs485RxBuffer[11] & 0x00FF)<<8)|(mrs485RxBuffer[12] & 0x00FF);
    if (value == OUT_OFF)
      OutDig[2] = OUT_OFF;
    else
      OutDig[2] = OUT_ON;

    mrs485TxBuffer[0] = (char)address;
    mrs485TxBuffer[1] = (char)MB_FUNC_WRITE_MULTIPLE_REGISTERS;
    mrs485TxBuffer[2] = mrs485RxBuffer[2];
    mrs485TxBuffer[3] = mrs485RxBuffer[3];
    mrs485TxBuffer[4] = mrs485RxBuffer[4];
    mrs485TxBuffer[5] = mrs485RxBuffer[5];
    
    // Num Bytes
    mrs485TxNumBytes = 8;
  }
  // CFGs 
  else if ((addr == MB_ADD_CFG) && (nregs == MB_NREG_CFG))
  {
    int eeprom_value_hi, eeprom_value_lo;
    
    value =  (int)((mrs485RxBuffer[7] & 0x00FF)<<8)|(mrs485RxBuffer[8] & 0x00FF);
    cfgMbId = value;
    
    value =  (int)((mrs485RxBuffer[9] & 0x00FF)<<8)|(mrs485RxBuffer[10] & 0x00FF);
    cfgADCm[0] = value;
    value = (int)((mrs485RxBuffer[11] & 0x00FF)<<8)|(mrs485RxBuffer[12] & 0x00FF);
    cfgADCb[0] = value;
    value = (int)((mrs485RxBuffer[13] & 0x00FF)<<8)|(mrs485RxBuffer[14] & 0x00FF);
    cfgADCp[0] = value;
    value = (int)((mrs485RxBuffer[15] & 0x00FF)<<8)|(mrs485RxBuffer[16] & 0x00FF);
    cfgADCs[0] = value;
    value = (int)((mrs485RxBuffer[17] & 0x00FF)<<8)|(mrs485RxBuffer[18] & 0x00FF);
    cfgADCf[0] = value;

    value = (int)((mrs485RxBuffer[19] & 0x00FF)<<8)|(mrs485RxBuffer[20] & 0x00FF);
    cfgADCm[1] = value;
    value = (int)((mrs485RxBuffer[21] & 0x00FF)<<8)|(mrs485RxBuffer[22] & 0x00FF);
    cfgADCb[1] = value;
    value = (int)((mrs485RxBuffer[23] & 0x00FF)<<8)|(mrs485RxBuffer[24] & 0x00FF);
    cfgADCp[1] = value;
    value = (int)((mrs485RxBuffer[25] & 0x00FF)<<8)|(mrs485RxBuffer[26] & 0x00FF);
    cfgADCs[1] = value;
    value = (int)((mrs485RxBuffer[27] & 0x00FF)<<8)|(mrs485RxBuffer[28] & 0x00FF);
    cfgADCf[1] = value;

    value = (int)((mrs485RxBuffer[29] & 0x00FF)<<8)|(mrs485RxBuffer[30] & 0x00FF);
    cfgADCm[2] = value;
    value = (int)((mrs485RxBuffer[31] & 0x00FF)<<8)|(mrs485RxBuffer[32] & 0x00FF);
    cfgADCb[2] = value;
    value = (int)((mrs485RxBuffer[33] & 0x00FF)<<8)|(mrs485RxBuffer[34] & 0x00FF);
    cfgADCp[2] = value;
    value = (int)((mrs485RxBuffer[35] & 0x00FF)<<8)|(mrs485RxBuffer[36] & 0x00FF);
    cfgADCs[2] = value;
    value = (int)((mrs485RxBuffer[37] & 0x00FF)<<8)|(mrs485RxBuffer[38] & 0x00FF);
    cfgADCf[2] = value; 

    value = (int)((mrs485RxBuffer[39] & 0x00FF)<<8)|(mrs485RxBuffer[40] & 0x00FF);
    cfgADCm[3] = value;
    value = (int)((mrs485RxBuffer[41] & 0x00FF)<<8)|(mrs485RxBuffer[42] & 0x00FF);
    cfgADCb[3] = value;
    value = (int)((mrs485RxBuffer[43] & 0x00FF)<<8)|(mrs485RxBuffer[44] & 0x00FF);
    cfgADCp[3] = value;
    value = (int)((mrs485RxBuffer[45] & 0x00FF)<<8)|(mrs485RxBuffer[46] & 0x00FF);
    cfgADCs[3] = value;
    value = (int)((mrs485RxBuffer[47] & 0x00FF)<<8)|(mrs485RxBuffer[48] & 0x00FF);
    cfgADCf[3] = value; 

    value = (int)((mrs485RxBuffer[49] & 0x00FF)<<8)|(mrs485RxBuffer[50] & 0x00FF);
    cfgLogicIns[0] = value;
    value = (int)((mrs485RxBuffer[51] & 0x00FF)<<8)|(mrs485RxBuffer[52] & 0x00FF);
    cfgLogicIns[1] = value;
    value = (int)((mrs485RxBuffer[53] & 0x00FF)<<8)|(mrs485RxBuffer[54] & 0x00FF);
    cfgLogicIns[2] = value;

    value = (int)((mrs485RxBuffer[55] & 0x00FF)<<8)|(mrs485RxBuffer[56] & 0x00FF);
    cfgRpm = value;
    value = (int)((mrs485RxBuffer[57] & 0x00FF)<<8)|(mrs485RxBuffer[58] & 0x00FF);
    cfgPres = value;

     // Data
    EEPROM.write(EEPROM_ADD_MODBUS_ID, (byte)cfgMbId);

    eeprom_value_lo =  cfgADCm[0] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC0_M_LO, eeprom_value_lo);
    eeprom_value_hi = ( cfgADCm[0] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC0_M_HI, eeprom_value_hi);
    eeprom_value_lo = cfgADCb[0] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC0_B_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgADCb[0] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC0_B_HI, eeprom_value_hi);
    eeprom_value_lo = cfgADCp[0] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC0_P_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgADCp[0] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC0_P_HI, eeprom_value_hi);
    EEPROM.write(EEPROM_ADD_ADC0_S,  cfgADCs[0]);
    EEPROM.write(EEPROM_ADD_ADC0_F,  cfgADCf[0]);

    eeprom_value_lo =  cfgADCm[1] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC1_M_LO, eeprom_value_lo);
    eeprom_value_hi = ( cfgADCm[1] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC1_M_HI, eeprom_value_hi);
    eeprom_value_lo = cfgADCb[1] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC1_B_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgADCb[1] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC1_B_HI, eeprom_value_hi);
    eeprom_value_lo = cfgADCp[1] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC1_P_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgADCp[1] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC1_P_HI, eeprom_value_hi);
    EEPROM.write(EEPROM_ADD_ADC1_S,  cfgADCs[1]);
    EEPROM.write(EEPROM_ADD_ADC1_F,  cfgADCf[1]);

    eeprom_value_lo =  cfgADCm[2] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC2_M_LO, eeprom_value_lo);
    eeprom_value_hi = ( cfgADCm[2] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC2_M_HI, eeprom_value_hi);
    eeprom_value_lo = cfgADCb[2] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC2_B_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgADCb[2] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC2_B_HI, eeprom_value_hi);
    eeprom_value_lo = cfgADCp[2] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC2_P_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgADCp[2] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC2_P_HI, eeprom_value_hi);
    EEPROM.write(EEPROM_ADD_ADC2_S,  cfgADCs[2]);
    EEPROM.write(EEPROM_ADD_ADC2_F,  cfgADCf[2]);

    eeprom_value_lo =  cfgADCm[3] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC3_M_LO, eeprom_value_lo);
    eeprom_value_hi = ( cfgADCm[3] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC3_M_HI, eeprom_value_hi);
    eeprom_value_lo = cfgADCb[3] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC3_B_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgADCb[3] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC3_B_HI, eeprom_value_hi);
    eeprom_value_lo = cfgADCp[3] & 0x00FF;
    EEPROM.write(EEPROM_ADD_ADC3_P_LO, eeprom_value_lo);
    eeprom_value_hi = (cfgADCp[3] & 0xFF00)>>8;
    EEPROM.write(EEPROM_ADD_ADC3_P_HI, eeprom_value_hi);
    EEPROM.write(EEPROM_ADD_ADC3_S,  cfgADCs[3]);
    EEPROM.write(EEPROM_ADD_ADC3_F,  cfgADCf[3]);

    EEPROM.write(EEPROM_ADD_LOGIC_IN0, cfgLogicIns[0]);
    EEPROM.write(EEPROM_ADD_LOGIC_IN1, cfgLogicIns[1]);
    EEPROM.write(EEPROM_ADD_LOGIC_IN2, cfgLogicIns[2]);

    EEPROM.write(EEPROM_ADD_RPM,   cfgRpm);
    EEPROM.write(EEPROM_ADD_PRESS, cfgPres);
    
    mrs485TxBuffer[0] = (char)address;
    mrs485TxBuffer[1] = (char)MB_FUNC_WRITE_MULTIPLE_REGISTERS;
    mrs485TxBuffer[2] = mrs485RxBuffer[2];
    mrs485TxBuffer[3] = mrs485RxBuffer[3];
    mrs485TxBuffer[4] = mrs485RxBuffer[4];
    mrs485TxBuffer[5] = mrs485RxBuffer[5];
    
    // Num Bytes
    mrs485TxNumBytes = 8;
  }
  // Expection
  else
  {
    mrs485TxBuffer[0] = (char)address;
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

void _mbReadHolding(char address)
{
  int addr, nregs;

  addr  = (int)((mrs485RxBuffer[2] & 0x00FF)<<8)|(mrs485RxBuffer[3] & 0x00FF);
  nregs = (int)((mrs485RxBuffer[4] & 0x00FF)<<8)|(mrs485RxBuffer[5] & 0x00FF);

  // OUTs 
  if ((addr == MB_ADD_OUTS) && (nregs == MB_NREG_OUTS))
  {
    mrs485TxBuffer[0] = (char)address;
    mrs485TxBuffer[1] = (char)MB_FUNC_READ_HOLDING_REGISTER;
    mrs485TxBuffer[2] = MB_NREG_OUTS*2;
    
    mrs485TxBuffer[3] = 0x00;
    mrs485TxBuffer[4] = OutDig[0];
    mrs485TxBuffer[5] = 0x00;
    mrs485TxBuffer[6] = OutDig[1];
    mrs485TxBuffer[7] = 0x00;
    mrs485TxBuffer[8] = OutDig[2];
    
    // Num Bytes
    mrs485TxNumBytes = mrs485TxBuffer[2] + 5;
  }
  // CFGs 
  else if ((addr == MB_ADD_CFG) && (nregs == MB_NREG_CFG))
  {
    mrs485TxBuffer[0] = (char)address;
    mrs485TxBuffer[1] = (char)MB_FUNC_READ_HOLDING_REGISTER;
    mrs485TxBuffer[2] = MB_NREG_CFG*2;
    
    mrs485TxBuffer[3]  = 0x00;
    mrs485TxBuffer[4]  = (byte)(cfgMbId & 0x00FF);

    mrs485TxBuffer[5]  = (cfgADCm[0] & 0xFF00)>>8;
    mrs485TxBuffer[6]  =  cfgADCm[0] & 0x00FF;
    mrs485TxBuffer[7]  = (cfgADCb[0] & 0xFF00)>>8;
    mrs485TxBuffer[8]  =  cfgADCb[0] & 0x00FF;
    mrs485TxBuffer[9]  = (cfgADCp[0] & 0xFF00)>>8;
    mrs485TxBuffer[10] =  cfgADCp[0] & 0x00FF;
    mrs485TxBuffer[11] = (cfgADCs[0] & 0xFF00)>>8;
    mrs485TxBuffer[12] =  cfgADCs[0] & 0x00FF;
    mrs485TxBuffer[13] = (cfgADCf[0] & 0xFF00)>>8;
    mrs485TxBuffer[14] =  cfgADCf[0] & 0x00FF;

    mrs485TxBuffer[15] = (cfgADCm[1] & 0xFF00)>>8;
    mrs485TxBuffer[16] =  cfgADCm[1] & 0x00FF;
    mrs485TxBuffer[17] = (cfgADCb[1] & 0xFF00)>>8;
    mrs485TxBuffer[18] =  cfgADCb[1] & 0x00FF;
    mrs485TxBuffer[19] = (cfgADCp[1] & 0xFF00)>>8;
    mrs485TxBuffer[20] =  cfgADCp[1] & 0x00FF;
    mrs485TxBuffer[21] = (cfgADCs[1] & 0xFF00)>>8;
    mrs485TxBuffer[22] =  cfgADCs[1] & 0x00FF;
    mrs485TxBuffer[23] = (cfgADCf[1] & 0xFF00)>>8;
    mrs485TxBuffer[24] =  cfgADCf[1] & 0x00FF;

    mrs485TxBuffer[25] = (cfgADCm[2] & 0xFF00)>>8;
    mrs485TxBuffer[26] =  cfgADCm[2] & 0x00FF;
    mrs485TxBuffer[27] = (cfgADCb[2] & 0xFF00)>>8;
    mrs485TxBuffer[28] =  cfgADCb[2] & 0x00FF;
    mrs485TxBuffer[29] = (cfgADCp[2] & 0xFF00)>>8;
    mrs485TxBuffer[30] =  cfgADCp[2] & 0x00FF;
    mrs485TxBuffer[31] = (cfgADCs[2] & 0xFF00)>>8;
    mrs485TxBuffer[32] =  cfgADCs[2] & 0x00FF;
    mrs485TxBuffer[33] = (cfgADCf[2] & 0xFF00)>>8;
    mrs485TxBuffer[34] =  cfgADCf[2] & 0x00FF;
    
    mrs485TxBuffer[35] = (cfgADCm[3] & 0xFF00)>>8;
    mrs485TxBuffer[36] =  cfgADCm[3] & 0x00FF;
    mrs485TxBuffer[37] = (cfgADCb[3] & 0xFF00)>>8;
    mrs485TxBuffer[38] =  cfgADCb[3] & 0x00FF;
    mrs485TxBuffer[39] = (cfgADCp[3] & 0xFF00)>>8;
    mrs485TxBuffer[40] =  cfgADCp[3] & 0x00FF;
    mrs485TxBuffer[41] = (cfgADCs[3] & 0xFF00)>>8;
    mrs485TxBuffer[42] =  cfgADCs[3] & 0x00FF;
    mrs485TxBuffer[43] = (cfgADCf[3] & 0xFF00)>>8;
    mrs485TxBuffer[44] =  cfgADCf[3] & 0x00FF;

    mrs485TxBuffer[45] = 0x00;
    mrs485TxBuffer[46] = (byte)(cfgLogicIns[0] & 0x00FF);
    mrs485TxBuffer[47] = 0x00;
    mrs485TxBuffer[48] = (byte)(cfgLogicIns[1] & 0x00FF);
    mrs485TxBuffer[49] = 0x00;
    mrs485TxBuffer[50] = (byte)(cfgLogicIns[2] & 0x00FF);

    mrs485TxBuffer[51] = 0x00;
    mrs485TxBuffer[52] = (byte)(cfgRpm & 0x00FF);

    mrs485TxBuffer[53] = 0x00;
    mrs485TxBuffer[54] = (byte)(cfgPres & 0x00FF);

    // Num Bytes
    mrs485TxNumBytes = mrs485TxBuffer[2] + 5;
  }
  // Expection
  else
  {
	  mrs485TxBuffer[0] = (char)address;
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

void _mbReadInput(char address)
{
  int addr, nregs;

  addr  = (int)((mrs485RxBuffer[2] & 0x00FF)<<8)|(mrs485RxBuffer[3] & 0x00FF);
  nregs = (int)((mrs485RxBuffer[4] & 0x00FF)<<8)|(mrs485RxBuffer[5] & 0x00FF);

  // Control 
  if ((addr == MB_ADD_CTR)  && (nregs == MB_NREG_CTR))
  { 
    mrs485TxBuffer[0] = (char)address;
    mrs485TxBuffer[1] = (char)MB_FUNC_READ_INPUT_REGISTER;
    mrs485TxBuffer[2] = MB_NREG_CTR*2;

    mrs485TxBuffer[3]  = (char)((EngineRpm & 0xFF00)>>8);
    mrs485TxBuffer[4]  = (char)(EngineRpm & 0x00FF);
    mrs485TxBuffer[5]  = (char)((EnginePres & 0xFF00)>>8);
    mrs485TxBuffer[6]  = (char)(EnginePres & 0x00FF);
    
    // Num Bytes
    mrs485TxNumBytes = mrs485TxBuffer[2] + 5;
  }
  // INs
  else if ((addr == MB_ADD_INS)  && (nregs == MB_NREG_INS))
  { 
    mrs485TxBuffer[0] = (char)address;
    mrs485TxBuffer[1] = (char)MB_FUNC_READ_INPUT_REGISTER;
    mrs485TxBuffer[2] = MB_NREG_INS*2;

    mrs485TxBuffer[3] = 0x00;
    mrs485TxBuffer[4] = InDig[0];
    mrs485TxBuffer[5] = 0x00;
    mrs485TxBuffer[6] = InDig[1];
    mrs485TxBuffer[7] = 0x00;
    mrs485TxBuffer[8] = InDig[1];
    
    // Num Bytes
    mrs485TxNumBytes = mrs485TxBuffer[2] + 5;
  }
  // OUTs
  else if ((addr == MB_ADD_OUTS)  && (nregs == MB_NREG_OUTS))
  {
    mrs485TxBuffer[0] = (char)address;
    mrs485TxBuffer[1] = (char)MB_FUNC_READ_INPUT_REGISTER;
    mrs485TxBuffer[2] = MB_NREG_OUTS*2;
    
    mrs485TxBuffer[3] = 0x00;
    mrs485TxBuffer[4] = OutDig[0];
    mrs485TxBuffer[5] = 0x00;
    mrs485TxBuffer[6] = OutDig[1];
    mrs485TxBuffer[7] = 0x00;
    mrs485TxBuffer[8] = OutDig[2];
    
    // Num Bytes
    mrs485TxNumBytes = mrs485TxBuffer[2] + 5;
  }
  // ADCs
  else if ((addr == MB_ADD_ADC)  && (nregs == MB_NREG_ADC))
  {
    mrs485TxBuffer[0] = (char)address;
    mrs485TxBuffer[1] = (char)MB_FUNC_READ_INPUT_REGISTER;
    mrs485TxBuffer[2] = MB_NREG_ADC*2;
    
    mrs485TxBuffer[3]  = (char)((AdcDig[0] & 0xFF00)>>8);
    mrs485TxBuffer[4]  = (char)(AdcDig[0] & 0x00FF);
    mrs485TxBuffer[5]  = (char)((AdcDig[1] & 0xFF00)>>8);
    mrs485TxBuffer[6]  = (char)(AdcDig[1] & 0x00FF);
    mrs485TxBuffer[7]  = (char)((AdcDig[2] & 0xFF00)>>8);
    mrs485TxBuffer[8]  = (char)(AdcDig[2] & 0x00FF);
    mrs485TxBuffer[9]  = (char)((AdcDig[3] & 0xFF00)>>8);
    mrs485TxBuffer[10] = (char)(AdcDig[3] & 0x00FF);
    
    // Num Bytes
    mrs485TxNumBytes = mrs485TxBuffer[2] + 5; 
  }
  // Pulsos
  else if ((addr == MB_ADD_PULS)  && (nregs == MB_NREG_PULS))
  {
    mrs485TxBuffer[0] = (char)address;
    mrs485TxBuffer[1] = (char)MB_FUNC_READ_INPUT_REGISTER;
    mrs485TxBuffer[2] = MB_NREG_PULS*2;

    #if ( _USE_INT0_  == 1)
    mrs485TxBuffer[3] = (char)((RpmCounterD2 & 0xFF00)>>8);
    mrs485TxBuffer[4] = (char)(RpmCounterD2 & 0x00FF);
    #else
    mrs485TxBuffer[3] = 0x00;
    mrs485TxBuffer[4] = 0x00;
    #endif

    #if ( _USE_INT1_  == 1)
    mrs485TxBuffer[5] = (char)((RpmCounterD3 & 0xFF00)>>8);
    mrs485TxBuffer[6] = (char)(RpmCounterD3 & 0x00FF);
    #else
    mrs485TxBuffer[5] = 0x00;
    mrs485TxBuffer[6] = 0x00;
    #endif
    
    // Num Bytes
    mrs485TxNumBytes = mrs485TxBuffer[2] + 5;
  }
  // Expection
  else
  {
    mrs485TxBuffer[0] = (char)address;
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

void _mbSlaveID(char address)
{
  mrs485TxBuffer[0] = (char)address;
  mrs485TxBuffer[1] = (char)MB_FUNC_OTHER_REPORT_SLAVEID;
  mrs485TxBuffer[2] = 0x18; // 18

  // DES
  mrs485TxBuffer[3]  = (char)PROJECT[0];
  mrs485TxBuffer[4]  = (char)PROJECT[1];
  mrs485TxBuffer[5]  = (char)PROJECT[2];
  mrs485TxBuffer[6]  = (char)PROJECT[3];
  mrs485TxBuffer[7]  = (char)PROJECT[4];
  mrs485TxBuffer[8]  = (char)PROJECT[5];
  mrs485TxBuffer[9]  = (char)PROJECT[6];
  mrs485TxBuffer[10] = (char)PROJECT[7];
  mrs485TxBuffer[11] = (char)'-';
  
  // Comp date
  mrs485TxBuffer[12] = (char)compdate[0]; //D
  mrs485TxBuffer[13] = (char)compdate[1]; //e
  mrs485TxBuffer[14] = (char)compdate[2]; //c
  mrs485TxBuffer[15] = (char)'/';
  mrs485TxBuffer[16] = (char)compdate[4]; //1
  mrs485TxBuffer[17] = (char)compdate[5]; //2
  mrs485TxBuffer[18] = (char)'/';
  mrs485TxBuffer[19] = (char)compdate[9]; //2
  mrs485TxBuffer[20] = (char)compdate[10];//2
  mrs485TxBuffer[21] = (char)'-';
  // Comp time
  mrs485TxBuffer[22] = (char)comptime[0]; //h
  mrs485TxBuffer[23] = (char)comptime[1]; //h
  mrs485TxBuffer[24] = (char)comptime[2]; //:
  mrs485TxBuffer[25] = (char)comptime[3]; //m
  mrs485TxBuffer[26] = (char)comptime[4]; //m
  mrs485TxBuffer[27] = (char)comptime[5]; //:
  mrs485TxBuffer[28] = (char)comptime[6]; //s
  mrs485TxBuffer[29] = (char)comptime[7]; //s

  mrs485TxNumBytes = mrs485TxBuffer[2] + 5;

  // Crc
  _mbCRC();
  mrs485TxBuffer[27] = mbCRC[0];
  mrs485TxBuffer[28] = mbCRC[1];

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

int _mbN1(char address)
{
  int error = 0;

  if (mrs485RxBuffer[0] == (char)address)
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
