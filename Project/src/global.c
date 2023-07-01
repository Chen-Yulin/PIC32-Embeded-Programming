#include "global.h"

char Str_Buffer[4];

char * uchar_2_str(uchar c, char * str){
    sprintf(str, "%u", c);
    return str;
}
