
#include <stdint.h>
#include <xbasic_types.h>
#include "steering_wheel_config.h"

int usbFfbInit();
int usbFfbSendPosition(int32_t position);
int usbFfbSetForceCallback(void (*ptr)(int32_t magnitude));
int usbRotationRangeReceivedCallback(void (*ptr)(WheelRotation rotation));
int usbRotationOffsetReceivedCallback(void (*ptr)(int32_t rotation));
