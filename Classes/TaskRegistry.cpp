// TaskRegistry.cpp
#include "TaskRegistry.h"

TaskRegistry &TaskRegistry::getInstance()
{
    static TaskRegistry instance;
    return instance;
}

std::vector<std::string> TaskRegistry::getCategories() const
{
    std::vector<std::string> categories;
    for (const auto &pair : tasksByCategory)
    {
        categories.push_back(pair.first);
    }
    return categories;
}

std::vector<std::string> TaskRegistry::getTasksForCategory(const std::string &category) const
{
    auto it = tasksByCategory.find(category);
    if (it != tasksByCategory.end())
    {
        return it->second;
    }
    return std::vector<std::string>();
}

std::shared_ptr<Task> TaskRegistry::getTask(const std::string &taskName) const
{
    auto it = taskMap.find(taskName);
    return (it != taskMap.end()) ? it->second : nullptr;
}

void TaskRegistry::registerTask(const std::string &category, const std::string &taskName, std::shared_ptr<Task> task)
{
    tasksByCategory[category].push_back(taskName);
    taskMap[taskName] = task;
}
