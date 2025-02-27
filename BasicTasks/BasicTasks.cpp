#include "BasicTasks.h"
#include "ConsoleManager.h"
#include <iostream>

void reverseString() {
    ConsoleManager::log("Enter a string to reverse:");
    std::string input;
    std::getline(std::cin, input);
    std::string reversed(input.rbegin(), input.rend());
    ConsoleManager::log("Reversed String: " + reversed);
}

void checkPalindrome() {
    ConsoleManager::log("Enter a string to check for palindrome:");
    std::string input;
    std::getline(std::cin, input);
    bool isPalin = (input == std::string(input.rbegin(), input.rend()));
    ConsoleManager::log("Palindrome: " + std::string(isPalin ? "Yes" : "No"));
}
