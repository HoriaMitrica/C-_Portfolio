#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include "external/imgui/imgui.h"
#include "external/imgui/backends/imgui_impl_glfw.h"
#include "BasicTasks/BasicTasks.h"
#include "Classes/ConsoleManager.h"
#include "Classes/MenuManager.h"
#include "Classes/InputManager.h"
#include "imgui_impl_opengl3.h"

GLFWwindow *window;
MenuManager menuManager;
char userInput[256] = "";
static bool shouldFocusInput = true;

void processUserInput()
{
    std::string inputStr(userInput);
    ConsoleManager::log("User entered: " + inputStr);

    if (InputManager::isWaitingForInput())
    {
        InputManager::handleInput(inputStr);
        menuManager.displayMenu();
    }
    else
    {
        try
        {
            menuManager.handleSelection(std::stoi(inputStr) - 1);
        }
        catch (const std::exception &e)
        {
            ConsoleManager::log("Invalid input: Please enter a number");
        }
    }

    userInput[0] = '\0';
    shouldFocusInput = true;
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

int main()
{
    setupOpenGL(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    io.FontGlobalScale = 1.5f;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    menuManager.setMenu("main");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(560, 600));
        ImGui::SetNextWindowPos(ImVec2(240, 0));
        ImGui::Begin("Console Output", nullptr, ImGuiWindowFlags_NoCollapse);
        for (const auto &line : ConsoleManager::getConsoleOutput())
        {
            ImGui::TextUnformatted(line.c_str());
        }
        ImGui::SetScrollHereY(1.0f);
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(240, 600));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_NoCollapse);

        bool interactingWithButtons = false;

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            interactingWithButtons = true;

        if (ImGui::Button("Main Menu"))
        {
            menuManager.setMenu("main");
            interactingWithButtons = true;
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            interactingWithButtons = true;

        if (!InputManager::isWaitingForInput())
        {
            if (ImGui::Button("Clear Console"))
            {
                ConsoleManager::clear();
                menuManager.displayMenu();
                interactingWithButtons = true;
            }

            if (ImGui::IsItemHovered() || ImGui::IsItemActive())
                interactingWithButtons = true;
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
            interactingWithButtons = true;
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            interactingWithButtons = true;

        ImGui::Text("Enter command:");

        if (shouldFocusInput && !interactingWithButtons)
        {
            ImGui::SetKeyboardFocusHere();
            shouldFocusInput = false;
        }

        bool enterPressed = ImGui::InputText("##input", userInput, sizeof(userInput),
                                             ImGuiInputTextFlags_EnterReturnsTrue);

        if (ImGui::IsItemActive())
        {
            shouldFocusInput = false;
        }

        if (enterPressed || ImGui::Button("Submit"))
        {
            processUserInput();
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            interactingWithButtons = true;

        ImGui::End();

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}