#ifndef USB_HID_DATA_ENDPOINT
#define USB_HID_DATA_ENDPOINT

#include "xusbps_hw.h"
#include "xil_types.h"
#include "xstatus.h"
#include "xusbps.h"
#include "steering_wheel_config.h"


int registerMagnitudeCallback(void (*ptr)(int32_t magnitude));
int registerRotationCallback(void (*ptr)(WheelRotation rotation));

void HandleInterruptDataPacket(XUsbPs *InstancePtr, u8 EpNum, u8 *BufferPtr, u32 BufferLen);

#endif /* USB_HID_DATA_ENDPOINT */
