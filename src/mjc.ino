//#include "lib/LineFollow.h"
#include <IRSensor.h>
//#include "lib/Motor.h"
// #include <string.h>
// #include <SPI.h>
// #include <Servo.h>

#define LIMIT 300
#define DARKLIMIT 650
#define NUMBEROFSENSORS 4
// #define MAXCONSECUTIVE 35


// Motor motorLeft(5, 4);
// Motor motorRight(6, 7);
// Encoder encoderLeft(20, 21);
// Encoder encoderRight(18, 19);
SensorIR irSensor(LIMIT);//, NUMBEROFSENSORS, MAXCONSECUTIVE);
// SensorUltraSonic ultraSonicSensor();
//LineFollow lf;

// Setup profiles
//profile defaultProfile;


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

    //defaultProfile.kp = 1;
    //defaultProfile.ki = 0;
    //defaultProfile.kd = 0;

    pinMode(13, OUTPUT);
}


// LOOP
// ==========================================================================
int now = 0;
void loop() {
    // digitalWrite(13, HIGH); delay(1000); digitalWrite(13, LOW); delay(1000);
    irSensor.update();
    Serial.println("qwiejqow");
    // Serial.println("Lol");
    // printSensorArray();

    // if (millis() - now > 2000) {
    //     now = millis();
        // print history
        // Serial.println("Printing history for sensors:");
        // for (int i=0; i<NUMBEROFSENSORS; i++) {
        //     Serial.print("  Sensor history for sensor ");
        //     Serial.println(i);
        //     Serial.print("    ");
        //     for (int j=0; j<MAXCONSECUTIVE; j++) {
        //         if (irSensor.getHistory(i,j))
        //             Serial.print("1 ");
        //         else
        //             Serial.print("0 ");
        //     }
        //     Serial.println();
        // }
    // }

    // Serial.println("Waiting..");
    // delay(500);

    // switch (mode) {
    //     case 'C':
    //         competition();
    //         break;
    //     default:
    //         break;
    // }
}


// COMPETITION
// ==========================================================================
char event;
int adjust;
void competition() {
    if (event = hasEvent()) { // event could be a specialcase
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
        //adjust = lf.getAdjustment(defaultProfile, 3.5); //irSensor.getError());
        // motorLeft.run(50 -  adjust);
        // motorRight.run(50 + adjust);
        // printSensorArray();
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


int val;
void printSensorArray() {
    // for(int i=0; i<6; i++) {
    //     if (analogRead(i) > 300)
    //         Serial.print("X");
    //     else
    //         Serial.print("-");
    // }
    // Serial.println();
    // delay(100);
    for (int i=0; i<NUMBEROFSENSORS; i++)
        // Serial.print( analogRead(i) ),
        // Serial.print(" - ");
        if (irSensor.getHistory(i, 1))
            Serial.print("X");
        else
            Serial.print("-");
    Serial.println();

    delay(100);
}