#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <vector>
#include <memory>
#include "TaskPlugin.h"

class PluginManager {
private:
    std::vector<std::unique_ptr<TaskPlugin>> plugins;
    
public:
    void registerPlugin(std::unique_ptr<TaskPlugin> plugin);
    
    void initializePlugins();
    
    void shutdownPlugins();
    
    static PluginManager& getInstance();
    
private:
    PluginManager() = default;
    static PluginManager* instance;
};

#endif