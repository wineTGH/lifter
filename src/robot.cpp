#include <Arduino.h>
#include "robot.h"
#include "defenitions.h"

Robot::Robot() {
    // Сервоприводы
    this->servoRight.attach(SERVO_RIGHT_PIN);
    this->servoLeft.attach(SERVO_LEFT_PIN);
    this->servoLift.attach(SERVO_LIFT_PIN);
    this->servoPlatform.attach(SERVO_PLATFORM_PIN);
}

void Robot::turn_left() {

}

void Robot::turn_right() {

}

void Robot::forward() {

}

int Robot::readStoperValue(int pin) {
    digitalWrite(pin, HIGH);
    return digitalRead(pin);
}