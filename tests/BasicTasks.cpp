#include <gtest/gtest.h>
#include "../BasicTasks/BasicTasks.h"

// Test for reversing a string
TEST(BasicTasksTest, ReverseString) {
    std::string testString = "hello";
    std::reverse(testString.begin(), testString.end());
    EXPECT_EQ(testString, "olleh");
}

// Test for palindrome
TEST(BasicTasksTest, CheckPalindrome) {
    std::string testString = "madam";
    std::string reversed = testString;
    std::reverse(reversed.begin(), reversed.end());
    EXPECT_EQ(reversed, testString);
}

// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
