#include "ConsoleManager.h"

// Store console output
static std::vector<std::string> consoleOutput;

void ConsoleManager::log(const std::string& message) {
    consoleOutput.push_back(message);
}

std::vector<std::string>& ConsoleManager::getConsoleOutput() {
    return consoleOutput;
}
