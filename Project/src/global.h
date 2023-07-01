#ifndef GLOBAL
#define GLOBAL

#include <pic32m-libs/p32xxxx.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// type definitions
typedef unsigned char uchar;
typedef uint16_t uint;

// Port definitions
#define Button PORTDbits.RD6
#define LED LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2
#define TFT_DC LATEbits.LATE7

// for radar UART
#define RADAR_GET_STATUS_LEN 6
#define RADAR_GET_DATA_LEN 14

// for radar data
#define RADAR_MAX_TARGET 10
#define RADAR_BUFFER_MAX_LEN 94 // 14 + RADAR_MAX_TARGET*8

// for TFT Displayer
#define TFT_WIDTH 240
#define TFT_HEIGHT 320

// global tool
char * uchar_2_str(uchar c, char * str);



#endif // !GLOBAL
