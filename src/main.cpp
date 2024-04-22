
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Events.h"
#include "Window/Window.h"
#include "graphics/Shader.h"
#include <iostream>
int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {
        0.f, 0.f, 0.f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
};


int main(void) {
    Window::initialize(WIDTH, HEIGHT, "Window 2");
    Events::initialize();
    Shader* shader = load_shader("res/main.glslv", "res/main.glslf");
    if(shader == nullptr){
        std::cerr << "failed to load shader" << std::endl;
        Window::terminate();
        return 1;
    }
    //create VAO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)(0*sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glClearColor(0.6f, 0.62f, 0.65f,1);
    while(!Window::isShouldClose()){
        Events::pullEvents();
        if(Events::jpressed(GLFW_KEY_ESCAPE)){
            Window::setShouldClose(true);
        }
        if(Events::jclicked(GLFW_MOUSE_BUTTON_1)){
            glClearColor(0.3f, 0, 0, 1);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        shader->use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        Window::swapBuffers();

    }
    return 0;
}


