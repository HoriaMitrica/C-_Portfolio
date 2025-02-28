cmake_minimum_required(VERSION 3.10)

project(CppPracticalTasks)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    StringTasks/StringTasks.cpp
    StringTasks/StringTasksPlugin.cpp
    OOPTasks/OOPTasks.cpp
    Classes/Menu.cpp
    Classes/ConsoleManager.cpp
    Classes/PluginManager.cpp
    Classes/TaskRegistry.cpp
    Classes/MenuManager.cpp
    Classes/InputManager.cpp
)

set(IMGUI_SOURCES
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(core_lib STATIC ${SOURCES})
target_include_directories(core_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    StringTasks
    OOPTasks
    Classes
)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    
    add_executable(main main.cpp ${IMGUI_SOURCES})
    
    target_link_libraries(main core_lib)
    
    target_include_directories(main PRIVATE 
        external/imgui
        external/imgui/backends
    )
    
    target_link_options(main PRIVATE
        -sUSE_GLFW=3
        -sUSE_WEBGL2=1
        -sALLOW_MEMORY_GROWTH=1
        -sMAX_WEBGL_VERSION=2
        -sMIN_WEBGL_VERSION=2
        -sASYNCIFY
        -sEXPORTED_RUNTIME_METHODS=ccall,cwrap
        -sEXPORTED_FUNCTIONS=_main,_malloc,_free
        --shell-file ${CMAKE_SOURCE_DIR}/shell.html
    )
else()
    add_executable(main main.cpp ${IMGUI_SOURCES})
    
    target_link_libraries(main core_lib)
    
    target_include_directories(main PRIVATE 
        external/imgui
        external/imgui/backends
    )
    
    find_package(OpenGL REQUIRED)
    find_package(glfw3 REQUIRED)
    target_link_libraries(main glfw OpenGL::GL)
    
    enable_testing()
    
    find_package(GTest REQUIRED)
    
    add_executable(tests tests/StringTasks.cpp)
    
    target_link_libraries(tests core_lib GTest::GTest GTest::Main pthread)
    
    add_test(NAME StringTasksTests COMMAND tests)
endif()