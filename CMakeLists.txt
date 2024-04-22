cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
project(opengl_tutorial)
#include(FetchContent)
#set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
#
#FetchContent_Declare(glew GIT_REPOSITORY https://github.com/nigels-com/glew.git
#        GIT_TAG e1a80a9f12d7def202d394f46e44cfced1104bfb) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
#FetchContent_MakeAvailable(glew)
#

add_executable(opengl_tutorial src/main.cpp
        src/Window/Window.h
        src/Window/Window.cpp
        src/Window/Events.h
        src/Window/Events.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)



find_package(GLEW REQUIRED)



add_subdirectory(glfw-3.4)

target_link_libraries(opengl_tutorial "-framework OpenGL")
target_link_libraries(opengl_tutorial glfw)
target_link_libraries(opengl_tutorial GLEW::glew)