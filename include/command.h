#pragma once
#include <Arduino.h>

class Command {
    public:
        String command;
        int arg = -1;

        Command(String command, int arg = -1) {
            this->command = command;
            this->arg = arg;
        }
};

String readCommand();
Command parseCommand(String rawCommand);
Command waitForCommand(Command command);
String stringifyCommand(Command command);
Command sendCommand(Command command);