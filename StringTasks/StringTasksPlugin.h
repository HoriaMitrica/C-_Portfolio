#ifndef STRINGTASKSPLUGIN_H
#define STRINGTASKSPLUGIN_H

#include "TaskPlugin.h"

class StringTasksPlugin : public TaskPlugin {
public:
    std::string getName() const override;
    
    void registerTasks(TaskRegistry& registry) override;
    
    void initialize() override;
    
    void shutdown() override;
};

#endif 