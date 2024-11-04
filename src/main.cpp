#include <Arduino.h>

#include "defenitions.h"
#include "config.h"
#include "robot.h"

void setup() {
    Serial.begin(9600);

    // Датчики линии
    pinMode(SENSOR_RIGHT_PIN, INPUT);
    pinMode(SENSOR_MIDDLE_PIN, INPUT);
    pinMode(SENSOR_LEFT_PIN, INPUT);

    // Концевики
    pinMode(STOPER_LIFT_DOWN_PIN, INPUT);
    pinMode(STOPER_LIFT_UP_PIN, INPUT);
    pinMode(STOPER_PLATFORM_BACK_PIN, INPUT);
    pinMode(STOPER_PLATFORM_FORWARD_PIN, INPUT);
}


void debugSensors() {
    Serial.println("======== Sensors ========");
    Serial.print("Right: ");
    Serial.println(digitalRead(SENSOR_RIGHT_PIN));
    Serial.print("Middle: ");
    Serial.println(digitalRead(SENSOR_MIDDLE_PIN));
    Serial.print("Left: ");
    Serial.println(digitalRead(SENSOR_LEFT_PIN));
    delay(300);
}

bool readStoperState(int pin) {
    digitalWrite(pin, HIGH);
    return digitalRead(pin);
}

void debugStopers() {
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

void loop() {
    #ifdef DEBUG_SENSORS
        debugSensors();
    #endif

    #ifdef DEBUG_STOPERS
        debugStopers();
    #endif
}