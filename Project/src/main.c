#include "global.h"
#include "Timer.h"
//#include "OC.h"
#include "init.h"
#include "UART.h"
#include "TFT.h"
//#include "SPI.h"


void Setup(){
    Init_MCU();
    Init_RadarInfo();
    TFT_Init();
    LED3 = 0;
    //SPI1_Send_u16(16);
}

void Loop(){
    //LED3 = !PORTDbits.RD2;
    TFT_Clear(GREEN);
    DelayMsec(500);
    U2_Print("targetNum:  ");
    U2_Print_uchar(radarInfo.targetNum);
    U2_Print("\r\n");
    for (uchar i = 0; i < 10; i++) {
        if (radarInfo.targets[i].hasTarget) {
            U2_Print("  targetID:  ");
            U2_Print_uchar(i);
            U2_Print("\r\n    Distance:  ");
            U2_Print_uchar(radarInfo.targets[i].distance);
            U2_Print("\r\n    Yaw:  ");
            U2_Print_uchar(radarInfo.targets[i].yaw);
            U2_Print("\r\n");
        }
    }
    /*
    if (radarInfo.targetNum > 0) {
        LED = 1;
    }else{
        LED = 0;
    }*/

}


int main(void)
{
    Setup();
    

    while(1){
        Loop();
    }
    return 0;
}
