#include "Semaphore.h"

Semaphore::Semaphore(int count) : count_(count), shutdown_(false)
{}

bool Semaphore::acquire()
{
    std::unique_lock<std::mutex> lock(mutex_);
    conditionVariable_.wait(lock, [this]{ return count_ > 0 || shutdown_;
    });

    bool result = false;
    if (!shutdown_)
    {
        --count_;
        result = true;
    }
    return result;
}

void Semaphore::release()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        ++count_;
    }
    conditionVariable_.notify_one();
}

void Semaphore::shutdown()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        shutdown_ = true;
    }
    conditionVariable_.notify_all();
}

int Semaphore::getCount() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return count_;
}