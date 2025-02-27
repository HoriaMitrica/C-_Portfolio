#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <functional>

class Menu {
public:
    std::string title;
    std::vector<std::string> options;
    std::vector<std::function<void()>> actions;

    Menu(); // ✅ Default constructor
    Menu(std::string title, std::vector<std::string> options, std::vector<std::function<void()>> actions);

    void execute(int choice);
};

#endif
