#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <map>
#include <thread>
#include <mutex>
#include <atomic>
#include "ILane.h"
#include "ITrafficLight.h"
#include "PhaseInfo.h"

class Intersection
{
public:
    Intersection(ILane* lane1, ILane* lane2, ILane* lane3, ILane* lane4, ITrafficLight* light);

    ~Intersection();

    void start();
    void stop();

    ILane* getLane(LaneId laneId) const;
    PhaseInfo getPhaseInfo() const;

private:
    void runController();
    void runPhase(LaneId laneId);

    std::map<LaneId, ILane*> lanes_;
    ITrafficLight* light_;
    std::thread controllerThread_;
    std::atomic<bool> running_;
    PhaseInfo phaseInfo_;
    mutable std::mutex phaseMutex_;
};

#endif 
