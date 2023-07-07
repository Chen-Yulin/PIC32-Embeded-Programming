#ifndef UART
#define UART

#include "global.h"

typedef struct TargetInfo{
    bool hasTarget;
    uchar distance;
    uchar pitch;
    uchar yaw;
    uchar closingRate;
} TargetInfo;

typedef struct RadarInfo{
    uchar targetNum;
    TargetInfo targets[RADAR_MAX_TARGET];
} RadarInfo;

extern uchar RADAR_GET_STATUS[RADAR_GET_STATUS_LEN];
extern uchar RADAR_GET_DATA[RADAR_GET_DATA_LEN];
extern RadarInfo radarInfo;
extern uchar RadarInfo_Buffer[RADAR_BUFFER_MAX_LEN];
extern uchar RadarInfo_Buffer_Index;
extern uchar RadarInfo_Buffer_ExpectLen;

void U2_Print(char *str);
void U2_Print_uchar(uchar c);
void U2_Print_float(float c);

void Print_RadarInfo(RadarInfo info);
void Print_Turrent_Para(Turret_para turrent_para);
void Print_Vector3D(Vector3D vector);

void Init_RadarInfo();
void Update_RadarInfo();
void UART1_SendData(unsigned char *data, int len);
void UART2_SendData(unsigned char *data, int len);


#endif // !UART
