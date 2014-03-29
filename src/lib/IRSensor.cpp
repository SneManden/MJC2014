#include "IRSensor.h"

#define ABEKAT 60000

// Constructor
SensorIR::SensorIR(int _limit, int _numberOfSensors, int _maxConsecutive) {
    limit = _limit;
    target = (numberOfSensors-1)/2.0;
    numberOfSensors = _numberOfSensors;
    // The number of consecutive readings
    // before some events are accepted
    maxConsecutive = _maxConsecutive;
    consecutive = _maxConsecutive;
    // Setup history arrays for each sensor
    sensorHistory[_numberOfSensors][_maxConsecutive];
    pivot = 0;
}
int SensorIR::getError() {
    return target - getPosition();
}

void SensorIR::update() {
    for (int i=0; i<numberOfSensors; i++) {
        sensorHistory[i][pivot] = (analogRead(i) > limit);
        pivot = pivot+1 % maxConsecutive;
    }
}

// val = analogRead(i);
// if (val > limit) {
//     total += i;
//     sensorCount++;
// }

int SensorIR::getPosition() {
    int val, total, sensorCount;
    total = sensorCount = 0;
    // For each sensor add sensornum to total
    for (int i=0; i<numberOfSensors; i++) {
        if (getHistory(i, consecutive)) { //sensorHistory[i][consecutive-1]) {
            total += i;
            sensorCount++;
        }
    }
    return (int) (total / (float) sensorCount);
}

int SensorIR::getEvent() {
    for (int i=0; i<numberOfSensors; i++)
        return getCountConsecutive(i);
    // (
    //     (
    //         (
    //             irSensor.phfmMinCount(sensNum, phfmNum)
    //         )
    //         ||
    //         irSensor.phfmCount(0, phfmNum)
    //     )
    //     && delayPassed(lastFinish, SCdelay)
    // )
}

// Get the number of sensors 
int SensorIR::getCount() {
    int count = 0;
    for (int i=0; i<numberOfSensors; i++)
        count += sensorHistory[i][consecutive-1];
    return count;
}

// Returns true when the given sensor was ON consecutive number of times
bool SensorIR::getCountConsecutive(int sensor) {
    //assert(sensor >= 0 && sensor < numberOfSensors);
    bool consecutiveOn;
    for (int i=1; i<=consecutive; i++)
        consecutiveOn &= getHistory(sensor, i);
    return consecutiveOn;
}

// Returns the index-nth last sensor-state for sensor: sensor.
bool SensorIR::getHistory(int sensor, int index) {
    //assert(sensor >= 0 && sensor < numberOfSensors);
    //assert(index >= 1 && index <= consecutive);
    int j;
    if (pivot - index < 0)
        j = maxConsecutive + (pivot - index);
    else
        j = pivot - index;
    return sensorHistory[sensor][j];
}


// Getter and setter methods
int SensorIR::getLimit() {
    return limit;
}
void SensorIR::setLimit(int _limit) {
    limit = _limit;
}
int SensorIR::getTarget() {
    return target;
}
void SensorIR::setTarget(int _target) {
    target = _target;
}
int SensorIR::getConsecutive() {
    return consecutive;
}
bool SensorIR::setConsecutive(int _consecutive) {
    consecutive = (_consecutive <= maxConsecutive
        ? _consecutive : maxConsecutive);
    return (_consecutive <= maxConsecutive);
}