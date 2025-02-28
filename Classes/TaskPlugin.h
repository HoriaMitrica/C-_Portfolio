#ifndef TASKPLUGIN_H
#define TASKPLUGIN_H

#include <string>
#include "TaskRegistry.h"

class TaskPlugin {
public:
    virtual ~TaskPlugin() = default;
    
    virtual std::string getName() const = 0;
    
    virtual void registerTasks(TaskRegistry& registry) = 0;
    
    virtual void initialize() = 0;
    
    virtual void shutdown() = 0;
};

#endif