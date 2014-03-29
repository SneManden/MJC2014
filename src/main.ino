#include "lib/LineFollow.h"
#include "lib/Motor.h"
// #include <string.h>
// #include <SPI.h>
// #include <Servo.h>


Motor motorLeft(5, 4);
Motor motorRight(6, 7);
Encoder encoderLeft(20, 21);
Encoder encoderRight(18, 19);
LineFollow lf(0);

// Setup profiles
profile defaultProfile;


// MODES
//  C:  Competition
char mode = 'D';


// SETUP
// ==========================================================================
void setup() {
    defaultProfile.kp = 1;
    defaultProfile.ki = 0;
    defaultProfile.kd = 0;
}


// LOOP
// ==========================================================================
void loop() {
    switch (mode) {
        case 'C':
            competition();
            break;
        default:
            break;
    }
}


// COMPETITION
// ==========================================================================
char event;
int adjust;
void competition() {
    // if (event = irSensor.getEvent()) { // event could be a specialcase
    if (false) {
        switch (event) {
            default: // Default behaviour: ignore event
                break;
        }
    } else {
        adjust = lf.getAdjustment(defaultProfile, 3.5); //irSensor.getError());
        motorLeft.run(50 -  adjust);
        motorRight.run(50 + adjust);
    }
}
