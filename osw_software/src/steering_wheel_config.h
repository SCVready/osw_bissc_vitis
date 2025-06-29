#ifndef STEERING_WHEEL_CONFIG
#define STEERING_WHEEL_CONFIG

#include <stdint.h>

typedef enum WheelRotation {
    rotation720 = 0,
    rotation540 = 1,
    rotation360 = 2,
    rotation1080 = 3
} WheelRotation;

typedef struct SteeringWheelControllerConfig {
    enum WheelRotation wheelRotation;
} SteeringWheelControllerConfig;

const char* rotationEnumToString(enum WheelRotation val);
uint32_t rotationEnumToValue(enum WheelRotation val);

#endif /* STEERING_WHEEL_CONFIG */