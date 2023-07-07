#ifndef UART
#define UART

#include "global.h"
#include "Radar.h"

void UART1_SendData(unsigned char *data, int len);
void UART2_SendData(unsigned char *data, int len);

void U2_Print(char *str);
void U2_Print_uchar(uchar c);
void U2_Print_float(float c);

void Print_RadarInfo(RadarInfo info);
void Print_Turrent_Para(Turret_para turrent_para);
void Print_Vector3D(Vector3D vector);



#endif // !UART
