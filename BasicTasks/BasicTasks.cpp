#include "BasicTasks.h"
#include "ConsoleManager.h"
#include "../Classes/InputManager.h"

void reverseString() {
    ConsoleManager::log("Enter a string to reverse:");

    InputManager::requestInput([](const std::string& input) {
        std::string reversed(input.rbegin(), input.rend());
        ConsoleManager::log("Reversed String: " + reversed);
    });
}

void checkPalindrome() {    
    ConsoleManager::log("Enter a string to check for palindrome:");

    InputManager::requestInput([](const std::string& input) {
        bool isPalin = (input == std::string(input.rbegin(), input.rend()));
        ConsoleManager::log("Palindrome: " + std::string(isPalin ? "Yes" : "No"));
    });
}
