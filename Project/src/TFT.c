#include "TFT.h"
#include "SPI.h"

void TFT_WR_REG(uint regval){
    DC_ON;
    SPI1_Send_u16(regval);
}

void TFT_WR_DATA8(uchar data){
    DC_OFF;
    SPI1_Send_u8(data);
}


void TFT_WR_DATA16(uint data){
    DC_OFF;
    SPI1_Send_u16(data);
}

void TFT_WriteReg(uint TFT_Reg, uint TFT_RegValue){
    TFT_WR_REG(TFT_Reg);
    TFT_WR_DATA16(TFT_RegValue);
}


