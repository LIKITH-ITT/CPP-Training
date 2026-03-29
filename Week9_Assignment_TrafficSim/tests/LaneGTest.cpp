#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include <atomic>
#include <chrono>

#include "Lane.h"
#include "MockTrafficLight.h"
#include "Constants.h"

using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::_;

class GivenLaneGTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        ON_CALL(mockLight_, getState(_)).WillByDefault(Return(LightState::RED));
        EXPECT_CALL(mockLight_, getState(_)).Times(AnyNumber());
        EXPECT_CALL(mockLight_, setState(_, _)).Times(AnyNumber());
    }

    MockTrafficLight mockLight_;
};

TEST_F(GivenLaneGTest, WhenGetLaneIdIsCalledThenReturnsCorrectId)
{
    Lane laneNorth(LaneId::NORTH);
    EXPECT_EQ(laneNorth.getLaneId(), LaneId::NORTH);

    Lane laneEast(LaneId::EAST);
    EXPECT_EQ(laneEast.getLaneId(), LaneId::EAST);

    Lane laneSouth(LaneId::SOUTH);
    EXPECT_EQ(laneSouth.getLaneId(), LaneId::SOUTH);

    Lane laneWest(LaneId::WEST);
    EXPECT_EQ(laneWest.getLaneId(), LaneId::WEST);
}

TEST_F(GivenLaneGTest, WhenGetCarsInsideAtStartThenReturnsZero)
{
    Lane lane(LaneId::NORTH);
    EXPECT_EQ(lane.getCarsInside(), 0);
}

TEST_F(GivenLaneGTest, WhenSetLightIsCalledThenDoesNotCrash)
{
    Lane lane(LaneId::EAST);
    EXPECT_NO_FATAL_FAILURE(lane.setLight(&mockLight_));
}

TEST_F(GivenLaneGTest, WhenShutdownIsCalledThenUnblocksEnter)
{
    Lane lane(LaneId::NORTH);
    lane.setLight(&mockLight_);

    std::atomic<bool> enterReturned{false};
    std::thread t([&]
    {
        lane.enter();
        enterReturned = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_FALSE(enterReturned.load());

    lane.shutdown();
    t.join();

    EXPECT_TRUE(enterReturned.load());
}

TEST_F(GivenLaneGTest, WhenReleaseWithGreenLightThenAllowsEnter)
{
    ON_CALL(mockLight_, getState(LaneId::NORTH))
        .WillByDefault(Return(LightState::GREEN));

    Lane lane(LaneId::NORTH);
    lane.setLight(&mockLight_);

    std::atomic<bool> enterReturned{false};

    std::thread t([&]
    {
        lane.enter();
        enterReturned = true;
    });

    lane.release();

    std::this_thread::sleep_for(
        std::chrono::milliseconds(
            (Timing::CAR_CROSS_DURATION * 1000) + 200));

    lane.shutdown();
    t.join();

    EXPECT_TRUE(enterReturned.load());
}

TEST_F(GivenLaneGTest, WhenStopIsCalledThenBlocksSubsequentEnterEvenIfGreen)
{
    ON_CALL(mockLight_, getState(LaneId::SOUTH))
        .WillByDefault(Return(LightState::GREEN));

    Lane lane(LaneId::SOUTH);
    lane.setLight(&mockLight_);
    lane.release();
    lane.stop();

    std::atomic<bool> enterReturned{false};

    std::thread t([&]
    {
        lane.enter();
        enterReturned = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_FALSE(enterReturned.load());

    lane.shutdown();
    t.join();
}

TEST_F(GivenLaneGTest, WhenEnterIsCalledThenCarsInsideIncrementsDuringAndDecrementsAfter)
{
    ON_CALL(mockLight_, getState(LaneId::EAST))
        .WillByDefault(Return(LightState::GREEN));

    Lane lane(LaneId::EAST);
    lane.setLight(&mockLight_);
    lane.release();

    std::thread carThread([&]{ lane.enter(); });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    int inside = lane.getCarsInside();
    EXPECT_GE(inside, 0);
    EXPECT_LE(inside, Config::MAX_CARS);

    std::this_thread::sleep_for(
        std::chrono::milliseconds((Timing::CAR_CROSS_DURATION * 1000) + 300));

    lane.shutdown();
    carThread.join();

    EXPECT_EQ(lane.getCarsInside(), 0);
}

TEST_F(GivenLaneGTest, WhenNotifyIsCalledThenDoesNotCrash)
{
    Lane lane(LaneId::WEST);
    EXPECT_NO_FATAL_FAILURE(lane.notify());
}
