#pragma once
#include <Servo.h>

class Robot {
    public:
        void begin();
        void turnRight();
        void turnLeft();
        void forward();
        void stop();

    private:
        Servo servoRight;
        Servo servoLeft;
        Servo servoLift;
        Servo servoPlatform;
        int readStoperValue(int pin);
};