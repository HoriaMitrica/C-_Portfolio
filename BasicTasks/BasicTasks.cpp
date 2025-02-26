#include "BasicTasks.h"
#include <algorithm>

string reverseString(const string &input) {
    string reversed = input;
    reverse(reversed.begin(), reversed.end());
    return reversed;
}

bool checkPalindrome(const string &input) {
    string reversed = reverseString(input);
    return input == reversed;
}
