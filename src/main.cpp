
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Events.h"
#include "Window/Window.h"
#include "graphics/Shader.h"
#include "Camera/Camera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "Cube/Cube.h"
#include <vector>

int WIDTH = 1280;
int HEIGHT = 720;


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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    std::vector<std::vector<std::vector<Cube> > > cubes(3, std::vector<std::vector<Cube> >(3, std::vector<Cube>(3,
                                                                                                                Cube())));

    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            for (int z = 0; z < 3; ++z) {
                cubes[x][y][z].model = glm::translate(cubes[x][y][z].model,
                                                      glm::vec3((float) (2.0f * x), (float) (2.0f * y),
                                                                (float) (2.0f * z)));
            }
        }
    }


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
        if (Events::jclicked(GLFW_MOUSE_BUTTON_1)) {
            glClearColor(0.1f, 0, 0, 1);
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


        if (Events::jpressed(GLFW_KEY_F)) {
            // Вращение верхней грани кубика
            for (int i = 0; i < 45; ++i) {
                for (int x = 0; x < 3; ++x) {
                    for (int z = 0; z < 3; ++z) {
                        glm::vec3 center = glm::vec3(2.0f, 3.0f, 2.0f); // Берем позицию (x, y, z) центрального кубика
                        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(2.0f),
                                                         glm::vec3(0.0f, -1.0f, 0.0f));
                        glm::mat4 translation = glm::translate(glm::mat4(1.0f),
                                                               -center); // Перемещаем в противоположную сторону от центра
                        glm::mat4 invTranslation = glm::translate(glm::mat4(1.0),
                                                                  center); // Возвращаем кубики обратно после вращения
                        cubes[x][2][z].model = invTranslation * rotation * translation * cubes[x][2][z].model;
                    }
                }

                for (int x = 0; x < 3; ++x)
                    for (int z = 0; z < 3; ++z) {
                        for (int y = 0; y < 3; ++y)
                            cubes[x][y][z].draw(shader, cubes[x][y][z].model);

                    }

                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3 / 2; j++) {
                    std::swap(cubes[i][2][j], cubes[i][2][3 - j - 1]);
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int j = i + 1; j < 3; j++) {
                    std::swap(cubes[i][2][j], cubes[j][2][i]);
                }
            }
        }

        if (Events::jpressed(GLFW_KEY_G)) {
            // Вращение правой грани кубика
            for (int i = 0; i < 45; ++i) {
                for (int y = 0; y < 3; ++y) {
                    for (int z = 0; z < 3; ++z) {
                        glm::vec3 center = glm::vec3(1.0f, 2.0f, 2.0f); // Берем позицию (x, y, z) центрального кубика
                        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(2.0f),
                                                         glm::vec3(1.0f, 0.0f, 0.0f));
                        glm::mat4 translation = glm::translate(glm::mat4(1.0f),
                                                               -center); // Перемещаем в противоположную сторону от центра
                        glm::mat4 invTranslation = glm::translate(glm::mat4(1.0f),
                                                                  center); // Возвращаем кубики обратно после вращения
                        cubes[0][y][z].model = invTranslation * rotation * translation * cubes[0][y][z].model;
                    }
                }
                for (int x = 0; x < 3; ++x)
                    for (int z = 0; z < 3; ++z) {
                        for (int y = 0; y < 3; ++y)
                            cubes[x][y][z].draw(shader, cubes[x][y][z].model);

                    }

                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            int n = 3;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n / 2; j++) {
                    std::swap(cubes[0][i][j], cubes[0][i][n - j - 1]);
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    std::swap(cubes[0][i][j], cubes[0][j][i]);
                }
            }
        }


        camX += -Events::dX / Window::height;

        camY += -Events::dY / Window::height;
        camera->rotation = glm::mat4(1.0f);
        camera->rotate(camY, camX, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shader->use();
        shader->uniformMatrix("projview", camera->getProjection() * camera->getView());

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                3,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void *) 0                          // array buffer offset
        );


        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                for (int z = 0; z < 3; ++z) {
                    cubes[x][y][z].draw(shader, cubes[x][y][z].model);
                }
            }
        }
        glBindVertexArray(0);

        Window::swapBuffers();
    }
    return 0;
}


