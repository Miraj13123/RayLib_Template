# Setting a minimum version of CMake
cmake_minimum_required(VERSION 3.5...4.0)

# Set default C++ compiler to g++ for MinGW if not specified
if(MINGW AND NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER "g++")
endif()

# Project name "Calculator", Language "CXX" means C++
project(Calculator LANGUAGES CXX)

# Recursively glob all .cpp files in the project folder
file(GLOB_RECURSE ALL_CPP_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/*.cpp")

# Exclude files from the bin directory
list(FILTER ALL_CPP_FILES EXCLUDE REGEX ".*/bin/.*")

# Add executable
add_executable(app ${ALL_CPP_FILES})

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags for MinGW
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

# Compiler flags for Clang with MSVC
if(MSVC AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(app PRIVATE -Wextra -Wall)
endif()

# Define paths for libraries
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(RAYLIB_DIR "${LIB_DIR}/raylib-5.5_win64_mingw-w64")
set(RAYGUI_DIR "${LIB_DIR}/raygui-4.0")

# Custom target to download dependencies
add_custom_target(updateDependency
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_SOURCE_DIR}/updateDependency.cmake"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    COMMENT "Updating raylib and raygui dependencies..."
)

# Create an interface library for external dependencies
add_library(ExternalLibrary INTERFACE)
target_include_directories(ExternalLibrary INTERFACE
    "${RAYLIB_DIR}/include"  # -I for raylib.h
    "${RAYGUI_DIR}/src"      # -I for raygui.h
)
target_link_libraries(ExternalLibrary INTERFACE
    "${RAYLIB_DIR}/lib/libraylib.a"  # -L and -l for raylib
    opengl32                         # -l for OpenGL
    gdi32                            # -l for GDI
    winmm                            # -l for Windows multimedia
)

# Link the app to ExternalLibrary
target_link_libraries(app PRIVATE ExternalLibrary)

# Optional: Ensure update_dependencies runs before app
# add_dependencies(app update_dependencies)