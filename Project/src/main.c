#include "global.h"
#include "Timer.h"
//#include "OC.h"
#include "init.h"
#include "UART.h"
#include "TFT.h"
#include <math.h>
//#include "SPI.h"

Turret_para turrent_para;

uchar choosenTargetID;

// use radar target info to calculate the position of target with respect to turrent
Vector3D Get_Target_Position(TargetInfo info){
    Vector3D target_Position;
    char pitch = 90-info.pitch;
    float distance_xz = (float)info.distance * cos(M_PI/180 * pitch);
    target_Position.x = distance_xz * cos(M_PI/180 * info.yaw);
    target_Position.z = distance_xz * sin(M_PI/180 * info.yaw);
    target_Position.y = (float)info.distance * sin(M_PI/180 * pitch); // refer to LD6001-60G instruction for details of implementation
    return target_Position;
}

void Update_FireControl_Direct(Vector3D lockedTarget_Position){
    Vector3D realTarget_Position = {lockedTarget_Position.x-TURRENT_X_OFFSET, 
                                    lockedTarget_Position.y-TURRENT_Y_OFFSET, 
                                    lockedTarget_Position.z-TURRENT_Z_OFFSET};  // calculate the target position with respect to turret
    Print_Vector3D(realTarget_Position);

    float distance_xyz = sqrt(pow(realTarget_Position.x, 2) + pow(realTarget_Position.y, 2) + pow(realTarget_Position.z, 2));
    float distance_xz = sqrt(pow(realTarget_Position.x, 2) + pow(realTarget_Position.z, 2));

    turrent_para.pitch = 180/M_PI * atan(realTarget_Position.y/distance_xz); // up: y positive
    turrent_para.yaw = 90 - 180/M_PI * atan(realTarget_Position.x/realTarget_Position.z); // forward: z positive; right: x positive; anti-clockwise: 0~180 yaw angle
}


void Setup(){
    Init_MCU();
    Init_RadarInfo();
    TFT_Init();
    LED3 = 0;
    turrent_para.yaw = 90;
    choosenTargetID = 0;
    //SPI1_Send_u16(16);
}

void Loop(){
    //LED3 = !PORTDbits.RD2;
    // do something on radar when the radar information is updated
    if (RadarInfo_Updated) {
        RadarInfo tmp_info;
        tmp_info = radarInfo;
        Print_RadarInfo(tmp_info);
        if (choosenTargetID < 10) {
            uchar id = 0;
            for (id = 0; id<10; id++) {
                if (tmp_info.targets[id].hasTarget) {
                    Update_FireControl_Direct(Get_Target_Position(tmp_info.targets[id]));
                    //Print_Turrent_Para(turrent_para);
                    break;
                }
            }
        }
        RadarInfo_Updated = false;
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
