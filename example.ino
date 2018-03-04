/* L298N library test */

#include "l298n.h"

#define IN1 2
#define IN2 3
#define ENA 9

/* my motor setup */
L298N mot(IN1, IN2, ENA, 100);

void setup() {
    /* noop */
};

/* main */
void loop() {
    mot.setDirection(L298N::CW);
    mot.setSpeed(20);
    delay(1000);
    
    mot.setDirection(L298N::OFF);
    delay(1000);
    
    mot.setDirection(L298N::CCW);
    mot.setSpeed(20);
    delay(1000);
    
    mot.setDirection(L298N::OFF);
    delay(1000);
}
