#pragma once

#include "Enums.h"

class ITrafficLight
{
public:
    virtual ~ITrafficLight() = default;

    virtual LightState getState(LaneId laneId) const = 0;
    virtual void setState(LaneId laneId, LightState st) = 0;
};
