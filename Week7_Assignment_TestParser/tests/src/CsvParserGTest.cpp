#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "JsonParser.h"

class GivenJsonParserTest : public ::testing::Test
{
protected:
    JsonParser _parser;
    const std::string _validArrayPath = "tests/docs/sample.json";
    const std::string _validObjectPath = "tests/docs/json2.json";
    const std::string _emptyFilePath = "tests/docs/json1.json";
    const std::string _malformedPath = "tests/docs/json3.json";
    const std::string _emptyArrayPath = "tests/docs/json1.json";
    const std::string _emptyObjectPath = "tests/docs/json1.json";
    const std::string _missingPath = "tests/docs/does_not_exist.json";
};

TEST_F(GivenJsonParserTest, WhenEmptyJsonArray_ThenParseFileReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(_emptyArrayPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(GivenJsonParserTest, WhenEmptyJsonObject_ThenParseFileReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(_emptyObjectPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(GivenJsonParserTest, WhenEmptyPath_ThenParseFileReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile("");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(GivenJsonParserTest, WhenValidArrayParsed_ThenShowParsedFileReturnsTrue)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validArrayPath);
    bool result = _parser.showParsedFile();
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(GivenJsonParserTest, WhenValidObjectParsed_ThenShowParsedFileReturnsTrue)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validObjectPath);
    bool result = _parser.showParsedFile();
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(GivenJsonParserTest, WhenArrayParsed_ThenOutputContainsJsonLabel)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validArrayPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("JSON"), std::string::npos);
}

TEST_F(GivenJsonParserTest, WhenArrayParsed_ThenOutputContainsFilePath)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validArrayPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(_validArrayPath), std::string::npos);
}

TEST_F(GivenJsonParserTest, WhenArrayParsed_ThenOutputContainsFieldValue)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validArrayPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Alice"), std::string::npos);
}

TEST_F(GivenJsonParserTest, WhenEmptyArrayParsed_ThenOutputContainsNoRecords)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_emptyArrayPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("No records"), std::string::npos);
}

TEST_F(GivenJsonParserTest, WhenArrayParsed_ThenOutputContainsRecordCount)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validArrayPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("2"), std::string::npos);
}
