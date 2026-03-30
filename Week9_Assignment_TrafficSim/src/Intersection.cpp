#include "Intersection.h"
#include "Constants.h"
#include <thread>
#include <chrono>

Intersection::Intersection(ILane* lane1, ILane* lane2, ILane* lane3, ILane* lane4, ITrafficLight* light)
: light_(light), running_(false), phaseInfo_{ Config::CYCLE_ORDER[0], 0, std::chrono::steady_clock::now() }
{
    lanes_[LaneId::NORTH] = lane1;
    lanes_[LaneId::EAST] = lane2;
    lanes_[LaneId::SOUTH] = lane3;
    lanes_[LaneId::WEST] = lane4;

    for (auto& [id, lane] : lanes_)
    {
        lane->setLight(light_);
    }
}

Intersection::~Intersection()
{
    stop();
}

void Intersection::start()
{
    running_ = true;
    controllerThread_ = std::thread(&Intersection::runController, this);
}

void Intersection::stop()
{
    if (running_.exchange(false))
    {
        for (auto& [id, lane] : lanes_)
        {
            lane->shutdown();
        }
        if (controllerThread_.joinable())
        {
            controllerThread_.join();
        }
    }
}

ILane* Intersection::getLane(LaneId laneId) const
{
    return lanes_.at(laneId);
}

PhaseInfo Intersection::getPhaseInfo() const
{
    std::lock_guard<std::mutex> lock(phaseMutex_);
    return phaseInfo_;
}

void Intersection::runController()
{
    int cycleIndex = 0;

    while (running_)
    {
        LaneId current = Config::CYCLE_ORDER[cycleIndex % Config::LANE_COUNT];
        runPhase(current);
        ++cycleIndex;
    }
}

void Intersection::runPhase(LaneId laneId)
{
    auto interruptibleSleep = [this](int seconds)
    {
        const int ticksPerSecond = 10;
        const int totalTicks = seconds * ticksPerSecond;

        for (int index = 0; index < totalTicks && running_; ++index)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };

    {
        std::lock_guard<std::mutex> lock(phaseMutex_);
        phaseInfo_ = { laneId, Timing::GREEN_DURATION, std::chrono::steady_clock::now() };
    }

    light_->setState(laneId, LightState::GREEN);
    lanes_.at(laneId)->release();

    for (int remaining = Timing::GREEN_DURATION; remaining > 0 && running_; --remaining)
    {
        {
            std::lock_guard<std::mutex> lock(phaseMutex_);
            phaseInfo_.secondsRemaining = remaining;
        }
        interruptibleSleep(1);
    }

    if (!running_) 
    return;

    {
        std::lock_guard<std::mutex> lock(phaseMutex_);
        phaseInfo_.secondsRemaining = Timing::YELLOW_DURATION;
    }

    light_->setState(laneId, LightState::YELLOW);
    lanes_.at(laneId)->stop();

    for (int remaining = Timing::YELLOW_DURATION; remaining > 0 && running_; --remaining)
    {
        {
            std::lock_guard<std::mutex> lock(phaseMutex_);
            phaseInfo_.secondsRemaining = remaining;
        }
        interruptibleSleep(1);
    }

    if (!running_) 
    return;

    light_->setState(laneId, LightState::RED);

    {
        std::lock_guard<std::mutex> lock(phaseMutex_);
        phaseInfo_.secondsRemaining = 0;
    }
}