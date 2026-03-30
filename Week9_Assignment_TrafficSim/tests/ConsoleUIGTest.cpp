#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>

#include "ConsoleUI.h"
#include "QueryResult.h"

class GivenConsoleUIGTest : public ::testing::Test
{
protected:
    ConsoleUI ui_;
};

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesUppercaseNThenReturnsNorth)
{
    std::istringstream in("N\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::NORTH);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesUppercaseSThenReturnsSouth)
{
    std::istringstream in("S\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::SOUTH);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesUppercaseEThenReturnsEast)
{
    std::istringstream in("E\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::EAST);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesUppercaseWThenReturnsWest)
{
    std::istringstream in("W\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::WEST);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesLowercaseNThenReturnsNorth)
{
    std::istringstream in("n\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::NORTH);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesLowercaseSThenReturnsSouth)
{
    std::istringstream in("s\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::SOUTH);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesLowercaseEThenReturnsEast)
{
    std::istringstream in("e\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::EAST);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesLowercaseWThenReturnsWest)
{
    std::istringstream in("w\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::WEST);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesWordNorthThenReturnsNorth)
{
    std::istringstream in("north\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::NORTH);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesWordSouthThenReturnsSouth)
{
    std::istringstream in("south\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::SOUTH);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesWordEastThenReturnsEast)
{
    std::istringstream in("east\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::EAST);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesWordWestThenReturnsWest)
{
    std::istringstream in("west\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::WEST);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesWordNorthUppercaseThenReturnsNorth)
{
    std::istringstream in("NORTH\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::NORTH);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesLeadingWhitespaceThenTrimsAndReturnsCorrectLane)
{
    std::istringstream in("  E\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::EAST);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesTrailingWhitespaceThenTrimsAndReturnsCorrectLane)
{
    std::istringstream in("W   \n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::WEST);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesInvalidInputThenRetriesAndReturnsValidLane)
{
    std::istringstream in("X\nS\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::SOUTH);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenPromptLaneReceivesEmptyLineThenRetriesAndReturnsValidLane)
{
    std::istringstream in("\nN\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_EQ(ui_.promptLane(""), LaneId::NORTH);

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenAskRepeatReceivesUppercaseYThenReturnsTrue)
{
    std::istringstream in("Y\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_TRUE(ui_.askRepeat());

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenAskRepeatReceivesLowercaseYThenReturnsTrue)
{
    std::istringstream in("y\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_TRUE(ui_.askRepeat());

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenAskRepeatReceivesYesThenReturnsTrue)
{
    std::istringstream in("yes\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_TRUE(ui_.askRepeat());

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenAskRepeatReceivesUppercaseNThenReturnsFalse)
{
    std::istringstream in("N\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_FALSE(ui_.askRepeat());

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenAskRepeatReceivesLowercaseNThenReturnsFalse)
{
    std::istringstream in("n\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_FALSE(ui_.askRepeat());

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenAskRepeatReceivesNoThenReturnsFalse)
{
    std::istringstream in("no\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_FALSE(ui_.askRepeat());

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenAskRepeatReceivesInvalidThenYesThenReturnsTrue)
{
    std::istringstream in("maybe\nY\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_TRUE(ui_.askRepeat());

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenAskRepeatReceivesInvalidThenNoThenReturnsFalse)
{
    std::istringstream in("?\nN\n");
    auto old_cin = std::cin.rdbuf(in.rdbuf());
    testing::internal::CaptureStdout();

    EXPECT_FALSE(ui_.askRepeat());

    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_cin);
}

TEST_F(GivenConsoleUIGTest, WhenShowWelcomeIsCalledThenProducesOutput)
{
    testing::internal::CaptureStdout();
    
    EXPECT_NO_FATAL_FAILURE(ui_.showWelcome());
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(GivenConsoleUIGTest, WhenShowIntersectionIsCalledThenProducesOutput)
{
    testing::internal::CaptureStdout();
    
    EXPECT_NO_FATAL_FAILURE(ui_.showIntersection());
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(GivenConsoleUIGTest, WhenShowIntersectionIsCalledThenContainsCardinalDirections)
{
    testing::internal::CaptureStdout();
    
    ui_.showIntersection();
    
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("NORTH"), std::string::npos);
    EXPECT_NE(output.find("SOUTH"), std::string::npos);
    EXPECT_NE(output.find("EAST"),  std::string::npos);
    EXPECT_NE(output.find("WEST"),  std::string::npos);
}

TEST_F(GivenConsoleUIGTest, WhenShowStatusWithGreenLaneThenPrintsGreen)
{
    QueryResult r{};
    r.fromLane = LaneId::NORTH;
    r.toLane = LaneId::SOUTH;
    r.moveType = MoveType::STRAIGHT;
    r.currentGreen = LaneId::NORTH;
    r.laneState = LightState::GREEN;
    r.secondsRemaining = 7;
    r.waitSeconds = 0;
    r.carsInside = 1;
    r.estDelaySecs = 2;

    testing::internal::CaptureStdout();
    
    EXPECT_NO_FATAL_FAILURE(ui_.showStatus(r));
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("GREEN"), std::string::npos);
}

TEST_F(GivenConsoleUIGTest, WhenShowStatusWithRedLaneThenPrintsRed)
{
    QueryResult r{};
    r.fromLane = LaneId::EAST;
    r.toLane = LaneId::WEST;
    r.moveType = MoveType::STRAIGHT;
    r.currentGreen = LaneId::NORTH;
    r.laneState = LightState::RED;
    r.secondsRemaining = 5;
    r.waitSeconds = 8;
    r.carsInside = 2;
    r.estDelaySecs = 4;

    testing::internal::CaptureStdout();
    
    EXPECT_NO_FATAL_FAILURE(ui_.showStatus(r));
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("RED"), std::string::npos);
}

TEST_F(GivenConsoleUIGTest, WhenShowStatusWithFreeMoveThenIndicatesFreeMove)
{
    QueryResult r{};
    r.fromLane = LaneId::NORTH;
    r.toLane = LaneId::EAST;
    r.moveType = MoveType::FREE_MOVE;
    r.laneState = LightState::GREEN;
    r.waitSeconds = 0;
    r.estDelaySecs = 0;
    r.carsInside = 0;

    testing::internal::CaptureStdout();
    
    EXPECT_NO_FATAL_FAILURE(ui_.showStatus(r));
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("FREE"), std::string::npos);
}
