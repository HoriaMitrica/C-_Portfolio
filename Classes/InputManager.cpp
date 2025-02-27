#include "InputManager.h"
#include "ConsoleManager.h"

std::queue<std::function<void(const std::string &)>> InputManager::inputHandlers;
std::function<void()> InputManager::menuRefreshCallback = nullptr; 

void InputManager::requestInput(std::function<void(const std::string &)> callback)
{
    inputHandlers.push(callback);
    ConsoleManager::log("Waiting for input...");
}

void InputManager::handleInput(const std::string &input)
{
    if (!inputHandlers.empty())
    {
        auto handler = inputHandlers.front();
        inputHandlers.pop();
        handler(input);
    }

    if (inputHandlers.empty() && menuRefreshCallback)
    {
        menuRefreshCallback();
    }
}

void InputManager::setMenuRefreshCallback(std::function<void()> callback)
{
    menuRefreshCallback = callback;
}

bool InputManager::isWaitingForInput()
{
    return !inputHandlers.empty();
}
