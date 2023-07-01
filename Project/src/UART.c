#include "UART.h"

// some standard command message
uchar RADAR_GET_STATUS[] = {0x44,0x11,0x00,0x00,0x55,0x4B};
uchar RADAR_GET_DATA[] = {  0x44,
                            0x62,
                            0x08,
                            0x00, 
                            0x10,   // normal sensitivity
                            0x00, 
                            0x00, 
                            0x00, 
                            0x00, 
                            0x00, 
                            0x00, 
                            0x00, 
                            0xBE,   //checksum   
                            0x4B};

RadarInfo radarInfo;
uchar RadarInfo_Buffer[RADAR_BUFFER_MAX_LEN];
uchar RadarInfo_Buffer_Index = 0;
uchar RadarInfo_Buffer_ExpectLen = 14;

void Init_RadarInfo(){
    radarInfo.targetNum = 0;
    for(int i = 0; i < RADAR_MAX_TARGET; i++){
        radarInfo.targets[i] = (TargetInfo){false, 0, 0, 0, 0};
    }
}

void Update_RadarInfo(){
    //U2_Print((char *)&RadarInfo_Buffer_ExpectLen);
    radarInfo.targetNum = RadarInfo_Buffer[5];
    bool hasTarget[10] = {0,0,0,0,0,0,0,0,0,0};
    for(int i = 0; i < radarInfo.targetNum; i++){
        uchar target_head = 12+i*8;
        int id = RadarInfo_Buffer[target_head];
        hasTarget[id] = 1;
        radarInfo.targets[id].hasTarget = true;
        radarInfo.targets[id].distance = RadarInfo_Buffer[target_head+1];
        radarInfo.targets[id].pitch = RadarInfo_Buffer[target_head+2];
        radarInfo.targets[id].yaw = RadarInfo_Buffer[target_head+3];
        radarInfo.targets[id].closingRate = 0;
    }
    //clear unused id
    for (int i = 0; i < 10; i++) {
        if (!hasTarget[i]) {
            radarInfo.targets[i].hasTarget = false;
        }
    }

}

// send data using UART1
void UART1_SendData(uchar *data, int len){
    int i = 0;
    for(i = 0; i < len; i++){
        while(U1STAbits.UTXBF);// wait until the transmit buffer is not full
        U1TXREG = data[i];
    }
}
void UART2_SendData(uchar *data, int len){
    int i = 0;
    for(i = 0; i < len; i++){
        while(U2STAbits.UTXBF);// wait until the transmit buffer is not full
        U2TXREG = data[i];
    }
}

void U2_Print(char *str){
    int len = strlen(str);
    UART2_SendData((uchar *)str, len);
}
void U2_Print_uchar(uchar c){
    char str[4];
    uchar_2_str(c,str);
    int len = strlen(str);
    UART2_SendData((uchar *)str, len);
}

//ISF for UART1 RX
#pragma interrupt U1_RX_Interrupt ipl1 vector 24
void U1_RX_Interrupt(void){
    //U2_Print("get\r\n");
    if (IFS0bits.U1RXIF == 1) {
        // read the data
        uchar data;
        while (U1STAbits.URXDA) {
            data = U1RXREG;
            RadarInfo_Buffer[RadarInfo_Buffer_Index] = data;
            
            if (RadarInfo_Buffer_Index == 5) {
                RadarInfo_Buffer_ExpectLen = 14 + data * 8;
            }

            // when a full message is received, update radar info and reset buffer
            RadarInfo_Buffer_Index ++;
            if(RadarInfo_Buffer_Index == RadarInfo_Buffer_ExpectLen){
                // update radar info using data in buffer
                Update_RadarInfo();

                // reset buffer
                RadarInfo_Buffer_Index = 0;
                RadarInfo_Buffer_ExpectLen = 14;
            }

        }
        IFS0bits.U1RXIF = 0; // clear the interrupt flag
    }else{
        // not a U1 RX interrupt
        return;
    }
    


}
