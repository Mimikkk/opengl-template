cmake_minimum_required (VERSION 3.17)
project(opengl-template)

# CMake setup
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/dependencies)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

# Executable output directory
set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

include(CompilerWarnings)
include(ConfigureOpenGL)

# Build static
set(BUILD_SHARED_LIBS OFF CACHE STRING "" FORCE)

# Include submodules
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glew)
add_subdirectory(dependencies/glm)

# Project
add_subdirectory(src)
