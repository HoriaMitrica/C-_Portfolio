#include "TaskManager.h"
#include "../BasicTasks/BasicTasks.h"

std::string TaskManager::storedInput = "";
std::string TaskManager::currentTask = "";

void TaskManager::requestInput(const std::string& task) {
    currentTask = task;
    ConsoleManager::log("Enter input for " + task + ":");
}

void TaskManager::processInput(const std::string& input) {
    storedInput = input;

    if (currentTask == "reverseString") {
        ConsoleManager::log("Reversed: " + reverseString(storedInput));
    } 
    else if (currentTask == "checkPalindrome") {
        bool result = checkPalindrome(storedInput);
        ConsoleManager::log("Palindrome: " + std::string(result ? "Yes" : "No"));
    }

    currentTask = "";
}
