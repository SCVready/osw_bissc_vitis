#include <stdint.h>
#include "steering_wheel_config.h"

const char* rotationEnumToString(enum WheelRotation val) {
    switch(val) {
        case rotation360: return "360°";
        case rotation540: return "540°";
        case rotation720: return "720°";
        case rotation1080: return "1080°";
        default:     return "Unknown";
    }
}

uint32_t rotationEnumToValue(enum WheelRotation val) {
    switch(val) {
        case rotation360: return 360U;
        case rotation540: return 540U;
        case rotation720: return 720U;
        case rotation1080: return 1080U;
        default:     return 720U;
    }
}