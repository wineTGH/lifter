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

void Robot::turnLeft() {
    this->servoLeft.write(120);
    this->servoRight.write(100);
}

void Robot::turnRight() {
    this->servoLeft.write(100);
    this->servoRight.write(120);
}

void Robot::forward() {
    this->servoLeft.write(120);
    this->servoRight.write(120);
}

void Robot::stop() {
    this->servoLeft.write(90);
    this->servoRight.write(90);
}

int Robot::readStoperValue(int pin) {
    digitalWrite(pin, HIGH);
    return digitalRead(pin);
}