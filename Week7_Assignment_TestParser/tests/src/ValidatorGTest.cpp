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

class GivenValidatorIsValidChoiceTest : public ::testing::TestWithParam<ValidatorChoiceParam> {};

TEST_P(GivenValidatorIsValidChoiceTest, WhenInputProvided_ThenIsValidChoiceReturnsExpected)
{
    testing::internal::CaptureStdout();
    ValidatorChoiceParam param = GetParam();
    bool result = Validator::isValidChoice(param.input);
    testing::internal::GetCapturedStdout();
    EXPECT_EQ(result, param.expectedResult);
}

INSTANTIATE_TEST_SUITE_P(
    ValidChoices,
    GivenValidatorIsValidChoiceTest,
    ::testing::Values(
        ValidatorChoiceParam{"y", true},
        ValidatorChoiceParam{"Y", true},
        ValidatorChoiceParam{"n", true},
        ValidatorChoiceParam{"N", true}
    )
);

INSTANTIATE_TEST_SUITE_P(
    InvalidChoices,
    GivenValidatorIsValidChoiceTest,
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
    bool expectedResult;
};

class GivenValidatorHasSupportedExtensionTest : public ::testing::TestWithParam<ValidatorExtensionParam> {};

TEST_P(GivenValidatorHasSupportedExtensionTest, WhenFilePathProvided_ThenExtensionCheckMatchesExpected)
{
    testing::internal::CaptureStdout();
    ValidatorExtensionParam param = GetParam();
    bool result = Validator::isValidFilePath(param.filePath);
    testing::internal::GetCapturedStdout();
    EXPECT_EQ(result, param.expectedResult);
}

INSTANTIATE_TEST_SUITE_P(
    SupportedExtensions,
    GivenValidatorHasSupportedExtensionTest,
    ::testing::Values(
        ValidatorExtensionParam{JSON_PATH, true},
        ValidatorExtensionParam{CSV_PATH,  true},
        ValidatorExtensionParam{XML_PATH,  true}
    )
);

INSTANTIATE_TEST_SUITE_P(
    UnsupportedExtensions,
    GivenValidatorHasSupportedExtensionTest,
    ::testing::Values(
        ValidatorExtensionParam{"tests/docs/file.txt", false},
        ValidatorExtensionParam{"tests/docs/file.pdf", false},
        ValidatorExtensionParam{"tests/docs/noextfile", false},
        ValidatorExtensionParam{"", false}
    )
);

TEST(GivenValidatorIsValidFilePathTest, WhenEmptyPath_ThenReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidFilePath("");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST(GivenValidatorIsValidFilePathTest, WhenNonExistentFile_ThenReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidFilePath("tests/docs/does_not_exist.json");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST(GivenValidatorIsValidFilePathTest, WhenUppercaseExtension_ThenReturnsTrue)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidFilePath("tests/docs/json4.JSON");
    testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST(GivenValidatorIsValidChoicePlainTest, WhenSingleSpaceInput_ThenReturnsFalse)
{
    testing::internal::CaptureStdout();
    bool result = Validator::isValidChoice(" ");
    testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}
