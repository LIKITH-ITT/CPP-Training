#pragma once

#include <gmock/gmock.h>
#include "IConsoleUI.h"

class MockConsoleUI : public IConsoleUI
{
public:
    MOCK_METHOD(void, showWelcome, (), (override));
    MOCK_METHOD(void, showIntersection, (), (override));
    MOCK_METHOD(LaneId, promptLane, (const std::string& prompt), (override));
    MOCK_METHOD(void, showStatus, (const QueryResult& result), (override));
    MOCK_METHOD(bool, askRepeat, (), (override));
};