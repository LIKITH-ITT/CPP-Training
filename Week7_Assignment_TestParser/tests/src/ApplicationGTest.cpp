#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Application.h"
#include "Logger.h"
#include "Constants.h"
#include "MockIParser.h"

const std::string filePath = "tests/docs/sample.json";

class GivenApplicationTest : public ::testing::Test
{
protected:
    MockIParser* mockParser;
    Application* app;

    void SetUp() override {
        mockParser = new MockIParser();
        app = new Application(mockParser, filePath);
    }
    void TearDown() override {
        delete app;
        delete mockParser;
    }
    void createNull() {
        delete app;
        app = new Application(nullptr, filePath);
    }
};

TEST_F(GivenApplicationTest, WhenNullParser_ThenPrintsUnsupportedTypeMessage)
{
    createNull();
    testing::internal::CaptureStdout();
    app->handleParsing();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Unsupported"), std::string::npos);
}
TEST_F(GivenApplicationTest, WhenParseFileFails_ThenPrintsParseFailedMessage)
{
    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(false));

    testing::internal::CaptureStdout();
    app->handleParsing();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("errors"), std::string::npos);
}

TEST_F(GivenApplicationTest, WhenParseFileFails_ThenShowParsedFileIsNotCalled)
{
    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(0);

    app->handleParsing();
}

TEST_F(GivenApplicationTest, WhenBothCallsSucceed_ThenPrintsParseSuccessMessage)
{
    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    testing::internal::CaptureStdout();
    app->handleParsing();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("successfully"), std::string::npos);
}

TEST_F(GivenApplicationTest, WhenBothCallsSucceed_ThenShowParsedFileIsCalledExactlyOnce)
{
    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    app->handleParsing();
}

TEST_F(GivenApplicationTest, WhenShowParsedFileFails_ThenPrintsDisplayFailedMessage)
{
    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(false));

    testing::internal::CaptureStdout();
    app->handleParsing();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Error"), std::string::npos);
}
TEST_F(GivenApplicationTest, WhenShowParsedFileFails_ThenParseSuccessMessageIsStillPrinted)
{
    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(false));

    testing::internal::CaptureStdout();
    app->handleParsing();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("successfully"), std::string::npos);
}

TEST_F(GivenApplicationTest, WhenValidParserProvided_ThenParseFileIsCalledExactlyOnce)
{
    EXPECT_CALL(*mockParser, parseFile(filePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    app->handleParsing();
}