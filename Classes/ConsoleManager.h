#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <vector>
#include <string>
#include <mutex>

class ConsoleManager {
private:
    static std::vector<std::string> consoleOutput;
    static std::mutex consoleMutex;
    static size_t maxHistorySize;

public:
    static void log(const std::string& message);
    
    static const std::vector<std::string>& getConsoleOutput();
    
    static void setMaxHistorySize(size_t size);
    
    static void clear();
    
    static std::vector<std::string> getLastNLines(size_t n);

private:
    static void limitConsoleHistory();
};

#endif