// L298N motor control library

#include "Arduino.h"
#include "L298N.h"

L298N::L298N(int dir1Pin, int dir2Pin,
             int speedPin, int minPwm) :
    _dir1Pin(dir1Pin),
    _dir2Pin(dir2Pin),
    _speedPin(speedPin),
    _direction(OFF),
    _minPwm(minPwm),
    _speed(OFF)
{
    // init pwr and direction outputs
    pinMode(_dir1Pin, OUTPUT);
    pinMode(_dir2Pin, OUTPUT);
    pinMode(_speedPin, OUTPUT);

    // turn the motor off
    analogWrite(_speedPin, OFF);
}

void L298N::setDirection(L298N::State dir)
{
    _direction = dir;
    _update();
}

L298N::State L298N::direction() const
{
    return _direction;
}

void L298N::setRawSpeed(int speed, int duration)
{
    int steps;
    int delayTime;
    int offset;

    speed = constrain(speed, 0, 255);
    steps = speed - _speed;
    delayTime = duration / abs(steps);
    offset = (steps > 0) ? +1 : -1;

    // ensure that direction is set
    if (_speed == OFF && !!speed)
        _update();

    // loop over steps if any
    for (int i = 0; i < abs(steps); i++) {
        _speed += offset;
        analogWrite(_speedPin, _speed);
        delay(delayTime);
    }

    // ensure correct final value
    _speed = speed;
    analogWrite(_speedPin, _speed);
}

void L298N::setSpeed(int speed, int duration)
{
    int steps;
    int delayTime;
    int offset;

    speed = constrain(speed, 0, 100);
    steps = speed - _speed;
    delayTime = duration / abs(steps);
    offset = (steps > 0) ? +1 : -1;

    // loop over steps if any
    for (int i = 0; i < abs(steps); i++) {
        _speed += offset;
        _update();
        delay(delayTime);
    }

    // ensure correct final value
    _speed = speed;
    _update();
}

int L298N::speed() const
{
    return _speed;
}

int L298N::_dutyCycleFromPercent()
{
    int d = 255 - _minPwm;
    int l = d / 100 * _speed;
    return (l + _minPwm);
}

void L298N::_off()
{
    digitalWrite(_dir1Pin, LOW);
    digitalWrite(_dir2Pin, LOW);
    analogWrite(_speedPin, 0);
}

void L298N::_update()
{
    switch (_speed) {
    case OFF:
        _off();
        break;
    default:
        analogWrite(_speedPin, _dutyCycleFromPercent());
        break;
    }

    switch (_direction) {
    case OFF:
        _off();
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
}
