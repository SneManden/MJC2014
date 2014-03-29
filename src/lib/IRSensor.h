#ifndef _SENSORIR_H_
#define _SENSORIR_H_

#include "Arduino.h"

class SensorIR
{
    public:
        SensorIR(int limit);
        int getMean();
        int getCount();
        int getLimit();
        void setLimit(int limit);
        bool phfm(String sensors, int readings);
        bool phfmToggle(String sensors, bool on, int readings);
        bool phfmCount(int sensors, int readings);
        bool phfmMinCount(int sensors, int readings);
    private:
        int _limit;
};

#endif