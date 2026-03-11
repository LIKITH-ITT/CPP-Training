#include <gtest/gtest.h>

class CalculatorTest : public ::testing::Test
{
protected:
    int a;
    int b;

    void SetUp() override
    {
        a = 10;
        b = 5;
    }
};

TEST_F(CalculatorTest, Addition)
{
    EXPECT_EQ(a + b, 15);
}

TEST_F(CalculatorTest, Subtraction)
{
    EXPECT_EQ(a - b, 5);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}