#include "SPI.h"

void SPI1_Send_u8(uchar data){
    while(SPI1STATbits.SPITBF);
    SPI1BUF = data;
    while (SPI1STATbits.SPIBUSY);
}

void SPI1_Send_u16(uint data){
    // big endian transmission
    SPI1_Send_u8(data >> 8);
    SPI1_Send_u8((uchar)data&0xFF);
}
