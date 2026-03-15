#include <gtest/gtest.h>
#include "Validator.h"

const std::string JSON_PATH = "tests/docs/sample.json";
const std::string CSV_PATH = "tests/docs/sample.csv";
const std::string XML_PATH = "tests/docs/sample.xml";

struct ValidatorChoiceParam
{
    std::string input;
    bool expectedResult;
};

class ValidatorIsValidChoiceTest : public ::testing::TestWithParam<ValidatorChoiceParam> {};

TEST_P(ValidatorIsValidChoiceTest, GivenInput_WhenIsValidChoice_ThenReturnsExpected)
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
        ValidatorChoiceParam{"", false},
        ValidatorChoiceParam{"x", false},
        ValidatorChoiceParam{"yes", false},
        ValidatorChoiceParam{"no", false},
        ValidatorChoiceParam{"1", false},
        ValidatorChoiceParam{"yy", false}
    )
);

struct ValidatorExtensionParam
{
    std::string filePath;
    bool expectedResult;
};

class ValidatorHasSupportedExtensionTest : public ::testing::TestWithParam<ValidatorExtensionParam> {};

TEST_P(ValidatorHasSupportedExtensionTest, GivenFilePath_WhenIsValidFilePath_ThenExtensionCheckMatchesExpected)
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
        ValidatorExtensionParam{JSON_PATH, true},
        ValidatorExtensionParam{CSV_PATH, true},
        ValidatorExtensionParam{XML_PATH, true}
    )
);

INSTANTIATE_TEST_SUITE_P(
    UnsupportedExtensions,
    ValidatorHasSupportedExtensionTest,
    ::testing::Values(
        ValidatorExtensionParam{"tests/docs/file.txt", false},
        ValidatorExtensionParam{"tests/docs/file.pdf", false},
        ValidatorExtensionParam{"tests/docs/noextfile", false},
        ValidatorExtensionParam{"", false}
    )
);

TEST(ValidatorIsValidFilePathTest, GivenEmptyPath_WhenIsValidFilePath_ThenReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidFilePath("");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST(ValidatorIsValidFilePathTest, GivenNonExistentFile_WhenIsValidFilePath_ThenReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidFilePath("tests/docs/does_not_exist.json");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST(ValidatorIsValidFilePathTest, GivenUppercaseExtension_WhenIsValidFilePath_ThenReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidFilePath("tests/docs/json4.JSON");
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST(ValidatorIsValidChoicePlainTest, GivenSingleSpaceInput_WhenIsValidChoice_ThenReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidChoice(" ");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}
