#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "XmlParser.h"

const std::string validXmlPath = "tests/docs/sample.xml";
const std::string emptyChildPath = "tests/docs/xml2.xml";
const std::string nonXmlPath = "tests/docs/sample.json";
const std::string missingPath = "tests/docs/does_not_exist.xml";

class GivenXmlParserTest : public ::testing::Test
{
protected:
    XmlParser _parser;
};

TEST_F(GivenXmlParserTest, WhenValidXmlFile_ThenParseFileReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(validXmlPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(GivenXmlParserTest, WhenMissingFile_ThenParseFileReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(missingPath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(GivenXmlParserTest, WhenNonXmlTextFile_ThenParseFileReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(nonXmlPath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(GivenXmlParserTest, WhenEmptyPath_ThenParseFileReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile("");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(GivenXmlParserTest, WhenEmptyRootXml_ThenParseFileReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(emptyChildPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(GivenXmlParserTest, WhenValidParsedFile_ThenOutputContainsXmlLabel)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(validXmlPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("XML"), std::string::npos);
}

TEST_F(GivenXmlParserTest, WhenValidParsedFile_ThenOutputContainsFilePath)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(validXmlPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(validXmlPath), std::string::npos);
}

TEST_F(GivenXmlParserTest, WhenValidParsedFile_ThenOutputContainsFieldValue)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(validXmlPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Bob"), std::string::npos);
}

TEST_F(GivenXmlParserTest, WhenEmptyRootParsed_ThenOutputContainsZeroRecords)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(emptyChildPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(GivenXmlParserTest, WhenEmptyRootParsed_ThenOutputContainsNoRecords)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(emptyChildPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("No records"), std::string::npos);
}
