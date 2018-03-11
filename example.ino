/* L298N library test */

#include "l298n.h"

#define IN1 2
#define IN2 3
#define ENA 9

#define DC_MOT 1
#define DC_MOT_ADJUST 1
//#define DC_MOT_RUN 1

/* DC motor setup */
#ifdef DC_MOT
L298N mot(IN1, IN2, ENA, 60);
#endif

void dcMotSetup() {
    Serial.begin(115200);
    Serial.println("*** DC motor demo for L298N ***");
}

void dcMotAdjustHelp() {
    Serial.println("Setup: use following keys");
    Serial.println("       h: print help");
    Serial.println("       c: rotate clock-wise");
    Serial.println("       a: rotate counter-clock-wise");
    Serial.println("       +: increase speed by 1 (raw)");
    Serial.println("       -: decrease speed by 1 (raw)");
    Serial.println("       o: turn off");
    Serial.println("       f: turn on at full speed");
}

void dcMotAdjust() {
    int c;
    Serial.println("Setup: Motor off");
    for (;;) {
        c = Serial.read();
        switch (c) {
        case 'h':
            dcMotAdjustHelp();
            break;
        case 'c':
            mot.setDirection(L298N::CW);
            break;
        case 'a':
            mot.setDirection(L298N::CCW);
            break;
        case '+':
            mot.setRawSpeed(mot.getSpeed() + 1);
            break;
        case '-':
            mot.setRawSpeed(mot.getSpeed() - 1);
            break;
        case 'o':
            mot.setRawSpeed(0);
            break;
        case 'f':
            mot.setRawSpeed(255);
            break;
        }
        if (c > 0) {
            Serial.print("Setup: Motor turns ");
            Serial.print(mot.getDirection() == L298N::CW ?
                         "clock-wise" : "counter-clock-wise");
            Serial.print(" at ");
            Serial.println(mot.getSpeed());
        }
    }
}

void dcMotRun() {
    Serial.println("Demo: Run clock wise at 1% speed for 5s");
    mot.setDirection(L298N::CW);
    mot.setSpeed(1);
    delay(5000);

    Serial.println("Demo: Run counter clock wise at 80% speed for 5s");
    mot.setDirection(L298N::CCW);
    mot.setSpeed(80);
    delay(5000);

    Serial.println("Demo: Slow down to 0% within 10s");
    mot.setSpeed(0, 10000);
    Serial.println("Demo: Speed up to 80% within 10s");
    mot.setSpeed(80, 10000);

    Serial.println("Demo: Turn off and sleep for 1s");
    mot.setSpeed(0);
    mot.setDirection(L298N::CW);
    delay(1000);
}

/* setup */
void setup() {
#ifdef DC_MOT
    dcMotSetup();
#endif
};

/* main */
void loop() {
#ifdef DC_MOT_ADJUST
    dcMotAdjust();
#elif DC_MOT_RUN
    dcMotRun();
#endif
}
