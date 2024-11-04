#include "command.h"

Command CommandManager::waitForCommand(String command) {
    byte attempts = 0;
    while (attempts < 15) {
        Command incomingCommand = parseCommand(readCommand());

        if (!incomingCommand.command.equals(command)) {
            attempts++;
            continue;
        }

        return incomingCommand;
    }

    Command failCommand("fail");
    return failCommand;
}

Command CommandManager::parseCommand(String rawCommand) {
    auto command = rawCommand.substring(0, rawCommand.indexOf(";"));
    auto arg = rawCommand.substring(rawCommand.indexOf(";") + 1, rawCommand.length()).toInt();

    Command parsedCommand(command, arg);
    return parsedCommand;
}

String CommandManager::stringifyCommand(Command command) {
    return command.command + ";" + String(command.arg) + "\n";
}

Command CommandManager::sendCommand(Command command, bool waitForResponse = true) {
    Serial.print(stringifyCommand(command));
    if (waitForResponse) {
        return parseCommand(readCommand());
    }

    Command emptyCommand ("empty");
    return emptyCommand;
}

String CommandManager::readCommand() {
    while (true) {
        if (Serial.available() > 0) {
            return Serial.readStringUntil('\n');
        }
    }
}