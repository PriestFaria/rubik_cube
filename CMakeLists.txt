cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
project(opengl_tutorial)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

add_executable(opengl_tutorial src/main.cpp
        src/Window/Window.h
        src/Window/Window.cpp
        src/Window/Events.h
        src/Window/Events.cpp
        src/graphics/Shader.h
        src/graphics/Shader.cpp
        src/Camera/Camera.h
        src/Camera/Camera.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


find_package(GLEW REQUIRED)


add_subdirectory(glfw-3.4)

target_link_libraries(opengl_tutorial  glm::glm)

target_link_libraries(opengl_tutorial "-framework OpenGL")
target_link_libraries(opengl_tutorial glfw)
target_link_libraries(opengl_tutorial GLEW::glew)
