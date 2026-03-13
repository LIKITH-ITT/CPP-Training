#include <gtest/gtest.h>
#include <string>

struct Credentials{
    std::string username;
    std::string password;
};
void PrintTo(const Credentials& creds, std::ostream* os)
{
    *os << "{ username: " << creds.username
        << ", password: " << creds.password << " }";
}

bool authenticate(const std::string& username, const std::string& password)
{
    if (password != "Password123")
        return false;

    if(username != "admin")
    {
        return false;
    }

    return true;
}

class PasswordFixture : public ::testing::TestWithParam<Credentials>{};

// TEST_P(PasswordFixture, PasswordChecking){
//     std::string username = std::get<0>(GetParam());
//     std::string password = std::get<1>(GetParam());
//     EXPECT_TRUE(authenticate(username, password));
// }

// INSTANTIATE_TEST_SUITE_P(PasswordInstantiate, PasswordFixture, ::testing::Combine(::testing::Values("user"," admin","admin","admin "),
//                                                                                   ::testing::Values("password","pass","pass123","Password123")));
TEST_P(PasswordFixture, PasswordChecking){
    Credentials creds = GetParam();
    EXPECT_TRUE(authenticate(creds.username, creds.password));
}

INSTANTIATE_TEST_SUITE_P(PasswordInstantiate, PasswordFixture, ::testing::Values(Credentials{"admin", "password"},Credentials{" admin","Pass123"}, Credentials{"admin","Password123"}));