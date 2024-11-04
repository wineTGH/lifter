#include <Arduino.h>

#include "defenitions.h"
#include "config.h"
#include "robot.h"

#if defined(DEBUG_SENSORS) || defined(DEBUG_STOPERS)
    #include "debug.h"
#endif

Robot robot;
int intersectionsCounter = 0;

void setup() {
    Serial.begin(9600);

    robot.begin();
}

void loop() {
    #ifdef DEBUG_SENSORS
        Debug::debugSensors();
    #endif

    #ifdef DEBUG_STOPERS
        Debug::debugStopers();
    #endif

    auto sensorsState = robot.getSensorsState();

    switch (sensorsState) {
        case SensorsState::Intersection:
            intersectionsCounter++;
            delay(300);
        case SensorsState::Forward:
            robot.forward();
            delay(100);
            break;
        case SensorsState::Left:
            robot.turnLeft();
            delay(100);
        case SensorsState::Right:
            robot.turnRight();
            delay(100);
        default:
            break;
    }

    if (intersectionsCounter >= 3 && !robot.isLoaded) {
        robot.grab();
    }

    if (intersectionsCounter >= 5) {
        robot.turnAround();
    }

    if (intersectionsCounter >= 10) {
        intersectionsCounter = 0;
        robot.unload();
    }
}