#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <functional>
#include <queue>
#include <string>

class InputManager {
private:
    static std::queue<std::function<void(const std::string&)>> inputHandlers;
    static std::function<void()> menuRefreshCallback;

public:
    static void requestInput(std::function<void(const std::string&)> callback);
    static void handleInput(const std::string& input);
    static bool isWaitingForInput();
    static void setMenuRefreshCallback(std::function<void()> callback);  // ✅ Function to register menu refresh
};

#endif
