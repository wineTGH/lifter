#include "command.h"

Command waitForCommand(String command) {
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

Command parseCommand(String rawCommand) {
    auto command = rawCommand.substring(0, rawCommand.indexOf(";"));
    auto arg = rawCommand.substring(rawCommand.indexOf(";"), rawCommand.length()).toInt();

    Command parsedCommand(command, arg);
    return parsedCommand;
}

String stringifyCommand(Command command) {
    return command.command + ";" + String(command.arg) + "\n";
}

Command sendCommand(Command command) {
    Serial.print(stringifyCommand(command));
    return parseCommand(readCommand());
}

String readCommand() {
    while (true) {
        if (Serial.available() > 0) {
            return Serial.readStringUntil('\n');
        }
    }
}