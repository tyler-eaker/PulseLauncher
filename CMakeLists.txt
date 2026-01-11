cmake_minimum_required(VERSION 3.25)

# Project name and language
project(PulseLauncher LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable verbose output (optional)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/app
    ${CMAKE_SOURCE_DIR}/src/data
    ${CMAKE_SOURCE_DIR}/src/platform
    ${CMAKE_SOURCE_DIR}/external/sqlite
)

# Source files
set(SOURCES
    src/main.cpp
    src/app/Application.cpp
    src/app/Launcher.cpp
    src/data/Database.cpp
    external/sqlite/sqlite3.c
)

# Add executable target
add_executable(PulseLauncher ${SOURCES})

# Link Windows system libraries
target_link_libraries(PulseLauncher
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