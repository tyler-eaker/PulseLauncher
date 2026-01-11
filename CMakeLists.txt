cmake_minimum_required(VERSION 3.25)

# Project name and language
project(PulseLauncher LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable verbose output (optional)
set(CMAKE_VERBOSE_MAKEFILE ON)


# Disable building GLFW docs/tests to speed up build
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add the GLFW subdirectory
add_subdirectory(external/glfw)


set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/external/imgui")

# Define the list of ImGui source files we need to compile
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)


# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/app
    ${CMAKE_SOURCE_DIR}/src/data
    ${CMAKE_SOURCE_DIR}/src/platform
    ${CMAKE_SOURCE_DIR}/external/sqlite
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Source files
set(SOURCES
    src/main.cpp
    src/app/Application.cpp
    src/app/GUI.cpp
    src/app/Launcher.cpp
    src/app/Window.cpp
    src/data/Database.cpp
    external/sqlite/sqlite3.c
    ${IMGUI_SOURCES}
)

# Add executable target
add_executable(PulseLauncher ${SOURCES})


# Link libraries
target_link_libraries(PulseLauncher
    PRIVATE
    glfw
    opengl32
    kernel32
    user32
    gdi32
    winspool
    shell32
    ole32
    oleaut32
    uuid
    comdlg32
    advapi32
)

# Specify output directories
set_target_properties(PulseLauncher PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Set warning levels for MSVC
if(MSVC)
    target_compile_options(PulseLauncher PRIVATE /W4 /permissive-)
endif()