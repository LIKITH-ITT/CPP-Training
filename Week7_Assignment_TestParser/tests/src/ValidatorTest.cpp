#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "Validator.h"

static const std::string TEMP_JSON = "/tmp/test_valid.json";
static const std::string TEMP_CSV  = "/tmp/test_valid.csv";
static const std::string TEMP_XML  = "/tmp/test_valid.xml";

static void createTempFile(const std::string& path, const std::string& content = "x")
{
    std::ofstream f(path);
    f << content;
}

static void removeTempFile(const std::string& path)
{
    std::remove(path.c_str());
}

struct ValidatorChoiceParam
{
    std::string input;
    bool        expectedResult;
};

class ValidatorIsValidChoiceTest : public ::testing::TestWithParam<ValidatorChoiceParam> {};

TEST_P(ValidatorIsValidChoiceTest, GivenInput_IsValidChoice_ReturnsExpected)
{
    testing::internal::CaptureStdout();
    ValidatorChoiceParam param = GetParam();
    bool result = Validator::isValidChoice(param.input);
    testing::internal::GetCapturedStdout();
    EXPECT_EQ(result, param.expectedResult);
}

INSTANTIATE_TEST_SUITE_P(
    ValidChoices,
    ValidatorIsValidChoiceTest,
    ::testing::Values(
        ValidatorChoiceParam{"y", true},
        ValidatorChoiceParam{"Y", true},
        ValidatorChoiceParam{"n", true},
        ValidatorChoiceParam{"N", true}
    )
);

INSTANTIATE_TEST_SUITE_P(
    InvalidChoices,
    ValidatorIsValidChoiceTest,
    ::testing::Values(
        ValidatorChoiceParam{"",    false},
        ValidatorChoiceParam{"x",   false},
        ValidatorChoiceParam{"yes", false},
        ValidatorChoiceParam{"no",  false},
        ValidatorChoiceParam{"1",   false},
        ValidatorChoiceParam{"yy",  false}
    )
);

struct ValidatorExtensionParam
{
    std::string filePath;
    bool        expectedResult;
};

class ValidatorHasSupportedExtensionTest
    : public ::testing::TestWithParam<ValidatorExtensionParam>
{
protected:
    void SetUp() override
    {
        createTempFile(TEMP_JSON);
        createTempFile(TEMP_CSV);
        createTempFile(TEMP_XML);
    }

    void TearDown() override
    {
        removeTempFile(TEMP_JSON);
        removeTempFile(TEMP_CSV);
        removeTempFile(TEMP_XML);
    }
};

TEST_P(ValidatorHasSupportedExtensionTest, GivenFilePath_IsValidFilePath_ExtensionCheckMatchesExpected)
{
    testing::internal::CaptureStdout();
    ValidatorExtensionParam param = GetParam();
    bool result = Validator::isValidFilePath(param.filePath);
    testing::internal::GetCapturedStdout();
    EXPECT_EQ(result, param.expectedResult);
}

INSTANTIATE_TEST_SUITE_P(
    SupportedExtensions,
    ValidatorHasSupportedExtensionTest,
    ::testing::Values(
        ValidatorExtensionParam{TEMP_JSON, true},
        ValidatorExtensionParam{TEMP_CSV,  true},
        ValidatorExtensionParam{TEMP_XML,  true}
    )
);

INSTANTIATE_TEST_SUITE_P(
    UnsupportedExtensions,
    ValidatorHasSupportedExtensionTest,
    ::testing::Values(
        ValidatorExtensionParam{"/tmp/file.txt",  false},
        ValidatorExtensionParam{"/tmp/file.pdf",  false},
        ValidatorExtensionParam{"/tmp/noextfile", false},
        ValidatorExtensionParam{"",               false}
    )
);

class ValidatorIsValidFilePathTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        createTempFile(TEMP_JSON);
    }

    void TearDown() override
    {
        removeTempFile(TEMP_JSON);
    }
};

TEST_F(ValidatorIsValidFilePathTest, GivenValidJsonFilePath_IsValidFilePath_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidFilePath(TEMP_JSON);
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(ValidatorIsValidFilePathTest, GivenEmptyPath_IsValidFilePath_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidFilePath("");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(ValidatorIsValidFilePathTest, GivenNonExistentFile_IsValidFilePath_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidFilePath("/tmp/does_not_exist.json");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(ValidatorIsValidFilePathTest, GivenUnsupportedExtension_IsValidFilePath_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidFilePath("/tmp/file.txt");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(ValidatorIsValidFilePathTest, GivenUppercaseExtension_IsValidFilePath_ReturnsTrue)
{
    std::string upperPath = "/tmp/test_valid.JSON";
    createTempFile(upperPath);
    testing::internal::CaptureStdout();
    bool result = Validator::isValidFilePath(upperPath);
    testing::internal::GetCapturedStdout();
    removeTempFile(upperPath);
    EXPECT_TRUE(result);
}

TEST(ValidatorIsValidChoicePlainTest, GivenSingleSpaceInput_IsValidChoice_ReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidChoice(" ");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST(ValidatorIsValidChoicePlainTest, GivenLowercaseY_IsValidChoice_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidChoice("y");
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST(ValidatorIsValidChoicePlainTest, GivenLowercaseN_IsValidChoice_ReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidChoice("n");
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}
