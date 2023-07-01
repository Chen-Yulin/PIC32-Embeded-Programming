#ifndef TFTHEADER
#define TFTHEADER

#include "global.h"

#define DC_ON TFT_DC = 0 // DC = 0, send command
#define DC_OFF TFT_DC = 1 // DC = 1, send data

void TFT_WR_REG(uint regval);
void TFT_WR_DATA8(uchar data);
void TFT_WR_DATA16(uint data);
void TFT_WriteReg(uint TFT_Reg, uint TFT_RegValue);


#endif // !TFTHEADER
