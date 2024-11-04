#include <Arduino.h>

#include "defenitions.h"
#include "config.h"
#include "robot.h"
#include "command.h"

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

    #ifdef DEBUG_STATE
        Serial.println("======== State ========");
        Serial.print("Sensors state: ");
        Serial.println(sensorsState);
        Serial.print("Intersections Counter: ");
        Serial.println(intersectionsCounter);
        Serial.print("Robot is loaded? ");
        Serial.println(robot.isLoaded);
        delay(300);
    #endif

    #ifdef DEBUG_COMMANDS
        auto parsedCommand = parseCommand("start;4\n");
        Serial.println("======== Parsed ========");
        Serial.print("Command: ");
        Serial.println(parsedCommand.command);
        Serial.print("Args: ");
        Serial.println(parsedCommand.arg);

        auto stringifiedCommand = stringifyCommand(parsedCommand);
        Serial.println("======== Parsed ========");
        Serial.print("Command: ");
        Serial.print(stringifiedCommand);

        delay(300);
    #endif

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
        //TODO: Add sending command to scan QR code
        //TODO: Save last intersection where robot grabed last item, so we can skip scaning unwanted items
        robot.grab();
    }

    if (intersectionsCounter >= 5) {
        robot.turnAround();
    }

    if (intersectionsCounter >= 10) {
        //TODO: Add lap counter (how many items left to pick up)
        intersectionsCounter = 0;
        robot.unload();
    }
}