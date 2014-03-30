//#include "lib/LineFollow.h"
#include <IRSensor.h>
//#include "lib/Motor.h"
// #include <string.h>
// #include <SPI.h>
// #include <Servo.h>

#define LIMIT 300
// #define DARKLIMIT 650
#define NUMBEROFSENSORS 8
#define MAXCONSECUTIVE 35

#define SERIALDISABLEPIN 22
#define sprint(X) do { if (!digitalRead(SERIALDISABLEPIN)) Serial.print(X); } while (0)
#define sprintln(X) do { if (!digitalRead(SERIALDISABLEPIN)) Serial.println(X); } while (0)

// Motor motorLeft(5, 4);
// Motor motorRight(6, 7);
// Encoder encoderLeft(20, 21);
// Encoder encoderRight(18, 19);
SensorIR irSensor(LIMIT, NUMBEROFSENSORS, MAXCONSECUTIVE);
// SensorUltraSonic ultraSonicSensor();
//LineFollow lf;

// Setup profiles
//profile defaultProfile;


// MODES
//  C:  Competition
// char mode = 'C';


// Forward declarations
// void competition();
// int hasEvent();
void printSensorOnOff();
void printSensorValues();

// SETUP
// ==========================================================================
void setup() {
    Serial.begin(9600);

    irSensor.init();

    //defaultProfile.kp = 1;
    //defaultProfile.ki = 0;
    //defaultProfile.kd = 0;

    // pinMode(13, OUTPUT);
    pinMode(SERIALDISABLEPIN, INPUT_PULLUP); // Enable serial when HIGH
}


// LOOP
// ==========================================================================
int now = 0;
void loop() {
    // digitalWrite(13, HIGH); delay(1000); digitalWrite(13, LOW); delay(1000);
    sprint("Updating... ");
    irSensor.update();
    sprintln("fin!");
    // sprintln("qwiejqow");
    // sprintln("Lol");

    // if (!digitalRead(SERIALDISABLEPIN))
    //     sprintln("Lorem ipsum dolor sit amet.");

    if (millis() - now > 2000) {
        now = millis();
        // print history
        sprintln("Printing history for sensors:");
        for (int i=0; i<NUMBEROFSENSORS; i++) {
            sprint("  Sensor history for sensor ");
            sprintln(i);
            sprint("    ");
            for (int j=1; j<=MAXCONSECUTIVE; j++) {
                // sprint( irSensor.sensorHistory[i][j] );
                // sprint(" ");
                // if (irSensor.sensorHistory[i][j])
                //     sprint("1 ");
                // else
                //     sprint("0 ");
                if (irSensor.getHistory(i,j))
                    sprint("1 ");
                else
                    sprint("0 ");
            }
            sprintln();
        }
        sprintln("=> Finished printing history.");
    }

    // printSensorOnOff();

    // sprintln("Waiting..");
    // delay(500);

    // switch (mode) {
    //     case 'C':
    //         competition();
    //         break;
    //     default:
    //         break;
    // }
}

/*
// COMPETITION
// ==========================================================================
char event;
int adjust;
void competition() {
    if (event = hasEvent()) { // event could be a specialcase
        sprint("Event ");
        sprint(event);
        sprintln("occoured!");

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
*/

int val;
bool value;
void printSensorOnOff() {
    for (int i=0; i<NUMBEROFSENSORS; i++) {
        // value = irSensor.getHistory(i, 1);
        // sprint( value );
        // sprint(" - ");
        // sprint(irSensor.getHistory(i, 1));
        if (irSensor.getHistory(i, 1))
            sprint("X");
        else
            sprint("-");
    }
    sprintln();

    delay(100);
}
void printSensorValues() {
    for (int i=0; i<NUMBEROFSENSORS; i++) {
        sprint( analogRead(i) );
        sprint(" - ");
    }
    sprintln();
    delay(100);
}