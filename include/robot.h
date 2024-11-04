#pragma once
#include <Servo.h>

enum SensorsState {
    Forward,
    Right,
    Left,
    Intersection,
};

class Robot {
    public:
        bool isLoaded = false;

        void begin();
        void turnRight();
        void turnLeft();
        void turnAround();
        void forward();
        void stop();
        void grab();
        void reset();

        SensorsState getSensorsState();

    private:
        Servo servoRight;
        Servo servoLeft;
        Servo servoLift;
        Servo servoPlatform;
        int readStoperValue(int pin);
};