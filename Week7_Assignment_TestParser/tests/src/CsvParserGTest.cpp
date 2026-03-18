#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "JsonParser.h"

const std::string validArrayPath = "tests/docs/sample.json";
const std::string validObjectPath = "tests/docs/json2.json";
const std::string emptyFilePath = "tests/docs/json1.json";
const std::string malformedPath = "tests/docs/json3.json";
const std::string emptyArrayPath = "tests/docs/json1.json";
const std::string emptyObjectPath = "tests/docs/json1.json";
const std::string missingPath = "tests/docs/does_not_exist.json";

class GivenJsonParserTest : public ::testing::Test
{
protected:
    JsonParser _parser;
};

TEST_F(GivenJsonParserTest, WhenEmptyJsonArray_ThenParseFileReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(emptyArrayPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(GivenJsonParserTest, WhenEmptyJsonObject_ThenParseFileReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(emptyObjectPath);
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
    _parser.parseFile(validArrayPath);
    bool result = _parser.showParsedFile();
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(GivenJsonParserTest, WhenValidObjectParsed_ThenShowParsedFileReturnsTrue)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(validObjectPath);
    bool result = _parser.showParsedFile();
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(GivenJsonParserTest, WhenArrayParsed_ThenOutputContainsJsonLabel)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(validArrayPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("JSON"), std::string::npos);
}

TEST_F(GivenJsonParserTest, WhenArrayParsed_ThenOutputContainsFilePath)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(validArrayPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(validArrayPath), std::string::npos);
}

TEST_F(GivenJsonParserTest, WhenArrayParsed_ThenOutputContainsFieldValue)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(validArrayPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Alice"), std::string::npos);
}

TEST_F(GivenJsonParserTest, WhenEmptyArrayParsed_ThenOutputContainsNoRecords)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(emptyArrayPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("No records"), std::string::npos);
}

TEST_F(GivenJsonParserTest, WhenArrayParsed_ThenOutputContainsRecordCount)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(validArrayPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("2"), std::string::npos);
}
