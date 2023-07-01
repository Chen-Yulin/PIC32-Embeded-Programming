#ifndef GLOBAL
#define GLOBAL

#include <pic32m-libs/p32xxxx.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

// for radar data
#define RADAR_MAX_TARGET 10
#define RADAR_BUFFER_MAX_LEN 94 // 14 + RADAR_MAX_TARGET*8

// global tool
char * uchar_2_str(uchar c, char * str);



#endif // !GLOBAL
