#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include <chrono>

#include "Intersection.h"
#include "MockILane.h"
#include "MockITrafficLight.h"
#include "Constants.h"

using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::_;

class GivenIntersectionGTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        EXPECT_CALL(north_, setLight(_)).Times(AnyNumber());
        EXPECT_CALL(east_,  setLight(_)).Times(AnyNumber());
        EXPECT_CALL(south_, setLight(_)).Times(AnyNumber());
        EXPECT_CALL(west_,  setLight(_)).Times(AnyNumber());

        EXPECT_CALL(north_, shutdown()).Times(AnyNumber());
        EXPECT_CALL(east_,  shutdown()).Times(AnyNumber());
        EXPECT_CALL(south_, shutdown()).Times(AnyNumber());
        EXPECT_CALL(west_,  shutdown()).Times(AnyNumber());

        EXPECT_CALL(north_, notify()).Times(AnyNumber());
        EXPECT_CALL(east_,  notify()).Times(AnyNumber());
        EXPECT_CALL(south_, notify()).Times(AnyNumber());
        EXPECT_CALL(west_,  notify()).Times(AnyNumber());

        EXPECT_CALL(north_, release()).Times(AnyNumber());
        EXPECT_CALL(east_,  release()).Times(AnyNumber());
        EXPECT_CALL(south_, release()).Times(AnyNumber());
        EXPECT_CALL(west_,  release()).Times(AnyNumber());
        EXPECT_CALL(north_, stop()).Times(AnyNumber());
        EXPECT_CALL(east_,  stop()).Times(AnyNumber());
        EXPECT_CALL(south_, stop()).Times(AnyNumber());
        EXPECT_CALL(west_,  stop()).Times(AnyNumber());

        ON_CALL(light_, getState(_)).WillByDefault(Return(LightState::RED));
        EXPECT_CALL(light_, getState(_)).Times(AnyNumber());
        EXPECT_CALL(light_, setState(_, _)).Times(AnyNumber());

        intersection_ = std::make_unique<Intersection>(
            &north_, &east_, &south_, &west_, &light_);
    }

    MockLane north_, east_, south_, west_;
    MockTrafficLight light_;
    std::unique_ptr<Intersection> intersection_;
};

TEST_F(GivenIntersectionGTest, WhenGetLaneWithNorthThenReturnsCorrectPointer)
{
    EXPECT_EQ(intersection_->getLane(LaneId::NORTH), &north_);
}

TEST_F(GivenIntersectionGTest, WhenGetLaneWithEastThenReturnsCorrectPointer)
{
    EXPECT_EQ(intersection_->getLane(LaneId::EAST), &east_);
}

TEST_F(GivenIntersectionGTest, WhenGetLaneWithSouthThenReturnsCorrectPointer)
{
    EXPECT_EQ(intersection_->getLane(LaneId::SOUTH), &south_);
}

TEST_F(GivenIntersectionGTest, WhenGetLaneWithWestThenReturnsCorrectPointer)
{
    EXPECT_EQ(intersection_->getLane(LaneId::WEST), &west_);
}

TEST_F(GivenIntersectionGTest, WhenGetPhaseInfoAtStartThenInitialPhaseIsFirstInCycleOrder)
{
    PhaseInfo info = intersection_->getPhaseInfo();
    EXPECT_EQ(info.currentGreen, Config::CYCLE_ORDER[0]);
}

TEST_F(GivenIntersectionGTest, WhenStartAndStopAreCalledThenDoNotCrash)
{
    EXPECT_NO_FATAL_FAILURE(
    {
        intersection_->start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        intersection_->stop();
    });
}

TEST_F(GivenIntersectionGTest, WhenStopIsCalledMultipleTimesThenItIsIdempotent)
{
    intersection_->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    intersection_->stop();
    EXPECT_NO_FATAL_FAILURE(intersection_->stop());
}

TEST_F(GivenIntersectionGTest, WhenPhaseRunsThenSecondsRemainingIsNonNegative)
{
    intersection_->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    PhaseInfo info = intersection_->getPhaseInfo();
    EXPECT_GE(info.secondsRemaining, 0);

    intersection_->stop();
}
