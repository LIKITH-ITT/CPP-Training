#ifndef CARSPAWNER_H
#define CARSPAWNER_H

#include <thread>
#include <atomic>
#include "Enums.h"

class ILane;

class CarSpawner
{
public:
    CarSpawner(ILane* north, ILane* east, ILane* south, ILane* west);
    ~CarSpawner();

    void start();

    void stop();

private:
    void runSpawner();
    void runCar(ILane* lane, int carId);

    ILane* lanes_[4];
    std::thread spawnerThread_;
    std::atomic<bool> running_;
    std::atomic<int> nextCarId_;
    std::atomic<int> activeCars_;
};

#endif 