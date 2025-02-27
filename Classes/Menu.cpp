#include "Menu.h"
#include "ConsoleManager.h"

Menu::Menu() : title(""), options({}), actions({}) {} // ✅ Default constructor

Menu::Menu(std::string title, std::vector<std::string> options, std::vector<std::function<void()>> actions) 
    : title(title), options(options), actions(actions) {}

void Menu::execute(int choice) {
    if (choice >= 0 && choice < actions.size()) {
        ConsoleManager::log("Executing option: " + options[choice]);
        actions[choice]();
    } else {
        ConsoleManager::log("Invalid choice!");
    }
}
