
#include "usb_hid_device.h"
#include "steering_wheel_config.h"
#include <xbasic_types.h>

int usbFfbInit()
{
    return usbInit();
}

int usbFfbSendPosition(int32_t position)
{
    return usbSendPositionEnp1(position);
}

int usbFfbSetForceCallback(void (*ptr)(int32_t magnitude))
{
    usbReceiveMagnitudeEnp0(ptr);
}

int usbRotationReceivedCallback(void (*ptr)(WheelRotation rotation))
{
    usbReceiveRotationEnp0(ptr);
}