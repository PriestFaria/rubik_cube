
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Events.h"
#include "Window/Window.h"
#include "graphics/Shader.h"
#include "Camera/Camera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {
        0.f, 0.f, 0.f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
};

int Window::width = WIDTH;
int Window::height = HEIGHT;

int main(void) {
    Window::initialize(WIDTH, HEIGHT, "Window 2");
    Events::initialize();
    Shader *shader = load_shader("res/main.glslv", "res/main.glslf");
    if (shader == nullptr) {
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glClearColor(0.6f, 0.62f, 0.65f, 1);

    Camera *camera = new Camera(glm::vec3(0.0f, 3.0f, 5.0f), glm::radians(70.0f));


    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));


    float lastTime = glfwGetTime();
    float delta = 0.0f;
    float speed = 5;

    float camX = 0.0f;
    float camY = 0.0f;

    while (!Window::isShouldClose()) {
        float currentTime = glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;
        Events::pullEvents();
        if (Events::jpressed(GLFW_KEY_ESCAPE)) {
            Window::setShouldClose(true);
        }
        if (Events::jclicked(GLFW_MOUSE_BUTTON_1)) {
            glClearColor(0.1f, 0, 0, 1);
        }
        if (Events::jpressed(GLFW_KEY_TAB)){
            Events::toggleCursor();
        }
        if (Events::pressed(GLFW_KEY_X)) {
            camera->position += camera->front * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_Z)) {
            camera->position -= camera->front * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_D)) {
            camera->position += camera->right * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_A)) {
            camera->position -= camera->right * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_W)) {
            camera->position += camera->up * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_S)) {
            camera->position -= camera->up * delta * speed;
        }

        camX += -Events::dX / Window::height;

        camY += -Events::dY/Window::height;
        camera->rotation = glm::mat4(1.0f);
        camera->rotate(camY, camX, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader->use();
        shader->uniformMatrix("model", model);
        shader->uniformMatrix("projview", camera->getProjection() * camera->getView());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        Window::swapBuffers();

    }
    return 0;
}


