#include "Lane.h"
#include "ITrafficLight.h"
#include "Constants.h"
#include <thread>
#include <chrono>

Lane::Lane(LaneId laneId) : laneId_(laneId), semaphore_(Config::MAX_CARS), light_(nullptr), stopped_(true), phaseStart_(std::chrono::steady_clock::now()), carsInside_(0)
{}

void Lane::enter()
{
    {
        std::unique_lock<std::mutex> lock(mutex_);
        conditionVariable_.wait(lock, [this]
        {
            return !stopped_ && light_ != nullptr && light_->getState(laneId_) == LightState::GREEN;
        });
    }
    semaphore_.acquire();
    {
        std::lock_guard<std::mutex> lock(mutex_);
        ++carsInside_;
    }
    std::this_thread::sleep_for(
        std::chrono::seconds(Timing::CAR_CROSS_DURATION));
    {
        std::lock_guard<std::mutex> lock(mutex_);
        --carsInside_;
    }
    semaphore_.release();
}

int Lane::getCarsInside() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return carsInside_;
}

void Lane::stop()
{
    std::lock_guard<std::mutex> lock(mutex_);
    stopped_ = true;
}

void Lane::release()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stopped_ = false;
        phaseStart_ = std::chrono::steady_clock::now();
    }
    conditionVariable_.notify_all();
}

void Lane::setLight(ITrafficLight* light)
{
    std::lock_guard<std::mutex> lock(mutex_);
    light_ = light;
}

LaneId Lane::getLaneId() const
{
    return laneId_;
}

void Lane::notify()
{
    conditionVariable_.notify_all();
}

int Lane::getWaitSeconds() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto elapsed = std::chrono::steady_clock::now() - phaseStart_;
    return static_cast<int>( std::chrono::duration_cast<std::chrono::seconds>(elapsed).count());
}