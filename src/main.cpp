
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Events.h"
#include "Window/Window.h"
#include "graphics/Shader.h"
#include "Camera/Camera.h"
#include <iostream>
#include "RubikCube/RubikCube.h"

#include <fstream>

int WIDTH = 1280;
int HEIGHT = 720;


int Window::width = WIDTH;
int Window::height = HEIGHT;


int main(void) {
    // file



    Window::initialize(WIDTH, HEIGHT, "Window 2");
    Events::initialize();
    Shader *shader = load_shader("res/main.glslv", "res/main.glslf");
    if (shader == nullptr) {
        std::cerr << "failed to load shader" << std::endl;
        Window::terminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    RubikCube cube(shader);
    cube.make_grid();

    std::ofstream out;
//    out.open("example.txt");

    cube.load_from_file("example.txt");
    glClearColor(0.6f, 0.62f, 0.65f, 1);

    Camera *camera = new Camera(glm::vec3(0.0f, 3.0f, 5.0f), glm::radians(70.0f));


    glm::mat4 model(1.0f);

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

        if (Events::jpressed(GLFW_KEY_TAB)) {
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


        if (Events::jpressed(GLFW_KEY_V)) {
            // Вращение верхней грани кубика
            for (int i = 0; i < 45; ++i) {
                cube.rotate_horizontal(2, 2.0f);

                cube.draw();
                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_horizontal_matrix(2);
            if (out.is_open())
                out << "1" << std::endl;
        }


        if (Events::jpressed(GLFW_KEY_B)) {
            // Вращение средней горизонтальной грани кубика
            for (int i = 0; i < 45; ++i) {
                cube.rotate_horizontal(1, 2.0f);
                cube.draw();
                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_horizontal_matrix(1);
            if (out.is_open())
                out << "2" << std::endl;
        }

        if (Events::jpressed(GLFW_KEY_N)) {
            // Вращение нижней грани кубика
            for (int i = 0; i < 45; ++i) {
                cube.rotate_horizontal(0, 2.0f);
                cube.draw();
                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_horizontal_matrix(0);
            if (out.is_open())
                out << "3" << std::endl;
        }


        if (Events::jpressed(GLFW_KEY_G)) {
            // Вращение правой грани кубика
            for (int i = 0; i < 45; ++i) {
                cube.rotate_vertical(0, 2.0f);
                cube.draw();
                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_vertical_matrix(0);
            if (out.is_open())
                out << "6" << std::endl;
        }
        if (Events::jpressed(GLFW_KEY_J)) {
            // Вращение левой грани кубика
            for (int i = 0; i < 45; ++i) {
                cube.rotate_vertical(2, 2.0f);
                cube.draw();

                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_vertical_matrix(2);
            if (out.is_open())
                out << "4" << std::endl;
        }

        if (Events::jpressed(GLFW_KEY_H)) {
            // Вращение средней вертикальной грани кубика
            for (int i = 0; i < 45; ++i) {
                cube.rotate_vertical(1, 2.0f);
                cube.draw();

                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_vertical_matrix(1);
            if (out.is_open())
                out << "5" << std::endl;
        }
        if (Events::jpressed(GLFW_KEY_P)){
            cube.solve(9.0f);
        }


        camX += -Events::dX / Window::height;
        camY += -Events::dY / Window::height;

        camera->rotation = glm::mat4(1.0f);
        camera->rotate(camY, camX, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        shader->uniformMatrix("projview", camera->getProjection() * camera->getView());

        cube.draw();
        glBindVertexArray(0);

        Window::swapBuffers();
    }
    out.close();
    return 0;
}

//горизонтальные
//1 - верхняя
//2 - средняя
//3 - нижняя
//вертикальные
//4 - левая
//5 - средняя
//6 - правая
