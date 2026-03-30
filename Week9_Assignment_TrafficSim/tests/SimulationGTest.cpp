#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Simulation.h"
#include "Intersection.h"
#include "MockIConsoleUI.h"
#include "MockILane.h"
#include "MockITrafficLight.h"
#include "QueryResult.h"

using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::_;
using ::testing::InSequence;

class GivenSimulationGTest : public ::testing::Test
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

        ON_CALL(north_, getLaneId()).WillByDefault(Return(LaneId::NORTH));
        ON_CALL(east_,  getLaneId()).WillByDefault(Return(LaneId::EAST));
        ON_CALL(south_, getLaneId()).WillByDefault(Return(LaneId::SOUTH));
        ON_CALL(west_,  getLaneId()).WillByDefault(Return(LaneId::WEST));

        ON_CALL(north_, getCarsInside()).WillByDefault(Return(0));
        ON_CALL(east_,  getCarsInside()).WillByDefault(Return(0));
        ON_CALL(south_, getCarsInside()).WillByDefault(Return(0));
        ON_CALL(west_,  getCarsInside()).WillByDefault(Return(0));
        EXPECT_CALL(north_, getCarsInside()).Times(AnyNumber());
        EXPECT_CALL(east_,  getCarsInside()).Times(AnyNumber());
        EXPECT_CALL(south_, getCarsInside()).Times(AnyNumber());
        EXPECT_CALL(west_,  getCarsInside()).Times(AnyNumber());

        ON_CALL(light_, getState(_)).WillByDefault(Return(LightState::RED));
        EXPECT_CALL(light_, getState(_)).Times(AnyNumber());
        EXPECT_CALL(light_, setState(_, _)).Times(AnyNumber());

        intersection_ = std::make_unique<Intersection>(
            &north_, &east_, &south_, &west_, &light_);

        sim_ = std::make_unique<Simulation>(intersection_.get());
        sim_->setUI(&mockUI_);
    }

    MockLane north_, east_, south_, west_;
    MockTrafficLight light_;
    MockConsoleUI mockUI_;

    std::unique_ptr<Intersection> intersection_;
    std::unique_ptr<Simulation> sim_;
};

TEST_F(GivenSimulationGTest, WhenRunNoRepeatThenCallsWelcomeAndIntersectionOnce)
{
    EXPECT_CALL(mockUI_, showWelcome()).Times(1);
    EXPECT_CALL(mockUI_, showIntersection()).Times(1);
    EXPECT_CALL(mockUI_, promptLane(_))
        .WillOnce(Return(LaneId::NORTH))
        .WillOnce(Return(LaneId::SOUTH));
    EXPECT_CALL(mockUI_, showStatus(_)).Times(1);
    EXPECT_CALL(mockUI_, askRepeat()).WillOnce(Return(false));

    sim_->run();
}

TEST_F(GivenSimulationGTest, WhenRunNoRepeatThenExecutesQueryLoopOnce)
{
    EXPECT_CALL(mockUI_, showWelcome()).Times(1);
    EXPECT_CALL(mockUI_, showIntersection()).Times(1);
    EXPECT_CALL(mockUI_, promptLane(_))
        .WillOnce(Return(LaneId::EAST))
        .WillOnce(Return(LaneId::WEST));
    EXPECT_CALL(mockUI_, showStatus(_)).Times(1);
    EXPECT_CALL(mockUI_, askRepeat()).WillOnce(Return(false));

    sim_->run();
}

TEST_F(GivenSimulationGTest, WhenRunUserRepeatsTwiceThenLoops)
{
    EXPECT_CALL(mockUI_, showWelcome()).Times(1);
    EXPECT_CALL(mockUI_, showIntersection()).Times(1);

    EXPECT_CALL(mockUI_, promptLane(_))
        .WillOnce(Return(LaneId::NORTH))
        .WillOnce(Return(LaneId::SOUTH))
        .WillOnce(Return(LaneId::EAST))
        .WillOnce(Return(LaneId::WEST))
        .WillOnce(Return(LaneId::SOUTH))
        .WillOnce(Return(LaneId::NORTH));

    EXPECT_CALL(mockUI_, showStatus(_)).Times(3);
    EXPECT_CALL(mockUI_, askRepeat())
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    sim_->run();
}

TEST_F(GivenSimulationGTest, WhenStopIsCalledThenPreventsFurtherLooping)
{
    EXPECT_CALL(mockUI_, showWelcome()).Times(1);
    EXPECT_CALL(mockUI_, showIntersection()).Times(1);
    EXPECT_CALL(mockUI_, promptLane(_))
        .WillOnce(Return(LaneId::NORTH))
        .WillOnce(Return(LaneId::EAST));
    EXPECT_CALL(mockUI_, showStatus(_)).Times(1);
    EXPECT_CALL(mockUI_, askRepeat())
        .WillOnce([this](){ sim_->stop(); return true; });

    sim_->run();
}

TEST_F(GivenSimulationGTest, WhenRunIsCalledThenShowStatusCalledWithFromLaneMatchingPromptAnswer)
{
    EXPECT_CALL(mockUI_, showWelcome()).Times(1);
    EXPECT_CALL(mockUI_, showIntersection()).Times(1);
    EXPECT_CALL(mockUI_, promptLane(_))
        .WillOnce(Return(LaneId::WEST))
        .WillOnce(Return(LaneId::EAST));
    EXPECT_CALL(mockUI_, showStatus(_))
        .WillOnce([](const QueryResult& r)
        {
            EXPECT_EQ(r.fromLane, LaneId::WEST);
            EXPECT_EQ(r.toLane,   LaneId::EAST);
        });
    EXPECT_CALL(mockUI_, askRepeat()).WillOnce(Return(false));

    sim_->run();
}
