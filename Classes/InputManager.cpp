#include "InputManager.h"
#include "ConsoleManager.h"

std::queue<std::function<void(const std::string &)>> InputManager::inputHandlers;

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
}

bool InputManager::isWaitingForInput()
{
    return !inputHandlers.empty();
}
