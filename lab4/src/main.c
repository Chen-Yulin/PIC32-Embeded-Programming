#include "global.h"
#include "header.h"
#include <stdbool.h>

int main(void)
{
    InitMCU();

    int period = 5;
    float dutyPercent = 0;
    bool changeDirection = 1;//1 for up, 0 for down
    int pressed = 0;
    
    while(1){
        if (Button == 0 && pressed == 0) {
            pressed = 70;
            if (dutyPercent > 0.999) {
                changeDirection = 0;
            }else if (dutyPercent < 0.001) {
                changeDirection = 1;
            }
            
            if (changeDirection == 1) {
                dutyPercent += 0.2;
            }else{
                dutyPercent -= 0.2;
            }
        }else{
            pressed -=1;
            if (pressed < 0) {
                pressed = 0;
            }
        }
        DelayMsec((int)(period*(1-dutyPercent)));
        if (dutyPercent > 0.001) {
            LED = 1;
        }
        DelayMsec((int)(period*dutyPercent));
        if (dutyPercent < 0.999) {
            LED = 0;
        }
        
        if (changeDirection == 0) {
            LED2 = 1;
            LED3 = 0;
        }else{
            LED2 = 0;
            LED3 = 1;

        }

    }
    return 0;
}
