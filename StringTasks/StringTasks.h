#ifndef STRINGTASKS_H
#define STRINGTASKS_H

#include "../Classes/Task.h"
#include <string>
#include <vector>

class StringTask : public Task
{
protected:
    bool active = false;

public:
    std::string getCategory() const override;

    bool isActive() const override { return active; }
    void exit() override { active = false; }
};

class ReverseStringTask : public StringTask
{
public:
    std::string getName() const override;
    std::string getDescription() const override;
    std::vector<std::string> getInputPrompts() const override;
    void execute(const std::vector<std::string> &inputs) override;
    void run() override;
    bool shouldExitOnInput(const std::string &input) const override;
    static std::string reverseString(const std::string &input);

private:
    void requestNextInput();
};

class PalindromeTask : public StringTask
{
public:
    std::string getName() const override;
    std::string getDescription() const override;
    std::vector<std::string> getInputPrompts() const override;
    void execute(const std::vector<std::string> &inputs) override;
    void run() override;
    bool shouldExitOnInput(const std::string &input) const override;
    static bool isPalindrome(const std::string &input);

private:
    void requestNextInput();
};

#endif