#ifndef USB_HID_DATA_ENDPOINT
#define USB_HID_DATA_ENDPOINT

#include "xusbps_hw.h"
#include "xil_types.h"
#include "xstatus.h"
#include "xusbps.h"
#include "steering_wheel_config.h"
#include <stdint.h>


int registerMagnitudeCallback(void (*ptr)(int32_t magnitude));
int registerRotationRangeCallback(void (*ptr)(WheelRotation rotation));
int registerRotationOffsetCallback(void (*ptr)(int32_t rotation));

void HandleInterruptDataPacket(XUsbPs *InstancePtr, u8 EpNum, u8 *BufferPtr, u32 BufferLen);

#endif /* USB_HID_DATA_ENDPOINT */
