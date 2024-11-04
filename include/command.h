#pragma once
#include <Arduino.h>

class Command {
    public:
        String command;
        int arg;
};

String readCommand();
Command parseCommand(String rawCommand);
Command waitForCommand(Command command);
String stringifyCommand(Command command);
Command sendCommand(Command command);