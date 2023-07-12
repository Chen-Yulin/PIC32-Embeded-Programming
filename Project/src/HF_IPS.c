#include "HF_IPS.h"

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
