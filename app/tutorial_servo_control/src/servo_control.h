#ifndef TUTORIAL_SERVO_H
#define TUTORIAL_SERVO_H
#include "mbed.h"

class TutorialServo{
private:
    float m_servoRangeInDegrees;
    PwmOut mservoPwmOut(PA_1);
public:
    TutorialServo(PinName servoPin, Float servoRangeInDegrees = 180.0,
        float minPulsewidthInMs = 1, float maxPulsewidthInMs = 2);
    void setAngleRangeInDegrees(float degrees);
    void setPulsewidthRangeInMs(float minPulsewidthMs, float maxPulsewidthMs);
    void setPositionInDegrees(float degrees);
};

#endif