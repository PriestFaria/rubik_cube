
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
int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {-1.0f, -1.0f, -1.0f, // triangle 1 : begin
                    -1.0f, -1.0f, 1.0f,
                    -1.0f, 1.0f, 1.0f, // triangle 1 : end
                    1.0f, 1.0f, -1.0f, // triangle 2 : begin
                    -1.0f, -1.0f, -1.0f,
                    -1.0f, 1.0f, -1.0f, // triangle 2 : end
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

float colors_data1[] = {1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,

                       1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,

                       1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,

                       1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,

                       1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,

                       1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 0.0f,

                       };

float colors_data2[] = {0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
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

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
// Accept fragment if it closer to the camera than the former one
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
    size_t colors_size1 = sizeof(colors_data1);
    size_t colors_size2 = sizeof(colors_data2);

    Cube cube1(vertices, colors_data1, vertices_size, colors_size1);
    Cube cube2(vertices, colors_data2, vertices_size, colors_size2);




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
                (void*)0                          // array buffer offset
        );

        // Рисуем первый куб
        glm::mat4 model1 = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f)); // смещаем первый куб влево
        cube1.draw(shader, model1);

        // Рисуем второй куб
        glm::mat4 model2 = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f)); // смещаем второй куб вправо
        cube2.draw(shader, model2) ;

        glBindVertexArray(0);

        Window::swapBuffers();
    }
    return 0;
}


