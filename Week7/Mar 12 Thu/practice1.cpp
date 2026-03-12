#include<iostream>
#include <gtest/gtest.h>
void greet()
{
    std::cout << "Hello World";
}

TEST(Testing, greet)
{
    testing::internal::CaptureStdout();
    greet();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, "Hello World");

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
