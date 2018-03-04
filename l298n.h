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

        L298N(int dir1Pin, int dir2Pin,
              int speedPin, int minPwm);

        void setDirection(L298N::State dir);
        L298N::State getDirection() const;

        void setSpeed(int speed);
        int getSpeed() const;
 
    private:
        int _calculateDutyCycle();
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
