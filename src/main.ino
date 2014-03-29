#include "lib/LineFollow.h"
#include "lib/IRSensor.h"
#include "lib/Motor.h"
// #include <string.h>
// #include <SPI.h>
// #include <Servo.h>

#define LIMIT 500
#define DARKLIMIT 650
#define NUMBEROFSENSORS 8
#define MAXCONSECUTIVE 35


Motor motorLeft(5, 4);
Motor motorRight(6, 7);
Encoder encoderLeft(20, 21);
Encoder encoderRight(18, 19);
SensorIR irSensor(LIMIT, NUMBEROFSENSORS, MAXCONSECUTIVE);
// SensorUltraSonic ultraSonicSensor();
LineFollow lf;

// Setup profiles
profile defaultProfile;


// MODES
//  C:  Competition
char mode = 'C';


// Forward declarations
void competition();
void printSensorArray();
int hasEvent();


// SETUP
// ==========================================================================
void setup() {
    Serial.begin(9600);

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
    if (event = hasEvent()) { // event could be a specialcase
        Serial.println();
        Serial.print("Event ");
        Serial.print(event);
        Serial.println("occoured!");

        switch (event) {
            case 101: case 102:
                // Do a specialcase corresponding to event 101
                break;
            default: // Default behaviour: ignore event
                break;
        }
    } else {
        adjust = lf.getAdjustment(defaultProfile, 3.5); //irSensor.getError());
        motorLeft.run(50 -  adjust);
        motorRight.run(50 + adjust);
        printSensorArray();
    }
}


int hasEvent() {
    int irEvent = irSensor.getEvent();
    // int usEvent = ultraSonicSensor.getEvent();
    if (irEvent > 0)
        return 100 + irEvent;
    // if (usEvent > 0)
    //     return 200 + usEvent;
    return 0;
}


void printSensorArray() {
    for (int i=0; i<NUMBEROFSENSORS; i++)
        if ( Serial.println(irSensor.getHistory(i, 1)) )
            Serial.print("X");
        else
            Serial.print("-");
    Serial.println();
}