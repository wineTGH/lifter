#pragma once

namespace Debug {
    void debugSensors();
    void debugStopers();
    int readStoperState(int pin);
}