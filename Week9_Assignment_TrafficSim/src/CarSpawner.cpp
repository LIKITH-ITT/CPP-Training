#include "CarSpawner.h"
#include "ILane.h"
#include "Constants.h"
#include <thread>
#include <chrono>

CarSpawner::CarSpawner(ILane* north, ILane* east, ILane* south, ILane* west)
    : running_(false)
    , nextCarId_(1)
    , activeCars_(0)
{
    lanes_[0] = north;
    lanes_[1] = east;
    lanes_[2] = south;
    lanes_[3] = west;
}

CarSpawner::~CarSpawner()
{
    stop();
}

void CarSpawner::start()
{
    running_       = true;
    spawnerThread_ = std::thread(&CarSpawner::runSpawner, this);
}

void CarSpawner::stop()
{
    if (running_.exchange(false))
    {
        if (spawnerThread_.joinable())
        {
            spawnerThread_.join();
        }
        // Spin-wait until every detached car thread has finished.
        // Intersection::stop() must be called before this so that any car
        // thread blocked in lane.enter() is unblocked via lane.shutdown().
        while (activeCars_.load() > 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

// ── Private ───────────────────────────────────────────────────────────────────

void CarSpawner::runSpawner()
{
    while (running_)
    {
        std::this_thread::sleep_for(
            std::chrono::seconds(Timing::CAR_SPAWN_INTERVAL));

        if (!running_) { break; }

        for (int i = 0; i < Config::LANE_COUNT; ++i)
        {
            int    carId = nextCarId_++;
            ILane* lane  = lanes_[i];

            ++activeCars_;
            std::thread t(&CarSpawner::runCar, this, lane, carId);
            t.detach();
        }
    }
}

// Car thread — silently enters the lane and crosses.
// No logging; car activity is reflected only via Lane::getCarsInside()
// which QueryEngine reads when building a QueryResult.
void CarSpawner::runCar(ILane* lane, int carId)
{
    (void)carId;        // id reserved for future use
    lane->enter();      // blocks until green + semaphore slot free, then crosses
    --activeCars_;
}