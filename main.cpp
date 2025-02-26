#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include "external/imgui/imgui.h"
#include "external/imgui/backends/imgui_impl_glfw.h"
#include "external/imgui/backends/imgui_impl_opengl3.h"
#include "BasicTasks/BasicTasks.h" // Include basic tasks

using namespace std;

// Console output storage for ImGui
vector<string> consoleOutput;
char userInput[256] = ""; // Persistent input buffer
string currentMenu = "main"; // Track current menu step

void addToConsole(const string &message) {
    consoleOutput.push_back(message);
}

// Function to process user input dynamically
void processUserInput() {
    string inputStr(userInput);
    consoleOutput.clear();

    // **Main Menu Navigation**
    if (currentMenu == "main") {
        if (inputStr == "1") {
            currentMenu = "basic_tasks";
            addToConsole("Basic C++ Tasks:");
            addToConsole("1. Reverse a String");
            addToConsole("2. Check Palindrome");
            addToConsole("Enter task number:");
        } 
        else if (inputStr == "2") {
            addToConsole("Exiting program...");
            currentMenu = "exit";
        } 
        else {
            addToConsole("Invalid choice! Enter 1 or 2.");
        }
    }

    // **Basic Tasks Menu**
    else if (currentMenu == "basic_tasks") {
        if (inputStr == "1") {
            addToConsole("Enter a string to reverse:");
            currentMenu = "reverse_string";
        } 
        else if (inputStr == "2") {
            addToConsole("Enter a string to check for palindrome:");
            currentMenu = "check_palindrome";
        } 
        else {
            addToConsole("Invalid choice! Enter 1 or 2.");
        }
    }

    // **Task: Reverse String**
    else if (currentMenu == "reverse_string") {
        addToConsole("Reversed String: " + reverseString(inputStr));
        currentMenu = "basic_tasks";
        addToConsole("Basic C++ Tasks:");
        addToConsole("1. Reverse a String");
        addToConsole("2. Check Palindrome");
        addToConsole("Enter task number:");
    }

    // **Task: Check Palindrome**
    else if (currentMenu == "check_palindrome") {
        bool isPalin = checkPalindrome(inputStr);
        addToConsole("Palindrome check: " + string(isPalin ? "Yes" : "No"));
        currentMenu = "basic_tasks";
        addToConsole("Basic C++ Tasks:");
        addToConsole("1. Reverse a String");
        addToConsole("2. Check Palindrome");
        addToConsole("Enter task number:");
    }

    userInput[0] = '\0'; // Clear input field after processing
}

// Run tests and capture output
void runTests() {
    consoleOutput.clear();
    addToConsole("Running Tests...");

    FILE *pipe = popen("ctest --verbose", "r");
    if (!pipe) {
        addToConsole("Failed to execute ctest.");
        return;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        addToConsole(buffer);
    }

    pclose(pipe);
}

// Clear console output
void clearConsole() {
    consoleOutput.clear();
}

// OpenGL + ImGui Setup
void setupOpenGL(GLFWwindow *&window) {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(800, 600, "C++ Practical Tasks GUI", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
}

int main() {
    GLFWwindow *window;
    setupOpenGL(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    addToConsole("Main Menu:");
    addToConsole("1. Basic C++ Tasks");
    addToConsole("2. Exit");
    addToConsole("Enter your choice:");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Console Output Window
        ImGui::SetNextWindowSize(ImVec2(640, 600));
        ImGui::SetNextWindowPos(ImVec2(160, 0));
        ImGui::Begin("Console Output", nullptr, ImGuiWindowFlags_NoCollapse);
        for (const auto &line : consoleOutput) {
            ImGui::TextUnformatted(line.c_str());
        }
        ImGui::End();

        // Controls Window
        ImGui::SetNextWindowSize(ImVec2(160, 600));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_NoCollapse);

        // Utility Buttons
        if (ImGui::Button("Run Tests")) {
            clearConsole();
            runTests();
        }
        if (ImGui::Button("Clear Console")) {
            clearConsole();
        }

        // Input Field & Submission
        ImGui::Text("Enter command:");
        ImGui::InputText("##input", userInput, sizeof(userInput));
        if (ImGui::Button("Submit")) {
            addToConsole(string("User entered: ") + userInput);
            processUserInput();
        }

        ImGui::End();

        // Render ImGui
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
