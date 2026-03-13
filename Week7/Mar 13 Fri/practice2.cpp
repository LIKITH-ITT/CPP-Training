#include <gtest/gtest.h>
#include <string>

bool isValidPassword(const std::string& password)
{
    if (password.length() < 8)
        return false;

    for (char c : password)
    {
        if (isdigit(c))
            return true;
    }

    return false;
}

class PasswordFixture : public ::testing::TestWithParam<std::string>{};

TEST_P(PasswordFixture, PasswordChecking){
    std::string password = GetParam();
    EXPECT_TRUE(isValidPassword(password));
}

INSTANTIATE_TEST_SUITE_P(PasswordInstantiate, PasswordFixture, ::testing::Values("password","pass","pass123","password123"));