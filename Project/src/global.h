#ifndef GLOBAL
#define GLOBAL

#include <pic32m-libs/p32xxxx.h>

// Port definitions
#define Button PORTDbits.RD6
#define LED LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2

// type definitions
typedef unsigned char uchar;


// for radar UART
#define RADAR_GET_STATUS_LEN 6
#define RADAR_GET_DATA_LEN 14
extern uchar RADAR_GET_STATUS[RADAR_GET_STATUS_LEN];
extern uchar RADAR_GET_DATA[RADAR_GET_DATA_LEN];

#endif // !GLOBAL
