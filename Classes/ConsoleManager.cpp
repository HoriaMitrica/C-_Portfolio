#include "ConsoleManager.h"
#include <algorithm>

std::vector<std::string> ConsoleManager::consoleOutput;
std::mutex ConsoleManager::consoleMutex;
size_t ConsoleManager::maxHistorySize = 1000; // Default to 1000 lines

void ConsoleManager::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(consoleMutex);
    consoleOutput.push_back(message);
    limitConsoleHistory();
}

const std::vector<std::string>& ConsoleManager::getConsoleOutput() {
    return consoleOutput;
}

void ConsoleManager::setMaxHistorySize(size_t size) {
    std::lock_guard<std::mutex> lock(consoleMutex);
    maxHistorySize = size;
    limitConsoleHistory();
}

void ConsoleManager::clear() {
    std::lock_guard<std::mutex> lock(consoleMutex);
    consoleOutput.clear();
}

std::vector<std::string> ConsoleManager::getLastNLines(size_t n) {
    std::lock_guard<std::mutex> lock(consoleMutex);
    if (consoleOutput.size() <= n) {
        return consoleOutput;
    }
    
    std::vector<std::string> result;
    result.reserve(n);
    auto startIter = consoleOutput.end() - n;
    std::copy(startIter, consoleOutput.end(), std::back_inserter(result));
    return result;
}

void ConsoleManager::limitConsoleHistory() {
    if (consoleOutput.size() > maxHistorySize) {
        size_t excessLines = consoleOutput.size() - maxHistorySize;
        consoleOutput.erase(consoleOutput.begin(), consoleOutput.begin() + excessLines);
    }
}