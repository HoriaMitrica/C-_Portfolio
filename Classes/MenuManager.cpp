#include "MenuManager.h"
#include "ConsoleManager.h"
#include "InputManager.h"
#include "../BasicTasks/BasicTasks.h"

MenuManager::MenuManager()
{
    initializeMenus();
    currentMenu = "main";
}

void MenuManager::initializeMenus()
{

    InputManager::setMenuRefreshCallback([this]()
                                         { displayMenu(); });

    menus["main"] = Menu("Main Menu",
                         {"Basic C++ Tasks", "Exit"},
                         {[this]()
                          { setMenu("basic_tasks"); },
                          []()
                          { ConsoleManager::log("Exiting program..."); }});

    menus["basic_tasks"] = Menu("Basic C++ Tasks",
                                {"Reverse a String", "Check Palindrome", "Back"},
                                {reverseString, checkPalindrome, [this]()
                                 { setMenu("main"); }});
}

void MenuManager::addMenu(const std::string &name, const Menu &menu)
{
    menus[name] = menu;
}

void MenuManager::setMenu(const std::string &name)
{
    if (menus.find(name) != menus.end())
    {
        currentMenu = name;
        ConsoleManager::log("Switched to menu: " + name);
        displayMenu();
    }
    else
    {
        ConsoleManager::log("Error: Menu not found - " + name);
    }
}

void MenuManager::displayMenu()
{
    ConsoleManager::log("===== " + menus[currentMenu].title + " =====");
    for (size_t i = 0; i < menus[currentMenu].options.size(); i++)
    {
        ConsoleManager::log(std::to_string(i + 1) + ". " + menus[currentMenu].options[i]);
    }
}

void MenuManager::handleSelection(int choice)
{
    if (menus.find(currentMenu) != menus.end())
    {
        menus[currentMenu].execute(choice);
    }
    else
    {
        ConsoleManager::log("Error: Invalid menu selection.");
    }
}
