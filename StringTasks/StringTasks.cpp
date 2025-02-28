#include "StringTasks.h"
#include "../Classes/ConsoleManager.h"
#include "../Classes/InputManager.h"
#include <iostream>
#include <algorithm>

std::string StringTask::getCategory() const {
    return "Basic C++ Tasks";
}

std::string ReverseStringTask::getName() const {
    return "Reverse String";
}

std::string ReverseStringTask::getDescription() const {
    return "Reverses a string input by the user";
}

std::vector<std::string> ReverseStringTask::getInputPrompts() const {
    return {"Enter a string to reverse:"};
}

void ReverseStringTask::execute(const std::vector<std::string>& inputs) {
    if (inputs.empty()) {
        ConsoleManager::log("Error: No input provided");
        return;
    }
    
    std::string result = reverseString(inputs[0]);
    ConsoleManager::log("Reversed String: " + result);
}

void ReverseStringTask::run() {
    active = true;
    requestNextInput(); 
}

void ReverseStringTask::requestNextInput() {
    if (!active) return;
    
    std::string prompt = "Enter a string to reverse (or 'exit' to quit):";
    ConsoleManager::log(prompt);
    
    InputManager::requestInput(prompt, [this](const std::string& input) {
        if (shouldExitOnInput(input)) {
            exit();
            return;
        }
        
        std::string result = reverseString(input);
        ConsoleManager::log("Reversed String: " + result);
        
        requestNextInput();
    });
}

bool ReverseStringTask::shouldExitOnInput(const std::string& input) const {
    return input == "exit" || input == "quit" || input == "back";
}

std::string ReverseStringTask::reverseString(const std::string& input) {
    std::string reversed;
    reversed.reserve(input.size());
    std::copy(input.rbegin(), input.rend(), std::back_inserter(reversed));
    return reversed;
}

std::string PalindromeTask::getName() const {
    return "Check Palindrome";
}

std::string PalindromeTask::getDescription() const {
    return "Checks if a string is a palindrome";
}

std::vector<std::string> PalindromeTask::getInputPrompts() const {
    return {"Enter a string to check for palindrome:"};
}

void PalindromeTask::execute(const std::vector<std::string>& inputs) {
    if (inputs.empty()) {
        ConsoleManager::log("Error: No input provided");
        return;
    }
    
    bool result = isPalindrome(inputs[0]);
    ConsoleManager::log("Palindrome: " + std::string(result ? "Yes" : "No"));
}

void PalindromeTask::run() {
    active = true;
    requestNextInput();
}

void PalindromeTask::requestNextInput() {
    if (!active) return;
    
    std::string prompt = getInputPrompts()[0];
    ConsoleManager::log(prompt);

    InputManager::requestInput(prompt, [this](const std::string& input) {
        if (shouldExitOnInput(input)) {
            exit();
            return;
        }

        execute({input});
    
        requestNextInput();
    });
}

bool PalindromeTask::shouldExitOnInput(const std::string& input) const {
    return input == "exit" || input == "quit" || input == "back";
}


bool PalindromeTask::isPalindrome(const std::string& input) {
    return std::equal(input.begin(), input.begin() + input.size()/2, 
                     input.rbegin());
}