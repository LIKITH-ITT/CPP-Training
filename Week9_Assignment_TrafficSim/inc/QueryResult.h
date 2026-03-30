#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include "Enums.h"

struct QueryResult
{
    LaneId fromLane;
    LaneId toLane;
    MoveType moveType;
    LaneId currentGreen;
    LightState laneState;
    int secondsRemaining;
    int waitSeconds;
    int carsInside;
    int estDelaySecs;
};

#endif 
