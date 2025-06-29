
#include <stdio.h>

int initBram();
void readWheelPositionFromBram(int32_t* position_incremental_enc, int32_t* position_bissc_enc);
void writeFfbMagnitudeToBram(int16_t magnitude);
void writeRotationToBram(uint8_t rotation);

