#pragma once
#include <Servo.h>

class Robot {
    public:
        Servo servoRight;
        Servo servoLeft;
        Servo servoLift;
        Servo servoPlatform;
        
        Robot();

        void turn_right();
        void turn_left();
        void forward();

    private:
        int readStoperValue(int pin);
};