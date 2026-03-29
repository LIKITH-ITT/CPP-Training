#pragma once

#include <gmock/gmock.h>
#include "ILane.h"

class MockLane : public ILane
{
public:
    MOCK_METHOD(void, enter, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, release, (), (override));
    MOCK_METHOD(void, shutdown, (), (override));
    MOCK_METHOD(void, setLight, (ITrafficLight* light), (override));
    MOCK_METHOD(LaneId, getLaneId, (), (const, override));
    MOCK_METHOD(void, notify, (), (override));
    MOCK_METHOD(int, getWaitSeconds, (), (const, override));
    MOCK_METHOD(int, getCarsInside, (), (const, override));
};