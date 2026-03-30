#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "QueryEngine.h"
#include "Intersection.h"
#include "MockILane.h"
#include "MockITrafficLight.h"
#include "Constants.h"

using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::_;

struct QueryEngineFixture
{
    MockLane north, east, south, west;
    MockTrafficLight light;
    std::unique_ptr<Intersection> intersection;
    std::unique_ptr<QueryEngine>  engine;

    int phaseSeconds = 5;

    void build(LaneId greenLane, int secondsRemaining = 5)
    {
        phaseSeconds = secondsRemaining;

        EXPECT_CALL(north, setLight(_)).Times(AnyNumber());
        EXPECT_CALL(east,  setLight(_)).Times(AnyNumber());
        EXPECT_CALL(south, setLight(_)).Times(AnyNumber());
        EXPECT_CALL(west,  setLight(_)).Times(AnyNumber());

        EXPECT_CALL(north, shutdown()).Times(AnyNumber());
        EXPECT_CALL(east,  shutdown()).Times(AnyNumber());
        EXPECT_CALL(south, shutdown()).Times(AnyNumber());
        EXPECT_CALL(west,  shutdown()).Times(AnyNumber());

        ON_CALL(north, getLaneId()).WillByDefault(Return(LaneId::NORTH));
        ON_CALL(east,  getLaneId()).WillByDefault(Return(LaneId::EAST));
        ON_CALL(south, getLaneId()).WillByDefault(Return(LaneId::SOUTH));
        ON_CALL(west,  getLaneId()).WillByDefault(Return(LaneId::WEST));

        ON_CALL(north, getCarsInside()).WillByDefault(Return(0));
        ON_CALL(east,  getCarsInside()).WillByDefault(Return(0));
        ON_CALL(south, getCarsInside()).WillByDefault(Return(0));
        ON_CALL(west,  getCarsInside()).WillByDefault(Return(0));
        EXPECT_CALL(north, getCarsInside()).Times(AnyNumber());
        EXPECT_CALL(east,  getCarsInside()).Times(AnyNumber());
        EXPECT_CALL(south, getCarsInside()).Times(AnyNumber());
        EXPECT_CALL(west,  getCarsInside()).Times(AnyNumber());

        ON_CALL(light, getState(_)).WillByDefault(Return(LightState::RED));
        ON_CALL(light, getState(greenLane)).WillByDefault(Return(LightState::GREEN));
        EXPECT_CALL(light, getState(_)).Times(AnyNumber());
        EXPECT_CALL(light, setState(_, _)).Times(AnyNumber());

        intersection = std::make_unique<Intersection>(&north, &east, &south, &west, &light);

        engine = std::make_unique<QueryEngine>(intersection.get());
    }
};

class GivenQueryEngineGTest : public ::testing::Test
{
protected:
    QueryEngineFixture fx;
};

TEST_F(GivenQueryEngineGTest, WhenResolveWithSameLaneThenReturnsUTurn)
{
    fx.build(LaneId::NORTH);
    QueryResult r = fx.engine->resolve(LaneId::NORTH, LaneId::NORTH);
    EXPECT_EQ(r.moveType, MoveType::U_TURN);
}

TEST_F(GivenQueryEngineGTest, WhenResolveWithOppositeDirectionThenReturnsStraight)
{
    fx.build(LaneId::NORTH);
    QueryResult r = fx.engine->resolve(LaneId::NORTH, LaneId::SOUTH);
    EXPECT_EQ(r.moveType, MoveType::STRAIGHT);
}

TEST_F(GivenQueryEngineGTest, WhenResolveWithRightTurnThenReturnsRightTurn)
{
    fx.build(LaneId::NORTH);
    QueryResult r = fx.engine->resolve(LaneId::NORTH, LaneId::WEST);
    EXPECT_EQ(r.moveType, MoveType::RIGHT_TURN);
}

TEST_F(GivenQueryEngineGTest, WhenResolveWithLeftTurnThenReturnsFreeMove)
{
    fx.build(LaneId::SOUTH);
    QueryResult r = fx.engine->resolve(LaneId::NORTH, LaneId::EAST);
    EXPECT_EQ(r.moveType,   MoveType::FREE_MOVE);
    EXPECT_EQ(r.laneState,  LightState::GREEN);
    EXPECT_EQ(r.waitSeconds, 0);
    EXPECT_EQ(r.estDelaySecs, 0);
}

TEST_F(GivenQueryEngineGTest, WhenResolveWithGreenLaneThenReturnsGreen)
{
    fx.build(LaneId::EAST);
    QueryResult r = fx.engine->resolve(LaneId::NORTH, LaneId::SOUTH);
    EXPECT_EQ(r.laneState, LightState::GREEN);
}

TEST_F(GivenQueryEngineGTest, WhenResolveWithNonGreenLaneThenReturnsRed)
{
    fx.build(LaneId::EAST);
    QueryResult r = fx.engine->resolve(LaneId::EAST, LaneId::WEST);
    EXPECT_EQ(r.laneState, LightState::RED);
}

TEST_F(GivenQueryEngineGTest, WhenResolveWithCarsInsideThenReturnsEstimatedDelay)
{
    fx.build(LaneId::NORTH);
    ON_CALL(fx.north, getCarsInside()).WillByDefault(Return(2));

    QueryResult r = fx.engine->resolve(LaneId::NORTH, LaneId::SOUTH);
    EXPECT_EQ(r.estDelaySecs, 2 * Timing::CAR_CROSS_DURATION);
}

TEST_F(GivenQueryEngineGTest, WhenResolveWithoutCarsInsideThenReturnsZeroDelay)
{
    fx.build(LaneId::NORTH);
    ON_CALL(fx.north, getCarsInside()).WillByDefault(Return(0));

    QueryResult r = fx.engine->resolve(LaneId::NORTH, LaneId::SOUTH);
    EXPECT_EQ(r.estDelaySecs, 0);
}

TEST_F(GivenQueryEngineGTest, WhenResolveIsCalledThenStoresFromAndToLanes)
{
    fx.build(LaneId::WEST);
    QueryResult r = fx.engine->resolve(LaneId::WEST, LaneId::EAST);
    EXPECT_EQ(r.fromLane, LaneId::WEST);
    EXPECT_EQ(r.toLane,   LaneId::EAST);
}

TEST_F(GivenQueryEngineGTest, WhenResolveIsCalledThenStoresCarsInside)
{
    fx.build(LaneId::SOUTH);
    ON_CALL(fx.south, getCarsInside()).WillByDefault(Return(1));

    QueryResult r = fx.engine->resolve(LaneId::SOUTH, LaneId::NORTH);
    EXPECT_EQ(r.carsInside, 1);
}
