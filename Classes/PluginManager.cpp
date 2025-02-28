#include "PluginManager.h"
#include "TaskRegistry.h"

PluginManager* PluginManager::instance = nullptr;

PluginManager& PluginManager::getInstance() {
    if (instance == nullptr) {
        instance = new PluginManager();
    }
    return *instance;
}

void PluginManager::registerPlugin(std::unique_ptr<TaskPlugin> plugin) {
    plugins.push_back(std::move(plugin));
}

void PluginManager::initializePlugins() {
    for (auto& plugin : plugins) {
        plugin->initialize();
        plugin->registerTasks(TaskRegistry::getInstance());
    }
}

void PluginManager::shutdownPlugins() {
    for (auto& plugin : plugins) {
        plugin->shutdown();
    }
}