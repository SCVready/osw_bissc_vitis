
#include <xbasic_types.h>
#include "steering_wheel_config.h"

int usbInit();
int usbSendPositionEnp1(int32_t position);
int usbReceiveMagnitudeEnp0(void (*ptr)(int32_t magnitude));
int usbReceiveRotationEnp0(void (*ptr)(WheelRotation rotation));