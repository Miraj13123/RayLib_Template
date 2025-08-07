# Define paths (must match CMakeLists.txt)
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(RAYLIB_DIR "${LIB_DIR}/raylib-5.5_win64_mingw-w64")
set(RAYGUI_DIR "${LIB_DIR}/raygui-4.0")

# Function to download and extract dependencies
function(download_and_extract_dependency url dest_dir zip_file)
    if(NOT EXISTS "${dest_dir}")
        file(DOWNLOAD "${url}" "${zip_file}" SHOW_PROGRESS STATUS DOWNLOAD_STATUS)
        list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
        if(NOT STATUS_CODE EQUAL 0)
            message(FATAL_ERROR "Failed to download ${zip_file}: ${DOWNLOAD_STATUS}")
        endif()
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf "${zip_file}"
            WORKING_DIRECTORY "${dest_dir}/.."
            RESULT_VARIABLE EXTRACT_RESULT
        )
        if(NOT EXTRACT_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to extract ${zip_file}")
        endif()
        file(REMOVE "${zip_file}")
    endif()
endfunction()

# Create lib directory
file(MAKE_DIRECTORY "${LIB_DIR}")

# Download and extract dependencies
download_and_extract_dependency(
    "https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_win64_mingw-w64.zip"
    "${RAYLIB_DIR}"
    "${LIB_DIR}/raylib-5.5_win64_mingw-w64.zip"
)
download_and_extract_dependency(
    "https://github.com/raysan5/raygui/archive/refs/tags/4.0.zip"
    "${RAYGUI_DIR}"
    "${LIB_DIR}/raygui-4.0.zip"
)

