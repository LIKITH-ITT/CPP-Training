#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Logger.h"
#include "Constants.h"
#include "IParser.h"

class MockIParser : public IParser
{
public:
    MOCK_METHOD(bool, parseFile, (const std::string& filePath), (override));
    MOCK_METHOD(bool, showParsedFile, (), (override));
};

class TestableApplication
{
    IParser* _parser;
    std::string _fakePath;

public:
    TestableApplication(IParser* fakeParser, const std::string& fakePath) : _parser(fakeParser), _fakePath(fakePath) {}

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
    const std::string _fakePath = "/fake/data.json";
};

TEST_F(ApplicationTest, GivenNullParser_WhenRunOnce_ThenPrintsUnsupportedTypeMessage)
{
    TestableApplication app(nullptr, _fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Unsupported"), std::string::npos);
}

TEST_F(ApplicationTest, GivenParseFileFails_WhenRunOnce_ThenPrintsParseFailedMessage)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(_fakePath))
        .Times(1)
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(0);

    TestableApplication app(&mockParser, _fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("errors"), std::string::npos);
}

TEST_F(ApplicationTest, GivenParseFileFails_WhenRunOnce_ThenNeverCallsShowParsedFile)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(_fakePath))
        .Times(1)
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(0);

    TestableApplication app(&mockParser, _fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    testing::internal::GetCapturedStdout();
}

TEST_F(ApplicationTest, GivenBothCallsSucceed_WhenRunOnce_ThenPrintsParseSuccessMessage)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(_fakePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    TestableApplication app(&mockParser, _fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("successfully"), std::string::npos);
}

TEST_F(ApplicationTest, GivenBothCallsSucceed_WhenRunOnce_ThenCallsShowParsedFileExactlyOnce)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(_fakePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    TestableApplication app(&mockParser, _fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    testing::internal::GetCapturedStdout();
}

TEST_F(ApplicationTest, GivenShowParsedFileFails_WhenRunOnce_ThenPrintsDisplayFailedMessage)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(_fakePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(false));

    TestableApplication app(&mockParser, _fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Error"), std::string::npos);
}

TEST_F(ApplicationTest, GivenShowParsedFileFails_WhenRunOnce_ThenStillPrintsParseSuccess)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(_fakePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(false));

    TestableApplication app(&mockParser, _fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("successfully"), std::string::npos);
}


TEST_F(ApplicationTest, GivenValidParser_WhenRunOnce_ThenCallsParseFileExactlyOnce)
{
    MockIParser mockParser;

    EXPECT_CALL(mockParser, parseFile(_fakePath))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(mockParser, showParsedFile())
        .Times(1)
        .WillOnce(::testing::Return(true));

    TestableApplication app(&mockParser, _fakePath);

    testing::internal::CaptureStdout();
    app.runOnce();
    testing::internal::GetCapturedStdout();
}
