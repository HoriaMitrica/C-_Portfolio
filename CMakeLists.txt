cmake_minimum_required(VERSION 3.10)

# Project name
project(CppPracticalTasks)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the main executable
add_executable(main 
    main.cpp
    BasicTasks/BasicTasks.cpp
    OOPTasks/OOPTasks.cpp
    Classes/Menu.cpp
    Classes/ConsoleManager.cpp
    Classes/MenuManager.cpp
    Classes/InputManager.cpp
    
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

# Include directories
target_include_directories(main PRIVATE 
    BasicTasks
    OOPTasks
    Classes
    external/imgui
    external/imgui/backends
)

# Find and link OpenGL, GLFW
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(main glfw OpenGL::GL)

# Enable testing
enable_testing()

# Add Google Test (if installed system-wide)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Create a test executable
add_executable(tests 
    tests/BasicTasks.cpp
)

# Link Google Test with the test executable
target_link_libraries(tests GTest::GTest GTest::Main pthread)

# Register tests
add_test(NAME BasicTasksTests COMMAND tests)
