#include "global.h"
//#include "Timer.h"
//#include "OC.h"
#include "init.h"
#include "UART.h"
#include "TFT.h"
#include "Radar.h"
#include <math.h>
#include "SPI.h"
#include "Timer.h"
#include "OC.h"
#include "Servo.h"
#include "HF_IPS.h"
//#include "SPI.h"

Turret_para turret_para;

uchar choosenTargetID;

bool TWS = false;
bool TWS_buttonDown = false;

// use radar target info to calculate the position of target with respect to turrent
Vector3 Get_Target_Position(TargetInfo info){
    Vector3 target_Position;
    char pitch = 90-info.pitch;
    float distance_xz = (float)info.distance * cos(M_PI/180 * pitch);
    target_Position.x = distance_xz * cos(M_PI/180 * info.yaw);
    target_Position.z = distance_xz * sin(M_PI/180 * info.yaw);
    target_Position.y = (float)info.distance * sin(M_PI/180 * pitch); // refer to LD6001-60G instruction for details of implementation
    return target_Position;
}

void Update_FireControl_Direct(Vector3 lockedTarget_Position){
    Vector3 realTarget_Position = {lockedTarget_Position.x-TURRENT_X_OFFSET, 
                                    lockedTarget_Position.y-TURRENT_Y_OFFSET, 
                                    lockedTarget_Position.z-TURRENT_Z_OFFSET};  // calculate the target position with respect to turret
    //Print_Vector3D(realTarget_Position);

    float distance_xyz = sqrt(pow(realTarget_Position.x, 2) + pow(realTarget_Position.y, 2) + pow(realTarget_Position.z, 2));
    float distance_xz = sqrt(pow(realTarget_Position.x, 2) + pow(realTarget_Position.z, 2));

    turret_para.pitch = 180/M_PI * atan(realTarget_Position.y/distance_xz); // up: y positive
    turret_para.yaw = 90 - 180/M_PI * atan(realTarget_Position.x/realTarget_Position.z); // forward: z positive; right: x positive; anti-clockwise: 0~180 yaw angle
}

void Update_Turret_Servo(){
    Set_Servo1(turret_para.yaw);
    Set_Servo2(turret_para.pitch+90);
}

void Init_Turret_Servo(){
    Enable_Servo1();
    Set_Servo1(90);
    Enable_Servo2();
    Set_Servo2(90);
}

void SwitchTWS(){
    // wait for the previous command to finish execution
    IPS_CHECKBUSY();
    TWS = !TWS;
    if (TWS) {
        U2_Print("SET_TXT(0,'TWS');\r\n");
    }else{
        U2_Print("SET_TXT(0,'RWS');\r\n");
    }
}


void Setup(){
    Init_MCU();
    Init_Turret_Servo();
    IPS_RESET();
}

void Loop(){
    if (PORTDbits.RD6 == 0) {
        IPS_RESET();
        TWS = false;
    }

    if (PORTDbits.RD7 == 0 && !TWS_buttonDown) {
        SwitchTWS();
        TWS_buttonDown = true;
    }else if(PORTDbits.RD7 == 1 && TWS_buttonDown){
        TWS_buttonDown = false;
    }
    DelayMsec(20);
    SPI1_Print_uchar(radarInfo.targetNum);
    SPI1_Print("\r\n");
    

    // do something on radar when the radar information is updated
    if (RadarInfo_Updated) {
        bool hasCommand = false;
        //SPI1_Print_RadarInfo(tmp_info);
        
        //first clear existing spot on radar
        //U2_Print("BOXF(11,11,228,248,0);");
        hasCommand = IPS_CLR_ALL_TARGET();
        SPI1_Print_uchar(radarInfo.targetNum);
        // update new spot on screen
        for (uchar id = 0; id<10; id++) {
            if (radarInfo.targets[id].hasTarget) {
                Update_FireControl_Direct(Get_Target_Position(radarInfo.targets[id]));
                //SPI1_Print_Turrent_Para(turret_para);
                IPS_DRAW_TARGET(radarInfo.targets[id]);
                hasCommand = true;
            }
        }

        // control turret
        Update_Turret_Servo();
        //radarInfo = tmp_info;
        RadarInfo_Updated = false;
        if (hasCommand) {
            IPS_CMD_EXECUTE();  // the execution command is sent, the commands will take some time for execution
        }
    }

}


int main(void)
{
    Setup();
    while(1){
        Loop();
    }
    return 0;
}
