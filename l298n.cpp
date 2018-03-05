/* L298N motor control library */

#include "Arduino.h"
#include "l298n.h"

L298N::L298N(int dir1Pin, int dir2Pin,
             int speedPin, int minPwm) :
    _dir1Pin(dir1Pin),
    _dir2Pin(dir2Pin),
    _speedPin(speedPin),
    _direction(OFF),
    _minPwm(minPwm),
    _speed(OFF) {
    /* init pwr and direction outputs */
    pinMode(_dir1Pin, OUTPUT);
    pinMode(_dir2Pin, OUTPUT);
    pinMode(_speedPin, OUTPUT);

    /* turn the motor off */
    analogWrite(_speedPin, OFF);
}

void L298N::setDirection(L298N::State dir) {
    _direction = dir;
    _update();
}

L298N::State L298N::getDirection() const {
    return _direction;
}

void L298N::setSpeed(int speed, int duration) {
    int s = duration <= 0 ? 0 : duration / 10;
    int d = (speed - _speed) / s;

    /* loop over steps if any */
    for (int i = 0; i < s; i++) {
        _speed += d;
        _update();
    }

    /* ensure correct final value */
    _speed = speed;
    _update();
}

int L298N::getSpeed() const {
    return _speed;
}

int L298N::_calculateDutyCycle() {
    int d = 255 - _minPwm;
    int l = d / 100 * _speed;
    return (l + _minPwm);
}

void L298N::_update() {
    switch (_direction) {
    case OFF:
        digitalWrite(_dir1Pin, LOW);
        digitalWrite(_dir2Pin, LOW);
        break;
    case CW:
        digitalWrite(_dir1Pin, HIGH);
        digitalWrite(_dir2Pin, LOW);
        break;
    case CCW:
        digitalWrite(_dir1Pin, LOW);
        digitalWrite(_dir2Pin, HIGH);
        break;
    }

    switch (_speed) {
    case OFF:
        digitalWrite(_dir1Pin, LOW);
        digitalWrite(_dir2Pin, LOW);
        break;
    default:
        analogWrite(_speedPin, _calculateDutyCycle());
        break;
    }
}
