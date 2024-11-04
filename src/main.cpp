#include <Arduino.h>

#include "defenitions.h"
#include "config.h"
#include "robot.h"
#include "command.h"

#if defined(DEBUG_SENSORS) || defined(DEBUG_STOPERS)
    #include "debug.h"
#endif

Robot robot;
CommandManager cmd(&Serial);

int intersectionsCounter = 0;
int totalLaps = 0;


void setup() {
    Serial.begin(9600);
    robot.begin();

    auto startCommand = cmd.waitForCommand("start");
    totalLaps = startCommand.arg;
}

void loop() {
    if (totalLaps <= 0) {
        return;
    }

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
        auto parsedCommand = cmd.parseCommand("end;5\n");
        Serial.println("======== Parsed ========");
        Serial.print("Command: ");
        Serial.println(parsedCommand.command);
        Serial.print("Args: ");
        Serial.println(parsedCommand.arg);

        auto stringifiedCommand = cmd.stringifyCommand(parsedCommand);
        Serial.println("======== Stringified ========");
        Serial.print("Command: ");
        Serial.print(stringifiedCommand);

        delay(300);

        Serial.print("waiting For command: ");
        auto recievedCommand = cmd.waitForCommand("start");
        Serial.println("======== Parsed ========");
        Serial.print("Command: ");
        Serial.println(recievedCommand.command);
        Serial.print("Args: ");
        Serial.println(recievedCommand.arg);
    #endif

    #ifdef DISABLE_MOVEMENT
        return;
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
        //TODO: Save last intersection where robot grabed last item, so we can skip scaning unwanted items
        Command scanCommad ("scan");
        if (cmd.sendCommand(scanCommad).command.equals("grab")) {
            robot.grab();
        }
    }

    if (intersectionsCounter >= 5) {
        robot.turnAround();
    }

    if (intersectionsCounter >= 10) {
        intersectionsCounter = 0;
        totalLaps--;
        robot.unload();
    }

    if (totalLaps <= 0) {
        Command stopCommand ("end");
        cmd.sendCommand(stopCommand);
    }
}