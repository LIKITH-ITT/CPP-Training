#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include <atomic>
#include <chrono>

#include "CarSpawner.h"
#include "MockLane.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::AtLeast;

class GivenCarSpawnerGTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        ON_CALL(north_, getLaneId()).WillByDefault(Return(LaneId::NORTH));
        ON_CALL(east_,  getLaneId()).WillByDefault(Return(LaneId::EAST));
        ON_CALL(south_, getLaneId()).WillByDefault(Return(LaneId::SOUTH));
        ON_CALL(west_,  getLaneId()).WillByDefault(Return(LaneId::WEST));
        EXPECT_CALL(north_, getLaneId()).Times(AnyNumber());
        EXPECT_CALL(east_,  getLaneId()).Times(AnyNumber());
        EXPECT_CALL(south_, getLaneId()).Times(AnyNumber());
        EXPECT_CALL(west_,  getLaneId()).Times(AnyNumber());

        EXPECT_CALL(north_, enter()).Times(AnyNumber());
        EXPECT_CALL(east_,  enter()).Times(AnyNumber());
        EXPECT_CALL(south_, enter()).Times(AnyNumber());
        EXPECT_CALL(west_,  enter()).Times(AnyNumber());
    }

    MockLane north_, east_, south_, west_;
};

TEST_F(GivenCarSpawnerGTest, WhenConstructIsCalledThenDoesNotCrash)
{
    EXPECT_NO_FATAL_FAILURE(
    {
        CarSpawner spawner(&north_, &east_, &south_, &west_);
    });
}

TEST_F(GivenCarSpawnerGTest, WhenDestructWithoutStartThenDoesNotCrash)
{
    EXPECT_NO_FATAL_FAILURE(
    {
        CarSpawner spawner(&north_, &east_, &south_, &west_);
    });
}

TEST_F(GivenCarSpawnerGTest, WhenStartAndStopAreCalledThenDoNotCrash)
{
    CarSpawner spawner(&north_, &east_, &south_, &west_);
    EXPECT_NO_FATAL_FAILURE(
    {
        spawner.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        spawner.stop();
    });
}

TEST_F(GivenCarSpawnerGTest, WhenStopIsCalledMultipleTimesThenItIsIdempotent)
{
    CarSpawner spawner(&north_, &east_, &south_, &west_);
    spawner.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    spawner.stop();
    EXPECT_NO_FATAL_FAILURE(spawner.stop());
}

TEST_F(GivenCarSpawnerGTest, WhenStopIsCalledWithoutStartThenDoesNotCrash)
{
    CarSpawner spawner(&north_, &east_, &south_, &west_);
    EXPECT_NO_FATAL_FAILURE(spawner.stop());
}

TEST_F(GivenCarSpawnerGTest, WhenSpawnerRunsThenCallsEnterOnAllFourLanes)
{
    EXPECT_CALL(north_, enter()).Times(AtLeast(1));
    EXPECT_CALL(east_,  enter()).Times(AtLeast(1));
    EXPECT_CALL(south_, enter()).Times(AtLeast(1));
    EXPECT_CALL(west_,  enter()).Times(AtLeast(1));

    CarSpawner spawner(&north_, &east_, &south_, &west_);
    spawner.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    spawner.stop();
}

TEST_F(GivenCarSpawnerGTest, WhenStopIsCalledThenBlocksUntilAllCarThreadsFinish)
{
    std::atomic<int> enterCallsDone{0};

    ON_CALL(north_, enter()).WillByDefault([&]
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ++enterCallsDone;
    });
    ON_CALL(east_, enter()).WillByDefault([&]
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ++enterCallsDone;
    });
    ON_CALL(south_, enter()).WillByDefault([&]
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ++enterCallsDone;
    });
    ON_CALL(west_, enter()).WillByDefault([&]
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ++enterCallsDone;
    });

    CarSpawner spawner(&north_, &east_, &south_, &west_);
    spawner.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    spawner.stop();

    int done = enterCallsDone.load();
    EXPECT_GT(done, 0);
}
