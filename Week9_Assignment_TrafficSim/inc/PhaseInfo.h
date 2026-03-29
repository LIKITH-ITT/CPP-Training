#ifndef PHASEINFO_H
#define PHASEINFO_H

#include <chrono>
#include "Enums.h"

struct PhaseInfo
{
    LaneId currentGreen;
    int secondsRemaining;
    std::chrono::steady_clock::time_point phaseStart;
};

#endif 
