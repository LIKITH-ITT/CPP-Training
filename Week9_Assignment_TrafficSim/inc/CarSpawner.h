#pragma once

#include <thread>
#include <atomic>
#include "Enums.h"

class ILane;

// Continuously spawns car threads onto all four lanes.
// Every CAR_SPAWN_INTERVAL seconds one car thread is dispatched to each lane.
// Each car thread is immediately detached — it runs independently until the
// car has crossed, then decrements activeCars_ and exits.
class CarSpawner
{
public:
    CarSpawner(ILane* north, ILane* east, ILane* south, ILane* west);
    ~CarSpawner();

    void start();

    // Stops spawning new cars and blocks until every in-flight car thread
    // has finished so callers can safely destroy shared objects (lanes).
    void stop();

private:
    void runSpawner();
    void runCar(ILane* lane, int carId);

    ILane*            lanes_[4];
    std::thread       spawnerThread_;
    std::atomic<bool> running_;
    std::atomic<int>  nextCarId_;
    std::atomic<int>  activeCars_;
};