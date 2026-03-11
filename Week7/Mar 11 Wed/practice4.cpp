#include <gtest/gtest.h>

TEST(StringTest, CStringCompare)
{
    const char* s1 = "hello";
    const char* s2 = "hello";
    const char* s3 = "world";

    EXPECT_STREQ(s1, s2);
    EXPECT_STRNE(s1, s3);
}

TEST(StringTest, StdStringCompare)
{
    std::string s1 = "abc";
    std::string s2 = "abc";

    EXPECT_EQ(s1, s2);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}