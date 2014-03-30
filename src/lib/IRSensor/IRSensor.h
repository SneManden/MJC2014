#ifndef _SENSORIR_H_
#define _SENSORIR_H_

#include "Arduino.h"

// class SensorIR
// {
//     public:
//         SensorIR(int limit);
//         int getMean();
//         int getCount();
//         int getLimit();
//         void setLimit(int limit);
//         bool phfm(String sensors, int readings);
//         bool phfmToggle(String sensors, bool on, int readings);
//         bool phfmCount(int sensors, int readings);
//         bool phfmMinCount(int sensors, int readings);
//     private:
//         int _limit;
// };

class SensorIR {
    public:
        SensorIR(int _limit, int _numberOfSensors, int _maxConsecutive);
        void update();
        int getPosition();
        int getError();
        int getEvent();
        int getCount();
        bool getCountConsecutive(int sensor);
        bool getHistory(int sensor, int index);
        // Getter and setters
        int getLimit();
        void setLimit(int _limit);
        int getTarget();
        void setTarget(int _target);
        int getConsecutive();
        bool setConsecutive(int _consecutive);
        bool **sensorHistory;
        void init();
    private:
        int limit;
        int pivot;
        int target;
        int consecutive;
        int maxConsecutive;
        int numberOfSensors;
};

#endif