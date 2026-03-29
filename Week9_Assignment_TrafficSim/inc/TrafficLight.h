#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <map>
#include <mutex>
#include "ITrafficLight.h"
#include "ILane.h"

class TrafficLight : public ITrafficLight
{
public:
    TrafficLight(ILane* lane1, ILane* lane2, ILane* lane3, ILane* lane4);

    LightState getState(LaneId laneId) const override;
    void setState(LaneId laneId, LightState st) override;

private:
    std::map<LaneId, LightState> states_;
    std::map<LaneId, ILane*> lanes_;
    mutable std::mutex mutex_;
};

#endif 
