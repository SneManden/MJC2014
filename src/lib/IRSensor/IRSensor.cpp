#include "IRSensor.h"

// static int sensorHistory[2][35];//NUMBEROFSENSORS][MAXCONSECUTIVE];

#define SERIALDISABLEPIN 22
#define sprint(X) do { if (!digitalRead(SERIALDISABLEPIN)) Serial.print(X); } while (0)
#define sprintln(X) do { if (!digitalRead(SERIALDISABLEPIN)) Serial.println(X); } while (0)

// Constructor
SensorIR::SensorIR(int _limit, int _numberOfSensors, int _maxConsecutive) {
    limit = _limit;
    target = (numberOfSensors-1)/2.0;
    numberOfSensors = _numberOfSensors; //_numberOfSensors;
    // The number of consecutive readings
    // before some events are accepted
    maxConsecutive = _maxConsecutive;//_maxConsecutive;
    consecutive = maxConsecutive;
    // Setup history arrays for each sensor
    // sprintln("Trying to allocate memory for the history.");
    // sprint("  need: ");
    // sprint( sizeof(int) * maxConsecutive * numberOfSensors );
    // sprintln(" bytes");
    // sensorHistory = NULL;/*(int **) malloc(
    //     sizeof(int) * maxConsecutive * numberOfSensors
    // );*/
    // if (sensorHistory == NULL)
    //     sprintln(" => Error allocating memory to history array");

    pivot = 0;
}
void SensorIR::init() {
    sprintln("Trying to allocate memory for the history.");
    sprint("  need: ");
    sprint( sizeof(bool) * maxConsecutive * numberOfSensors );
    sprintln(" bytes");
    sensorHistory = (bool **) malloc(
        sizeof(bool) * maxConsecutive * numberOfSensors
    );
    if (sensorHistory == NULL)
        sprintln(" => Error allocating memory to history array");
    else
        sprintln(" => Succes: memory allocated");
}
int SensorIR::getError() {
    return target - getPosition();
}

void SensorIR::update() {
    if (pivot < 0 || pivot >= maxConsecutive)
        return;
    bool val;
    for (int i=0; i<numberOfSensors; i++) {
        val = (analogRead(i) > limit);
        // sprint("val = ");
        // sprint(val);
        // sprint(" (analogRead: ");
        // sprint(analogRead(i));
        // sprint(")");
        sensorHistory[i][pivot] = val;
        // sprint(" => wrote ");
        // sprint( sensorHistory[i][pivot] );
        // sprint(" at index=");
        // sprintln(pivot);
    }
    pivot = (pivot+1) % maxConsecutive;
    // sprint("pivot is now ");
    // sprintln(pivot);
}

int SensorIR::getPosition() {
    int total, sensorCount;
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
    return 0;
    // for (int i=0; i<numberOfSensors; i++)
    //     return getCountConsecutive(i);
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
        count += getHistory(i, consecutive); //sensorHistory[i][consecutive-1];
    return count;
}

// Returns true when the given sensor was ON consecutive number of times
bool SensorIR::getCountConsecutive(int sensor) {
    //assert(sensor >= 0 && sensor < numberOfSensors);
    bool consecutiveOn = 1;
    for (int i=1; i<=consecutive; i++)
        consecutiveOn *= getHistory(sensor, i);
    return consecutiveOn;
}

// Returns the index-nth last sensor-state for sensor: sensor.
bool SensorIR::getHistory(int sensor, int index) {
    //assert(sensor >= 0 && sensor < numberOfSensors);
    //assert(index >= 1 && index <= consecutive);
    // return sensorHistory[sensor][0];

    if (sensor < 0 || sensor >= numberOfSensors)
        return 0;
    if (index < 1 || index > consecutive)
        return 0;

    int j;
    if (pivot - index < 0)
        j = maxConsecutive + (pivot - index);
    else
        j = pivot - index;
    // sprint("reading at index ");
    // sprint(j);
    // sprint(" => ");
    // sprintln(sensorHistory[sensor][j]);
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