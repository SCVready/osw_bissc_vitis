
#include <stdio.h>
#include <stdint.h>

#include <xbasic_types.h>

#include "logging.h"
#include "usb_hid_data_endpoint.h"
#include "steering_wheel_config.h"
#include "velaro_hid_report.h"

void (*magnitudeCallback)(int32_t magnitude) = NULL;
void (*rotationCallback)(WheelRotation rotation) = NULL;

void HandleInterruptDataPacket(XUsbPs *InstancePtr, u8 EpNum, u8 *BufferPtr, u32 BufferLen)
{
    if (BufferLen == 0) {
        LOG("DataPacket Size 0 received on data Endpoint \n");
        return;
    }

    uint8_t reportID = BufferPtr[0];
    u8 *data = &(BufferPtr[1]);
    u32 dataLen = BufferLen - 1;

    //printf("Received data on ReportID %u len %u\n", reportID, dataLen);

    switch (reportID) {
        case SET_CONSTANT_FORCE_REPORT_ID:
            if (dataLen >= sizeof(USB_HID_REPORT_SET_CONSTANT_FORCE_REPORT)) {
                USB_HID_REPORT_SET_CONSTANT_FORCE_REPORT report;
                memcpy(&report, data, sizeof(report));

                LOG("EffectBlockIndex %u \n", report.effectBlockIndex);
                LOG("Magnitude %d \n", report.magnitude);

                if (report.effectBlockIndex == 0x01) {
                    if (magnitudeCallback != NULL) {
                        magnitudeCallback(report.magnitude);
                    }
                }
                else {
                    LOG("SET_CONSTANT_FORCE_REPORT_ID  effectBlockIndex %u\n", report.effectBlockIndex);
                }
            }
            break;
        case VELARO_CUSTOM_0_REPORT_ID:
            if (dataLen >= sizeof(USB_HID_REPORT_VELARO_CUSTOM_0)) {
                USB_HID_REPORT_VELARO_CUSTOM_0 report;
                memcpy(&report, data, sizeof(report));
                LOG("WheelRotation change received %s \n", rotationEnumToString(report.rotation));
                if (rotationCallback != NULL) {
                    rotationCallback(report.rotation);
                }
            }
            break;
            
        case SET_ENVELOPE_REPORT_ID:
            LOG("SET_ENVELOPE_REPORT_ID  \n");
            break;
        case SET_CONDITION_REPORT_ID:
            LOG("SET_CONDITION_REPORT_ID  \n");
            break;
        case SET_PERIODIC_REPORT_ID:
            LOG("SET_PERIODIC_REPORT_ID  \n");
            break;
        case EFFECT_OPERATION_REPORT_ID:
            LOG("EFFECT_OPERATION_REPORT_ID  \n");
            break;
        case PID_DEVICE_CONTROL_REPORT_ID:
            LOG("PID_DEVICE_CONTROL_REPORT_ID  \n");
            break;
        default:
            break;
    }
}

int registerMagnitudeCallback(void (*ptr)(int32_t magnitude))
{
    magnitudeCallback = ptr;
}

int registerRotationCallback(void (*ptr)(WheelRotation rotation))
{
    rotationCallback = ptr;
}
