#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "JsonParser.h"

class JsonParserTest : public ::testing::Test
{
protected:
    JsonParser parser;

    const std::string validArrayPath = "/tmp/json_test_array.json";
    const std::string validObjectPath = "/tmp/json_test_object.json";
    const std::string emptyFilePath = "/tmp/json_test_empty.json";
    const std::string malformedPath = "/tmp/json_test_malformed.json";
    const std::string emptyArrayPath = "/tmp/json_test_empty_array.json";
    const std::string emptyObjectPath = "/tmp/json_test_empty_object.json";
    const std::string missingPath = "/tmp/json_test_does_not_exist.json";

    void SetUp() override
    {
        std::ofstream arr(validArrayPath);
        arr << R"([{"name":"Alice","age":30},{"name":"Bob","age":25}])";
        arr.close();

        std::ofstream obj(validObjectPath);
        obj << R"({"id":1,"title":"Test Record","active":true})";
        obj.close();

        std::ofstream empty(emptyFilePath);
        empty.close();

        std::ofstream bad(malformedPath);
        bad << R"({"key": "value")";
        bad.close();

        std::ofstream emptyArr(emptyArrayPath);
        emptyArr << "[]";
        emptyArr.close();

        std::ofstream emptyObj(emptyObjectPath);
        emptyObj << "{}";
        emptyObj.close();
    }

    void TearDown() override
    {
        std::remove(validArrayPath.c_str());
        std::remove(validObjectPath.c_str());
        std::remove(emptyFilePath.c_str());
        std::remove(malformedPath.c_str());
        std::remove(emptyArrayPath.c_str());
        std::remove(emptyObjectPath.c_str());
    }
};

TEST_F(JsonParserTest, GivenValidJsonArray_ParseFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(validArrayPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(JsonParserTest, GivenValidJsonObject_ParseFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(validObjectPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(JsonParserTest, GivenEmptyFile_ParseFile_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(emptyFilePath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(JsonParserTest, GivenMissingFile_ParseFile_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(missingPath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(JsonParserTest, GivenMalformedJson_ParseFile_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(malformedPath);
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(JsonParserTest, GivenEmptyJsonArray_ParseFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(emptyArrayPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(JsonParserTest, GivenEmptyJsonObject_ParseFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile(emptyObjectPath);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(JsonParserTest, GivenEmptyPath_ParseFile_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = parser.parseFile("");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(JsonParserTest, GivenValidArrayParsed_ShowParsedFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validArrayPath);
    bool result = parser.showParsedFile();
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(JsonParserTest, GivenValidObjectParsed_ShowParsedFile_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validObjectPath);
    bool result = parser.showParsedFile();
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(JsonParserTest, GivenArrayParsed_ShowParsedFile_OutputContainsJsonLabel)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validArrayPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("JSON"), std::string::npos);
}

TEST_F(JsonParserTest, GivenArrayParsed_ShowParsedFile_OutputContainsFilePath)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validArrayPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(validArrayPath), std::string::npos);
}

TEST_F(JsonParserTest, GivenArrayParsed_ShowParsedFile_OutputContainsFieldValue)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validArrayPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Alice"), std::string::npos);
}

TEST_F(JsonParserTest, GivenEmptyArrayParsed_ShowParsedFile_OutputContainsNoRecords)
{
    testing::internal::CaptureStdout();
    parser.parseFile(emptyArrayPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("No records"), std::string::npos);
}

TEST_F(JsonParserTest, GivenArrayParsed_ShowParsedFile_OutputContainsRecordCount)
{
    testing::internal::CaptureStdout();
    parser.parseFile(validArrayPath);
    parser.showParsedFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("2"), std::string::npos);
}
