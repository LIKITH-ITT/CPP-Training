#include "Semaphore.h"

Semaphore::Semaphore(int count) : count_(count)
{}

void Semaphore::acquire()
{
    std::unique_lock<std::mutex> lock(mutex_);
    conditionVariable_.wait(lock, [this]{ return count_ > 0; });
    --count_;
}

void Semaphore::release()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        ++count_;
    }
    conditionVariable_.notify_one();
}

int Semaphore::getCount() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return count_;
}
