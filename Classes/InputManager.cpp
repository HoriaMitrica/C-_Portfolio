#include "InputManager.h"

std::queue<std::string> InputManager::inputQueue;
bool InputManager::waitingForInput = false;
std::string InputManager::currentPrompt = "";
std::mutex InputManager::inputMutex;
std::function<void(const std::string &)> InputManager::inputCallback = nullptr;

void InputManager::requestInput(const std::string &prompt,
                                std::function<void(const std::string &)> callback)
{
    std::lock_guard<std::mutex> lock(inputMutex);
    waitingForInput = true;
    currentPrompt = prompt;
    inputCallback = callback;
}

void InputManager::provideInput(const std::string &input)
{
    std::lock_guard<std::mutex> lock(inputMutex);
    inputQueue.push(input);
}

bool InputManager::isWaitingForInput()
{
    std::lock_guard<std::mutex> lock(inputMutex);
    return waitingForInput;
}

std::string InputManager::getCurrentPrompt()
{
    std::lock_guard<std::mutex> lock(inputMutex);
    return currentPrompt;
}

void InputManager::processNextInput()
{
    std::lock_guard<std::mutex> lock(inputMutex);

    if (!inputQueue.empty() && waitingForInput && inputCallback)
    {
        std::string input = inputQueue.front();
        inputQueue.pop();

        auto callback = inputCallback;
        waitingForInput = false;
        currentPrompt = "";
        inputCallback = nullptr;

        lock.~lock_guard();
        callback(input);
    }
}

void InputManager::clearInputQueue()
{
    std::lock_guard<std::mutex> lock(inputMutex);
    std::queue<std::string> empty;
    std::swap(inputQueue, empty);
}