#pragma once
#include <Servo.h>

class Robot {
    public:
        bool isLoaded = false;

        void begin();
        void turnRight();
        void turnLeft();
        void forward();
        void stop();
        void grab();
        void reset();

    private:
        Servo servoRight;
        Servo servoLeft;
        Servo servoLift;
        Servo servoPlatform;
        int readStoperValue(int pin);
};