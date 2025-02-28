#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include "external/imgui/imgui.h"
#include "external/imgui/backends/imgui_impl_glfw.h"
#include "external/imgui/backends/imgui_impl_opengl3.h"
#include "Classes/TaskRegistry.h"
#include "Classes/PluginManager.h"
#include "Classes/Task.h"
#include "StringTasks/StringTasksPlugin.h"
#include "Classes/ConsoleManager.h"
#include "Classes/MenuManager.h"
#include "Classes/InputManager.h"

GLFWwindow *window;
MenuManager *menuManager;
char userInput[256] = "";

void processUserInput()
{
    std::string inputStr(userInput);
    if (!inputStr.empty())
    {
        ConsoleManager::log("User entered: " + inputStr);

        if (InputManager::isWaitingForInput())
        {
            InputManager::provideInput(inputStr);

            InputManager::processNextInput();
        }
        else
        {
            try
            {
                int choice = std::stoi(inputStr);
                menuManager->handleSelection(choice);
            }
            catch (const std::exception &e)
            {
                ConsoleManager::log("Error processing input: " + std::string(e.what()));
            }
        }

        userInput[0] = '\0';
    }
}
void setupOpenGL(GLFWwindow *&window)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(800, 600, "C++ Practical Tasks GUI", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
}

void setupPlugins()
{
    auto stringPlugin = std::make_unique<StringTasksPlugin>();
    PluginManager::getInstance().registerPlugin(std::move(stringPlugin));

    PluginManager::getInstance().initializePlugins();
}

int main()
{
    setupPlugins();

    menuManager = new MenuManager();

    setupOpenGL(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    menuManager->setMenu("main");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(640, 600));
        ImGui::SetNextWindowPos(ImVec2(160, 0));
        ImGui::Begin("Console Output", nullptr, ImGuiWindowFlags_NoCollapse);

        auto consoleLines = ConsoleManager::getLastNLines(200);
        for (const auto &line : consoleLines)
        {
            ImGui::TextUnformatted(line.c_str());
        }

        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(160, 600));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_NoCollapse);

        bool taskActive = false;
        auto &registry = TaskRegistry::getInstance();

        for (const auto &category : registry.getCategories())
        {
            for (const auto &taskName : registry.getTasksForCategory(category))
            {
                auto task = registry.getTask(taskName);
                if (task && task->isActive())
                {
                    taskActive = true;
                    break;
                }
            }
            if (taskActive)
                break;
        }

        if (InputManager::isWaitingForInput())
        {
            ImGui::TextWrapped("%s", InputManager::getCurrentPrompt().c_str());
            if (taskActive && ImGui::Button("Back to Menu"))
            {
                for (const auto &category : registry.getCategories())
                {
                    for (const auto &taskName : registry.getTasksForCategory(category))
                    {
                        auto task = registry.getTask(taskName);
                        if (task && task->isActive())
                        {
                            task->exit();
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            if (ImGui::Button("Main Menu"))
            {
                menuManager->setMenu("main");
            }
            if (ImGui::Button("Clear Console"))
            {
                ConsoleManager::clear();
                menuManager->displayMenu();
            }
            if (ImGui::Button("Run Tests"))
            {
                ConsoleManager::log("Running Tests...");
                FILE *pipe = popen("ctest --verbose", "r");
                if (!pipe)
                {
                    ConsoleManager::log("Failed to execute tests.");
                }
                else
                {
                    char buffer[256];
                    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
                    {
                        ConsoleManager::log(buffer);
                    }
                    pclose(pipe);
                }
                ConsoleManager::log("Test execution complete.");
            }
        }
        ImGui::Text("Enter command:");
        if (ImGui::InputText("##input", userInput, sizeof(userInput),
                             ImGuiInputTextFlags_EnterReturnsTrue))
        {
            processUserInput();
        }
        if (ImGui::Button("Submit"))
        {
            processUserInput();
        }

        ImGui::End();

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    PluginManager::getInstance().shutdownPlugins();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    delete menuManager;

    return 0;
}