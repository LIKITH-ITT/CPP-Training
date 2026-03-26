#pragma once

#include "Enums.h"
#include <string>

struct QueryResult;

class IConsoleUI
{
public:
    virtual ~IConsoleUI() = default;

    virtual void showWelcome() = 0;
    virtual void showIntersection() = 0;
    virtual LaneId promptLane(const std::string& prompt) = 0;
    virtual void showStatus(const QueryResult& result) = 0;
    virtual bool askRepeat() = 0;
};
