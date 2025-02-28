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

// Add Emscripten header when compiling for web
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// Global state for main loop
struct AppState {
    GLFWwindow* window;
    MenuManager menuManager;
    char userInput[256] = "";
    bool shouldFocusInput = true;
};

// Global instance of app state
AppState appState;

void processUserInput()
{
    std::string inputStr(appState.userInput);
    ConsoleManager::log("User entered: " + inputStr);

    if (InputManager::isWaitingForInput())
    {
        InputManager::handleInput(inputStr);
        appState.menuManager.displayMenu();
    }
    else
    {
        try
        {
            appState.menuManager.handleSelection(std::stoi(inputStr) - 1);
        }
        catch (const std::exception &e)
        {
            ConsoleManager::log("Invalid input: Please enter a number");
        }
    }

    appState.userInput[0] = '\0';
    appState.shouldFocusInput = true;
}

void setupOpenGL(GLFWwindow *&window)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Set GL context version for both native and web
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
    window = glfwCreateWindow(800, 600, "C++ Practical Tasks GUI", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
}

// Main loop function that will be called each frame
void main_loop_iteration()
{
    // Skip if window should close
    if (glfwWindowShouldClose(appState.window)) {
        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        #endif
        return;
    }
    
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
        appState.menuManager.setMenu("main");
        interactingWithButtons = true;
    }

    if (ImGui::IsItemHovered() || ImGui::IsItemActive())
        interactingWithButtons = true;

    if (!InputManager::isWaitingForInput())
    {
        if (ImGui::Button("Clear Console"))
        {
            ConsoleManager::clear();
            appState.menuManager.displayMenu();
            interactingWithButtons = true;
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            interactingWithButtons = true;
    }

    // We need to modify the test button for web environment
    #ifndef __EMSCRIPTEN__
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
    #else
    // Optional: Add a disabled button or alternative for the web version
    ImGui::BeginDisabled(true);
    if (ImGui::Button("Run Tests (Disabled in Web)"))
    {
        // No action
    }
    ImGui::EndDisabled();
    #endif

    if (ImGui::IsItemHovered() || ImGui::IsItemActive())
        interactingWithButtons = true;

    ImGui::Text("Enter command:");

    if (appState.shouldFocusInput && !interactingWithButtons)
    {
        ImGui::SetKeyboardFocusHere();
        appState.shouldFocusInput = false;
    }

    bool enterPressed = ImGui::InputText("##input", appState.userInput, sizeof(appState.userInput),
                                         ImGuiInputTextFlags_EnterReturnsTrue);

    if (ImGui::IsItemActive())
    {
        appState.shouldFocusInput = false;
    }

    if (enterPressed || ImGui::Button("Submit"))
    {
        processUserInput();
    }

    if (ImGui::IsItemHovered() || ImGui::IsItemActive())
        interactingWithButtons = true;

    ImGui::End();

    ImGui::Render();
    
    // Get current frame buffer size
    int display_w, display_h;
    glfwGetFramebufferSize(appState.window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(appState.window);
}

int main()
{
    // Initialize OpenGL
    setupOpenGL(appState.window);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    io.FontGlobalScale = 1.5f;

    // Set up ImGui backends
    ImGui_ImplGlfw_InitForOpenGL(appState.window, true);
    
    // Use WebGL compatible version
    const char* glsl_version = "#version 100";
    #ifndef __EMSCRIPTEN__
    glsl_version = "#version 130";
    #endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Initialize menu
    appState.menuManager.setMenu("main");

    // Start the main loop
    #ifdef __EMSCRIPTEN__
    // Emscripten main loop - 0 fps means to use browser's requestAnimationFrame
    emscripten_set_main_loop(main_loop_iteration, 0, true);
    #else
    // Native main loop
    while (!glfwWindowShouldClose(appState.window)) {
        main_loop_iteration();
    }
    #endif

    // Cleanup - this will only be reached in the native build
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(appState.window);
    glfwTerminate();

    return 0;
}