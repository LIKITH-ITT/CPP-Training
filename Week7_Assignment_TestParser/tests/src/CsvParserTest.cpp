#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "CsvParser.h"

class CsvParserTest : public ::testing::Test
{
protected:
    CsvParser parser;

    const std::string validCsvPath = "/tmp/csv_test_valid.csv";
    const std::string emptyCsvPath = "/tmp/csv_test_empty.csv";
    const std::string headerOnlyCsvPath = "/tmp/csv_test_header_only.csv";
    const std::string missingPath = "/tmp/csv_test_does_not_exist.csv";
    const std::string multiColCsvPath = "/tmp/csv_test_multicol.csv";

    void SetUp() override
    {
        std::ofstream valid(validCsvPath);
        valid << "name,age,city\n";
        valid << "Alice,30,London\n";
        valid << "Bob,25,Paris\n";
        valid.close();

        std::ofstream empty(emptyCsvPath);
        empty.close();

        std::ofstream headerOnly(headerOnlyCsvPath);
        headerOnly << "id,value\n";
        headerOnly.close();

        std::ofstream multi(multiColCsvPath);
        multi << "a,b,c,d\n";
        multi << "1,2,3,4\n";
        multi.close();
    }

    void TearDown() override
    {
        std::remove(validCsvPath.c_str());
        std::remove(emptyCsvPath.c_str());
        std::remove(headerOnlyCsvPath.c_str());
        std::remove(multiColCsvPath.c_str());
    }
};

TEST_F(CsvParserTest, GivenValidCsvFile_ParseFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(validCsvPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(CsvParserTest, GivenEmptyFile_ParseFile_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(emptyCsvPath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(CsvParserTest, GivenMissingFile_ParseFile_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(missingPath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(CsvParserTest, GivenEmptyFilePath_ParseFile_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile("");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(CsvParserTest, GivenMultiColumnCsvFile_ParseFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(multiColCsvPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(CsvParserTest, GivenValidParsedFile_ShowParsedFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validCsvPath);
    bool result = parser.showParsedFile();
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(CsvParserTest, GivenValidParsedFile_ShowParsedFile_OutputContainsFilePath)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validCsvPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(validCsvPath), std::string::npos);
}

TEST_F(CsvParserTest, GivenValidParsedFile_ShowParsedFile_OutputContainsCsvLabel)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validCsvPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("CSV"), std::string::npos);
}

TEST_F(CsvParserTest, GivenValidParsedFile_ShowParsedFile_OutputContainsRecordData)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validCsvPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Alice"), std::string::npos);
}

TEST_F(CsvParserTest, GivenHeaderOnlyFile_ParseFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(headerOnlyCsvPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(CsvParserTest, GivenHeaderOnlyParsedFile_ShowParsedFile_OutputContainsZeroRecords)
{
    testing::internal::CaptureStdout();
    parser.parseFile(headerOnlyCsvPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("0"), std::string::npos);
}
