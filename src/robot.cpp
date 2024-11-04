#include <Arduino.h>
#include "robot.h"
#include "defenitions.h"

void Robot::begin() {
    // Сервоприводы
    this->servoRight.attach(SERVO_RIGHT_PIN);
    this->servoLeft.attach(SERVO_LEFT_PIN);
    this->servoLift.attach(SERVO_LIFT_PIN);
    this->servoPlatform.attach(SERVO_PLATFORM_PIN);
    this->reset();
}

void Robot::reset() {
    while (this->readStoperValue(STOPER_LIFT_DOWN_PIN)) {
        this->servoLift.write(120);
    }
    
    this->servoLift.write(90);

    while (this->readStoperValue(STOPER_PLATFORM_BACK_PIN)) {
        this->servoPlatform.write(120);
    }

    this->servoPlatform.write(90);
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

void Robot::grab() {
    
    this->stop();
    while (this->readStoperValue(STOPER_PLATFORM_FORWARD_PIN)) {
        this->servoPlatform.write(30);
    }

    this->servoPlatform.write(90);

    while (this->readStoperValue(STOPER_LIFT_UP_PIN)) {
        this->servoLift.write(30);
    }

    this->servoLift.write(90);
}

int Robot::readStoperValue(int pin) {
    digitalWrite(pin, HIGH);
    return digitalRead(pin);
}