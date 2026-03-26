#pragma once

#include <atomic>
#include "IConsoleUI.h"
#include "QueryEngine.h"

class Intersection;

class Simulation
{
public:
    Simulation(Intersection* intersection);

    void setUI(IConsoleUI* ui);
    void run();
    void stop();

private:
    void runQueryLoop();

    Intersection* intersection_;
    IConsoleUI* ui_;
    QueryEngine query_;
    std::atomic<bool> running_;
    std::atomic<bool> stopped_;
};
