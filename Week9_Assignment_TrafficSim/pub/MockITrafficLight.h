#pragma once

#include <gmock/gmock.h>
#include "ITrafficLight.h"

class MockTrafficLight : public ITrafficLight
{
public:
    MOCK_METHOD(LightState, getState, (LaneId laneId), (const, override));
    MOCK_METHOD(void, setState, (LaneId laneId, LightState st), (override));
};