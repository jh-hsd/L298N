/* L298N motor control library */

#ifndef L298N_h
#define L298N_h

class L298N {
    public:
        enum State {
            OFF, /* motor off */
            CW,  /* turn clock-wise */
            CCW, /* turn counter clock wise */
        };

        /* initialize L298N motor class
           dir1Pin: direction pin #1
           dir2Pin: direction pin #2
           speedPin: PWM pin
           minPwm: min. PWM value (0-255) when the motor
           starts turning */
        L298N(int dir1Pin, int dir2Pin,
              int speedPin, int minPwm);

        void setDirection(L298N::State dir);
        L298N::State getDirection() const;

        /* adjust speed
           speed: PWM duty cycle (0-255)
           duration: speed ramp is in milli seconds */
        void setRawSpeed(int speed, int duration = 0);
        /* adjust speed
           speed: in percent (0-100)
           duration: speed ramp is in milli seconds */
        void setSpeed(int speed, int duration = 0);
        /* returns either raw speed value (duty-cycle) or 
           percent value depending on the setSpeed method used */
        int getSpeed() const;
 
    private:
        int _dutyCycleFromPercent();
        void _off();
        void _update();

        /* pins */
        int _dir1Pin;
        int _dir2Pin;
        int _speedPin;
        /* abstract controls and state */
        L298N::State _direction;
        int _minPwm;
        int _speed;
};

#endif
