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

class CommandManager {
    public:
        HardwareSerial* serial;
        CommandManager(HardwareSerial *serial) {
            this->serial = serial;
        };
        String readCommand();
        Command parseCommand(String rawCommand);
        Command waitForCommand(String command);
        String stringifyCommand(Command command);
        Command sendCommand(Command command, bool waitForResponse = true);
};
