#include <Arduino.h>

#include "defenitions.h"
#include "config.h"
#include "robot.h"

#if defined(DEBUG_SENSORS) || defined(DEBUG_STOPERS)
    #include "debug.h"
#endif

Robot robot;

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

    robot.getSensorsState();
}