#include "HF_IPS.h"
#include "SPI.h"

uchar ScreenOK_Buffer[4];
uchar ScreenOK_Index = 0;


void IPS_BOXF(uint x, uint y, uint w, uint h, uint color){
    U2_Print("BOXF(");
    U2_Print_uint(x-w/2);
    U2_Print(",");
    U2_Print_uint(y-h/2);
    U2_Print(",");
    U2_Print_uint(x+w/2);
    U2_Print(",");
    U2_Print_uint(y+h/2);
    U2_Print(",");
    U2_Print_uint(color);
    U2_Print(");\r\n");
}

void IPS_CIR(uint x, uint y, uint r, uint color){
    U2_Print("CIR(");
    U2_Print_uint(x);
    U2_Print(",");
    U2_Print_uint(y);
    U2_Print(",");
    U2_Print_uint(r);
    U2_Print(",");
    U2_Print_uint(color);
    U2_Print(");\r\n");
}

void IPS_LINE(uint xs, uint ys, uint xe, uint ye, uint color){
    U2_Print("PL(");
    U2_Print_uint(xs);
    U2_Print(",");
    U2_Print_uint(ys);
    U2_Print(",");
    U2_Print_uint(xe);
    U2_Print(",");
    U2_Print_uint(ye);
    U2_Print(",");
    U2_Print_uint(color);
    U2_Print(");\r\n");
}


//ISF for UART2 RX
#pragma interrupt U2_RX_Interrupt ipl1 vector 32
void U2_RX_Interrupt(void){
    if (IFS1bits.U2RXIF == 1) {
        // read the data
        uchar data;
        while (U2STAbits.URXDA) {
            data = U2RXREG;
            ScreenOK_Buffer[ScreenOK_Index] = data;
            
            ScreenOK_Index ++;
            if(ScreenOK_Index == 4){
                // update radar info using data in buffer
                ScreenExcution_OK = true;
                // reset buffer
                ScreenOK_Index = 0;
            }

        }
        IFS1bits.U2RXIF = 0; // clear the interrupt flag
    }else{
        // not a U2 RX interrupt
        return;
    }
}
