#include <gtest/gtest.h>

bool isEven(int x)
{
    return x % 2 == 0;
}

TEST(PredicateTest, EvenCheck)
{
    EXPECT_PRED1(isEven, 4);
    EXPECT_PRED1(isEven, 6);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}