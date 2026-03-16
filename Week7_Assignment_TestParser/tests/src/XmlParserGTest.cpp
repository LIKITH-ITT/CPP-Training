#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "XmlParser.h"

class GivenXmlParserTest : public ::testing::Test
{
protected:
    XmlParser _parser;
    const std::string _validXmlPath = "tests/docs/sample.xml";
    const std::string _emptyChildPath = "tests/docs/xml2.xml";
    const std::string _nonXmlPath = "tests/docs/sample.json";
    const std::string _missingPath = "tests/docs/does_not_exist.xml";
};

TEST_F(GivenXmlParserTest, WhenValidXmlFile_ThenParseFileReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(_validXmlPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(GivenXmlParserTest, WhenMissingFile_ThenParseFileReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(_missingPath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(GivenXmlParserTest, WhenNonXmlTextFile_ThenParseFileReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(_nonXmlPath);
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
    bool result = _parser.parseFile(_emptyChildPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(GivenXmlParserTest, WhenValidParsedFile_ThenOutputContainsXmlLabel)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validXmlPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("XML"), std::string::npos);
}

TEST_F(GivenXmlParserTest, WhenValidParsedFile_ThenOutputContainsFilePath)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validXmlPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(_validXmlPath), std::string::npos);
}

TEST_F(GivenXmlParserTest, WhenValidParsedFile_ThenOutputContainsFieldValue)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validXmlPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Bob"), std::string::npos);
}

TEST_F(GivenXmlParserTest, WhenEmptyRootParsed_ThenOutputContainsZeroRecords)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_emptyChildPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(GivenXmlParserTest, WhenEmptyRootParsed_ThenOutputContainsNoRecords)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_emptyChildPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("No records"), std::string::npos);
}
