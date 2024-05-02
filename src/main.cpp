
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

//    std::ofstream out;
////    out.open("example.txt");

//    cube.load_from_file("example.txt");
    glClearColor(0.6f, 0.62f, 0.65f, 1);

    Camera *camera = new Camera(glm::vec3(7.0f, 7.0f, 15.0f), glm::radians(90.0f));

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
            for (int i = 0; i < 15; ++i) {
                cube.rotate_horizontal(2, 6.0f);

                cube.draw();
                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_horizontal_matrix(2);
            cube.st.push_back('1');
        }


        if (Events::jpressed(GLFW_KEY_B)) {
            // Вращение передней грани кубика

            for (int i = 0; i < 15; ++i) {
                cube.rotate_front(6.0f);
                cube.draw();
                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_vertical_matrix_front();
            cube.st.push_back('2');
        }

        if (Events::jpressed(GLFW_KEY_N)) {
            // Вращение нижней грани кубика
            for (int i = 0; i < 15; ++i) {
                cube.rotate_horizontal(0, 6.0f);
                cube.draw();
                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_horizontal_matrix(0);
            cube.st.push_back('3');
        }


        if (Events::jpressed(GLFW_KEY_G)) {
            // Вращение правой грани кубика
            for (int i = 0; i < 15; ++i) {
                cube.rotate_vertical(0, 6.0f);
                cube.draw();
                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_vertical_matrix(0);
            cube.st.push_back('6');
        }
        if (Events::jpressed(GLFW_KEY_J)) {
            // Вращение левой грани кубика
            for (int i = 0; i < 15; ++i) {
                cube.rotate_vertical(2, 6.0f);
                cube.draw();

                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_vertical_matrix(2);
            cube.st.push_back('4');
        }


        if (Events::jpressed(GLFW_KEY_H)) {
            // Вращение задней  грани кубика

            //на деле тут зад вертикальный
            for (int i = 0; i < 15; ++i) {
                cube.rotate_back(6.0f);
                cube.draw();

                Window::swapBuffers();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            cube.swap_vertical_matrix_back();
            cube.st.push_back('5');

        }
        if (Events::jpressed(GLFW_KEY_P)) {
            cube.solve(9.0f);
        }
        if (Events::jpressed(GLFW_KEY_T)) {
            cube.y_swap_cube();
        }
        if (Events::jpressed(GLFW_KEY_R)) {
            cube.y_backwards_swap_cube();
        }
        if (Events::jpressed(GLFW_KEY_K)) {
            cube.x_swap_cube();
        }

        if (Events::jpressed(GLFW_KEY_1)) {
            glm::vec3 coords = cube.find_cube_coords(cube.red_center_id);
            std::cout << "( " << coords.x << ", " << coords.y << ", " << coords.z << " )";
        }

//        if (Events::jpressed(GLFW_KEY_Y)) {
//            std::string filename;
//            std::cout << "Input write file name: ";
//            std::cin >> filename;
//            cube.write_state(filename.c_str());
//        }
//        if (Events::jpressed(GLFW_KEY_U)) {
//            std::string filename;
//            std::cout << "Input load file name: ";
//            std::cin >> filename;
//            cube.load_from_file(filename.c_str());
//        }
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
//    out.close();
    return 0;
}

//горизонтальные
//1 - верхняя
//2 - передняя
//3 - нижняя
//вертикальные
//4 - левая
//5 - задняя
//6 - правая
