#include "command.h"

Command waitForCommand(Command command) {

}

Command parseCommand(String rawCommand) {

}

String stringifyCommand(Command command) {
    
}

Command sendCommand(Command command) {

}

String readCommand() {
    while (true) {
        if (Serial.available() > 0) {
            return Serial.readStringUntil('\n');
        }
    }
}