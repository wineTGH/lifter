#include <Arduino.h>
#include "robot.h"
#include "defenitions.h"
#include "config.h"

void Robot::begin() {
    // Сервоприводы
    this->servoRight.attach(SERVO_RIGHT_PIN);
    this->servoLeft.attach(SERVO_LEFT_PIN);
    this->servoLift.attach(SERVO_LIFT_PIN);
    this->servoPlatform.attach(SERVO_PLATFORM_PIN);
    #ifndef DISABLE_MANIPULATOR_RESET
        this->reset();
    #endif
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

void Robot::turnAround() {
    //TODO: Implement
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

SensorsState Robot::getSensorsState() {
    if (!digitalRead(SENSOR_LEFT_PIN) && !digitalRead(SENSOR_MIDDLE_PIN) && !digitalRead(SENSOR_RIGHT_PIN)) {
        return SensorsState::Intersection;

    } else if (!digitalRead(SENSOR_LEFT_PIN)) {
        return SensorsState::Right;

    } else if (!digitalRead(SENSOR_RIGHT_PIN)) {
        return SensorsState::Left;

    } else {
        return SensorsState::Forward;
    }
}

int Robot::readStoperValue(int pin) {
    digitalWrite(pin, HIGH);
    return digitalRead(pin);
}