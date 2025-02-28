cmake_minimum_required(VERSION 3.10)

project(CppPracticalTasks)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    BasicTasks/BasicTasks.cpp
    OOPTasks/OOPTasks.cpp
    Classes/Menu.cpp
    Classes/ConsoleManager.cpp
    Classes/MenuManager.cpp
    Classes/InputManager.cpp
)
# Define ImGui source files
set(IMGUI_SOURCES
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

# Check if we're compiling with Emscripten
if(EMSCRIPTEN)
    # Emscripten-specific settings
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    
    # Add the main executable
    add_executable(main ${SOURCES} ${IMGUI_SOURCES})
    
    # Include directories
    target_include_directories(main PRIVATE 
        BasicTasks
        OOPTasks
        Classes
        external/imgui
        external/imgui/backends
    )
    
    # Emscripten-specific link options
    target_link_options(main PRIVATE
        -sUSE_GLFW=3
        -sUSE_WEBGL2=1
        -sALLOW_MEMORY_GROWTH=1
        -sMAX_WEBGL_VERSION=2
        -sMIN_WEBGL_VERSION=2
        -sASYNCIFY
        -sEXPORTED_RUNTIME_METHODS=ccall,cwrap
        -sEXPORTED_FUNCTIONS=_main,_malloc,_free
        # Add any asset directories you need to preload
        # --preload-file assets@/assets
        # Uncomment if you create a custom HTML shell
         --shell-file ${CMAKE_SOURCE_DIR}/shell.html
    )
else()
    
    add_executable(main ${SOURCES} ${IMGUI_SOURCES})
    
    target_include_directories(main PRIVATE 
        BasicTasks
        OOPTasks
        Classes
        external/imgui
        external/imgui/backends
    )
    
    find_package(OpenGL REQUIRED)
    find_package(glfw3 REQUIRED)
    target_link_libraries(main glfw OpenGL::GL)
    
    enable_testing()
    
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    
    add_executable(tests 
        tests/BasicTasks.cpp
    )
    
    target_link_libraries(tests GTest::GTest GTest::Main pthread)
    
    add_test(NAME BasicTasksTests COMMAND tests)
endif()