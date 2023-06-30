#include "header.h"
#include <stdbool.h>

//uchar hello[] = "hello";

void Setup(){
    Init_MCU();
}

void Loop(){
    DelayMsec(500);
    UART1_SendData(RADAR_GET_DATA,RADAR_GET_DATA_LEN);
}


int main(void)
{
    Setup();
    

    while(1){
        Loop();
    }
    return 0;
}
