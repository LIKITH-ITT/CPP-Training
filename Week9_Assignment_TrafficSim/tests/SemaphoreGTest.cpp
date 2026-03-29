#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

#include "Semaphore.h"

class GivenSemaphoreGTest : public ::testing::Test
{
protected:
    static constexpr int DEFAULT_COUNT = 3;
};

TEST_F(GivenSemaphoreGTest, WhenGetCountAtStartThenReturnsInitialCount)
{
    Semaphore sem(DEFAULT_COUNT);
    EXPECT_EQ(sem.getCount(), DEFAULT_COUNT);
}

TEST_F(GivenSemaphoreGTest, WhenGetCountAtStartWithZeroThenReturnsZero)
{
    Semaphore sem(0);
    EXPECT_EQ(sem.getCount(), 0);
}

TEST_F(GivenSemaphoreGTest, WhenAcquireIsCalledThenDecrementsCount)
{
    Semaphore sem(DEFAULT_COUNT);

    bool acquired = false;
    std::thread t([&]{ acquired = sem.acquire(); });
    t.join();

    EXPECT_TRUE(acquired);
    EXPECT_EQ(sem.getCount(), DEFAULT_COUNT - 1);
}

TEST_F(GivenSemaphoreGTest, WhenReleaseIsCalledThenIncrementsCount)
{
    Semaphore sem(DEFAULT_COUNT);

    std::thread([&]{ sem.acquire(); }).join();
    EXPECT_EQ(sem.getCount(), DEFAULT_COUNT - 1);

    sem.release();
    EXPECT_EQ(sem.getCount(), DEFAULT_COUNT);
}

TEST_F(GivenSemaphoreGTest, WhenAcquireIsCalledForAllSlotsThenExhaustsCount)
{
    Semaphore sem(DEFAULT_COUNT);

    std::vector<std::thread> threads;
    for (int i = 0; i < DEFAULT_COUNT; ++i)
    {
        threads.emplace_back([&]{ sem.acquire(); });
    }
    for (auto& t : threads) { t.join(); }

    EXPECT_EQ(sem.getCount(), 0);
}

TEST_F(GivenSemaphoreGTest, WhenAcquireWithZeroCountThenBlocksUntilRelease)
{
    Semaphore sem(1);

    std::thread([&]{ sem.acquire(); }).join();
    EXPECT_EQ(sem.getCount(), 0);

    std::atomic<bool> unblocked{false};

    std::thread waiter([&]
    {
        sem.acquire();
        unblocked = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_FALSE(unblocked.load());

    sem.release();
    waiter.join();
    EXPECT_TRUE(unblocked.load());
}

TEST_F(GivenSemaphoreGTest, WhenShutdownIsCalledThenUnblocksWaitingAcquire)
{
    Semaphore sem(0);

    std::atomic<bool> returned{false};
    bool acquireResult = true;

    std::thread waiter([&]
    {
        acquireResult = sem.acquire();
        returned = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_FALSE(returned.load());

    sem.shutdown();
    waiter.join();

    EXPECT_TRUE(returned.load());
    EXPECT_FALSE(acquireResult);
}

TEST_F(GivenSemaphoreGTest, WhenShutdownIsCalledThenPreventsSuccessfulAcquire)
{
    Semaphore sem(5);
    sem.shutdown();

    bool result = true;
    std::thread([&]{ result = sem.acquire(); }).join();

    EXPECT_FALSE(result);
}

TEST_F(GivenSemaphoreGTest, WhenAcquireAndReleaseAreCalledConcurrentlyThenMaintainsCapacity)
{
    const int capacity = 2;
    const int producers = 8;
    Semaphore sem(capacity);

    std::atomic<int> maxObserved{0};
    std::atomic<int> inside{0};
    std::vector<std::thread> threads;

    for (int i = 0; i < producers; ++i)
    {
        threads.emplace_back([&]
        {
            if (sem.acquire())
            {
                int cur = ++inside;
                int prev = maxObserved.load();
                while (cur > prev && !maxObserved.compare_exchange_weak(prev, cur)) {}

                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                --inside;
                sem.release();
            }
        });
    }

    for (auto& t : threads) { t.join(); }

    EXPECT_LE(maxObserved.load(), capacity);
    EXPECT_EQ(sem.getCount(), capacity);
}
