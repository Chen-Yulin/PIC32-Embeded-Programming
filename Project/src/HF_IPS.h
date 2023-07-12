#ifndef HF_IPS_H
#define HF_IPS_H

#include "global.h"
#include "Radar.h"
#include "UART.h"


#define IPS_BLACK 0
#define IPS_GREEN 29
#define IPS_YELLOW 31


void Draw_RadarTarget(TargetInfo info);

void IPS_BOXF(uint x, uint y, uint w, uint h, uint color);
void IPS_CIR(uint x, uint y, uint r, uint color);
void IPS_LINE(uint xs, uint ys, uint xe, uint ye, uint color);
void IPS_REPAIR();

#endif // !HF_IPS_H

