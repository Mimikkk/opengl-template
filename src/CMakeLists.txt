cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
project(grafika)

set(PROJECT_LIBRARY ${PROJECT_NAME}-lib)

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.h ${SRC_DIR}/*.glsl)

add_library(${PROJECT_LIBRARY} STATIC ${SOURCES})
target_compile_definitions(${PROJECT_LIBRARY} PUBLIC GLEW_STATIC=1)
target_link_libraries(${PROJECT_LIBRARY} PUBLIC glfw ${GLFW_LIBRARIES}
        libglew_static glm compiler_warnings compiler_options)


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBRARY} compiler_warnings compiler_options)