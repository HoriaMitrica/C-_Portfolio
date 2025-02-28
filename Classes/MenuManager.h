#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include "Menu.h"
#include "TaskRegistry.h"

class MenuManager {
private:
    std::unordered_map<std::string, Menu> menus;
    std::string currentMenu;
    TaskRegistry& taskRegistry;

public:
    MenuManager();
    
    void buildMenusFromRegistry();
    
    void addMenu(const std::string& name, const Menu& menu);
    
    void setMenu(const std::string& name);
    
    void displayMenu();
    
    void handleSelection(int choice);
    
    std::string getCurrentMenu() const;
};

#endif