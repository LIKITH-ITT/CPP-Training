#pragma once

#include <mutex>
#include <string>
#include "IConsoleUI.h"
#include "QueryResult.h"

class ConsoleUI : public IConsoleUI
{
public:
    ConsoleUI() = default;

    void showWelcome() override;
    void showIntersection() override;
    LaneId promptLane(const std::string& prompt) override;
    void showStatus(const QueryResult& result) override;
    bool askRepeat() override;

private:
    void print(const std::string& msg) const;
    LaneId parseLane(char c) const;
    bool parseLaneInput(const std::string& line, char& c) const;
    bool parseYesNoInput(const std::string& line, bool& value) const;
    std::string laneToString(LaneId id) const;
    std::string moveToString(MoveType m) const;
    std::string stateToString(LightState s) const;

    mutable std::mutex printMutex_;
};