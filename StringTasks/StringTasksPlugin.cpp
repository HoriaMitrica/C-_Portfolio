#include "StringTasksPlugin.h"
#include "StringTasks.h"
#include <memory>

std::string StringTasksPlugin::getName() const
{
    return "String Tasks Plugin";
}

void StringTasksPlugin::registerTasks(TaskRegistry &registry)
{
registry.registerTask("String Tasks", "Reverse String", std::make_shared<ReverseStringTask>());
registry.registerTask("String Tasks", "Palindrome Task", std::make_shared<PalindromeTask>());

}

void StringTasksPlugin::initialize()
{
}

void StringTasksPlugin::shutdown()
{
}