#include <gtest/gtest.h>

TEST(MathTest, Addition) {
    ASSERT_EQ(1 + 2, 4);
}

TEST(MathTest, Subtraction) {
    EXPECT_EQ(5 - 3, 2);
}

TEST(MathTest, Multiplication) {
    EXPECT_EQ(3 * 4, 12);
}

TEST(MathTest, Division) {
    EXPECT_EQ(3 / 4, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}