#pragma once

#include <mutex>
#include <condition_variable>
#include <chrono>
#include "ILane.h"
#include "Semaphore.h"

class Lane : public ILane
{
public:
    Lane(LaneId laneId);

    void enter() override;
    void stop() override;
    void release() override;
    void setLight(ITrafficLight* light) override;
    LaneId getLaneId() const override;
    void notify() override;
    int getWaitSeconds() const override;
    int getCarsInside() const override;

private:
    LaneId laneId_;
    Semaphore semaphore_;
    mutable std::mutex mutex_;
    std::condition_variable conditionVariable_;
    ITrafficLight* light_;
    bool stopped_;
    std::chrono::steady_clock::time_point phaseStart_;
    int carsInside_;
};
