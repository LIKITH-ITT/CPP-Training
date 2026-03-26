#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
    explicit Semaphore(int count);

    void acquire();
    void release();
    int  getCount() const;

private:
    int count_;
    mutable std::mutex mutex_;
    std::condition_variable conditionVariable_;
};
