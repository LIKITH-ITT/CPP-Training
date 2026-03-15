#include <gtest/gtest.h>
#include "Logger.h"

TEST(LoggerTest, GivenConstCharMessage_WhenPrintMessage_ThenOutputsCorrectly)
{
    testing::internal::CaptureStdout();
    Logger::printMessage("test logger");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "test logger");
}

TEST(LoggerTest, GivenStdStringMessage_WhenPrintMessage_ThenOutputsCorrectly)
{
    testing::internal::CaptureStdout();
    std::string message = "test string message";
    Logger::printMessage(message);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, message);
}

TEST(LoggerTest, GivenEmptyString_WhenPrintMessage_ThenOutputsNothing)
{
    testing::internal::CaptureStdout();
    std::string message = "";
    Logger::printMessage(message);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, message);
}

TEST(LoggerTest, GivenEmptyConstChar_WhenPrintMessage_ThenOutputsNothing)
{
    testing::internal::CaptureStdout();
    Logger::printMessage((""));
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

TEST(LoggerTest, GivenCall_WhenPrintNextLine_ThenReturnsNewlineString)
{
    std::string result = Logger::printNextLine();
    EXPECT_EQ(result, "\n");
}
