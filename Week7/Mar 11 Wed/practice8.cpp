#include <gtest/gtest.h>

class EvenTest : public ::testing::TestWithParam<int>
{
};

TEST_P(EvenTest, CheckEven)
{
    int num = GetParam();
    EXPECT_EQ(num % 2, 0);
}

INSTANTIATE_TEST_SUITE_P(
    EvenNumbers,
    EvenTest,
    ::testing::Values(2,4,6,8)
);
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}