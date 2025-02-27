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
#include "imgui_impl_opengl3.h"

GLFWwindow *window;
MenuManager menuManager;
char userInput[256] = "";

void processUserInput() {
    std::string inputStr(userInput);
    ConsoleManager::log("User entered: " + inputStr);
    menuManager.handleSelection(std::stoi(inputStr));
    userInput[0] = '\0';
}

void setupOpenGL(GLFWwindow *&window) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(800, 600, "C++ Practical Tasks GUI", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
}

int main() {
    setupOpenGL(window);
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    menuManager.setMenu("main");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(640, 600));
        ImGui::SetNextWindowPos(ImVec2(160, 0));
        ImGui::Begin("Console Output", nullptr, ImGuiWindowFlags_NoCollapse);
        for (const auto &line : ConsoleManager::getConsoleOutput()) {
            ImGui::TextUnformatted(line.c_str());
        }
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(160, 600));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_NoCollapse);

        if (ImGui::Button("Main Menu")) {
            menuManager.setMenu("main");
        }
        if (ImGui::Button("Clear Console")) {
            ConsoleManager::log(""); 
            menuManager.displayMenu();
        }
        if (ImGui::Button("Run Tests")) {
            ConsoleManager::log("Running Tests...");
            FILE *pipe = popen("ctest --verbose", "r");
            if (!pipe) {
                ConsoleManager::log("Failed to execute tests.");
            } else {
                char buffer[256];
                while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                    ConsoleManager::log(buffer);
                }
                pclose(pipe);
            }
            ConsoleManager::log("Test execution complete.");
        }

        ImGui::Text("Enter command:");
        ImGui::InputText("##input", userInput, sizeof(userInput));
        if (ImGui::Button("Submit")) {
            processUserInput();
        }

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
