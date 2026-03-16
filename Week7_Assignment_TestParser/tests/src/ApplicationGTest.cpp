#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Application.h"
#include "Logger.h"
#include "Constants.h"
#include "MockIParser.h"

const std::string filePath = "tests/docs/sample.json";

TEST(GivenApplicationTest, WhenNullParser_ThenPrintsUnsupportedTypeMessage)
{
    Application app(nullptr, filePath);

    testing::internal::CaptureStdout();
    app.handleParsing();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Unsupported"), std::string::npos);
}

TEST(GivenApplicationTest, WhenParseFileFails_ThenPrintsParseFailedMessage)
{
    MockIParser* mockParser = new MockIParser();

    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(false));

    Application app(mockParser, filePath);

    testing::internal::CaptureStdout();
    app.handleParsing();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("errors"), std::string::npos);
}

TEST(GivenApplicationTest, WhenParseFileFails_ThenShowParsedFileIsNotCalled)
{
    MockIParser* mockParser = new MockIParser();

    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(0);

    Application app(mockParser, filePath);

    testing::internal::CaptureStdout();
    app.handleParsing();
    testing::internal::GetCapturedStdout();
}

TEST(GivenApplicationTest, WhenBothCallsSucceed_ThenPrintsParseSuccessMessage)
{
    MockIParser* mockParser = new MockIParser();

    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    Application app(mockParser, filePath);

    testing::internal::CaptureStdout();
    app.handleParsing();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("successfully"), std::string::npos);
}

TEST(GivenApplicationTest, WhenBothCallsSucceed_ThenShowParsedFileIsCalledExactlyOnce)
{
    MockIParser* mockParser = new MockIParser();

    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    Application app(mockParser, filePath);

    testing::internal::CaptureStdout();
    app.handleParsing();
    testing::internal::GetCapturedStdout();
}

TEST(GivenApplicationTest, WhenShowParsedFileFails_ThenPrintsDisplayFailedMessage)
{
    MockIParser* mockParser = new MockIParser();

    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(false));

    Application app(mockParser, filePath);

    testing::internal::CaptureStdout();
    app.handleParsing();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Error"), std::string::npos);
}

TEST(GivenApplicationTest, WhenShowParsedFileFails_ThenParseSuccessMessageIsStillPrinted)
{
    MockIParser* mockParser = new MockIParser();

    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(false));

    Application app(mockParser, filePath);

    testing::internal::CaptureStdout();
    app.handleParsing();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("successfully"), std::string::npos);
}

TEST(GivenApplicationTest, WhenValidParserProvided_ThenParseFileIsCalledExactlyOnce)
{
    MockIParser* mockParser = new MockIParser();

    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    Application app(mockParser, filePath);

    testing::internal::CaptureStdout();
    app.handleParsing();
    testing::internal::GetCapturedStdout();
}
