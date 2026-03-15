#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "CsvParser.h"

class CsvParserTest : public ::testing::Test
{
protected:
    CsvParser _parser;
    const std::string _validCsvPath = "tests/docs/sample.csv";
    const std::string _emptyCsvPath = "tests/docs/csv1.csv";
    const std::string _headerOnlyCsvPath = "tests/docs/csv2.csv";
    const std::string _missingPath = "tests/docs/does_not_exist.csv";
    const std::string _multiColCsvPath = "tests/docs/csv3.csv";
};

TEST_F(CsvParserTest, GivenValidCsvFile_WhenParseFile_ThenReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(_validCsvPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(CsvParserTest, GivenEmptyFile_WhenParseFile_ThenReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(_emptyCsvPath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(CsvParserTest, GivenMissingFile_WhenParseFile_ThenReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(_missingPath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(CsvParserTest, GivenEmptyFilePath_WhenParseFile_ThenReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile("");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(CsvParserTest, GivenMultiColumnCsvFile_WhenParseFile_ThenReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(_multiColCsvPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(CsvParserTest, GivenValidParsedFile_WhenShowParsedFile_ThenReturnsTrue)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validCsvPath);
    bool result = _parser.showParsedFile();
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(CsvParserTest, GivenValidParsedFile_WhenShowParsedFile_ThenOutputContainsFilePath)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validCsvPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(_validCsvPath), std::string::npos);
}

TEST_F(CsvParserTest, GivenValidParsedFile_WhenShowParsedFile_ThenOutputContainsCsvLabel)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validCsvPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("CSV"), std::string::npos);
}

TEST_F(CsvParserTest, GivenValidParsedFile_WhenShowParsedFile_ThenOutputContainsRecordData)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_validCsvPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Alice"), std::string::npos);
}

TEST_F(CsvParserTest, GivenHeaderOnlyFile_WhenParseFile_ThenReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = _parser.parseFile(_headerOnlyCsvPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(CsvParserTest, GivenHeaderOnlyParsedFile_WhenShowParsedFile_ThenOutputContainsZeroRecords)
{
    testing::internal::CaptureStdout();
    _parser.parseFile(_headerOnlyCsvPath);
    _parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("0"), std::string::npos);
}
