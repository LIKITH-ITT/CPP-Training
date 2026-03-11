#include <gtest/gtest.h>

TEST(AssertionTest, ExpectExample)
{
    EXPECT_EQ(1, 2);
    std::cout << "This still runs\n";
}

TEST(AssertionTest, AssertExample)
{
    ASSERT_EQ(1, 2);
    std::cout << "This will NOT run\n";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}