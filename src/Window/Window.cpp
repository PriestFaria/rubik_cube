//
// Created by Timur on 06.04.2024.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include <iostream>
GLFWwindow *Window::window;

int Window::initialize(int width, int height, const char *title) {
    height = height;
    width = width;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    Window::window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //init GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
}



bool Window::isShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {

    glfwSwapBuffers(Window::window);
}

void Window::setShouldClose(bool flag) {
    glfwSetWindowShouldClose(window, flag);
}

void Window::terminate() {

    glfwTerminate();
}

void Window::setCursorMode(int mode) {
    glfwSetInputMode(window, GLFW_CURSOR, mode);
}