#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "XmlParser.h"

class XmlParserTest : public ::testing::Test
{
protected:
    XmlParser parser;

    const std::string validXmlPath = "/tmp/xml_test_valid.xml";
    const std::string noRootXmlPath = "/tmp/xml_test_no_root.xml";
    const std::string emptyChildPath = "/tmp/xml_test_empty_root.xml";
    const std::string malformedPath = "/tmp/xml_test_malformed.xml";
    const std::string missingPath = "/tmp/xml_test_missing.xml";
    const std::string multiRecordPath = "/tmp/xml_test_multi.xml";

    void SetUp() override
    {
        std::ofstream valid(validXmlPath);
        valid << R"(<?xml version="1.0"?>)"  "\n"
              << "<employees>\n"
              << "  <employee><name>Alice</name><age>30</age></employee>\n"
              << "  <employee><name>Bob</name><age>25</age></employee>\n"
              << "</employees>\n";
        valid.close();

        std::ofstream emptyRoot(emptyChildPath);
        emptyRoot << R"(<?xml version="1.0"?>)" "\n"
                  << "<records/>\n";
        emptyRoot.close();

        std::ofstream bad(malformedPath);
        bad << "no xml tags";
        bad.close();

        std::ofstream multi(multiRecordPath);
        multi << R"(<?xml version="1.0"?>)" "\n"
              << "<catalog>\n"
              << "  <book><title>C++ Primer</title><year>2012</year></book>\n"
              << "  <book><title>Clean Code</title><year>2008</year></book>\n"
              << "  <book><title>Refactoring</title><year>2018</year></book>\n"
              << "</catalog>\n";
        multi.close();

    }

    void TearDown() override
    {
        std::remove(validXmlPath.c_str());
        std::remove(emptyChildPath.c_str());
        std::remove(malformedPath.c_str());
        std::remove(multiRecordPath.c_str());
    }
};


TEST_F(XmlParserTest, GivenValidXmlFile_ParseFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(validXmlPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(XmlParserTest, GivenMissingFile_ParseFile_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(missingPath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(XmlParserTest, GivenNonXmlTextFile_ParseFile_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(malformedPath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(XmlParserTest, GivenEmptyPath_ParseFile_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile("");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(XmlParserTest, GivenEmptyRootXml_ParseFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(emptyChildPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(XmlParserTest, GivenMultiRecordXml_ParseFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(multiRecordPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(XmlParserTest, GivenValidParsedFile_ShowParsedFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validXmlPath);
    bool result = parser.showParsedFile();
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(XmlParserTest, GivenValidParsedFile_ShowParsedFile_OutputContainsXmlLabel)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validXmlPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("XML"), std::string::npos);
}

TEST_F(XmlParserTest, GivenValidParsedFile_ShowParsedFile_OutputContainsFilePath)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validXmlPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(validXmlPath), std::string::npos);
}

TEST_F(XmlParserTest, GivenValidParsedFile_ShowParsedFile_OutputContainsFieldValue)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validXmlPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Alice"), std::string::npos);
}

TEST_F(XmlParserTest, GivenEmptyRootParsed_ShowParsedFile_OutputContainsZeroRecords)
{
    testing::internal::CaptureStdout();
    parser.parseFile(emptyChildPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(XmlParserTest, GivenEmptyRootParsed_ShowParsedFile_OutputContainsNoRecords)
{
    testing::internal::CaptureStdout();
    parser.parseFile(emptyChildPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("No records"), std::string::npos);
}

TEST_F(XmlParserTest, GivenMultiRecordParsed_ShowParsedFile_OutputContainsRecordCount)
{
    testing::internal::CaptureStdout();
    parser.parseFile(multiRecordPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("3"), std::string::npos);
}

TEST_F(XmlParserTest, GivenMultiRecordParsed_ShowParsedFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    parser.parseFile(multiRecordPath);
    bool result = parser.showParsedFile();
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}
