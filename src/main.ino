#include "../lib/Motor.h"
#include <string.h>
#include <SPI.h>
#include <Servo.h>

void setup() {
    pinMode(13, OUTPUT);
}

void loop() {
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
}