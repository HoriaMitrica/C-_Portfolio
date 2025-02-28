#include <gtest/gtest.h>
#include "../StringTasks/StringTasks.h"

TEST(StringTasksTest, ReverseString) {
    std::string testString = "hello";
    std::string expected = "olleh";
    EXPECT_EQ(ReverseStringTask::reverseString(testString), expected);
}

TEST(StringTasksTest, CheckPalindrome) {
    EXPECT_TRUE(PalindromeTask::isPalindrome("madam"));
    EXPECT_TRUE(PalindromeTask::isPalindrome("racecar"));
    EXPECT_FALSE(PalindromeTask::isPalindrome("hello"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}