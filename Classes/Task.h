#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

// In Task.h
class Task {
public:
    virtual ~Task() = default;
    
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getCategory() const = 0;
    
    virtual std::vector<std::string> getInputPrompts() const = 0;
    
    virtual void execute(const std::vector<std::string>& inputs) = 0;
    
    virtual void run() = 0;
    
    virtual bool isActive() const = 0;
    
    virtual void exit() = 0;
    
    virtual bool shouldExitOnInput(const std::string& input) const = 0;
};
#endif