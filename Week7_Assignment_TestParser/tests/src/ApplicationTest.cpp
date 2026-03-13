#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MockIParser.h"
#include "Logger.h"
#include "Constants.h"

class TestableApplication
{
    IParser* _parser;
    std::string _fakePath;

public:
    explicit TestableApplication(IParser* injectedParser, const std::string& fakePath)
        : _parser(injectedParser), _fakePath(fakePath) {}

    void runOnce()
    {
        if (_parser == nullptr)
        {
            Logger::printMessage(Constants::MSG_UNSUPPORTED_TYPE);
            return;
        }

        if (!_parser->parseFile(_fakePath))
        {
            Logger::printMessage(Constants::MSG_PARSE_FAILED);
            return;
        }

        Logger::printMessage(Constants::MSG_PARSE_SUCCESS);

        if (!_parser->showParsedFile())
        {
            Logger::printMessage(Constants::MSG_DISPLAY_FAILED);
        }
    }

};

class ApplicationTest : public ::testing::Test
{
protected:
    const std::string fakePath = "/fake/path/data.json";
};

TEST_F(ApplicationTest, GivenNullParser_RunOnce_PrintsUnsupportedTypeMessage)
{
    TestableApplication app(nullptr, fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Unsupported"), std::string::npos);
}

TEST_F(ApplicationTest, GivenParseFileFails_RunOnce_PrintsParseFailedMessage)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(fakePath))
        .Times(1)
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(0);

    TestableApplication app(&mockParser, fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("errors"), std::string::npos);
}

TEST_F(ApplicationTest, GivenParseFileFails_RunOnce_NeverCallsShowParsedFile)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(fakePath))
        .Times(1)
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(0);

    TestableApplication app(&mockParser, fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    testing::internal::GetCapturedStdout();
}

TEST_F(ApplicationTest, GivenBothCallsSucceed_RunOnce_PrintsParseSuccessMessage)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(fakePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    TestableApplication app(&mockParser, fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("successfully"), std::string::npos);
}

TEST_F(ApplicationTest, GivenBothCallsSucceed_RunOnce_CallsShowParsedFileExactlyOnce)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(fakePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    TestableApplication app(&mockParser, fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    testing::internal::GetCapturedStdout();
}

TEST_F(ApplicationTest, GivenShowParsedFileFails_RunOnce_PrintsDisplayFailedMessage)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(fakePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(false));

    TestableApplication app(&mockParser, fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Error"), std::string::npos);
}

TEST_F(ApplicationTest, GivenShowParsedFileFails_RunOnce_StillPrintsParseSuccess)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(fakePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(false));

    TestableApplication app(&mockParser, fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("successfully"), std::string::npos);
}


TEST_F(ApplicationTest, GivenValidParser_RunOnce_CallsParseFileExactlyOnce)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(fakePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    TestableApplication app(&mockParser, fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    testing::internal::GetCapturedStdout();
}
