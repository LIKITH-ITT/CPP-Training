#include <gtest/gtest.h>
#include "Logger.h"

TEST(GivenLoggerTest, WhenConstCharMessage_ThenOutputsCorrectly)
{
    testing::internal::CaptureStdout();
    Logger::printMessage("test logger");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "test logger");
}

TEST(GivenLoggerTest, WhenStdStringMessage_ThenOutputsCorrectly)
{
    testing::internal::CaptureStdout();
    std::string message = "test string message";
    Logger::printMessage(message);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, message);
}

TEST(GivenLoggerTest, WhenEmptyString_ThenOutputsNothing)
{
    testing::internal::CaptureStdout();
    std::string message = "";
    Logger::printMessage(message);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, message);
}

TEST(GivenLoggerTest, WhenEmptyConstChar_ThenOutputsNothing)
{
    testing::internal::CaptureStdout();
    Logger::printMessage((""));
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

TEST(GivenLoggerTest, WhenPrintNextLineCalled_ThenReturnsNewlineString)
{
    std::string result = Logger::printNextLine();
    EXPECT_EQ(result, "\n");
}
