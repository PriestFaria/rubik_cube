
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Events.h"
#include "Window/Window.h"
#include "graphics/Shader.h"
#include "Camera/Camera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "Cube/Cube.cpp"
#include <vector>

int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {-1.0f, -1.0f, -1.0f,
                    -1.0f, -1.0f, 1.0f,
                    -1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, -1.0f,
                    -1.0f, -1.0f, -1.0f,
                    -1.0f, 1.0f, -1.0f,
                    1.0f, -1.0f, 1.0f,
                    -1.0f, -1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,
                    1.0f, 1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,
                    -1.0f, -1.0f, -1.0f,
                    -1.0f, -1.0f, -1.0f,
                    -1.0f, 1.0f, 1.0f,
                    -1.0f, 1.0f, -1.0f,
                    1.0f, -1.0f, 1.0f,
                    -1.0f, -1.0f, 1.0f,
                    -1.0f, -1.0f, -1.0f,
                    -1.0f, 1.0f, 1.0f,
                    -1.0f, -1.0f, 1.0f,
                    1.0f, -1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f,
                    1.0f, -1.0f, -1.0f,
                    1.0f, 1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,
                    1.0f, 1.0f, 1.0f,
                    1.0f, -1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, -1.0f,
                    -1.0f, 1.0f, -1.0f,
                    1.0f, 1.0f, 1.0f,
                    -1.0f, 1.0f, -1.0f,
                    -1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f,
                    -1.0f, 1.0f, 1.0f,
                    1.0f, -1.0f, 1.0f
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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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

    //colors
//    GLuint colorbuffer;
//    glGenBuffers(1, &colorbuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(colors_data1), colors_data1, GL_STATIC_DRAW);
    size_t vertices_size = sizeof(vertices);


//    Cube cube1(vertices, vertices_size);
//    Cube cube2(vertices, vertices_size);


    std::vector<std::vector<std::vector<Cube> > > cubes(3, std::vector<std::vector<Cube> >(3, std::vector<Cube>(3,
                                                                                                          Cube(vertices,
                                                                                                               vertices_size))));

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

        camX += -Events::dX / Window::height;

        camY += -Events::dY / Window::height;
        camera->rotation = glm::mat4(1.0f);
        camera->rotate(camY, camX, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shader->use();
        shader->uniformMatrix("projview", camera->getProjection() * camera->getView());
        glBindVertexArray(VAO);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                3,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void *) 0                          // array buffer offset
        );

//        // Рисуем первый куб
//        glm::mat4 model1 = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f)); // смещаем первый куб влево
//        cube1.draw(shader, model1);
//
//        // Рисуем второй куб
//        glm::mat4 model2 = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f)); // смещаем второй куб вправо
//        cube2.draw(shader, model2);
//
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                for (int z = 0; z < 3; ++z) {
                    glm::mat4 model_cube = glm::translate(model, glm::vec3((float) (2.0f * x + 0.1f*x), (float) (2.0f * y +  0.1f*y),
                                                                           (float) (2.0f * z +  0.1f*z)));
                    cubes[x][y][z].draw(shader, model_cube);
                }
            }
        }
        glBindVertexArray(0);

        Window::swapBuffers();
    }
    return 0;
}


