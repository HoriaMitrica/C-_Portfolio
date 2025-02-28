#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <string>
#include <functional>
#include <queue>
#include <mutex>

// InputManager provides a way to request and receive input
// that works with both console and GUI interfaces
class InputManager
{
private:
    static std::queue<std::string> inputQueue;
    static bool waitingForInput;
    static std::string currentPrompt;
    static std::mutex inputMutex;
    static std::function<void(const std::string &)> inputCallback;

public:
    static void requestInput(const std::string &prompt,
                             std::function<void(const std::string &)> callback);

    static void provideInput(const std::string &input);

    static bool isWaitingForInput();

    static std::string getCurrentPrompt();
    static void clearInputQueue();
    static void processNextInput();
};

#endif