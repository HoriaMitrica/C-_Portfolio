#ifndef TASKREGISTRY_H
#define TASKREGISTRY_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Task;

class TaskRegistry {
public:
    static TaskRegistry& getInstance();

    std::vector<std::string> getCategories() const;
    std::vector<std::string> getTasksForCategory(const std::string &category) const;
    std::shared_ptr<Task> getTask(const std::string &taskName) const;
    void registerTask(const std::string &category, const std::string &taskName, std::shared_ptr<Task> task);

private:
    TaskRegistry() = default;
    std::unordered_map<std::string, std::vector<std::string>> tasksByCategory;
    std::unordered_map<std::string, std::shared_ptr<Task>> taskMap;
};

#endif 
