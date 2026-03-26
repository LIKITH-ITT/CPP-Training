#pragma once

#include "Enums.h"

class ITrafficLight;

class ILane
{
public:
    virtual ~ILane() = default;

    virtual void enter() = 0;
    virtual void stop() = 0;
    virtual void release() = 0;
    virtual void setLight(ITrafficLight* light) = 0;
    virtual LaneId getLaneId() const = 0;
    virtual void notify() = 0;
    virtual int getWaitSeconds() const = 0;
    virtual int  getCarsInside() const = 0;
};
