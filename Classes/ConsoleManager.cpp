#include "ConsoleManager.h"

static std::vector<std::string> consoleOutput;

void ConsoleManager::log(const std::string& message) {
    consoleOutput.push_back(message);
}

void ConsoleManager::clear() {
    consoleOutput.clear();
}

std::vector<std::string>& ConsoleManager::getConsoleOutput() {
    return consoleOutput;
}
