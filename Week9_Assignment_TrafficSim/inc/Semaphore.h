#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
    explicit Semaphore(int count);

    bool acquire();
    void release();
    int getCount() const;
    void shutdown();

private:
    int count_;
    bool shutdown_;
    mutable std::mutex mutex_;
    std::condition_variable conditionVariable_;
};

#endif 
