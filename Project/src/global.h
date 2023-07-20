#ifndef GLOBAL
#define GLOBAL

#include <pic32m-libs/p32xxxx.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// math
#define M_PI 3.1415

// global variables
extern bool RadarInfo_Updated;
extern bool ScreenExcution_OK;

// type definitions
typedef unsigned char uchar;
typedef uint16_t uint;


// struct definition
typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    uint x;
    uint y;
} u_Vector2;

typedef struct {
    float x;
    float y;
} f_Vector2;

typedef struct {
    float yaw;
    float pitch;
} Turret_para;

// Port definitions
#define Button PORTDbits.RD6
#define LED0 LATDbits.LATD0
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
#define TFT_WIDTH 10
#define TFT_HEIGHT 20

// for turret
#define TURRENT_X_OFFSET 0
#define TURRENT_Y_OFFSET 0
#define TURRENT_Z_OFFSET 0

// for screen
#define TDC_SPEED 1

// global tool
char * uchar_2_str(uchar c, char * str);
char * float_2_str(float i, char * str);
char * uint_2_str(uint i, char * str);




#endif // !GLOBAL
