#include<gtest/gtest.h>
class Math
{
private:
    int multiply(int a, int b)
    {
        return a * b;
    }

    FRIEND_TEST(MathTest, MultiplyTest);
};
TEST(MathTest, MultiplyTest)
{
    Math m;
    EXPECT_EQ(m.multiply(3,4), 12);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}