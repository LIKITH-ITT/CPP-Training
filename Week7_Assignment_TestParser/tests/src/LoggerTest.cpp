#include <gtest/gtest.h>
#include "Logger.h"

TEST(LoggerTest, GivenConstCharMessage_PrintMessage_OutputsCorrectly)
{
    testing::internal::CaptureStdout();
    Logger::printMessage("hello world");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello world");
}

TEST(LoggerTest, GivenStdStringMessage_PrintMessage_OutputsCorrectly)
{
    testing::internal::CaptureStdout();
    std::string msg = "test string message";
    Logger::printMessage(msg);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, msg);
}

TEST(LoggerTest, GivenEmptyString_PrintMessage_OutputsNothing)
{
    testing::internal::CaptureStdout();
    Logger::printMessage("");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

TEST(LoggerTest, GivenEmptyConstChar_PrintMessage_OutputsNothing)
{
    testing::internal::CaptureStdout();
    Logger::printMessage(static_cast<const char*>(""));
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

TEST(LoggerTest, GivenCall_PrintNextLine_ReturnsNewlineString)
{
    std::string result = Logger::printNextLine();
    EXPECT_EQ(result, "\n");
}

TEST(LoggerTest, GivenMultipleCalls_PrintNextLine_AlwaysReturnsNewline)
{
    for (int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(Logger::printNextLine(), "\n");
    }
}

TEST(LoggerTest, GivenMessageWithNewline_PrintMessage_OutputsWithNewline)
{
    testing::internal::CaptureStdout();
    Logger::printMessage("line1\nline2");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "line1\nline2");
}
