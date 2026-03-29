#include "CarSpawner.h"
#include "ILane.h"
#include "Constants.h"
#include <thread>
#include <chrono>

CarSpawner::CarSpawner(ILane* north, ILane* east, ILane* south, ILane* west) : running_(false), nextCarId_(1), activeCars_(0)
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
    running_ = true;
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
        while (activeCars_.load() > 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

void CarSpawner::runSpawner()
{
    const int tickMs = 100;
    const int totalTicks = (Timing::CAR_SPAWN_INTERVAL * 1000) / tickMs;

    while (running_)
    {
        for (int t = 0; t < totalTicks && running_; ++t)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(tickMs));
        }

        if (!running_) { break; }

        for (int i = 0; i < Config::LANE_COUNT; ++i)
        {
            int carId = nextCarId_++;
            ILane* lane = lanes_[i];

            ++activeCars_;
            std::thread t(&CarSpawner::runCar, this, lane, carId);
            t.detach();
        }
    }
}

void CarSpawner::runCar(ILane* lane, int carId)
{
    (void)carId;
    lane->enter();
    --activeCars_;
}