#include "MenuManager.h"
#include "ConsoleManager.h"
#include "Task.h"
#include <iostream>

MenuManager::MenuManager() : taskRegistry(TaskRegistry::getInstance()) {
    menus.clear();
    currentMenu = "main";
    
    buildMenusFromRegistry();
}

void MenuManager::buildMenusFromRegistry() {
    std::vector<std::string> mainOptions;
    std::vector<std::function<void()>> mainActions;
    
    for (const auto& category : taskRegistry.getCategories()) {
        mainOptions.push_back(category);
        mainActions.push_back([this, category]() {
            this->setMenu(category);
        });
    }
    
    mainOptions.push_back("Exit");
    mainActions.push_back([]() {
        ConsoleManager::log("Exiting program...");
    });
    
    menus["main"] = Menu("Main Menu", mainOptions, mainActions);
    
    for (const auto& category : taskRegistry.getCategories()) {
        std::vector<std::string> options;
        std::vector<std::function<void()>> actions;
        
        for (const auto& taskName : taskRegistry.getTasksForCategory(category)) {
            options.push_back(taskName);
            actions.push_back([this, taskName]() {
                std::shared_ptr<Task> task = taskRegistry.getTask(taskName);
                if (task) {
                    task->run();
                } else {
                    ConsoleManager::log("Error: Task not found.");
                }
            });
        }
        
        options.push_back("Back");
        actions.push_back([this]() {
            this->setMenu("main");
        });
        
        menus[category] = Menu(category, options, actions);
    }
}

void MenuManager::addMenu(const std::string& name, const Menu& menu) {
    menus[name] = menu;
}

void MenuManager::setMenu(const std::string& name) {
    if (menus.find(name) != menus.end()) {
        currentMenu = name;
        ConsoleManager::log("Switched to menu: " + name);
        displayMenu();
    } else {
        ConsoleManager::log("Error: Menu not found - " + name);
    }
}

void MenuManager::displayMenu() {
    if (menus.find(currentMenu) != menus.end()) {
        ConsoleManager::log("===== " + menus[currentMenu].title + " =====");
        for (size_t i = 0; i < menus[currentMenu].options.size(); i++) {
            ConsoleManager::log(std::to_string(i + 1) + ". " + menus[currentMenu].options[i]);
        }
    } else {
        ConsoleManager::log("Error: Cannot display menu.");
    }
}

void MenuManager::handleSelection(int choice) {
    if (menus.find(currentMenu) != menus.end()) {
        int adjustedChoice = choice - 1; // Convert from 1-based to 0-based indexing
        if (adjustedChoice >= 0 && adjustedChoice < static_cast<int>(menus[currentMenu].options.size())) {
            ConsoleManager::log("Selected: " + menus[currentMenu].options[adjustedChoice]);
            menus[currentMenu].execute(adjustedChoice);
        } else {
            ConsoleManager::log("Error: Invalid selection.");
        }
    } else {
        ConsoleManager::log("Error: Invalid menu selection.");
    }
}

std::string MenuManager::getCurrentMenu() const {
    return currentMenu;
}