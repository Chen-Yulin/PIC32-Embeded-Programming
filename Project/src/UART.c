#include "UART.h"

// some standard command message
uchar RADAR_GET_STATUS[] = {0x44,0x11,0x00,0x00,0x55,0x4B};
uchar RADAR_GET_DATA[] = {  0x44,
                            0x62,
                            0x08,
                            0x00, 
                            0x10,   // normal sensitivity
                            0x00, 
                            0x00, 
                            0x00, 
                            0x00, 
                            0x00, 
                            0x00, 
                            0x00, 
                            0xBE,   //checksum   
                            0x4B};

// send data using UART1
void UART1_SendData(uchar *data, int len){
    int i = 0;
    for(i = 0; i < len; i++){
        while(U1STAbits.UTXBF);// wait until the transmit buffer is not full
        U1TXREG = data[i];
    }
}
