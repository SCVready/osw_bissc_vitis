#ifndef STEERING_WHEEL_CONFIG
#define STEERING_WHEEL_CONFIG

#include <stdint.h>

#define STEERING_WHEEL_MAX_ROTATION_VALUE 12582911
#define STEERING_WHEEL_MIN_ROTATION_VALUE -12582912

typedef enum WheelRotation {
    rotation720 = 0,
    rotation540 = 1,
    rotation360 = 2,
    rotation1080 = 3
} WheelRotation;

typedef struct SteeringWheelControllerConfig {
    enum WheelRotation wheelRotationRange;
    int32_t wheelRotationOffset;
} SteeringWheelControllerConfig;

const char* rotationEnumToString(enum WheelRotation val);
uint32_t rotationEnumToValue(enum WheelRotation val);

#endif /* STEERING_WHEEL_CONFIG */