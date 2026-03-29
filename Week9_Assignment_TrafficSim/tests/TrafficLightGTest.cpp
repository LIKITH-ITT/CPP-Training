#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TrafficLight.h"
#include "MockLane.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AnyNumber;

class GivenTrafficLightGTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        ON_CALL(mockNorth_, getLaneId()).WillByDefault(Return(LaneId::NORTH));
        ON_CALL(mockEast_,  getLaneId()).WillByDefault(Return(LaneId::EAST));
        ON_CALL(mockSouth_, getLaneId()).WillByDefault(Return(LaneId::SOUTH));
        ON_CALL(mockWest_,  getLaneId()).WillByDefault(Return(LaneId::WEST));

        EXPECT_CALL(mockNorth_, notify()).Times(AnyNumber());
        EXPECT_CALL(mockEast_,  notify()).Times(AnyNumber());
        EXPECT_CALL(mockSouth_, notify()).Times(AnyNumber());
        EXPECT_CALL(mockWest_,  notify()).Times(AnyNumber());

        light_ = std::make_unique<TrafficLight>(
            &mockNorth_, &mockEast_, &mockSouth_, &mockWest_);
    }

    MockLane mockNorth_;
    MockLane mockEast_;
    MockLane mockSouth_;
    MockLane mockWest_;
    std::unique_ptr<TrafficLight> light_;
};

TEST_F(GivenTrafficLightGTest, WhenGetStateAtStartThenAllLanesStartRed)
{
    EXPECT_EQ(light_->getState(LaneId::NORTH), LightState::RED);
    EXPECT_EQ(light_->getState(LaneId::EAST),  LightState::RED);
    EXPECT_EQ(light_->getState(LaneId::SOUTH), LightState::RED);
    EXPECT_EQ(light_->getState(LaneId::WEST),  LightState::RED);
}

TEST_F(GivenTrafficLightGTest, WhenSetStateToGreenThenGetStateReturnsGreen)
{
    light_->setState(LaneId::NORTH, LightState::GREEN);
    EXPECT_EQ(light_->getState(LaneId::NORTH), LightState::GREEN);
}

TEST_F(GivenTrafficLightGTest, WhenSetStateToYellowThenGetStateReturnsYellow)
{
    light_->setState(LaneId::EAST, LightState::YELLOW);
    EXPECT_EQ(light_->getState(LaneId::EAST), LightState::YELLOW);
}

TEST_F(GivenTrafficLightGTest, WhenSetStateToRedAfterGreenThenGetStateReturnsRed)
{
    light_->setState(LaneId::SOUTH, LightState::GREEN);
    light_->setState(LaneId::SOUTH, LightState::RED);
    EXPECT_EQ(light_->getState(LaneId::SOUTH), LightState::RED);
}

TEST_F(GivenTrafficLightGTest, WhenSetStateOnIndependentLanesThenDoNotAffectEachOther)
{
    light_->setState(LaneId::NORTH, LightState::GREEN);
    light_->setState(LaneId::SOUTH, LightState::YELLOW);

    EXPECT_EQ(light_->getState(LaneId::NORTH), LightState::GREEN);
    EXPECT_EQ(light_->getState(LaneId::SOUTH), LightState::YELLOW);
    EXPECT_EQ(light_->getState(LaneId::EAST),  LightState::RED);
    EXPECT_EQ(light_->getState(LaneId::WEST),  LightState::RED);
}

TEST_F(GivenTrafficLightGTest, WhenSetStateIsCalledThenNotifiesCorrectLane)
{
    MockLane strictNorth;
    MockLane dummyEast, dummySouth, dummyWest;

    ON_CALL(dummyEast,  notify()).WillByDefault(Return());
    ON_CALL(dummySouth, notify()).WillByDefault(Return());
    ON_CALL(dummyWest,  notify()).WillByDefault(Return());
    EXPECT_CALL(dummyEast,  notify()).Times(AnyNumber());
    EXPECT_CALL(dummySouth, notify()).Times(AnyNumber());
    EXPECT_CALL(dummyWest,  notify()).Times(AnyNumber());

    EXPECT_CALL(strictNorth, notify()).Times(1);

    TrafficLight tl(&strictNorth, &dummyEast, &dummySouth, &dummyWest);
    tl.setState(LaneId::NORTH, LightState::GREEN);
}

TEST_F(GivenTrafficLightGTest, WhenSetStateCycleThenGreenYellowRedCycleForSingleLane)
{
    light_->setState(LaneId::WEST, LightState::GREEN);
    EXPECT_EQ(light_->getState(LaneId::WEST), LightState::GREEN);

    light_->setState(LaneId::WEST, LightState::YELLOW);
    EXPECT_EQ(light_->getState(LaneId::WEST), LightState::YELLOW);

    light_->setState(LaneId::WEST, LightState::RED);
    EXPECT_EQ(light_->getState(LaneId::WEST), LightState::RED);
}
