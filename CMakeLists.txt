# Setting a minimum version of CMake
cmake_minimum_required(VERSION 3.5...4.0)

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

# Option to trigger dependency download
option(DEPENDENCY_UPDATE "Download and extract raylib and raygui if missing" OFF)

# Download and extract dependencies only if DEPENDENCY_UPDATE is ON and directories are missing
if(DEPENDENCY_UPDATE)
    file(MAKE_DIRECTORY "${LIB_DIR}")

    # Download and extract raylib if not present
    if(NOT EXISTS "${RAYLIB_DIR}")
        file(DOWNLOAD
            "https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_win64_mingw-w64.zip"
            "${LIB_DIR}/raylib-5.5_win64_mingw-w64.zip"
            SHOW_PROGRESS
            STATUS DOWNLOAD_STATUS
        )
        list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
        if(NOT STATUS_CODE EQUAL 0)
            message(FATAL_ERROR "Failed to download raylib: ${DOWNLOAD_STATUS}")
        endif()
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf "${LIB_DIR}/raylib-5.5_win64_mingw-w64.zip"
            WORKING_DIRECTORY "${LIB_DIR}"
            RESULT_VARIABLE EXTRACT_RESULT
        )
        if(NOT EXTRACT_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to extract raylib")
        endif()
        file(REMOVE "${LIB_DIR}/raylib-5.5_win64_mingw-w64.zip")
    endif()

    # Download and extract raygui if not present
    if(NOT EXISTS "${RAYGUI_DIR}")
        file(DOWNLOAD
            "https://github.com/raysan5/raygui/archive/refs/tags/4.0.zip"
            "${LIB_DIR}/raygui-4.0.zip"
            SHOW_PROGRESS
            STATUS DOWNLOAD_STATUS
        )
        list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
        if(NOT STATUS_CODE EQUAL 0)
            message(FATAL_ERROR "Failed to download raygui: ${DOWNLOAD_STATUS}")
        endif()
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf "${LIB_DIR}/raygui-4.0.zip"
            WORKING_DIRECTORY "${LIB_DIR}"
            RESULT_VARIABLE EXTRACT_RESULT
        )
        if(NOT EXTRACT_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to extract raygui")
        endif()
        file(REMOVE "${LIB_DIR}/raygui-4.0.zip")
    endif()
endif()

# Verify that required library directories exist
if(NOT EXISTS "${RAYLIB_DIR}/include/raylib.h")
    message(FATAL_ERROR "raylib headers not found in ${RAYLIB_DIR}/include. Please run 'cmake -DDEPENDENCY_UPDATE=ON' to download dependencies.")
endif()
if(NOT EXISTS "${RAYLIB_DIR}/lib/libraylib.a")
    message(FATAL_ERROR "raylib library not found in ${RAYLIB_DIR}/lib. Please run 'cmake -DDEPENDENCY_UPDATE=ON' to download dependencies.")
endif()
if(NOT EXISTS "${RAYGUI_DIR}/src/raygui.h")
    message(FATAL_ERROR "raygui headers not found in ${RAYGUI_DIR}/src. Please run 'cmake -DDEPENDENCY_UPDATE=ON' to download dependencies.")
endif()

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