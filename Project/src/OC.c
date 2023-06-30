# include "OC.h"

void Enable_PWM1(){
    T2CONSET = 0x8000;//start timer 2
    OC1CONSET = 0x8000;//start oc1
}
void Disable_PWM1(){
    T2CONCLR = 0x8000;//start timer 2
    OC1CONCLR = 0x8000;//stop oc1
}

void Set_PWM1R(uchar val){
    OC1R = val;
}

void Set_PWM1RS(uchar val){
    OC1RS = val;
}
