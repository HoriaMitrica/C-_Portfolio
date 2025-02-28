#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <functional>
#include <queue>
#include <string>

class InputManager {
private:
    static std::queue<std::function<void(const std::string&)>> inputHandlers;

public:
    static void requestInput(std::function<void(const std::string&)> callback);
    static void handleInput(const std::string& input);
    static bool isWaitingForInput();
};

#endif
