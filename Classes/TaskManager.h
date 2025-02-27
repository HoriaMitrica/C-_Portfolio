#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <string>
#include "ConsoleManager.h"

class TaskManager {
private:
    static std::string storedInput;
    static std::string currentTask;

public:
    static void requestInput(const std::string& task);
    static void processInput(const std::string& input);
};

#endif
