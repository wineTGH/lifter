#include <Arduino.h>
#include "defenitions.h"
#include "debug.h"


void Debug::debugSensors() {
    Serial.println("======== Sensors ========");
    Serial.print("Right: ");
    Serial.println(digitalRead(SENSOR_RIGHT_PIN));
    Serial.print("Middle: ");
    Serial.println(digitalRead(SENSOR_MIDDLE_PIN));
    Serial.print("Left: ");
    Serial.println(digitalRead(SENSOR_LEFT_PIN));
    delay(300);
}

int Debug::readStoperState(int pin) {
    digitalWrite(pin, HIGH);
    return digitalRead(pin);
}

void Debug::debugStopers() {
    Serial.println("======== Stopers ========");
    Serial.print("Lift Up: ");
    Serial.println(readStoperState(STOPER_LIFT_UP_PIN));
    Serial.print("Lift Down: ");
    Serial.println(readStoperState(STOPER_LIFT_DOWN_PIN));
    Serial.print("Platform Forward: ");
    Serial.println(readStoperState(STOPER_PLATFORM_FORWARD_PIN));
    Serial.print("Platform Back: ");
    Serial.println(readStoperState(STOPER_PLATFORM_BACK_PIN));
    delay(300);
}