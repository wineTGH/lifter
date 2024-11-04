#pragma once
#include <Servo.h>

class Robot {
    public:
        Servo servoRight;
        Servo servoLeft;
        Servo servoLift;
        Servo servoPlatform;
        
        Robot();

        void turnRight();
        void turnLeft();
        void forward();
        void stop();

    private:
        int readStoperValue(int pin);
};