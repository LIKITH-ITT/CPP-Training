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

// ── Global shutdown flag ──────────────────────────────────────────────────────
static std::atomic<bool> g_shutdown{ false };

static void signalHandler(int /*sig*/)
{
    g_shutdown = true;
}

// ── main ─────────────────────────────────────────────────────────────────────
int main()
{
    std::signal(SIGINT, signalHandler);

    // ── Build the object graph bottom-up ─────────────────────────────────────

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

    // ── Start threads ─────────────────────────────────────────────────────────
    intersection.start();
    spawner.start();

    // ── Auto-stop after SIMULATION_DURATION seconds ───────────────────────────
    std::thread timerThread([&sim]()
    {
        std::this_thread::sleep_for(
            std::chrono::seconds(Timing::SIMULATION_DURATION));
        sim.stop();
    });
    timerThread.detach();

    // ── Interactive query loop (blocks until user quits or timer fires) ────────
    sim.run();

    // ── Teardown — order matters ───────────────────────────────────────────────
    // 1. Stop the light controller so no new GREEN signals are issued.
    // 2. intersection.stop() releases all lanes, unblocking any car thread
    //    stuck in lane.enter() so it can finish and decrement activeCars_.
    // 3. spawner.stop() joins the spawner thread then spin-waits until
    //    activeCars_ == 0, guaranteeing ui and lanes are not touched after
    //    this point.
    intersection.stop();
    spawner.stop();

    std::cout << "\nSimulation ended. Goodbye.\n";

    return 0;
}