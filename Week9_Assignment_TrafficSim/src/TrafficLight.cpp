#include "TrafficLight.h"
#include "Constants.h"

TrafficLight::TrafficLight(ILane* lane1, ILane* lane2, ILane* lane3, ILane* lane4)
{
    const ILane* lanesArr[Config::LANE_COUNT] = { lane1, lane2, lane3, lane4 };

    for (int i = 0; i < Config::LANE_COUNT; ++i)
    {
        LaneId id = Config::CYCLE_ORDER[i];
        states_[id] = LightState::RED;
        (void)lanesArr[i];
    }

    lanes_[LaneId::NORTH] = lane1;
    lanes_[LaneId::EAST] = lane2;
    lanes_[LaneId::SOUTH] = lane3;
    lanes_[LaneId::WEST] = lane4;
}

LightState TrafficLight::getState(LaneId laneId) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return states_.at(laneId);
}

void TrafficLight::setState(LaneId laneId, LightState st)
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        states_[laneId] = st;
    }
    lanes_.at(laneId)->notify();
}
