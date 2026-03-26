#pragma once

#include <string>
#include "Enums.h"

namespace Timing
{
    constexpr int GREEN_DURATION = 10;
    constexpr int YELLOW_DURATION = 3;
    constexpr int CAR_CROSS_DURATION = 2;
    constexpr int CAR_SPAWN_INTERVAL = 5;
    constexpr int SIMULATION_DURATION = 60;
}

namespace Config
{
    constexpr int MAX_CARS = 4;
    constexpr int LANE_COUNT = 4;
    const LaneId CYCLE_ORDER[LANE_COUNT] = {LaneId::NORTH, LaneId::EAST, LaneId::SOUTH, LaneId::WEST};
}

namespace UI
{
    const std::string HEADER    = "===================================\n"
                                  "   Traffic Intersection Simulator  \n"
                                  "===================================";
    const std::string SEPARATOR = "──────────────────────────────────";
    const std::string PROMPT_FROM = "Enter your lane  [N/S/E/W]: ";
    const std::string PROMPT_TO = "Enter destination [N/S/E/W]: ";
    const std::string STATUS_GREEN = "[GREEN ] ";
    const std::string STATUS_RED = "[RED   ] ";
    const std::string STATUS_FREE = "[FREE  ] ";
}
