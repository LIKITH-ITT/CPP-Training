#include <gtest/gtest.h>
bool isEven(int x)
{
    return x % 2 == 0;
}
TEST(EvenTest, AllTestCases)
{
    EXPECT_TRUE(isEven(2));
    EXPECT_TRUE(isEven(4));
    EXPECT_TRUE(isEven(7));
    EXPECT_TRUE(isEven(8));
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
