#ifndef _LINEFOLLOW_H_
#define _LINEFOLLOW_H_

#include "Arduino.h"

// A tuning profile structure
struct _profile {
    // char *name;
    float kp;
    float ki;
    float kd;
};
typedef struct _profile profile;

class LineFollow {
    public: 
        LineFollow(int ghost);
        int getAdjustment(profile profile, int error);
    private:
        int proportional, integral, derivative;
        int lastError;
};

#endif