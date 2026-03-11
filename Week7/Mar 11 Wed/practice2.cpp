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
    std::cout << "Number of arguments: " << argc << std::endl;
    for (int i = 0; i < *&argc; ++i) {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "Number of arguments: " << &argc << std::endl;
    for (int i = 0; i < *&argc; ++i) {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }
    return RUN_ALL_TESTS();

}