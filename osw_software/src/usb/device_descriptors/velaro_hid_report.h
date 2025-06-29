
#ifndef __VELARO_REPORT_H_
#define __VELARO_REPORT_H_

#include <xbasic_types.h>

// REPORT IDs
#define JOYSTICK_REPORT_ID              0x01
#define SET_ENVELOPE_REPORT_ID          0x02
#define SET_CONDITION_REPORT_ID         0x03
#define SET_PERIODIC_REPORT_ID          0x04
#define SET_CONSTANT_FORCE_REPORT_ID    0x05
#define EFFECT_OPERATION_REPORT_ID      0x0A
#define PID_DEVICE_CONTROL_REPORT_ID    0x0B
#define VELARO_CUSTOM_0_REPORT_ID       0x9C

// INPUT (from host)
#pragma pack(push, 1)
typedef struct {
    uint8_t reportId;
    int32_t xPosition;
} USB_HID_JOYSTICK_REPORT;
#pragma pack(pop)

// OUTPUT (from host)
#pragma pack(push, 1)
typedef struct {
    uint8_t  effectBlockIndex;
    int16_t magnitude;
} USB_HID_REPORT_SET_CONSTANT_FORCE_REPORT;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    uint8_t  rotation;
} USB_HID_REPORT_VELARO_CUSTOM_0;
#pragma pack(pop)

#endif
