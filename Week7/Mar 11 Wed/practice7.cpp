#include <gtest/gtest.h>

class LifecycleTest : public ::testing::Test
{
protected:
    LifecycleTest()
    {
        std::cout << "Constructor\n";
    }

    ~LifecycleTest()
    {
        std::cout << "Destructor\n";
    }

    void SetUp() override
    {
        std::cout << "SetUp\n";
    }

    void TearDown() override
    {
        std::cout << "TearDown\n";
    }
};

TEST_F(LifecycleTest, Test1)
{
    std::cout << "Test1\n";
}

TEST_F(LifecycleTest, Test2)
{
    std::cout << "Test2\n";
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}