#include "LineFollow.h"


// Constructor
LineFollow::LineFollow() {
    proportional = 0;
    integral = 0;
    derivative = 0;

    lastError = 0;
}
// Get adjustment for PID line following
int LineFollow::getAdjustment(profile profile, int error) {
    int adjust;

    // Calulating the PID adjustment constant
    proportional = profile.kp * error;
    integral     = profile.ki * (integral + error);
    derivative   = profile.kd * (error - lastError);
    adjust = proportional + integral + derivative;

    lastError = error;

    return adjust;
}