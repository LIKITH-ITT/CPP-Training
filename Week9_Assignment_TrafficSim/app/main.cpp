#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <atomic>

#include "Enums.h"
#include "Constants.h"
#include "Semaphore.h"
#include "Lane.h"
#include "TrafficLight.h"
#include "Intersection.h"
#include "QueryEngine.h"
#include "ConsoleUI.h"
#include "Simulation.h"
#include "CarSpawner.h"

static std::atomic<bool> g_shutdown{ false };

static void signalHandler(int)
{
    g_shutdown = true;
}

int main()
{
    std::signal(SIGINT, signalHandler);

    Lane laneNorth(LaneId::NORTH);
    Lane laneEast (LaneId::EAST);
    Lane laneSouth(LaneId::SOUTH);
    Lane laneWest (LaneId::WEST);

    TrafficLight light(&laneNorth, &laneEast, &laneSouth, &laneWest);

    Intersection intersection(&laneNorth, &laneEast, &laneSouth, &laneWest, &light);

    ConsoleUI ui;

    CarSpawner spawner(&laneNorth, &laneEast, &laneSouth, &laneWest);

    Simulation sim(&intersection);
    sim.setUI(&ui);

    intersection.start();
    spawner.start();

    sim.run();

    intersection.stop();
    spawner.stop();

    std::cout << "\nSimulation ended. Goodbye.\n";

    return 0;
}