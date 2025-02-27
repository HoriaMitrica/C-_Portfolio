#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <vector>
#include <string>

class ConsoleManager {
public:
    static void log(const std::string& message);
    static std::vector<std::string>& getConsoleOutput();
};

#endif
